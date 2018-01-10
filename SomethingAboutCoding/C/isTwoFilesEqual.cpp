bool isFilesEqual(const std::string& lFilePath, const std::string& rFilePath)
{
#define BUFFER_SIZE (1024*1024)
	std::ifstream lFile(lFilePath.c_str(), std::ifstream::in | std::ifstream::binary);
	std::ifstream rFile(rFilePath.c_str(), std::ifstream::in | std::ifstream::binary);

	if (!lFile.is_open() || !rFile.is_open())
	{
		return false;
	}

	char *lBuffer = new char[BUFFER_SIZE]();
	char *rBuffer = new char[BUFFER_SIZE]();

	do {
		lFile.read(lBuffer, BUFFER_SIZE);
		rFile.read(rBuffer, BUFFER_SIZE);

		if (std::memcmp(lBuffer, rBuffer, BUFFER_SIZE) != 0)
		{
			delete[] lBuffer;
			delete[] rBuffer;
			return false;
		}
	} while (lFile.good() || rFile.good());

	delete[] lBuffer;
	delete[] rBuffer;
	return true;
}