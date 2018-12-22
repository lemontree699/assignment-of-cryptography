#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import threading
import time
import generate_prime
import base64
from Crypto.Cipher import AES

# str不是16的倍数那就补足为16的倍数
def add_to_16(text):
    while len(text) % 16 != 0:
        text += '\0'
    return str.encode(text)  # 返回bytes

def Padding_128(m):
    for i in range(128 - len(m)):
        m += '0'
    return m

def Bin2Hex_str(s):
	# print(s)
	transform = {'0000':'0', '0001':'1', '0010':'2', '0011':'3', '0100':'4', '0101':'5', '0110':'6', 
		'0111':'7', '1000':'8', '1001':'9', '1010':'a', '1011':'b', '1100':'c', '1101':'d', '1110':'e', '1111':'f'}
	new_s = ''
	for i in range(len(s) // 4):
		new_s += transform[s[4*i:4*i+4]]
	return new_s

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

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 监听端口:
s.bind(('127.0.0.1', 9999))

s.listen(5)
print('Waiting for connection...')

def tcplink(sock, addr):
    print('Accept new connection from %s:%s...' % addr)
    sock.send(b'Welcome!')
    
    # 发送yb
    xb = generate_prime.proPrime(160)
    g = 2
    p = 295708653884425819303222693475275755143
    yb = square_and_multiply(g, xb, p)
    print('g =', g)
    print('p =', p)
    print('yb =', yb)
    yb = str(yb)
    sock.send(yb.encode('utf8'))

    # 接受ya
    ya = sock.recv(1024).decode('utf8')
    ya = int(ya)
    print('ya =', ya)

    # 计算密钥
    key = square_and_multiply(ya, xb, p)
    print('key =', key)
    key = bin(key)[2:]
    key = Padding_128(key)
    key = Bin2Hex_str(key)
    key = bytes.fromhex(key)
   
    aes = AES.new(key, AES.MODE_CBC, add_to_16('IV'))  # 初始化加密器

    # 接受密文
    ciphertext = sock.recv(1024).decode('utf8')
    print('ciphertext =', ciphertext)
    # print(type(ciphertext))
    message = str(aes.decrypt(base64.decodebytes(bytes(ciphertext, encoding='utf8'))).rstrip(b'\0').decode("utf8"))  # 解密
    print('ciphertext after Decryption =', message)

    sock.close()
    print('Connection from %s:%s closed.\n' % addr)

while True:
    # 接受一个新连接:
    sock, addr = s.accept()
    # 创建新线程来处理TCP连接:
    t = threading.Thread(target=tcplink, args=(sock, addr))
    t.start()