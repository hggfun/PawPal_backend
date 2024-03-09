#pragma once

#include <string>
#include <string_view>
#include <ostream>
#include <ctime>

#include <userver/components/component_list.hpp>

namespace UserverBackendTest {

struct Advertisement {
    std::string phone;
    int place;
    std::time_t time;
    std::string picture;
    std::string description;
    }; // struct Advertisement
// TODO
// inline::ostream& operator << (std::ostream &os, const Profile &s) {
//     return (os << Profile.name + " " + Profile.phone);
//     }

}  // namespace UserverBackendTest