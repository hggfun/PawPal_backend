INSERT INTO dog_owner_app.advertisements (phone, place, time, picture, description)
VALUES ('+77777777777', 1, to_timestamp(1000000000), 'picture', 'description')
ON CONFLICT DO NOTHING;
