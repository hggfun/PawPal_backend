INSERT INTO dog_owner_app.users(name, phone, password)
VALUES ('alim', '+77777777777', '1234')
ON CONFLICT DO NOTHING;
