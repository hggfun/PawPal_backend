#pragma once

#include <string>
#include <string_view>
#include <ostream>

#include <userver/components/component_list.hpp>

namespace UserverBackendTest {

struct Profile {
    std::string name;
    std::string phone;
    std::string password;
    }; // struct Profile
// TODO
// inline::ostream& operator << (std::ostream &os, const Profile &s) {
//     return (os << Profile.name + " " + Profile.phone);
//     }

}  // namespace UserverBackendTest