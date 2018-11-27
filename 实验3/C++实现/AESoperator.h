#include <string>
#include "fieldoperator.h"
using namespace std;



string Padding_0(string a) {
	string ans = a;
	while (ans.length() < 128) {
		ans += '0';
	}
	return ans;
}

string Padding_PKCS5(string a) {
	int x = (128 - a.length()) / 8;
	string temp;
	while (x != 0) {
		temp = char(x % 2 + '0') + temp;
		x = x / 2;
	}
	while (temp.length() < 8) {
		temp = '0' + temp;
	}
	string ans = a;
	for (int i = 0; i < (128 - a.length()) / 8; i++) {
		ans += temp;
	}
	return ans;
}

string AddRoundKey(string state, string RoundKey) {
	return exclusive_or(state, RoundKey);
}

string SubBytes(string state) {
	string sub_state[16];
	string sub[16];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			sub_state[i] += state[j + i * 8];
		}
		
	}
	string c = "11000110";
	for (int i = 0; i < 16; i++) {
		if(sub_state[i] != "00000000")
			sub_state[i] = inverse(sub_state[i]);
		int len = sub_state[i].length();
		for (int j = 0; j < 8 - len; j++) {
			sub_state[i] = '0' + sub_state[i];
		}
		string temp = sub_state[i];
		temp = reverse(temp);
		for (int j = 0; j < 8; j++) {
			int x = temp[j] + temp[(j + 4) % 8] + temp[(j + 5) % 8]
				+ temp[(j + 6) % 8] + temp[(j + 7) % 8] + c[j] - '0' * 6;
			//cout << x << endl;
			sub[i] = char(x % 2 + '0') + sub[i];
		}
	}
	string ans;
	for (int i = 0; i < 16; i++) {
		ans += sub[i];
	}
	return ans;

}

string ShiftRows(string state) {//l -> r ??
	string sub_state[16];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			sub_state[i] += state[j + i * 8];
		}
	}
	string sub[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sub[4 * j + i] = sub_state[4 * ((j + i) % 4) + i];
		}
	}
	string ans;
	for (int i = 0; i < 16; i++) {
		//cout << sub_state[i] << " " << sub[i] << endl;
		ans += sub[i];
	}
	return ans;
}

string MixColumns(string state) {
	string sub_state[16];
	string sub[16];
	string x1 = shift_char(2);
	string x2 = shift_char(3);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			sub_state[i] += state[j + i * 8];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			string a1 = multiply(sub_state[4 * i + (j + 0) % 4], x1);
			string a2 = multiply(sub_state[4 * i + (j + 1) % 4], x2);
			sub[i * 4 + j] = exclusive_or(a1, a2);
			sub[i * 4 + j] = exclusive_or(sub[i * 4 + j], sub_state[4 * i + (j + 2) % 4]);
			sub[i * 4 + j] = exclusive_or(sub[i * 4 + j], sub_state[4 * i + (j + 3) % 4]);
		}
	}
	string ans;
	for (int i = 0; i < 16; i++) {
		ans += sub[i];
	}
	return ans;
}

void getRoundKey(string key, string RoundKey[11]) {
	string RCON[10];
	string w[44];
	RCON[0] = "00000001000000000000000000000000";
	RCON[1] = "00000010000000000000000000000000";
	RCON[2] = "00000100000000000000000000000000";
	RCON[3] = "00001000000000000000000000000000";
	RCON[4] = "00010000000000000000000000000000";
	RCON[5] = "00100000000000000000000000000000";
	RCON[6] = "01000000000000000000000000000000";
	RCON[7] = "10000000000000000000000000000000";
	RCON[8] = "00011011000000000000000000000000";
	RCON[9] = "00110110000000000000000000000000";
	string sub_state[16];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			sub_state[i] += key[j + i * 8];
		}
	}
	for (int i = 0; i < 4; i++) {
		w[i] = sub_state[i * 4] + sub_state[i * 4 + 1] + sub_state[i * 4 + 2] + sub_state[i * 4 + 3];
	}
	for (int i = 4; i < 44; i++) {
		string temp = w[i - 1];
		if (i % 4 == 0) {
			string sub[4];
			int count = 0;
			for (int j = 0; j < 4; j++) {
				for (int m = 0; m < 8; m++) {
					sub[j] += temp[count];
					count++;
				}
			}
			//RotWord\SubWord
			for (int x = 0; x < 4; x++) {
				string c = "11000110";
				string s = sub[x];
				sub[x] = "";
				if (s != "00000000")
					s = inverse(s);
				int len = s.length();
				for (int j = 0; j < 8 - len; j++) {
					s = '0' + s;
				}
				string temp_sub = s;
				temp_sub = reverse(temp_sub);
				for (int j = 0; j < 8; j++) {
					int m = temp_sub[j] + temp_sub[(j + 4) % 8] + temp_sub[(j + 5) % 8]
						+ temp_sub[(j + 6) % 8] + temp_sub[(j + 7) % 8] + c[j] - '0' * 6;
					//cout << x << endl;
					sub[x] = char(m % 2 + '0') + sub[x];
				}
			}
			temp = sub[1] + sub[2] + sub[3] + sub[0];
			temp = exclusive_or(temp, RCON[i / 4 - 1]);
		}
		w[i] = exclusive_or(w[i - 4], temp);
	}
	for (int i = 0; i < 11; i++) {
		RoundKey[i] = w[i * 4] + w[i * 4 + 1] + w[i * 4 + 2] + w[i * 4 + 3];
	}
}

