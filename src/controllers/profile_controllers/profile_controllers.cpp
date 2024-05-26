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
#include <userver/storages/postgres/io/buffer_io.hpp>
#include <userver/storages/postgres/io/buffer_io_base.hpp>
#include <userver/storages/postgres/io/type_mapping.hpp>
#include <openssl/sha.h>



namespace UserverBackendTest {

boost::uuids::uuid GetNameUUID(const std::string& name) {
  auto result = utils::generators::GenerateBoostUuidV7(name);
  return name;
}

boost::uuids::uuid GetPhoneUUID(const std::string& phone) {
  auto result = utils::generators::GenerateBoostUuid(phone);
  return name;
}

std::string generateHashedPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    std::string hashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char hex[3];
        sprintf(hex, "%02x", hash[i]);
        hashedPassword += hex;
    }

    return hashedPassword;
}

std::string InsertProfile (const userver::storages::postgres::ClusterPtr& cluster , const std::string& name, const std::string& phone, const std::string& password) {
    if (!name.empty() && !phone.empty() && !password.empty()) {
      std::string safeName = std::static_cast<std::string>(GetNameUUID(name));
      std::string safePhone = std::static_cast<std::string>(GetNameUUID(phone));
      std::string safePassword = generateHashedPassword(password);
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kCreateProfileSQL, safeName, safePhone, safePassword);
    if (!result.IsEmpty()) return "Successfuly inserted";
    } else {
        return "Not enough data";
    }
    return "Profile already exists";
}

std::string SelectProfile (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone) {
    std::string safePhone = std::static_cast<std::string>(GetNameUUID(phone));
    auto result = cluster->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        kGetProfileSQL, safePhone);    
    auto profileInfo = result.AsOptionalSingleRow<Profile>(userver::storages::postgres::kRowTag);
    if (!profileInfo.has_value()) {
      return "User not found";
    }
    return profileInfo.value().name + " " + profileInfo.value().phone;
}

std::string RemoveProfile (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone, const std::string& password) {
      std::string safePhone = std::static_cast<std::string>(GetNameUUID(phone));
      std::string safePassword = generateHashedPassword(password);
    if (!phone.empty() && !password.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kDeleteProfileSQL, safePhone, safePassword);
    if (!result.IsEmpty()) return "Successfuly deleted";
    } else {
        return "Not enough data";
    }
    return "Profile not found";
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

bool checkForSQLInjection(const std::string& input) {
    std::vector<std::string> forbiddenExpressions = {"DROP", "DELETE", "UPDATE", "INSERT", "TRUNCATE", "--"};

    std::string uppercaseInput = input;
    std::transform(uppercaseInput.begin(), uppercaseInput.end(), uppercaseInput.begin(), ::toupper);

    for (const auto& expression : forbiddenExpressions) {
        if (uppercaseInput.find(expression) != std::string::npos) {
            return true;
        }
    }

    return false;
}

}  // namespace UserverBackendTest