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
    int price;
    std::time_t time;
    std::string picture;
    std::string description;
    }; // struct Advertisement

    std::string JsonPost(const Advertisement& advertisement) {
        return "{\n\t\"phone\": \"" + advertisement.phone + "\",\n\t\"price\": \"" + std::to_string(advertisement.price) + "\",\n\t\"place\": \"" + std::to_string(advertisement.place) + "\",\n\t\"description\": \"" + advertisement.description + "\"\n}";
    }

// TODO
// inline::ostream& operator << (std::ostream &os, const Profile &s) {
//     return (os << Profile.name + " " + Profile.phone);
//     }

}  // namespace UserverBackendTest