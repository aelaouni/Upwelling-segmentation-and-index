
import matplotlib.pyplot as plt
import csv

x = []
y = []

xx = []
yy = []

with open('ind.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))


with open('ext.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        xx.append(float(row[0]))
        yy.append(float(row[1]))


# plt.plot(x,y, label='upwelling index')
# plt.xlabel('latitudes')
# plt.ylabel('intensity')
# plt.title('Spatial variation of upwelling index')
# plt.legend()
# plt.show()


fig, ax1 = plt.subplots()

ax1.plot(x, y, 'b-')
ax1.set_xlabel('latitudes')
# Make the y-axis label, ticks and tick labels match the line color.
ax1.set_ylabel('Upwelling intensity', color='b')
ax1.tick_params('y', colors='b')

ax2 = ax1.twinx()
ax2.plot(xx, yy, 'r-')
ax2.set_ylabel('Upwelling extension (km)', color='r')
ax2.tick_params('y', colors='r')

fig.tight_layout()
plt.show()
