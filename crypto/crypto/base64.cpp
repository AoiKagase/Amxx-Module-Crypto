#include "base64.hpp"


//	base64の1文字を6bitの値に変換する
inline int base64_to_6bit(int c)
{
    if (c == '=')
        return 0;
    if (c == '/')
        return 63;
    if (c == '+')
        return 62;
    if (c <= '9')
        return (c - '0') + 52;
    if ('a'<=c)
        return (c - 'a') + 26;
    return (c - 'A');
}
//	base64の文字列srcをデコードしてバイナリ値に変換しdtcに格納
//	lenはbase64の文字数
//	変換後のバイト数を返す
int BASE64::Decode(const char* src, char* dtc)
{
	unsigned o0, o1, o2, o3;
	char* p = dtc;
	for (int n = 0; src[n];){
		o0 = base64_to_6bit(src[n]);
		o1 = base64_to_6bit(src[n + 1]);
		o2 = base64_to_6bit(src[n + 2]);
		o3 = base64_to_6bit(src[n + 3]);

		*p++ = (o0 << 2) | ((o1 & 0x30) >> 4);
		*p++ = ((o1 & 0xf) << 4) | ((o2 & 0x3c) >> 2);
		*p++ = ((o2 & 0x3) << 6) | o3 & 0x3f;
		n += 4;
	}
	*p = 0;
	return static_cast<int>(p - dtc);
}

//	バイナリの配列srcをbase64でエンコードする
//	src:バイナリ配列 len:バイナリ配列長さ
//	dtc:変換後の文字列を保存するアドレス dtc_len:変換後のバイト数を保存するアドレス
void BASE64::Encode(const char* src, const int len, char* dtc, int* dtc_len)
{
	//	6bitからbase64の文字へ変換するテーブル
	//                              1         2         3         4         5         6
	//                    0123456789012345678901234567890123456789012345678901234567890123456789
	//                                    1               2               3
	//                    0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF
	const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int n;
	int mod = len % 3;

	int adj_len = len - mod;	//	3の倍数に修正
	char* p = dtc;
	int o0, o1, o2, o3;
	for (n = 0; n < adj_len;){
		unsigned x = ((unsigned)src[n] << 16) + ((unsigned)src[n + 1] << 8) + unsigned(src[n + 2]);
		o0 = (x >> 18) & 0x3f;
		o1 = (x >> 12) & 0x3f;
		o2 = (x >> 6) & 0x3f;
		o3 = x & 0x3f;
		*p++ = table[o0];
		*p++ = table[o1];
		*p++ = table[o2];
		*p++ = table[o3];
		n += 3;
	}
	if (mod){
		if (mod==1){
			unsigned x = (unsigned)src[n] << 16;
			o0 = (x >> 18) & 0x3f;
			o1 = (x >> 12) & 0x3f;
			*p++ = table[o0];
			*p++ = table[o1];
			*p++ = '=';
			*p++ = '=';
		}
		else if (mod==2){
			unsigned x = ((unsigned)src[n] << 16) + ((unsigned)src[n + 1] << 8) ;
			o0 = (x >> 18) & 0x3f;
			o1 = (x >> 12) & 0x3f;
			o2 = (x >> 6) & 0x3f;
			*p++ = table[o0];
			*p++ = table[o1];
			*p++ = table[o2];
			*p++ = '=';
		}
	}
	*p = 0;
	*dtc_len = int(p - dtc);
}