import random

f = open('scene1.txt', 'w+')
for x in range(0, 100, 4):
    for y in range(0, 100, 4):
        d = random.uniform(-1, 1)
        f.write(str(abs(x + d)) + ' ' + str(abs(y - d)) + '\n')
f.close()