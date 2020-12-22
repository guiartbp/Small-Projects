SELECT DISTINCT people.name FROM people JOIN stars ON people.id = stars.person_id WHERE people.name IS NOT 'Kevin Bacon' and stars.movie_id IN
(SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE people.name LIKE "Kevin Bacon" AND people.birth = 1958);