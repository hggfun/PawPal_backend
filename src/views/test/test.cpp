#include "test.hpp"
#include "../../controllers/profile_controllers/profile_controllers.hpp"

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace UserverBackendTest {

namespace {

class Test final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-test";

  Test(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db")
                .GetCluster()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    
    return "test complete";
    const auto& name = request.GetArg("name");
    const auto& phone = "+79874869380";
    const auto& password = "1234";

    return InsertProfile(pg_cluster_, name, phone, password);
  }

  userver::storages::postgres::ClusterPtr pg_cluster_;

};

}  // namespace

void AppendTest(userver::components::ComponentList& component_list) {
  component_list.Append<Test>();
}

}  // namespace UserverBackendTest
