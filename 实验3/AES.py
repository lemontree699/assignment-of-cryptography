#所有表示均使用字符串形式

import numpy as np

S_box = {
	'00':'63', '01':'7c', '02':'77', '03':'7b', '04':'f2', '05':'6b', '06':'6f', '07':'c5', '08':'30', '09':'01', '0a':'67', '0b':'2b', '0c':'fe', '0d':'d7', '0e':'ab', '0f':'76',
	'10':'ca', '11':'82', '12':'c9', '13':'7d', '14':'fa', '15':'59', '16':'47', '17':'f0', '18':'ad', '19':'d4', '1a':'a2', '1b':'af', '1c':'9c', '1d':'a4', '1e':'72', '1f':'c0',
	'20':'b7', '21':'fd', '22':'93', '23':'26', '24':'36', '25':'3f', '26':'f7', '27':'cc', '28':'34', '29':'a5', '2a':'e5', '2b':'f1', '2c':'71', '2d':'d8', '2e':'31', '2f':'15',
	'30':'04', '31':'c7', '32':'23', '33':'c3', '34':'18', '35':'96', '36':'05', '37':'9a', '38':'07', '39':'12', '3a':'80', '3b':'e2', '3c':'eb', '3d':'27', '3e':'b2', '3f':'75',
	'40':'09', '41':'83', '42':'2c', '43':'1a', '44':'1b', '45':'6e', '46':'5a', '47':'a0', '48':'52', '49':'3b', '4a':'d6', '4b':'b3', '4c':'29', '4d':'e3', '4e':'2f', '4f':'84',
	'50':'53', '51':'d1', '52':'00', '53':'ed', '54':'20', '55':'fc', '56':'b1', '57':'5b', '58':'6a', '59':'cb', '5a':'be', '5b':'39', '5c':'4a', '5d':'4c', '5e':'58', '5f':'cf',
	'60':'d0', '61':'ef', '62':'aa', '63':'fb', '64':'43', '65':'4d', '66':'33', '67':'85', '68':'45', '69':'f9', '6a':'02', '6b':'7f', '6c':'50', '6d':'3c', '6e':'9f', '6f':'a8',
	'70':'51', '71':'a3', '72':'40', '73':'8f', '74':'92', '75':'9d', '76':'38', '77':'f5', '78':'bc', '79':'b6', '7a':'da', '7b':'21', '7c':'10', '7d':'ff', '7e':'f3', '7f':'d2',
	'80':'cd', '81':'0c', '82':'13', '83':'ec', '84':'5f', '85':'97', '86':'44', '87':'17', '88':'c4', '89':'a7', '8a':'7e', '8b':'3d', '8c':'64', '8d':'5d', '8e':'19', '8f':'73',
	'90':'60', '91':'81', '92':'4f', '93':'dc', '94':'22', '95':'2a', '96':'90', '97':'88', '98':'46', '99':'ee', '9a':'b8', '9b':'14', '9c':'de', '9d':'5e', '9e':'0b', '9f':'db',
	'a0':'e0', 'a1':'32', 'a2':'3a', 'a3':'0a', 'a4':'49', 'a5':'06', 'a6':'24', 'a7':'5c', 'a8':'c2', 'a9':'d3', 'aa':'ac', 'ab':'62', 'ac':'91', 'ad':'95', 'ae':'e4', 'af':'79',
	'b0':'e7', 'b1':'c8', 'b2':'37', 'b3':'6d', 'b4':'8d', 'b5':'d5', 'b6':'4e', 'b7':'a9', 'b8':'6c', 'b9':'56', 'ba':'f4', 'bb':'ea', 'bc':'65', 'bd':'7a', 'be':'ae', 'bf':'08',
	'c0':'ba', 'c1':'78', 'c2':'25', 'c3':'2e', 'c4':'1c', 'c5':'a6', 'c6':'b4', 'c7':'c6', 'c8':'e8', 'c9':'dd', 'ca':'74', 'cb':'1f', 'cc':'4b', 'cd':'bd', 'ce':'8b', 'cf':'8a',
	'd0':'70', 'd1':'3e', 'd2':'b5', 'd3':'66', 'd4':'48', 'd5':'03', 'd6':'f6', 'd7':'0e', 'd8':'61', 'd9':'35', 'da':'57', 'db':'b9', 'dc':'86', 'dd':'c1', 'de':'1d', 'df':'9e',
	'e0':'e1', 'e1':'f8', 'e2':'98', 'e3':'11', 'e4':'69', 'e5':'d9', 'e6':'8e', 'e7':'94', 'e8':'9b', 'e9':'1e', 'ea':'87', 'eb':'e9', 'ec':'ce', 'ed':'55', 'ee':'28', 'ef':'df',
	'f0':'8c', 'f1':'a1', 'f2':'89', 'f3':'0d', 'f4':'bf', 'f5':'e6', 'f6':'42', 'f7':'68', 'f8':'41', 'f9':'99', 'fa':'2d', 'fb':'0f', 'fc':'b0', 'fd':'54', 'fe':'bb', 'ff':'16',
}

