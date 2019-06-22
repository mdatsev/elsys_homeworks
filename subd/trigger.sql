USE subd;

delimiter //
CREATE TRIGGER del AFTER DELETE ON likes
       FOR EACH ROW
       BEGIN
			UPDATE likes v
			LEFT JOIN posts p ON OLD.post_id = p.id
			LEFT JOIN users u ON p.user_id = p.id 
            SET u.number_of_likes_on_own_posts=u.number_of_likes_on_own_posts-1;
       END;//
delimiter ;

delimiter //
CREATE TRIGGER ins AFTER INSERT ON likes
       FOR EACH ROW
       BEGIN
			UPDATE likes v
			LEFT JOIN posts p ON NEW.post_id = p.id
			LEFT JOIN users u ON p.user_id = p.id 
			SET u.number_of_likes_on_own_posts=u.number_of_likes_on_own_posts+1;
       END;//
delimiter ;

delimiter //
CREATE TRIGGER upd AFTER UPDATE ON likes
       FOR EACH ROW
       BEGIN
			UPDATE likes v
			LEFT JOIN posts p ON OLD.post_id = p.id
			LEFT JOIN users u ON p.user_id = p.id 
            SET u.number_of_likes_on_own_posts=u.number_of_likes_on_own_posts-1;
			UPDATE likes v
			LEFT JOIN posts p ON NEW.post_id = p.id
			LEFT JOIN users u ON p.user_id = p.id 
			SET u.number_of_likes_on_own_posts=u.number_of_likes_on_own_posts+1;
       END;//
delimiter ;
