import pytest

from testsuite.databases import pgsql


# Start the tests via `make test-debug` or `make test-release`

@pytest.mark.parametrize("phone, expected", [
    ('+77777777777', 'Successfuly inserted'),
    ('', 'Not enough data')])
async def test_create_advertisement(service_client, phone, expected):
    response = await service_client.post('/create_advertisement', params={'phone': phone})
    assert response.status == 200
    assert response.text == expected

async def test_duplicate_advertisement(service_client):
    response = await service_client.post('/create_advertisement', params={'phone': '+77777777777'})
    assert response.status == 200
    assert response.text == 'Successfuly inserted'
    
    response = await service_client.post('/create_advertisement', params={'phone': '+77777777777'})
    assert response.status == 200
    assert response.text == 'Advertisement already exists'    

@pytest.mark.parametrize("phone, expected", [
    ('+77777777777', '+77777777777 picture description'),
    ('+78777777777', 'Advertisement not found')])
@pytest.mark.pgsql('db_1', files=['initial_advertisement.sql'])
async def test_get_advertisement(service_client, phone, expected):
    response = await service_client.post('/get_advertisement', params={'phone': phone})
    assert response.status == 200
    assert response.text == expected

@pytest.mark.parametrize("phone, expected", [
    ('+77777777777', 'Successfuly deleted'),
    ('', 'Not enough data'),
    ('+78777777777', 'Advertisement not found')])
@pytest.mark.pgsql('db_1', files=['initial_advertisement.sql'])  
async def test_delete_advertisement(service_client, phone, expected):
    response = await service_client.post(
        '/delete_advertisement',
        params={'phone': phone},
    )
    assert response.status == 200
    assert response.text == expected