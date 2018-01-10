#include	<fstream>
#include	<cstdint>	// for uint8_t

uint8_t			inBuffer[AES128_BLOCKSIZE];
std::ifstream	inFile("data_enc.bin", std::ios::in | std::ios::binary);
uint8_t			outBuffer[AES128_BLOCKSIZE];
int32_t			outBufferLen;
std::ofstream	outFile("data_dec.bin", std::ios::out | std::ios::binary);

inFile.read(reinterpret_cast<char*>(inBuffer), AES128_BLOCKSIZE);

outFile.write(reinterpret_cast<char*>(outBuffer), AES128_BLOCKSIZE);


// ate = open file and move pointer to the end of file
		std::ifstream	inFile(path, std::ios::in | std::ios::binary | std::ios::ate);
		int32_t			inFileSize = inFile.tellg();	// get size of file
		inFile.seekg(0, inFile.beg);					// move file pointer to begin