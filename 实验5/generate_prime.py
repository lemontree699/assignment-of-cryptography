import random

def proBin(w):  # w为随机生成的伪素数的比特数
    Pseudo_prime = ""
    Pseudo_prime += '1'
    for i in range(w - 2):
        c = random.randrange(0,2)
        Pseudo_prime += str(c)
    Pseudo_prime += '1'

    return Pseudo_prime

def is_probable_prime(n, trials = 5):  # n为十进制
    assert n >= 2
    # 2是素数~
    if n == 2:
        return True
    # 先判断n是否为偶数，用n&1==0的话效率更高
    if n % 2 == 0:
        return False
    # 把n-1写成(2^s)*d的形式
    s = 0
    d = n - 1
    while True:
        quotient, remainder = divmod(d, 2)
        if remainder == 1:
            break
        s += 1
        d = quotient
    assert(2 ** s * d == n - 1)

    # 测试以a为底时，n是否为合数
    def try_composite(a):
        if pow(a, d, n) == 1: # 相当于(a^d)%n
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1: #相当于(a^((2^i)*d))%n
                return False
        return True # 以上条件都不满足时，n一定是合数
    
    # trials为测试次数，默认测试5次
    # 每次的底a是不一样的，只要有一次未通过测试，则判定为合数
    for i in range(trials):
        a = random.randrange(2, n)
        if try_composite(a):
            return False

    return True #通过所有测试，n很大可能为素数

def proPrime(w):  # w为生成的素数的比特数
    count = 0
    a = proBin(w)  # 返回的a为二进制
    a_int = int(a, base = 2)  # 将a转换为十进制
    for i in range(1000):
        count += 1
        if is_probable_prime(a_int) == 1:
            print("trial:", count)
            print("The prime number generated is:", a_int)
            return a_int
        a_int += 2
    print("can not find a prime.")