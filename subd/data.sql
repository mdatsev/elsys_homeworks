USE subd;

INSERT INTO users(id, username) VALUES (1,'marti');
INSERT INTO users(username) VALUES ('marti2');
INSERT INTO users(username) VALUES ('marti3');

INSERT INTO posts(id, name, user_id) VALUES (1, 'post11', 1);
INSERT INTO posts(name, user_id) VALUES ('post12', 1);
INSERT INTO posts(name, user_id) VALUES ('post21', 2);
INSERT INTO posts(name, user_id) VALUES ('post22', 2);
INSERT INTO posts(name, user_id) VALUES ('post31', 3);
INSERT INTO posts(name, user_id) VALUES ('post32', 3);

INSERT INTO likes(id, user_id, post_id) VALUES (1, 1, 1);
INSERT INTO likes(user_id, post_id) VALUES (1, 2);
INSERT INTO likes(user_id, post_id) VALUES (1, 3);
INSERT INTO likes(user_id, post_id) VALUES (1, 4);
INSERT INTO likes(user_id, post_id) VALUES (1, 5);
INSERT INTO likes(user_id, post_id) VALUES (1, 6);

INSERT INTO likes(user_id, post_id) VALUES (1, 1);
INSERT INTO likes(user_id, post_id) VALUES (2, 1);
INSERT INTO likes(user_id, post_id) VALUES (3, 1);
INSERT INTO likes(user_id, post_id) VALUES (1, 3);
INSERT INTO likes(user_id, post_id) VALUES (2, 3);
INSERT INTO likes(user_id, post_id) VALUES (3, 3);
