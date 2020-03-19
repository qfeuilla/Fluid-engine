import os
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.animation as manimation


FFMpegWriter = manimation.writers['ffmpeg']
metadata = dict(title='Movie Test', artist='Matplotlib',
                comment='Movie support!')
writer = FFMpegWriter(fps=60, metadata=metadata)

fig = plt.figure()
l, = plt.plot([], [], 'o')

plt.xlim(-50, 150)
plt.ylim(-50, 120)

dir = './values/'
files = os.listdir(dir)
with writer.saving(fig, "./video/spring_animation.mp4", 100):
    for f in files:
        file = open(dir + f, 'r+')
        points = []
        for line in file:
            line = line.split(',')
            if len(line) == 2:
                points.append(list(map(float, line)))
        l.set_data([i[0] for i in points], [i[1] for i in points])
        writer.grab_frame()