from cs50 import get_int

while True:
    height = get_int("What's the height? ")
    if 1 <= height <= 8:
        break
for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for l in range(i + 1):
        print("#", end="")
    print()
