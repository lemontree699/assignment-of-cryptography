import math
# import numpy as np

p = 5682549022748424631339131913370125786212509227588493537874673173634936008725904358935442101466555561124455782847468955028529037660533553941399408331331403379
g = 2410497055970432881345493397846112198995088771364307195189734031205605186951241875096796459061741781667380437076874705300974836586165283741668656930807264789
ya = 973768284341326272301553751114322685324340805902069613339667142187801529585352406975030927008752571917079716318221077758236884342662829402529734009607531649
yb = 4149822765985031146554298777122732051870868431387323913747785791685310508836836283702926446817000114868007555717546362425841865173929670156568682745060708314
n = p - 1
# n = 4309874666

# p = 809
# g = 89
# ya = 618
# n = 101

# 平方-乘算法，计算(base ^ exponent) mod n
def square_and_multiply(base, exponent, n):
    # 将exponent化为二进制存入bin_exponent中。
    # 切片[2:]是因为bin()函数作用后前面会有0b
    bin_exponent = bin(exponent)[2:]
    # print("exponent:", exponent)
    # print("bin_exponent:", bin_exponent)
    length = len(bin_exponent)
    
    z = 1
    for i in range(length):
        z = (z ** 2) % n
        # 从高位访问到低位
        if int(bin_exponent[i]) == 1:
            # print("true")
            z = (z * base) % n
        # print(z)
    return z

# 计算乘法逆  a-1 mod n = t mod n
def multiplicative_inverse(n,a):
    while a < 0:
        a += n 
    a0 = n
    b0 = a
    t0 = 0
    t = 1
    q = a0 // b0
    r = a0 - q * b0
    while r > 0:
        temp = (t0 - q * t) % n
        t0 = t
        t = temp
        a0 = b0
        b0 = r
        q = a0 // b0
        r = a0 - q * b0
    if(b0 != 1): # 不存在a模n的逆
        pass
    else:
        return t

# 计算最大公因数
def gcd(a,b):
	r = []
	r.append(a)
	r.append(b)
	m = 1
	while(r[m] != 0):
		temp = math.floor(r[m - 1] / r[m])
		r.append(r[m - 1] - temp * r[m])
		m = m + 1
	m = m - 1
	return r[m]

# return (r,s,t) r = gcd(a,b) s*a+t*b=r
def extended_euclidean_algorithm(a,b):
	a0 = a
	b0 = b
	t0 = 0
	t = 1
	s0 = 1
	s = 0
	q = math.floor(a0 / b0)
	r = a0 - q * b0
	while r > 0:
		temp = t0 - q * t
		t0 = t
		t = temp
		temp = s0 - q * s
		s0 = s
		s = temp
		a0 = b0
		b0 = r
		q = math.floor(a0 / b0)
		r = a0 - q * b0
	r = b0
	return (r,s,t)

def fx(x,a,b):
	if x % 3 == 1:
		x = (ya * x) % p
		b = (b + 1) % n
		return (x,a,b)
	elif x % 3 == 0:
		x = (x ** 2) % p
		a = (2 * a) % n
		b = (2 * b) % n
		return (x,a,b)
	elif x % 3 == 2:
		x = (g * x) % p
		a = (a + 1) % n
		return (x,a,b)

def congruence_equation(a,b,m):
	d = gcd(a,m)
	aa = a // d
	bb = b // d
	mm = m // d
	r,s,t = extended_euclidean_algorithm(aa,mm)
	x = []
	for k in range(d):
		x.append(int((s * bb + k * mm) % m))
	return x

# def congruence_equation(a,b,m):
# 	d = gcd(a,m)
# 	mm = m // d
# 	aa = a // d
# 	bb = b // d
# 	# print(gcd(aa,mm))
# 	# print("aa =", aa)
# 	# print("bb =", bb)
# 	# print("mm =", mm)
# 	# print(multiplicative_inverse(mm, aa))
# 	x = bb * multiplicative_inverse(mm, aa) % mm
# 	result = []
# 	for i in range(d):
# 		result.append(x + i * mm)
# 	return result


x,a,b = fx(1,0,0)
x_,a_,b_ = fx(x,a,b)
i = 0
while x != x_:
	x,a,b = fx(x,a,b)
	x_,a_,b_ = fx(x_,a_,b_)
	x_,a_,b_ = fx(x_,a_,b_)
	# i += 1
	# if(i % 10000 == 0):
	# 	print("test", i)
if gcd(b_ - b, n) != 1:
	d = gcd(b_ - b, n)
	print("Failed", d)
	xx = congruence_equation(b_ - b,a - a_,n)
	for i in xx:
		if square_and_multiply(g,i,p) == ya:
			xa = i
			print("xa =", i)
			print("ya =", square_and_multiply(g,i,p))
	common_information = square_and_multiply(yb,xa,p)
	print("The common information is:", common_information)

else:
	print("xa =", ((a - a_) * multiplicative_inverse(n, b_ - b)) % n)
	# print("ya =", square_and_multiply(g, ((a - a_) * multiplicative_inverse(n, b_ - b)) % n, p))