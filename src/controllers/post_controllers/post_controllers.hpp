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

std::string InsertPost (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone,
                        const std::string& picture, const std::string& description);

std::string SelectPost (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone);

std::string SelectListOfPosts (const userver::storages::postgres::ClusterPtr& cluster , const std::string& offset);

std::string RemovePost (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone);

}  // namespace UserverBackendTest