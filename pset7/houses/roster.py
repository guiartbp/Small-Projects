from sys import exit, argv
import cs50

# Correct form of initialize the program
if len(argv) != 2:
    print("Usage: python roster.py [name house]")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

# Count number of houses for loop
counter = db.execute("SELECT COUNT(*) as COUNT FROM students  WHERE house = ?", (argv[1]))
count = int(counter[0]['COUNT'])

for i in range(count):

    # Name
    first = db.execute("SELECT first as FIRST FROM students WHERE house = ? ORDER BY last, first", (argv[1]))
    middle = db.execute("SELECT middle as MIDDLE FROM students WHERE house = ? ORDER BY last, first", (argv[1]))
    last = db.execute("SELECT last as LAST FROM students WHERE house = ? ORDER BY last, first", (argv[1]))

    # Birth
    birth = db.execute("SELECT birth as BIRTH FROM students WHERE house = ? ORDER BY last, first", (argv[1]))

    # If middle name exist
    if middle[i]['MIDDLE'] != None:
        print(f"{first[i]['FIRST']} {middle[i]['MIDDLE']} {last[i]['LAST']}, born {birth[i]['BIRTH']}")
    else:
        print(f"{first[i]['FIRST']} {last[i]['LAST']}, born {birth[i]['BIRTH']}")

