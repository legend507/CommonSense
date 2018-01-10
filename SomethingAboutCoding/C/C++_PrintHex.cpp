	void	CryptEngine::outputKey() {
		std::cout << "IV	:";
		for (int ii = 0; ii < sizeof(key_Decrypt.generatedIv); ii++) {
			std::cout << " " << std::hex << static_cast<int>(key_Decrypt.generatedIv[ii]);
		}
		std::cout << std::endl;
		std::cout << "key	:";
		for (int ii = 0; ii < sizeof(key_Decrypt.generatedKey); ii++) {
			std::cout << " " << std::hex << static_cast<int>(key_Decrypt.generatedKey[ii]);
		}
		std::cout << std::endl;
	}