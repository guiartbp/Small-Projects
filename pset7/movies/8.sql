SELECT name FROM people WHERE id IN
(SELECT people.id FROM people JOIN stars ON people.id = stars.person_id WHERE stars.movie_id IN
(SELECT stars.movie_id FROM stars JOIN movies ON stars.movie_id = movies.id WHERE movies.title LIKE "Toy Story"));