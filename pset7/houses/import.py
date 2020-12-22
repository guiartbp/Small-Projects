from sys import exit, argv
import cs50
import csv

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(argv[1]) as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        # name
        rowname = row['name']
        name = rowname.split(' ')

        # houses
        house = row['house']
        # birth
        birth = row['birth']

        if len(name) == 3:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       name[0], name[1], name[2], house, birth)
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       name[0], (None,), name[1], house, birth)
