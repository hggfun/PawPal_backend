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
