#pragma once

#include <userver/utest/using_namespace_userver.hpp>
 
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace UserverBackendTest {

const storages::postgres::Query kCreateProfileSQL{
    "INSERT INTO dog_owner_app.users (name, phone, password)"
    "VALUES ($1, $2, $3)"
    "ON CONFLICT DO NOTHING "
    "RETURNING 1;",
    storages::postgres::Query::Name{"create_profile"},
};

const storages::postgres::Query kGetProfileSQL{
    "SELECT name, phone, password FROM dog_owner_app.users "
    "WHERE phone = $1;",
    storages::postgres::Query::Name{"get_profile"},
};

const storages::postgres::Query kDeleteProfileSQL{
    "DELETE FROM dog_owner_app.users "
    "WHERE phone = $1 AND password = $2 "
    "RETURNING phone;",
    storages::postgres::Query::Name{"delete_profile"},
};

const storages::postgres::Query kCreateAdvertisementSQL{
    "INSERT INTO dog_owner_app.advertisements (phone, place, time, picture, description) "
    "VALUES ($1, $2, to_timestamp($3), $4, $5)"
    "ON CONFLICT DO NOTHING "
    "RETURNING 1;",
    storages::postgres::Query::Name{"create_advertisement"},
};

const storages::postgres::Query kGetAdvertisementSQL{
    "SELECT * FROM dog_owner_app.advertisements "
    "WHERE phone = $1;",
    storages::postgres::Query::Name{"get_advertisement"},
};

const storages::postgres::Query kDeleteAdvertisementSQL{
    "DELETE FROM dog_owner_app.advertisements "
    "WHERE phone = $1 "
    "RETURNING phone;",
    storages::postgres::Query::Name{"delete_profile"},
};

}  // namespace UserverBackendTest