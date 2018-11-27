#include <string>
using namespace std;

char convert_hex(string a) {
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

string encode_hex(string a) {
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
		ans += convert_hex(temp);
	}
	return ans;
}

string shift_char(char a) {
	int temp = int(a);
	string ans;
	while (temp != 0) {
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

string reverse(string a) {
	int len = a.length();
	string ans;
	for (int i = len - 1; i >= 0; i--) {
		ans += a[i];
	}
	return ans;
}

string exclusive_or(string a, string b) {//a[0] is the biggest bit
	string ans;
	if (a.length() < b.length()) {
		string temp = a;
		a = b;
		b = temp;
	}
	int x = a.length() - b.length();
	for (int i = 0; i < x; i++) {
		b = '0' + b;
	}
	ans = a;
	for (int i = 0; i < b.length(); i++) {
		if (a[i] == b[i]) ans[i] = '0';
		else ans[i] = '1';
	}
	return ans;
}

string remove_zero(string a) {
	string ans;
	int j = 0;
	while (a[j] == '0') j++;
	for (int i = j; i < a.length(); i++) {
		ans += a[i];
	}
	return ans;
}

bool bigger(string a, string b) {
	if (a.length() > b.length()) return 1;
	else if (a.length() < b.length()) return 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		if (a[i] > b[i]) return 1;
		else if(a[i] < b[i]) return 0;
	}
	return 0;
}

string mod(string a) {//a[0] is the biggest bit
	char m[9];
	for (int i = 0; i < 9; i++) {
		m[i] = '0';
	}
	m[0] = '1';
	m[1] = '1';
	m[3] = '1';
	m[4] = '1';
	m[8] = '1';
	string mo;
	for (int i = 0; i < 9; i++) {
		mo += m[i];
	}
	mo = reverse(mo);
	string ans = a;
	while (ans.length() >= mo.length()) {
		string temp = mo;
		for (int i = 0; i < ans.length() - mo.length(); i++) {
			temp = temp + "0";
		}
		ans = exclusive_or(temp, ans);
		ans = remove_zero(ans);
	}
	if (ans == "") ans = "0";
	return ans;
}

string multiply(string a, string b) {
	string ans = "0";
	int len = a.length();
	for (int i = 0; i < len; i++) {
		if (a[len - i - 1] == '1') {
			string temp = b;
			for (int j = 0; j < i; j++) {
				temp += '0';
			}
			ans = exclusive_or(ans, temp);

		}
	}
	return mod(ans);
}

string inverse(string a) {
	char b1[9];
	char c1[9];
	string u = a;
	u = remove_zero(u);
	char m[9];
	for (int i = 0; i < 9; i++) {
		m[i] = '0';
		b1[i] = '0';
		c1[i] = '0';
	}
	b1[8] = '1';
	m[0] = '1';
	m[1] = '1';
	m[3] = '1';
	m[4] = '1';
	m[8] = '1';
	string mo, b, c;
	for (int i = 0; i < 9; i++) {
		mo += m[i];
		b += b1[i];
		c += c1[i];
	}
	mo = reverse(mo);
	int j;
	while (u.length() != 1) {
		j = u.length() - mo.length();
		if (j < 0) {
			string temp = u;
			u = mo;
			mo = temp;
			temp = c;
			c = b;
			b = temp;
			j *= -1;
		}
		string temp1 = mo;
		string temp2 = c;
		for (int i = 0; i < j; i++) {
			temp1 += '0';
			temp2 += '0';
		}
		u = exclusive_or(u, temp1);
		b = exclusive_or(b, temp2);
		u = remove_zero(u);
		b = remove_zero(b);
	}
	return b;
}