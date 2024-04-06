#include "view.hpp"
#include "../../../../controllers/post_controllers/post_controllers.hpp"

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace UserverBackendTest {

namespace {

  class DeletePost final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-delete-post";

  DeletePost(const userver::components::ComponentConfig& config,
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
    return RemovePost(pg_cluster_, phone);
  }
  
  userver::storages::postgres::ClusterPtr pg_cluster_;
};
}

void AppendDeletePost (userver::components::ComponentList& component_list) {
  component_list.Append<DeletePost>();
}

}  // namespace UserverBackendTest userver::storages::postgres::ClusterPtr