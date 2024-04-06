#include "view.hpp"
#include "../../../../controllers/post_controllers/post_controllers.hpp"

#include <fmt/format.h>
#include <ctime>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace UserverBackendTest {

namespace {

  class CreatePost final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-create-post";

  CreatePost(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db")
                .GetCluster()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    const auto& phone = request.GetArg("phone");
    const auto& picture = request.GetArg("picture");
    const auto& text = request.GetArg("text");
    return InsertPost(pg_cluster_, phone, picture, text);
  }
  
  userver::storages::postgres::ClusterPtr pg_cluster_;
};
}

void AppendCreatePost (userver::components::ComponentList& component_list) {
  component_list.Append<CreatePost>();
}

}  // namespace UserverBackendTest userver::storages::postgres::ClusterPtr