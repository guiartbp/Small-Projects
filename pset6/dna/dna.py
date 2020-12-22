from sys import exit, argv
from collections import Counter
import csv

if len(argv) != 3:
    print("Usage: python dna.py file.csv file_text.txt")
    exit(1)
filecsv = argv[1]
filetxt = argv[2]
acgt = []
str_txt = "str"

# Open CSV File
with open(filecsv, 'r') as csv_file:
    csvreader = csv.reader(csv_file)
    # Header of STR's
    for strs in csvreader:
        acgt = strs[1:]
        break

# Open TXT File
with open(filetxt, 'r') as str_file:
    # String of STR File
    for line in str_file:
        str_txt = line

# Find if not found = return -1 if found = position
value_found = []
# F find in acgt
for f in range(len(acgt)):

    position_find = 0
    position_diff = 0
    count = 0
    diff = len(acgt[f])
    # maxcounter is the largest repetition of STR in STR_FILE
    maxcounter = 0
    # if position_find = -1 is because there is no more ACGT to search
    while position_find > -1:
        # starts in position_find +1 because in STR it repeats from the found
        position_find = str_txt.find(acgt[f], position_find)
        # no found
        if position_find == -1:
            break
        # first found
        elif position_find != -1 and position_diff == 0:
            count += 1
            position_diff = position_find
            maxcounter = count
        # 2, 3, 4, ... found
        elif (position_diff + diff) == position_find:
            count += 1
            position_diff = position_find
            if maxcounter < count:
                maxcounter = count
        # if you have a longer pause than found position plus the difference
        elif (position_diff + diff) != position_find and position_find != -1:
            count = 1
            position_diff = position_find
            if maxcounter < count:
                maxcounter = count
        position_find += 1
    # add maxcounter in list for compare after
    value_found.append(maxcounter)
# transform items int(maxcounter) in str(maxcounter)
value_found = list(map(str, value_found))
# open CSV file again for compare Peoples and value_found
with open(filecsv, newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    next(spamreader)
    for row in spamreader:
        # if values of row equals value_found = print person and exit(sucess)
        if row[1:] == value_found:
            print(f"{row[0]}")
            exit(1)
# if not found anybody == No found
print("No match")