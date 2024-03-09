#include "adv_controllers.hpp"
#include "../../psql/consts.hpp"
#include "../../models/advertisement.hpp"

#include <fmt/format.h>

#include <string>
#include <tuple>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>
#include <ctime>

namespace UserverBackendTest {

std::string InsertAdvertisement (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone, int place,
                                const std::time_t& time, const std::string& picture, const std::string& description) {
    if (!phone.empty() && /*!place.empty()  && !time.empty() &&*/ !picture.empty() && !description.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kCreateAdvertisementSQL, phone, place, time, picture, description);
    if (!result.IsEmpty()) return "Successfuly inserted";
    } else {
        return "Not enough data";
    }
    return "Advertisement already exists";
}

std::string SelectAdvertisement (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone) {
    auto result = cluster->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        kGetAdvertisementSQL, phone);    
    auto advertisementInfo = result.AsOptionalSingleRow<Advertisement>(userver::storages::postgres::kRowTag);
    if (!advertisementInfo.has_value()) {
      return "Advertisement not found";
    }
    return advertisementInfo.value().phone + " " + advertisementInfo.value().picture + " " + advertisementInfo.value().description;
}

std::string RemoveAdvertisement (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone) {
    if (!phone.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kDeleteAdvertisementSQL, phone);
    if (!result.IsEmpty()) return "Successfuly deleted";
    } else {
        return "Not enough data";
    }
    return "Advertisement not found";
}

}  // namespace UserverBackendTest