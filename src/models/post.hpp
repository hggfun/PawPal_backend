#pragma once

#include <string>
#include <string_view>
#include <ostream>
#include <ctime>

#include <userver/components/component_list.hpp>

namespace UserverBackendTest {

struct Post {
    std::string phone;
    std::string picture;
    std::string description;
    int likes;
    int comments;
    }; // struct Advertisement

    std::string JsonPost(const Post& post) {
        return "{\n\t\"phone\": \"" + post.phone + "\",\n\t\"picture\": \"" + post.picture + "\",\n\t\"description\": \"" + post.description + "\"\n}";
    }
// TODO
// inline::ostream& operator << (std::ostream &os, const Profile &s) {
//     return (os << Profile.name + " " + Profile.phone);
//     }

}  // namespace UserverBackendTest