#include <iostream>
#include <string>
#include "sha1_operation.h"
using namespace std;

int main(int argc, char const *argv[])
{
	string K0_19 = HexToBin("5A827999");
	string K20_39 = HexToBin("6ED9EBA1");
	string K40_59 = HexToBin("8F1BBCDC");
	string K60_79 = HexToBin("CA62C1D6");
	string message = "16337183";

	string x;
	for (unsigned int i = 0; i < message.size(); i++)
		x += message_bin(message[i]);

	string y = SHA_1_PAD(x);  //y为512比特

	int group_size = y.size() / 512;
	string M[1000];
	for (int i = 0; i < group_size; ++i)
	{
		M[i] = y.substr(i*512,512);
	}

	string H0 = HexToBin("67452301");
	string H1 = HexToBin("EFCDAB89");
	string H2 = HexToBin("98BADCFE");
	string H3 = HexToBin("10325476");
	string H4 = HexToBin("C3D2E1F0");

	for (int group = 0; group < group_size; group++)
	{
	//for i←1 to n
		string W[80];
		for (int i = 0; i < 16; i++)
			W[i] = M[group].substr(i * 32, 32);
		for (int t = 16; t < 80; t++)
		{
			string temp1 = XOR(W[t - 3], W[t - 8]);
			string temp2 = XOR(temp1, W[t - 14]);
			string temp3 = XOR(temp2, W[t - 16]);
			W[t] = ROTL(temp3, 1);
		}

		string A = H0;
		string B = H1;
		string C = H2;
		string D = H3;
		string E = H4;

		for (int t = 0; t < 80; t++)
		{
			string temp1 = ROTL(A, 5);
			string temp2;
			string K;
			if (t >= 0 && t <= 19)
			{
				temp2 = f0_19(B, C, D);
				K = K0_19;
			}
			else if (t >= 20 && t <= 39)
			{
				temp2 = f20_39(B, C, D);
				K = K20_39;
			}
			else if (t >= 40 && t <= 59)
			{
				temp2 = f40_59(B, C, D);
				K = K40_59;
			}
			else if (t >= 60 && t <= 79)
			{
				temp2 = f60_79(B, C, D);
				K = K60_79;
			}
			string temp3 = ADD_mod32(temp1, temp2);
			string temp4 = ADD_mod32(temp3, E);
			string temp5 = ADD_mod32(temp4, W[t]);
			string temp = ADD_mod32(temp5, K);
			E = D;
			D = C;
			C = ROTL(B, 30);
			B = A;
			A = temp;
		}

		H0 = ADD_mod32(H0, A);
		H1 = ADD_mod32(H1, B);
		H2 = ADD_mod32(H2, C);
		H3 = ADD_mod32(H3, D);
		H4 = ADD_mod32(H4, E);
	}

	//cout << "The hash value is:" << endl << H0 << H1 << H2 << H3 << H4 << endl;
	cout << "The hash value is:" << endl << BinToHex(H0) << BinToHex(H1) << BinToHex(H2) << BinToHex(H3) << BinToHex(H4) << endl;
	
	system("pause");
	return 0;
}