#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

string DecToBin(int a)
{
	string a_bin;
	for (int i = 0; a > 0; i++)
	{
		a_bin += to_string(a % 2);
		a /= 2;
	}
	reverse(a_bin.begin(), a_bin.end());
	return a_bin;
}

string SHA_1_PAD(string x)
{
	int d = (447 - x.size()) % 512;
	string l = DecToBin(x.size());
	while (l.size() < 64)
		l.insert(0,"0");
	string y = x;
	y += '1';
	for (int i = 0; i < d; ++i)
		y += '0';
	y += l;
	return y;
}

string message_bin(char a)
{
	int temp = int(a);
	string ans;
	while (temp != 0) 
	{
		int m = temp % 2;
		ans = char(m + '0') + ans;
		temp /= 2;
	}
	int len = ans.length();
	for (int j = 0; j < 8 - len; j++) {
		ans = '0' + ans;
	}
	return ans;
}

string ROTL(string a, int i)
{
	string ans;
	string start = a.substr(0, i);
	string last = a.substr(i, 32 - i);
	ans = last;
	ans += start;
	return ans;
}

string HexToBin_assist(char ch)
{
	string ans;
	switch (ch)
	{
	case '0':
		ans = "0000";
		break;
	case '1':
		ans = "0001";
		break;
	case '2':
		ans = "0010";
		break;
	case '3':
		ans = "0011";
		break;
	case '4':
		ans = "0100";
		break;
	case '5':
		ans = "0101";
		break;
	case '6':
		ans = "0110";
		break;
	case '7':
		ans = "0111";
		break;
	case '8':
		ans = "1000";
		break;
	case '9':
		ans = "1001";
		break;
	case 'A':
		ans = "1010";
		break;
	case 'B':
		ans = "1011";
		break;
	case 'C':
		ans = "1100";
		break;
	case 'D':
		ans = "1101";
		break;
	case 'E':
		ans = "1110";
		break;
	case 'F':
		ans = "1111";
		break;
	}
	return ans;
}

string HexToBin(string hex)
{
	string bin;
	for (unsigned int i = 0; i < hex.size(); i++)
	{
		bin += HexToBin_assist(hex[i]);
	}
	return bin;
}

char BinToHex_assist(string a) {
	int temp = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		temp += int(a[i] - '0') * pow(2, a.length() - i - 1);
	}
	switch (temp) {
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'e';
	case 15:
		return 'f';
	default:
		return char(temp + '0');
	}
}

string BinToHex(string a) {
	string ans;
	int len = a.length();
	int count = 0;
	int n = len / 4;
	for (int i = 0; i < n; i++) {
		string temp;
		for (int j = 0; j < 4; j++) {
			temp += a[count];
			count++;
		}
		ans += BinToHex_assist(temp);
	}
	return ans;
}

string AND(string a, string b)
{
	string ans;
	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] == '1' && b[i] == '1')
			ans += '1';
		else
			ans += '0';
	}
	return ans;
}

string OR(string a, string b)
{
	string ans;
	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] == '0' && b[i] == '0')
			ans += '0';
		else
			ans += '1';
	}
	return ans;
}

string XOR(string a, string b)
{
	string ans;
	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] == b[i])
			ans += '0';
		else
			ans += '1';
	}
	return ans;
}

string NOT(string a)
{
	string ans;
	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] == '0')
			ans += '1';
		else
			ans += '0';
	}
	return ans;
}

string ADD_mod32(string a, string b)
{
	char carry = '0';
	string ans;
	for (int i = a.size() - 1; i >= 0; i--)
	{
		int count = 0;
		if (a[i] == '1')
			count++;
		if (b[i] == '1')
			count++;
		if (carry == '1')
			count++;
		switch (count)
		{
		case 0:
			ans += '0';
			carry = '0';
			continue;
		case 1:
			ans += '1';
			carry = '0';
			continue;
		case 2:
			ans += '0';
			carry = '1';
			continue;
		case 3:
			ans += '1';
			carry = '1';
			continue;
		}
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

string f0_19(string B, string C, string D) 
{
	string ans;
	string temp1 = AND(B, C);
	string temp2 = NOT(B);
	string temp3 = AND(temp2, D);
	ans = OR(temp1, temp3);
	return ans;
}

string f20_39(string B, string C, string D)
{
	string ans;
	string temp1 = XOR(B, C);
	ans = XOR(temp1, D);
	return ans;
}

string f40_59(string B, string C, string D)
{
	string ans;
	string temp1 = AND(B, C);
	string temp2 = AND(B, D);
	string temp3 = AND(C, D);
	string temp4 = OR(temp1, temp2);
	ans = OR(temp4, temp3);
	return ans;
}

string f60_79(string B, string C, string D)
{
	string ans;
	string temp1 = XOR(B, C);
	ans = XOR(temp1, D);
	return ans;
}