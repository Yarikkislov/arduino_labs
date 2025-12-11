#МНК

import matplotlib.pyplot as plt
import numpy as np

#эксперементальные данные
x = np.array([90, 100, 105, 110, 115, 130, 150, 190, 230, 340, 630, 900])
y = np.array([690, 700, 715, 720, 725, 735, 760, 785, 810, 840, 875, 945])

M = 4 #степень аппроксимирующего многочлена

s = np.array([np.sum(np.power(x, i)) for i in range(2 * M + 1)])
t = np.array([np.sum(np.multiply(y, np.power(x, i))) for i in range(M + 1)])

A = np.array([s[i : i + M + 1] for i in range(len(s) - M)])
B = np.array([[t[i]] for i in range(len(t))])
X = np.linalg.solve(A, B) #вектор коэффицентов аппроксимирующего многочлена

np.set_printoptions(linewidth = 100)
#for m in [A, B, X]: print(m)

#аппроксимация
x_ = np.linspace(x[0], x[-1], 100)
y_ = np.array([np.sum([X[i] * x ** i for i in range(len(X))]) for x in x_])

#octave
X__ = np.array([[5.3088e+02], [2.2937e+00], [-6.2742e-03], [7.5372e-06], [-3.1439e-09]])
print(X__)
y__ = np.array([np.sum([X__[i] * x ** i for i in range(len(X__))]) for x in x_])
plt.plot(x_, y__)

#погрешность
y0 = np.array([np.sum([X__[i] * x ** i for i in range(len(X__))]) for x in x])
E = max(np.abs(y - y0) / max(np.abs(y))) * 100
print(f"Погрешность = {E}%")

#графики
plt.plot(x, y)
#plt.plot(x_, y_)
plt.show()

