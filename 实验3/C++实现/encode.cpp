#include <iostream>
#include "AESoperator.h"

using namespace std;
#define max 100
#define Nr 10
string RoundKey_word = "sysu";
string VI = "123";
string message = "School of data science and computer, Sun Yat-sen University.";
int main() {
	string state, RoundKey[11], key;
	string encrypted_message;
	string vi;
	for (int i = 0; i < RoundKey_word.length(); i++) {
		key += shift_char(RoundKey_word[i]);
	}
	for (int i = 0; i < VI.length(); i++) {
		vi += shift_char(VI[i]);
	}
	vi = Padding_0(vi);//get vi
	key = Padding_0(key);//get key
	getRoundKey(key, RoundKey);
	for (int i = 0; i < message.length(); i++) {
		state += shift_char(message[i]);
	}//get state
	int n = state.length() / 128 + 1;
	string x[max], y[max];
	y[0] = vi;
	int count = 0;
	for(int i = 0; i < n; i++){
		for (int j = 0; j < 128; j++) {
			x[i] += state[count];
			count++;
			if (count == state.length()) break;
		}
	}
	x[n - 1] = Padding_PKCS5(x[n - 1]);
	for (int j = 0; j < n; j++) {
		string temp_x = x[j];
		temp_x = exclusive_or(temp_x, y[j]);
		
		temp_x = AddRoundKey(temp_x, RoundKey[0]);
		for (int i = 1; i < Nr; i++) {
			temp_x = SubBytes(temp_x);
			temp_x = ShiftRows(temp_x);
			temp_x = MixColumns(temp_x);
			temp_x = AddRoundKey(temp_x, RoundKey[i]);
		}
		temp_x = SubBytes(temp_x);
		temp_x = ShiftRows(temp_x);
		temp_x = AddRoundKey(temp_x, RoundKey[10]);
		y[j + 1] = temp_x;
	}
	string ans;
	for (int i = 1; i <= n; i++) {
		ans += y[i];
	}
	cout << encode_hex(ans) << endl;
	system("pause");
}
