#pragma once

#include <userver/utest/using_namespace_userver.hpp>
 
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

namespace UserverBackendTest {

const storages::postgres::Query kCreateProfileSQL{
    "INSERT INTO dog_owner_app.users (name, phone, password)"
    "VALUES ($1, $2, $3)"
    "ON CONFLICT DO NOTHING "
    "RETURNING 1;",
    storages::postgres::Query::Name{"create_profile"},
};

const storages::postgres::Query kGetProfileSQL{
    "SELECT name, phone, password FROM dog_owner_app.users "
    "WHERE phone = $1;",
    storages::postgres::Query::Name{"get_profile"},
};

const storages::postgres::Query kDeleteProfileSQL{
    "DELETE FROM dog_owner_app.users "
    "WHERE phone = $1 AND password = $2 "
    "RETURNING phone;",
    storages::postgres::Query::Name{"delete_profile"},
};

const storages::postgres::Query kCreateAdvertisementSQL{
    "INSERT INTO dog_owner_app.advertisements (phone, place, time, picture, description) "
    "VALUES ($1, $2, to_timestamp($3), $4, $5)"
    "ON CONFLICT DO NOTHING "
    "RETURNING 1;",
    storages::postgres::Query::Name{"create_advertisement"},
};

const storages::postgres::Query kGetAdvertisementSQL{
    "SELECT * FROM dog_owner_app.advertisements "
    "WHERE phone = $1;",
    storages::postgres::Query::Name{"get_advertisement"},
};

const storages::postgres::Query kDeleteAdvertisementSQL{
    "DELETE FROM dog_owner_app.advertisements "
    "WHERE phone = $1 "
    "RETURNING phone;",
    storages::postgres::Query::Name{"delete_advertisement"},
};

const storages::postgres::Query kCreatePostSQL{
    "INSERT INTO dog_owner_app.posts (phone, picture, text, likes, comments) "
    "VALUES ($1, $2, $3, $4, $5)"
    "ON CONFLICT DO NOTHING "
    "RETURNING 1;",
    storages::postgres::Query::Name{"create_post"},
};

const storages::postgres::Query kGetPostSQL{
    "SELECT * FROM dog_owner_app.posts "
    "WHERE phone = $1;",
    storages::postgres::Query::Name{"get_post"},
};

const storages::postgres::Query kGetListOfPostsSQL{
    "SELECT * FROM dog_owner_app.posts "
    "LIMIT 1 OFFSET $1;",
    storages::postgres::Query::Name{"get_post"},
};

const storages::postgres::Query kDeletePostSQL{
    "DELETE FROM dog_owner_app.posts "
    "WHERE phone = $1 "
    "RETURNING phone;",
    storages::postgres::Query::Name{"delete_post"},
};

const storages::postgres::Query kCreateCommentSQL{
    "WITH insert AS ( "
	"INSERT INTO dog_owner_app.comments (phone, post_id, text) "
	"SELECT $1, $2, $3 "
	"WHERE EXISTS ( "
		"SELECT 1 FROM dog_owner_app.posts "
		"WHERE phone = $2) "
	"ON CONFLICT DO NOTHING "
	"RETURNING 1 "
    ") "
    " "
    "UPDATE dog_owner_app.posts "
    "SET comments = comments + 1 "
    "WHERE EXISTS (SELECT 1 FROM insert) AND phone = $2 "
    "RETURNING comments; ",
    storages::postgres::Query::Name{"create_comment"},
};

const storages::postgres::Query kGetCommentSQL{
    "SELECT * FROM dog_owner_app.comments "
    "WHERE phone = $1 AND post_id = $2;",
    storages::postgres::Query::Name{"get_comment"},
};

const storages::postgres::Query kCreateLikeSQL{
    "WITH insert AS ( "
	"INSERT INTO dog_owner_app.likes (phone, post_id) "
	"SELECT $1, $2 "
	"WHERE EXISTS ( "
		"SELECT 1 FROM dog_owner_app.posts "
		"WHERE phone = $2) "
	"ON CONFLICT DO NOTHING "
	"RETURNING 1 "
    ") "
    " "
    "UPDATE dog_owner_app.posts "
    "SET likes = likes + 1 "
    "WHERE EXISTS (SELECT 1 FROM insert) AND phone = $2 "
    "RETURNING likes; ",
    storages::postgres::Query::Name{"create_like"},
};

const storages::postgres::Query kGetLikeSQL{
    "SELECT * FROM dog_owner_app.likes "
    "WHERE phone = $1 AND post_id = $2;",
    storages::postgres::Query::Name{"get_like"},
};

}  // namespace UserverBackendTest