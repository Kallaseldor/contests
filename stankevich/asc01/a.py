f = open ("china.in", "w+")
n = integer (f.read())
f.close()

f = open ("china.out", "w+")
x = integer (n / 2)

if n % 2 == 0:
	x = x - 1
	if x % 2 == 0:
		f.write (x - 1)
	else:
		f.write (x)
else:
	f.write (x)