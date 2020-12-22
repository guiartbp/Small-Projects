SELECT DISTINCT title FROM movies JOIN stars ON movies.id = stars.movie_id WHERE id IN
(SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE people.name LIKE "Johnny Depp"
INTERSECT
SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE people.name LIKE "Helena Bonham Carter");