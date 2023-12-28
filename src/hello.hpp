#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

namespace UserverBackendTest {

enum class UserType { kNewbie, kKnown };

std::string SayHelloTo(std::string_view name, UserType type);

void AppendHello(userver::components::ComponentList& component_list);

}  // namespace UserverBackendTest
