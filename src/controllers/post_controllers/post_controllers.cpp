#include "post_controllers.hpp"
#include "../../psql/consts.hpp"
#include "../../models/post.hpp"

#include <fmt/format.h>

#include <iostream>
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

std::string InsertPost (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone,
                        const std::string& picture, const std::string& description) {
    if (!phone.empty() && !picture.empty() && !description.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kCreatePostSQL, phone, picture, description, 0, 0);
    if (!result.IsEmpty()) return "Successfuly inserted";
    } else {
        return "Not enough data";
    }
    return "Post already exists";
}

std::string SelectPost (const userver::storages::postgres::ClusterPtr& cluster , const std::string& phone) {
    auto result = cluster->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        kGetPostSQL, phone);    
    auto postInfo = result.AsOptionalSingleRow<Post>(userver::storages::postgres::kRowTag);
    if (!postInfo.has_value()) {
      return "Post not found";
    }
    return JsonPost(postInfo.value());
}

std::string SelectListOfPosts (const userver::storages::postgres::ClusterPtr& cluster , const std::string& offset) {
    int position = stoi(offset);
    auto result = cluster->Execute(
        userver::storages::postgres::ClusterHostType::kMaster,
        kGetListOfPostsSQL, position);    
    auto postInfo = result.AsOptionalSingleRow<Post>(userver::storages::postgres::kRowTag);
    if (!postInfo.has_value()) {
      return "Post not found";
    }
    return JsonPost(postInfo.value());
}

std::string RemovePost (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone) {
    if (!phone.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kDeletePostSQL, phone);
    if (!result.IsEmpty()) return "Successfuly deleted";
    } else {
        return "Not enough data";
    }
    return "Post not found";
}

std::string InsertComment (const userver::storages::postgres::ClusterPtr& cluster, const std::string& phone,
                        const std::string& picture, const std::string& description) {
    if (!phone.empty() && !picture.empty() && !description.empty()) {
      auto result = cluster->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          kCreatePostSQL, phone, picture, description, 0, 0);
    if (!result.IsEmpty()) return "Successfuly inserted";
    } else {
        return "Not enough data";
    }
    return "Post already exists";
}

}  // namespace UserverBackendTest