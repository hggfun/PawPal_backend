#include "view.hpp"
#include "../../../../controllers/profile_controllers/profile_controllers.hpp"

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace UserverBackendTest {

namespace {

  class CreateProfile final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-create-profile";

  CreateProfile(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db")
                .GetCluster()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    const auto& name = request.GetArg("name");
    const auto& phone = ValidatePhoneNumber(request.GetArg("phone")); //returns empty string for invalid number
    if (phone.empty()) return "Incorrect phone number";

    const auto& password = request.GetArg("password");
    return InsertProfile(pg_cluster_, name, phone, password);
  }
  
  userver::storages::postgres::ClusterPtr pg_cluster_;
};
}

void AppendCreateProfile (userver::components::ComponentList& component_list) {
  component_list.Append<CreateProfile>();
}

}  // namespace UserverBackendTest userver::storages::postgres::ClusterPtr