#include	<codecvt>
		
std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
std::wstring path = cv.from_bytes(path_);
std::ifstream	iFile(path, std::ios::binary | std::ios::ate);


void	log(std::wstring str) {
	std::wofstream oFile("./log", std::ios::app | std::ios::out);
	oFile << str << std::endl;
	oFile.close();
}