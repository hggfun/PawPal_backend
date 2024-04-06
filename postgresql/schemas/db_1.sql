DROP SCHEMA IF EXISTS hello_schema CASCADE;

CREATE SCHEMA IF NOT EXISTS hello_schema;

CREATE TABLE IF NOT EXISTS hello_schema.users (
    name TEXT PRIMARY KEY,
    count INTEGER DEFAULT(1)
);

DROP SCHEMA IF EXISTS dog_owner_app CASCADE;

CREATE SCHEMA IF NOT EXISTS dog_owner_app;

CREATE TABLE IF NOT EXISTS dog_owner_app.users (
    phone TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    password TEXT NOT NULL,
    rating NUMERIC(2, 1)
);

CREATE TABLE IF NOT EXISTS dog_owner_app.advertisements (
    phone TEXT PRIMARY KEY,
    place INTEGER NOT NULL,
    time TIMESTAMP NOT NULL,
    picture TEXT NOT NULL,
    description TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS dog_owner_app.posts (
    phone TEXT PRIMARY KEY,
    picture TEXT NOT NULL,
    text TEXT NOT NULL,
    likes INTEGER,
    comments INTEGER
);

CREATE TABLE IF NOT EXISTS dog_owner_app.comments (
    phone TEXT NOT NULL,
    post_id TEXT NOT NULL,
    text TEXT NOT NULL,
    UNIQUE (phone, post_id)
);

CREATE TABLE IF NOT EXISTS dog_owner_app.likes (
    phone TEXT NOT NULL,
    post_id TEXT NOT NULL,
    UNIQUE (phone, post_id)
);
