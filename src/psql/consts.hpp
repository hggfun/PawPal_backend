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

}  // namespace UserverBackendTest