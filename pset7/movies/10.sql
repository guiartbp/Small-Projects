SELECT  name FROM people WHERE id IN
(SELECT people.id FROM people JOIN directors ON people.id = directors.person_id WHERE directors.movie_id IN
(SELECT directors.movie_id FROM directors JOIN ratings ON directors.movie_id = ratings.movie_id WHERE ratings.rating >= 9.0));