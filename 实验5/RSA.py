import generate_prime

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

# 计算乘法逆  a-1 mod Φ(n) = t mod Φ(n)
def multiplicative_inverse(n,a):
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
    if(b0 != 1):
        pass
    else:
        return t

# 生成公钥私钥 a*b≡1(mod Φ(n))  公钥：n,b  私钥：p,q,a
def Key(p, q, a):
    n = p * q
    Euler_function = (p - 1) * (q - 1)      # 计算与n互质的整数个数 欧拉函数
    b = multiplicative_inverse(Euler_function, a) # 公钥
    return n, b

# 加密 m是被加密的信息 加密成为c
def encrypt(message, n, b):
    ciphertext = square_and_multiply(message, b, n)
    return ciphertext

# 解密 c是密文，解密为明文m
def decrypt(ciphertext, n, a):
    message = square_and_multiply(ciphertext, a, n)
    return message

# 将需要加密的信息转换为数字
def ToDec(m):
    ans = ""
    for i in m:
        ans += str(ord(i))
    return int(ans)

# main
# 生成大素数p、q
p = generate_prime.proPrime(512)
q = generate_prime.proPrime(512)
# print(type(p))
# 生成公钥私钥。公钥：n,b  私钥：p,q,a
a = 16337183  # 私钥
n, b = Key(p, q, a)
# 需要加密的消息
m = "SUN YAT-SEN UNIVERSITY"
print("\nThe message that needs to be encrypted:", m)
message = ToDec(m)
print("message:", message)
# 加密
ciphertext = encrypt(message, n, b)
print ("ciphertext:", ciphertext)
# 解密
decode = decrypt(ciphertext, n, a)
print ("decode message:", decode)