from cs50 import get_int

# Receive the card number
while(True):
    cardnumber = get_int("Number: ")
    if cardnumber > 0:
        break

# Reverse number
card = str(cardnumber)
reversenumber = str(cardnumber)[::-1]
lenreverse = len(reversenumber)

multsum = 0  # Sum of multiplied numbers
sumnum = 0  # Sum of the numbers not multiplied


# Starting with the number’s second-to-last digit
for i in range(1, lenreverse, 2):
    num = int(reversenumber[i]) * 2

    # Add those products’ digits together
    if num == 10:
        num = 1 + 0
    elif num == 12:
        num = 1 + 2
    elif num == 14:
        num = 1 + 4
    elif num == 16:
        num = 1 + 6
    elif num == 18:
        num = 1 + 8

    multsum += num

# The sum of the digits that weren’t multiplied by 2
for j in range(0, lenreverse, 2):
    num = int(reversenumber[j])
    sumnum += num

total = multsum + sumnum

if (total % 10) == 0:
    # VISA conditions
    if (lenreverse == 13 or lenreverse == 16) and (card[0] == "4"):
        print("VISA")
    # AMEX conditions
    elif (lenreverse == 15) and (card[0] == "3") and (card[1] == "4" or card[1] == "7"):
        print("AMEX")
     # MASTERCARD conditions
    elif (lenreverse == 16) and (card[0] == "5") and (card[1] == "1" or card[1] == "2" or card[1] == "3" or card[1] == "4" or card[1] == "5"):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
