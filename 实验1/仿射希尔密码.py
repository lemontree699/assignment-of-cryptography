import numpy
from numpy import*
message = 'adisplayedequation'  #明文
ciphertext = 'DSRMSIOPLXLJBZULLM'   #密文
message_n = [ord(x) - ord('a') for x in message]  #[0, 3, 8, 18, 15, 11, 0, 24, 4, 3, 4, 16, 20, 0, 19, 8, 14, 13]
ciphertext_n = [ord(x.lower()) - ord('a') for x in ciphertext]  #[3, 18, 17, 12, 18, 8, 14, 15, 11, 23, 11, 9, 1, 25, 20, 11, 11, 12]

matrix_x1 = numpy.array(message_n[:9]).reshape([3,3])
matrix_x2 = numpy.array(message_n[-9:]).reshape([3,3])
matrix_y1 = numpy.array(ciphertext_n[:9]).reshape([3,3])
matrix_y2 = numpy.array(ciphertext_n[-9:]).reshape([3,3])  #构造矩阵
print('matrix_x1 = ','\n',matrix_x1)
print('matrix_x2 = ','\n',matrix_x2)
print('matrix_y1 = ','\n',matrix_y1)
print('matrix_y2 = ','\n',matrix_y2)

matrix_differ_x = matrix_x2 - matrix_x1
matrix_differ_y = matrix_y2 - matrix_y1
def Mod26(x):
	for i in range(len(x)):
		for j in range(len(x[i])):
			x[i][j] = x[i][j] % 26
	return x
matrix_differ_x = Mod26(matrix_differ_x)
matrix_differ_y = Mod26(matrix_differ_y)
print('matrix_differ_x = ','\n',matrix_differ_x)
print('matrix_differ_y = ','\n',matrix_differ_y)

det_x = floor(numpy.linalg.det(matrix_differ_x)) % 26
print('The determinant of matrix_differ_x is:',det_x)
def findModReverse(a,m):   #求模26的逆
	import itertools
	for b in itertools.count(1):
		if (a*b)%m==1:
			return b
det_x_rev = findModReverse(det_x,26)
print('The inverse of det_x is:',det_x_rev)

def findAdjointMatrix(ma):   #求伴随矩阵
	m_adj = numpy.zeros([3,3])
	# print(ma)
	for i in range(len(ma)):
		for j in range(len(ma[i])):
			if((i + j) % 2 == 1):
				s = -1
			else:
				s = 1
			b = ma
			c = delete(delete(b,i,axis = 0),j,axis = 1)
			# print(c)
			m_adj[i,j] = s * (numpy.linalg.det(c))
	# print(numpy.transpose(m_adj))
	return numpy.transpose(Mod26(m_adj))
matrix_differ_x_adj = findAdjointMatrix(matrix_differ_x)  #得到伴随矩阵
print('The adjoint matrix of matrix_differ_x is:','\n',matrix_differ_x_adj)

matrix_differ_x_inv = Mod26(det_x_rev * matrix_differ_x_adj)
print('The inverse of matrix_differ_x is:','\n',matrix_differ_x_inv)

L = Mod26(numpy.dot(matrix_differ_x_inv,matrix_differ_y))   #求出密钥L
print('The key is:','\n','L = ','\n',L)

b = Mod26(matrix_y2 - numpy.dot(matrix_x2,L))   #求出密钥b
print('b = ','\n', b)