def SubBytes(state):
	newstate = [[],[],[],[]]  # 为了返回4*4的列表
	for i in range(len(state)):
		for j in range(len(state[0])):
			result = S_box[state[i][j]]
			newstate[i].append(result)
	return newstate

def ShiftRows(state):
	newstate = [[],[],[],[]]
	newstate[0].append(state[0][0])
	newstate[0].append(state[1][1])
	newstate[0].append(state[2][2])
	newstate[0].append(state[3][3])
	newstate[1].append(state[1][0])
	newstate[1].append(state[2][1])
	newstate[1].append(state[3][2])
	newstate[1].append(state[0][3])
	newstate[2].append(state[2][0])
	newstate[2].append(state[3][1])
	newstate[2].append(state[0][2])
	newstate[2].append(state[1][3])
	newstate[3].append(state[3][0])
	newstate[3].append(state[0][1])
	newstate[3].append(state[1][2])
	newstate[3].append(state[2][3])
	return newstate


def Hex2Bin(state):
	transform = {'0':'0000', '1':'0001', '2':'0010', '3':'0011', '4':'0100', '5':'0101', '6':'0110', 
		'7':'0111', '8':'1000', '9':'1001', 'a':'1010', 'b':'1011', 'c':'1100', 'd':'1101', 'e':'1110', 'f':'1111'}
	state_bin = [[],[],[],[]]
	for i in range(len(state)):
		for j in range(len(state[0])):
			result = transform[state[i][j][0]] + transform[state[i][j][1]]
			state_bin[i].append(result)
	return state_bin

def Bin2Hex(state):
	transform = {'0000':'0', '0001':'1', '0010':'2', '0011':'3', '0100':'4', '0101':'5', '0110':'6', 
		'0111':'7', '1000':'8', '1001':'9', '1010':'a', '1011':'b', '1100':'c', '1101':'d', '1110':'e', '1111':'f'}
	state_hex = [[],[],[],[]]
	for i in range(len(state)):
		for j in range(len(state[0])):
			result = transform[state[i][j][:4]] + transform[state[i][j][-4:]]
			state_hex[i].append(result)
	return state_hex

def XOR(a,b):
	c = ''
	for i in range(len(a)):
		c += str(int(a[i]) ^ int(b[i]))
	return c

def shift_8(s):
	result = ''
	if(s[0] == '0'):
		result += s[1:8]
		result += '0'
	else:
		result += s[1:8]
		result += '0'
		result = XOR(result,'00011011')
	return result

