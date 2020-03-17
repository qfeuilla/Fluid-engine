import random

f = open('scene1.txt', 'w+')
for x in range(50):
    for y in range(50):
        for z in range(50):
            d = random.uniform(-1, 1)
            f.write(str(abs(x + d)) + ' ' + str(abs(y - d)) + ' ' + str(z) + '\n')
f.close()