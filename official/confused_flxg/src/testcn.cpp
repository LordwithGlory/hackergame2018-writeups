// testcn.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>


// -------------------------------------------------
std::string base64_encode(unsigned char const*, unsigned int len);
std::string base64_decode(std::string const& s);


static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}

std::string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

// -------------------------------------------------
const char fakeflxg[] = "==QfzMzMzIzXnFGbm9VZrFmZfF0XtF2XJt3Z4xmZ";
int main(int argc, wchar_t* argv[])
{
//	std::cout << "这是测试";
	char getflxg[200] = { 0 };
	std::cout << "请输入你要验证的flxg,格式为flxg{xxxxx}:";
	std::cin >> getflxg;
	int count = 60;
	try {
		if (argc < 60)
		{
			//wprintf(L"\n你解密到得到的flxg为 %ls ", fakeflxg);
			std::cout << "你解密到得到的flxg为:" << fakeflxg;
		}
		else if (argc == 60) {
			throw L"enter in exception!";
		}
		else if (argc > 60)
		{
			//wprintf(L"对不起参数过多！\n");
			std::cout << "对不起参数过多！\n";
			return 0;
		}
	}
	catch (const wchar_t* msg) {
		//wprintf(L"\nU enter in the exception!");
		int len = strlen(getflxg);
		//const char realflxg[200] = "9eETw_4_d_fh<4XU\x7fC!K\x7f Cv_ LMzSp}VMeGL]qC\x18oGHB\x18\x1cMtE\x01i\x00M[m";
		const char realflxg[200] = "9eETw_4_d_fh<4XU""\x7f""C!K\x7f"" Cv_ LMzSp}VMeGL]qC\x18""oGHB\x18\x1c""MtE\x01""i\x00""M[m";
		// "flxg{Congratulations_U_FiNd_the_trUe_flXg}"
		// b'Zmx4Z3tDb25ncmF0dWxhdGlvbnNfVV9GaU5kX3RoZV90clVlX2ZsWGd9'
		// b"9dGWsZ2XlVlc09VZoR3Xk5UaG9VVfNnbvlGdhxWd0Fmcn52bDt3Z4xmZ"
		std::string codedstr = base64_encode((const unsigned char *)getflxg, len);

		char temp[200] = { 0 };
		strcpy(temp, codedstr.c_str());
		_strrev(temp);
		char result[200] = { 0 };
		for (int i = 0; i < strlen(temp); i++)
		{
			result[i] = temp[i] ^ i;
		}
		if (strcmp(result, realflxg) == 0)
		{
			std::cout << "\n祝贺你，你输入的flxg是正确的！";
			//wprintf(L"\n祝贺你，你输入的flxg是正确的！");
			return 0;
		}
		std::cout << "\n你的flxg不正确！";
		return 0;
	}

	char my[100];
	std::cin >> my;
    return 0;
}

