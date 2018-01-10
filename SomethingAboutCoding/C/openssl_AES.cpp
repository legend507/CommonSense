#include	<iostream>
#include	<openssl/aes.h>
using namespace std;

static const unsigned char key[] = {
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};


int main() {
	unsigned char text[] = "hello world!";
	unsigned char enc_out[80];
	unsigned char dec_out[80];

	AES_KEY enc_key, dec_key;

	// Encrypt
	AES_set_encrypt_key(key, 128, &enc_key);
	AES_encrypt(text, enc_out, &enc_key);

	// Decrypt
	AES_set_decrypt_key(key, 128, &dec_key);
	AES_decrypt(enc_out, dec_out, &dec_key);

	cout << "Decrypt:" << dec_out << endl;

	system("pause");
	return 0;
}