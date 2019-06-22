USE subd;

SELECT 
    u.username AS 'User name',
    p.name AS 'Post name'
FROM
    posts p
        LEFT JOIN
    users u ON p.user_id = u.id;
    
SELECT 
    u.username AS 'User name',
    COUNT(*) as 'number of likes'
FROM
    users u
        LEFT JOIN
    likes l ON l.user_id = u.id
    GROUP BY u.id;
    
SELECT 
    u.username AS 'User username (който е харесал)',
    u2.username as 'User username (който е харесван)'
FROM
    likes l 
        LEFT JOIN
    users u ON l.user_id = u.id
    LEFT JOIN
    posts p ON l.post_id = p.id
    LEFT JOIN
    users u2 ON p.user_id = u2.id;
    
SELECT 
    p.name AS 'User name',
    COUNT(*) as 'number of likes'
FROM 
	posts p
    LEFT JOIN likes l on l.post_id = p.id
    group by p.id;
    