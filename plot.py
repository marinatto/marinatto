import matplotlib.pyplot as plt
import numpy as np

def plot_data(time, sensor, out, modulation, mean, filtro):
    plt.plot(time, sensor, label='sensor')
    plt.plot(time, out, label='out')
    plt.plot(time, modulation, label='modulation')
    plt.plot(time, mean, label='mean')
    plt.plot(time, filtro, label='lowpass')
    plt.legend()

time, ym = np.loadtxt('sensor.log', unpack=True)
time, y  = np.loadtxt('out.log', unpack=True)
time, y1 = np.loadtxt('modulation.log', unpack=True)
time, y2 = np.loadtxt('mean.log',unpack=True)
time, y3 = np.loadtxt('lowpass.log',unpack=True)
plot_data(time, ym, y, y1, y2, y3)

plt.show()
