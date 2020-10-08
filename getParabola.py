#!/usr/bin/python3
from numpy import array, linalg
L, R = [], []
for _ in range(3):
	x, y = map(float, input().split())
	L.append([x * x, x, 1])
	R.append(y)
R = array(R)
L = array(L)
X = linalg.solve(L, R)
print(X)