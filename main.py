"""
str = \"""
Normal	1x	1x	1x	1x	1x	1/2x	1x	0x	1/2x	1x	1x	1x	1x	1x	1x	1x	1x
Fighting	2x	1x	1/2x	1/2x	1x	2x	1/2x	0x	2x	1x	1x	1x	1x	1/2x	2x	1x	2x
Flying	1x	2x	1x	1x	1x	1/2x	2x	1x	1/2x	1x	1x	2x	1/2x	1x	1x	1x	1x
Poison	1x	1x	1x	1/2x	1/2x	1/2x	1x	1/2x	0x	1x	1x	2x	1x	1x	1x	1x	1x
Ground	1x	1x	0x	2x	1x	2x	1/2x	1x	2x	2x	1x	1/2x	2x	1x	1x	1x	1x
Rock	1x	1/2x	2x	1x	1/2x	1x	2x	1x	1/2x	2x	1x	1x	1x	1x	2x	1x	1x
Bug	1x	1/2x	1/2x	1/2x	1x	1x	1x	1/2x	1/2x	1/2x	1x	2x	1x	2x	1x	1x	2x
Ghost	0x	1x	1x	1x	1x	1x	1x	2x	1/2x	1x	1x	1x	1x	2x	1x	1x	1/2x
Steel	1x	1x	1x	1x	1x	2x	1x	1x	1/2x	1/2x	1/2x	1x	1/2x	1x	2x	1x	1x
Fire	1x	1x	1x	1x	1x	1/2x	2x	1x	2x	1/2x	1/2x	2x	1x	1x	2x	1/2x	1x
Water	1x	1x	1x	1x	2x	2x	1x	1x	1x	2x	1/2x	1/2x	1x	1x	1x	1/2x	1x
Grass	1x	1x	1/2x	1/2x	2x	2x	1/2x	1x	1/2x	1/2x	2x	1/2x	1x	1x	1x	1/2x	1x
Electric	1x	1x	2x	1x	0x	1x	1x	1x	1x	1x	2x	1/2x	1/2x	1x	1x	1/2x	1x
Psychic	1x	2x	1x	2x	1x	1x	1x	1x	1/2x	1x	1x	1x	1x	1/2x	1x	1x	0x
Ice	1x	1x	2x	1x	2x	1x	1x	1x	1/2x	1/2x	1/2x	2x	1x	1x	1/2x	2x	1x
Dragon	1x	1x	1x	1x	1x	1x	1x	1x	1/2x	1x	1x	1x	1x	1x	1x	2x	1x
Dark	1x	1/2x	1x	1x	1x	1x	1x	2x	1/2x	1x	1x	1x	1x	2x	1x	1x	1/2x
\"""

str = str.replace("1/2x", "0.5")
str = str.replace("1x", "1")
str = str.replace("2x", "2")
str = str.replace("0x", "0")

arr = str.split("\n")

for s in arr:
    a = s.split("\t")
    print("{", end="")
    print(", ".join(a[1:]), end="")
    print("}, //", a[0].capitalize(), len(a))
"""

def redoPokedex():
    with open("./Pokedex.csv", "r") as p:
        with open("./P2.csv", "a") as f:
            for line in p.readlines():
                arr = line.split(",")[:-1]
                f.write(",".join(arr) + "\n")

redoPokedex()