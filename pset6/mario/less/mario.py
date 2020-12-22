from cs50 import get_int

# While infinity, but if height = between 1 and 8: GO
while(True):
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break


for i in range(h):
    # spaces for Right-Aligning
    for s in range(h - i - 1):
        print(" ", end="")
    # hs = hashes
    for hs in range(i + 1):
        print("#", end="")
    print()
