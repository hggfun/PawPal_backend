import pytest

from testsuite.databases import pgsql


# Start the tests via `make test-debug` or `make test-release`

async def test_test(service_client):
    response = await service_client.post(
        '/test',
        params={'name': 'o, curva!'},
    )
    assert response.status == 200
    assert response.text == 'test complete'

async def test_create_profile(service_client):
    response = await service_client.post(
        '/create_profile',
        params={'name': 'userver', 'phone': '+79874869380', 'password': '1234'},
    )
    assert response.status == 200
    assert response.text == 'Successfuly inserted'


async def test_create_incorrect_data(service_client):
    response = await service_client.post('/create_profile', params={'name': 'userver', 'phone': '+79874869380', 'password': '1234'})
    assert response.status == 200
    assert response.text == 'Successfuly inserted'
    
    response = await service_client.post('/create_profile', params={'name': 'userver', 'phone': '+79874869380', 'password': '1234'})
    assert response.status == 200
    assert response.text == 'Profile already exists'

    response = await service_client.post('/create_profile', params={'name': 'userver', 'phone': '+79874869380'})
    assert response.status == 200
    assert response.text == 'Not enough data'

    response = await service_client.post('/create_profile', params={'name': 'userver', 'phone': '874869380', 'password': '1234'})
    assert response.status == 200
    assert response.text == 'Incorrect phone number'
    

@pytest.mark.pgsql('db_1', files=['initial_profile.sql'])
async def test_get_profile(service_client):
    response = await service_client.post('/get_profile', params={'phone': '+77777777777'})
    assert response.status == 200
    assert response.text == 'alim +77777777777'

async def test_get_no_data(service_client):
    response = await service_client.post(
        '/get_profile',
        params={'phone': '+79874869380'},
    )
    assert response.status == 200
    assert response.text == 'User not found'