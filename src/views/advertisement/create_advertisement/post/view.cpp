#include "view.hpp"
#include "../../../../controllers/adv_controllers/adv_controllers.hpp"
#include "../../../../controllers/profile_controllers/profile_controllers.hpp"

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

  class CreateAdvertisement final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-create-advertisement";

  CreateAdvertisement(const userver::components::ComponentConfig& config,
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
    phone = getPhoneUUID(phone);
    return InsertAdvertisement(pg_cluster_, phone, 1, std::time(0), "picture", "description");
  }
  
  userver::storages::postgres::ClusterPtr pg_cluster_;
};
}

void AppendCreateAdvertisement (userver::components::ComponentList& component_list) {
  component_list.Append<CreateAdvertisement>();
}

}  // namespace UserverBackendTest userver::storages::postgres::ClusterPtr