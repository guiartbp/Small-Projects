from cs50 import get_int

# While infinity, but if height = between 1 and 8: GO
while(True):
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break

for i in range(h):
    # Cr = Column left
    for cl in range(h):
        if cl < (h - i - 1):
            print(" ", end="")
        else:
            print("#", end="")

    # space between the two columns
    print("  ", end="")

    # Cr = Column Right
    for p in range(i + 1):
        print("#", end="")
    print()