#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "hello.hpp"
#include "views/test/test.hpp"
#include "views/profile/create_profile/post/view.hpp"
#include "views/profile/get_profile/post/view.hpp"
#include "views/profile/delete_profile/post/view.hpp"

#include "views/advertisement/create_advertisement/post/view.hpp"
#include "views/advertisement/read_advertisement/post/view.hpp"
#include "views/advertisement/delete_advertisement/post/view.hpp"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::server::handlers::TestsControl>();

  UserverBackendTest::AppendHello(component_list);
  UserverBackendTest::AppendTest(component_list);

  UserverBackendTest::AppendCreateProfile(component_list);
  UserverBackendTest::AppendGetProfile(component_list);
  UserverBackendTest::AppendDeleteProfile(component_list);

  UserverBackendTest::AppendCreateAdvertisement(component_list);
  UserverBackendTest::AppendGetAdvertisement(component_list);
  UserverBackendTest::AppendDeleteAdvertisement(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
