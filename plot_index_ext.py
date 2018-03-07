import sys
import scipy.ndimage as ndimage
import matplotlib.pyplot as plt
from matplotlib import ticker
from matplotlib.colors import LinearSegmentedColormap

import matplotlib.pyplot as plt
import numpy as np
import csv



x = []
y = []

xx = []
yy = []

with open(sys.argv[1],'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))


with open(sys.argv[2],'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        xx.append(float(row[0]))
        yy.append(float(row[1]))



maxss=np.amax(yy, axis=0) ;
lenn=len(xx)

print(maxss)
print(lenn)

Matrix = [[0 for i in range(lenn)] for j in range(int(maxss))] 

for j in range(lenn):
     for i in range(int(maxss)):
        Matrix[i][j]=float('nan')




Matrix = [[0 for i in range(lenn)] for j in range(int(maxss))] 

for j in range(lenn):
     for i in range(int(yy[j])):
        Matrix[i][j]=y[j]


levels = [0.1,2.5,4]
#plt.contour(img, levels, colors='k')
plt.contourf(Matrix, 100,cmap = LinearSegmentedColormap.from_list('mycmap', ['white', 'blue', 'yellow', 'red', 'black']))
#plt.contourf(img, 100)
#plt.contour(img, colors='black', linewidth=.5)
#plt.clim(1,5.8)

cb=plt.colorbar(orientation="horizontal")
tick_locator = ticker.MaxNLocator(nbins=5)
cb.locator = tick_locator
cb.update_ticks()
cb.set_label("Upwelling intensity ($^{\circ}$C)")
#labels = ['J', 'F', 'M', 'A','M','J','J','A','S','O','N','D']
labelsy = ['$36N^{\circ}$', '$33^{\circ}N$', '$30^{\circ}N$', '$27^{\circ}N$','$24^{\circ}N$','$21^{\circ}N$']
#xxx = np.arange(0,46,3.835)
yyy = np.arange(0,375,64)


plt.xticks(yyy, labelsy, rotation='horizontal')
plt.ylabel('Spatial extension (km)')
plt.xlabel('Latitudes')

plt.axhline(0, color='white')
plt.axvline(0, color='white')

plt.show()
