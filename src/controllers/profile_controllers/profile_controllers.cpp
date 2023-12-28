#include "profile_controllers.hpp"
#include "../../psql/consts.hpp"
#include "../../models/profile.hpp"

#include <fmt/format.h>

#include <string>
#include <tuple>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace UserverBackendTest {

std::string InsertProfile (const userver::storages::postgres::ClusterPtr& cluster , const std::string& name, const std::string& phone, const std::string& password) {
    if (!name.empty() && !phone.empty() && !password.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kCreateProfileSQL,
          name, phone, password);
    if (!result.IsEmpty()) return "Successfuly inserted";
    } else {
        return "Not enough data";
    }
    return "Profile already exists";
}

std::string SelectProfile (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone) {
    auto result = cluster->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        kGetProfileSQL, phone);    
    auto profileInfo = result.AsOptionalSingleRow<Profile>(userver::storages::postgres::kRowTag);
    if (!profileInfo.has_value()) {
      return "User not found";
    }
    return profileInfo.value().name + " " + profileInfo.value().phone;
}

std::string ValidatePhoneNumber (const std::string& phone) {
    auto phone_copy = phone;
  if (phone_copy[0] == '8' || phone_copy[0] == '7' ) {
    phone_copy = "+7" + phone_copy.substr(1);
  }
  if (phone_copy.length() != 12) {
    return "";

  } else {
    if (phone_copy[1] != '7') {
      return "";

    } else {
      for (int position = 2; position < 12; ++position) {
       if (phone_copy[position] < '0' || phone_copy[position] > '9') return "";
      }
    }
  }
  return phone_copy;
}

}  // namespace UserverBackendTest