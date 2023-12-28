INSERT INTO dog_owner_app.users (name, phone, password)
VALUES ($1, $2, $3)
ON CONFLICT DO NOTHING;