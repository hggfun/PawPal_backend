#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace UserverBackendTest {

std::string InsertProfile (const userver::storages::postgres::ClusterPtr& cluster , const std::string& name, const std::string& phone, const std::string& password);

std::string SelectProfile (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone);

std::string ValidatePhoneNumber (const std::string& phone);

}  // namespace UserverBackendTest