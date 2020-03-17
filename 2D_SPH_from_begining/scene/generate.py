import random

f = open('scene1.txt', 'w+')
for x in range(100):
    for y in range(100):
        d = random.uniform(-1, 1)
        f.write(str(abs(x + d)) + ' ' + str(abs(y - d)))
f.close()