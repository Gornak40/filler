#!/usr/bin/python3
from numpy import array, linalg
L, R = [], []
for _ in range(2):
	x, y = map(float, input().split())
	L.append([x, 1])
	R.append(y)
L, R = array(L), array(R)
X = linalg.solve(L, R)
print(X)