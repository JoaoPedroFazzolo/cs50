SELECT title
FROM movies
    JOIN ratings on movies.id = ratings.movie_id
    JOIN stars on movies.id = stars.movie_id
    JOIN people on stars.person_id = people.id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;
