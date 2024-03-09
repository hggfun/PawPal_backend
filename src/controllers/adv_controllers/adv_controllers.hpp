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

std::string InsertAdvertisement (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone, int place,
                                const std::time_t& time, const std::string& picture, const std::string& description);

std::string SelectAdvertisement (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone);

std::string RemoveAdvertisement (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone);

}  // namespace UserverBackendTest