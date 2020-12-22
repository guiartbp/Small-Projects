from cs50 import get_float

# Value of change
while(True):
    dollar = get_float("Change owed: ")
    if dollar > 0:
        break

# Transform dollar -> cents
cents = round(dollar * 100)
# Coins available
coins = [25, 10, 5, 1]

change = 0
coin = 0

# if If you can still switch to the bigger one, switch
while(cents > change):
    if change + coins[0] <= cents:
        change += coins[0]
    elif change + coins[1] <= cents:
        change += coins[1]
    elif change + coins[2] <= cents:
        change += coins[2]
    else:
        change += coins[3]
    coin += 1

print(coin)
