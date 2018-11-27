#include <iostream>
#include <string>
#include <bitset>
using namespace std;

//计算多项式的度
int degree(string a)
{
	int pos = a.find_first_of("1");
	int deg = a.size() - pos - 1;
	return deg;
}

//去除多余的0
string cut(string a,int c)
{
	string b = a.substr(c, a.size());
	return b;
}

string polynomial_addition(string str_a, string str_b)
{
	bitset<260> a (str_a);
	bitset<260> b (str_b);
	bitset<260> c;
	c = a ^ b;

	string str_c = c.to_string();
	//cout << "addtion:" << endl << str_c << endl;
	return str_c;
}

string polynomial_modulo(string str_a)
{
	string fx = "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000111";
	string cx[5];
	cx[0] = "000000000000000000000000000000000000000000000000000000000000";
	string temp = str_a.substr(0,4);
	cx[0] += temp;
	cx[1] = str_a.substr(4,68);
	cx[2] = str_a.substr(68,132);
	cx[3] = str_a.substr(132,196);
	cx[4] = str_a.substr(196,260);

	bitset<64> c0 (cx[0]);
	bitset<64> c1 (cx[1]);
	bitset<64> c2 (cx[2]);
	bitset<64> c3 (cx[3]);
	bitset<64> c4 (cx[4]);
	bitset<64> t;
	//c4 mod f(x)
	t = c4;
	c1 = c1 ^ (t << 63) ^ (t << 62) ^ (t << 61);
	c2 = c2 ^ (t << 10) ^ (t >> 1) ^ (t >> 2) ^ (t >> 3);
	//c3 mod f(x)
	t = c3;
	c0 = c0 ^ (t << 63) ^ (t << 62) ^ (t << 61);
	c1 = c1 ^ (t << 10) ^ (t >> 1) ^ (t >> 2) ^ (t >> 3);
	c2 = c2 ^ (t >> 54);
	//c2
	bitset<64> t1 (0xfffffffffffffff8);
	bitset<64> t2 (0x0000000000000007);
	t = c2 & t1;
	c0 = c0 ^ (t << 10) ^ (t >> 1) ^ (t >> 2) ^ (t >> 3);
	c1 = c1 ^ (t >> 54);
	c2 = c2 & t2;

	string m = c0.to_string();
	m += c1.to_string();
	m += c2.to_string();
	//cout << "modulo:" << endl << m << endl;
	return m;
}

string polynomial_multiply(string str_a,string str_b)
{
	bitset<260> a (str_a);
	bitset<260> b (str_b);
	bitset<260> c;
	if(a[str_a.size() - 1] == 1)
	{
		bitset<260> cc (str_b);
		c = cc;
	}
	for (int i = 1; i < 130; ++i)
	{
		string temp_b = polynomial_modulo((b << 1).to_string());
		bitset<260> t (temp_b);
		b = t;
		if(a[i] == 1)
		{
			string temp_c = polynomial_addition(b.to_string(),c.to_string());
			bitset<260> tt (temp_c);
			c = tt;
		}
	}

	string str_c = c.to_string();
	//cout << "multiply:" << endl << str_c << endl;
	return str_c;
}

string polynomial_square(string str_a)
{
	string s = polynomial_multiply(str_a,str_a);
	return s;
}

string polynomial_inverse(string str_a)
{
	string f = "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000111";
	
	bitset<260> u (str_a);
	bitset<260> v (f);
	string str_g1,str_g2;
	for (int i = 0; i < 130; ++i)
		str_g1 += "0";
	str_g1 += "1";
	for (int i = 0; i < 131; ++i)
		str_g2 += "0";

	while(degree(u.to_string()) >= 1)
	{
		int j = degree(u.to_string()) - degree(v.to_string());  //j = deg(u) - deg(v)
		if(j < 0)
		{
			swap(u,v);

			swap(str_g1,str_g2);

			j = -j;
		}

		//u ⬅ u + z^j * v
		string str_u = polynomial_addition((v << j).to_string(), u.to_string());
		bitset<260> tempu (str_u);
		u = tempu;

		//g1 ⬅ g1 + z^j * v
		bitset<260> g2 (str_g2);
		str_g1 = polynomial_addition(str_g1,(g2 << j).to_string());

		// cout << "111" << endl;
	}
	return str_g1;
}

int main(int argc, char const *argv[])
{
	//多项式最高位在右边

	//131位
	string add_a = "00010101001010101001010110111010101010101010101000000111111010101010101010100010101001010101010000011101010111010101010101010101010";
	string add_b = "01010101010010101111110101010101010010101000000101111110101010010101010000001111110010010101010101010100101010101001000000111111110";
	string add_c = polynomial_addition(add_a,add_b);
	cout << "addtion:" << endl << cut(add_c,129) << endl;
	cout << endl;

	//260位
	string modulo_a = "01101010100110101010011010101001101010100110101010011010101001101010100110101010011010101001101010100110101010011010101001101010100110101010011010101001101010100110101010011010101001101010100110101010011010101001101010100110101010011010101001101010100110101010";
	string modulo_b = polynomial_modulo(modulo_a);
	cout << "modulo:" << endl << cut(modulo_b,modulo_b.find_first_of("1")) << endl;
	cout << endl;

	//131位
	string multiply_a = "10100101010100100000000101111110010101001010101000010101010010101001010101001001010110100101010001010101001010101001010100101010010";
	string multiply_b = "01000101010001010101010010101010111111110101010100100010101010010100101000011101010111101010101011000000101010111101001010100000011";
	string multiply_c = polynomial_multiply(multiply_a,multiply_b);
	cout << "multiply:" << endl << cut(multiply_c,multiply_c.find_first_of("1")) << endl;
	cout << endl;

	//131位
	string square_a = "10100101001010101011111110010101010010001001010010101010010101010101010101001010101001010101010010101010100101010100101010101010101";
	string square_b = polynomial_square(square_a);
	cout << "square:" << endl << cut(square_b,square_b.find_first_of("1")) << endl;
	cout << endl;

	//16337183 -> 111110010100100100011111
	string inverse_a = "111110010100100100011111";  //低位在右边
	string inverse_b = polynomial_inverse(inverse_a);
	cout << "inverse:" << endl << cut(inverse_b,inverse_b.find_first_of("1")) << endl;
	cout << endl;

	system("pause");
	return 0;
}
