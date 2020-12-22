from cs50 import get_string
import string

while(True):
    text = get_string("Text: ")
    if len(text) > 0:
        break

# Lenght of Letters
count_punctuation = 0
for p in range(len(text)):
    if (text[p] in string.punctuation):
        count_punctuation += 1

letters = len(text) - text.count(" ") - count_punctuation

# Lenght of sentences
sentences = 0
for p in range(len(text)):
    if (text[p] == ".") or (text[p] == "!") or (text[p] == "?"):
        sentences += 1

# Lenght of words
words = len(text.split())

# Index Coleman-Liau
L = letters / words * 100
S = sentences / words * 100
CLI = (0.0588 * L) - (0.296 * S) - 15.8
CLI = round(CLI)

if CLI <= 1:
    print("Before Grade 1")
elif CLI >= 16:
    print("Grade 16+")
else:
    print(f"Grade {CLI}")