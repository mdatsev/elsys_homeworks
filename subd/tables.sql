USE subd;

CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL,
    username VARCHAR(32) UNIQUE NOT NULL,
    number_of_likes_on_own_posts INTEGER NOT NULL DEFAULT 0
);

CREATE TABLE posts (
    id INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL,
    name VARCHAR(255) NOT NULL,
    user_id INTEGER NOT NULL,
    FOREIGN KEY (user_id)
        REFERENCES users (id)
);

CREATE TABLE likes (
    id INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    post_id INTEGER NOT NULL,
    FOREIGN KEY (user_id)
        REFERENCES users (id),
    FOREIGN KEY (post_id)
        REFERENCES posts (id)
);
