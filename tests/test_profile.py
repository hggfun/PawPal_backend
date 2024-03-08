import pytest

from testsuite.databases import pgsql


# Start the tests via `make test-debug` or `make test-release`

@pytest.mark.parametrize("name, phone, password, expected", [
    ('userver', '+77777777777', '1234', 'Successfuly inserted'),
    ('userver', '+77777777777', '', 'Not enough data'),
    ('userver', '777777777', '1234', 'Incorrect phone number')])
async def test_create_profile(service_client, name, phone, password, expected):
    response = await service_client.post('/create_profile', params={'name': name, 'phone': phone, 'password': password})
    assert response.status == 200
    assert response.text == expected

async def test_duplicate_profile(service_client):
    response = await service_client.post('/create_profile', params={'name': 'userver', 'phone': '+77777777777', 'password': '1234'})
    assert response.status == 200
    assert response.text == 'Successfuly inserted'
    
    response = await service_client.post('/create_profile', params={'name': 'userver', 'phone': '+77777777777', 'password': '1234'})
    assert response.status == 200
    assert response.text == 'Profile already exists'    

@pytest.mark.pgsql('db_1', files=['initial_profile.sql'])
async def test_get_profile(service_client):
    response = await service_client.post('/get_profile', params={'phone': '+77777777777'})
    assert response.status == 200
    assert response.text == 'alim +77777777777'

async def test_get_no_data(service_client):
    response = await service_client.post(
        '/get_profile',
        params={'phone': '+77777777777'},
    )
    assert response.status == 200
    assert response.text == 'User not found'

@pytest.mark.parametrize("phone, password, expected", [
    ('+77777777777', '1234', 'Successfuly deleted'),
    ('+77777777777', '', 'Not enough data'),
    ('+77777777777', '1111', 'Profile not found')])
@pytest.mark.pgsql('db_1', files=['initial_profile.sql'])  
async def test_delete_profile(service_client, phone, password, expected):
    response = await service_client.post(
        '/delete_profile',
        params={'phone': phone, 'password': password},
    )
    assert response.status == 200
    assert response.text == expected