def FieldMult(c):
	new_c = []
	t0 = c[0]
	t1 = c[1]
	t2 = c[2]
	t3 = c[3]
	# u0 = reduce(XOR, [shift_8(t0), XOR(shift_8(t1),t1), t2, t3])
	u0 = XOR(shift_8(t0), XOR(shift_8(t1),t1))
	u0 = XOR(u0, t2)
	u0 = XOR(u0, t3)
	# u1 = reduce(XOR, [shift_8(t1), XOR(shift_8(t2),t2), t3, t0])
	u1 = XOR(shift_8(t1), XOR(shift_8(t2),t2))
	u1 = XOR(u1, t3)
	u1 = XOR(u1, t0)
	# u2 = reduce(XOR, [shift_8(t2), XOR(shift_8(t3),t3), t0, t1])
	u2 = XOR(shift_8(t2), XOR(shift_8(t3),t3))
	u2 = XOR(u2, t0)
	u2 = XOR(u2, t1)
	# u3 = reduce(XOR, [shift_8(t3), XOR(shift_8(t0),t0), t1, t2])
	u3 = XOR(shift_8(t3), XOR(shift_8(t0),t0))
	u3 = XOR(u3, t1)
	u3 = XOR(u3, t2)
	new_c.append(u0)
	new_c.append(u1)
	new_c.append(u2)
	new_c.append(u3)
	return new_c

def MixColumns(state):
	state = Hex2Bin(state)
	newcol = []
	for i in range(len(state)):
		newcol.append(FieldMult(state[i]))
	newcol = Bin2Hex(newcol)
	return newcol


def Hex2Bin_str(s):
	transform = {'0':'0000', '1':'0001', '2':'0010', '3':'0011', '4':'0100', '5':'0101', '6':'0110', 
		'7':'0111', '8':'1000', '9':'1001', 'a':'1010', 'b':'1011', 'c':'1100', 'd':'1101', 'e':'1110', 'f':'1111'}
	new_s = ''
	for i in range(len(s)):
		new_s += transform[s[i]]
	return new_s

def Bin2Hex_str(s):
	# print(s)
	transform = {'0000':'0', '0001':'1', '0010':'2', '0011':'3', '0100':'4', '0101':'5', '0110':'6', 
		'0111':'7', '1000':'8', '1001':'9', '1010':'a', '1011':'b', '1100':'c', '1101':'d', '1110':'e', '1111':'f'}
	new_s = ''
	for i in range(len(s) // 4):
		new_s += transform[s[4*i:4*i+4]]
	return new_s

def XOR_hex(a,b):
	c_bin = ''
	a_bin = Hex2Bin_str(a)
	b_bin = Hex2Bin_str(b)
	for i in range(len(a_bin)):
		c_bin += str(int(a_bin[i]) ^ int(b_bin[i]))
	c = Bin2Hex_str(c_bin)
	return c

def RotWord(t):
	new_t = ''
	new_t += t[2:8]
	new_t += t[:2]
	return new_t

def SubWord(t):
	new_t = ''
	new_t += S_box[t[:2]]
	new_t += S_box[t[2:4]]
	new_t += S_box[t[4:6]]
	new_t += S_box[t[6:8]]
	return new_t

def KeyExpansion(key):
	w = [] # 用来储存输出的轮密钥
	for i in range(44):
		w.append('')
	RCon = []
	RCon.append('01000000')
	RCon.append('02000000')
	RCon.append('04000000')
	RCon.append('08000000')
	RCon.append('10000000')
	RCon.append('20000000')
	RCon.append('40000000')
	RCon.append('80000000')
	RCon.append('1b000000')
	RCon.append('36000000')
	for i in range(4):
		w[i] += key[4*i]
		w[i] += key[4*i+1]
		w[i] += key[4*i+2]
		w[i] += key[4*i+3]
		# print(w[i])

	for i in range(4,44):
		temp = w[i - 1]
		if(i % 4 == 0):
			temp = XOR_hex(SubWord(RotWord(temp)), RCon[int(i/4) - 1])
		w[i] = XOR_hex(w[i - 4], temp) 
		# print(w[i])
	return w


def ToBinary(m):
	result = ''
	for i in m:
		result += hex(ord(i)).replace('0x','')
	result = Hex2Bin_str(result)
	return result

def Padding_128(m):
	for i in range(128 - len(m)):
		m += '0'
	return m

def Padding_PKCS5(m):
	x = int((128 - len(m)) / 8)
	y = format(x, '02x')
	ans = m
	for i in range(x):
		ans += Hex2Bin_str(y)
	return ans


# main
message = 'School of data science and computer, Sun Yat-sen University.'
key = 'sysu'
IV = '123'

message_group = [] # 每组128位
message_bin = ToBinary(message)
for i in range(len(message_bin) // 128):
	message_group.append(message_bin[128*i:128*(i+1)])
message_group.append(Padding_PKCS5(message_bin[-(len(message_bin) - 128 * (len(message_bin) // 128)):]))
# print(message_group)

key_bin = Padding_128(ToBinary(key))
# print(key_bin)
IV_bin = Padding_128(ToBinary(IV))
# print(IV_bin)

key_expansion = [] # 存储11个轮密钥
key_hex = []
for i in range(16):
	key_hex.append(Bin2Hex_str(key_bin[8*i:8*(i+1)]))
# print(key_hex)
key_expansion = KeyExpansion(key_hex)
# print(key_expansion)
key_expansion_bin_44 = [] 
for i in range(44):
	key_expansion_bin_44.append(Hex2Bin_str(key_expansion[i]))
key_expansion_bin_11 = []
for i in range(11):
	key_expansion_bin_11.append(key_expansion_bin_44[4*i] + key_expansion_bin_44[4*i+1] + key_expansion_bin_44[4*i+2] + key_expansion_bin_44[4*i+3])
# print(key_expansion_bin_11)

ciphertext = [] # 存储密文

# CBC模式
for cbc in range(len(message_group)):
	if(cbc == 0):
		message_1 = XOR(message_group[0],IV_bin)
	else:
		message_1 = XOR(message_group[cbc], state_bin_str)
	# print(message_1)

	# 开始加密
	message_2 = XOR(message_1, key_expansion_bin_11[0])
	# print(message_2)

	# 将输入转化为二维数组形式
	message_2_hex = [[],[],[],[]]
	for j in range(4):
		message_2_hex[j].append(Bin2Hex_str(message_2[32*j:32*j+8]))
		message_2_hex[j].append(Bin2Hex_str(message_2[32*j+8:32*j+16]))
		message_2_hex[j].append(Bin2Hex_str(message_2[32*j+16:32*j+24]))
		message_2_hex[j].append(Bin2Hex_str(message_2[32*j+24:32*j+32]))
	# print(state)

	state = message_2_hex
	# 9次循环
	for i in range(9):
		state = SubBytes(state)
		state = ShiftRows(state)
		state = MixColumns(state)
		# print(Hex2Bin(state))

		# 将轮密钥转化为二维数组形式
		temp = [[],[],[],[]]
		for j in range(4):
			temp[j].append(Bin2Hex_str(key_expansion_bin_11[i+1][32*j:32*j+8]))
			temp[j].append(Bin2Hex_str(key_expansion_bin_11[i+1][32*j+8:32*j+16]))
			temp[j].append(Bin2Hex_str(key_expansion_bin_11[i+1][32*j+16:32*j+24]))
			temp[j].append(Bin2Hex_str(key_expansion_bin_11[i+1][32*j+24:32*j+32]))

		for j in range(4):
			for k in range(4):
				state[j][k] = XOR_hex(state[j][k], temp[j][k])
		# print(Hex2Bin(state))

	# 第10轮
	state = SubBytes(state)
	state = ShiftRows(state)
	temp = [[],[],[],[]]
	for j in range(4):
		temp[j].append(Bin2Hex_str(key_expansion_bin_11[10][32*j:32*j+8]))
		temp[j].append(Bin2Hex_str(key_expansion_bin_11[10][32*j+8:32*j+16]))
		temp[j].append(Bin2Hex_str(key_expansion_bin_11[10][32*j+16:32*j+24]))
		temp[j].append(Bin2Hex_str(key_expansion_bin_11[10][32*j+24:32*j+32]))

	for j in range(4):
		for k in range(4):
			state[j][k] = XOR_hex(state[j][k], temp[j][k])

	# 将二维数组转化为二进制形式
	state_bin = Hex2Bin(state)
	state_bin_str = ''
	for i in range(4):
		for j in range(4):
			state_bin_str += state_bin[i][j]
	ciphertext.append(state_bin_str)
# print(state)

# print(ciphertext)
ciphertext_hex = ''
for i in range(len(ciphertext)):
	ciphertext_hex += Bin2Hex_str(ciphertext[i])
print(ciphertext_hex)