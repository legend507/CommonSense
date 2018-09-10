#include <fstream>
#include <iostream>
#include <filesystem>

// only work above C++17
// if error, try std::filesystem
namespace fs = std::experimental::filesystem;


int main(int argc, char *argv[])
{
	fs::create_directories("sandbox/a/b");
	std::ofstream("sandbox/file1.txt");
	std::ofstream("sandbox/file2.txt");
	for (auto& p : fs::directory_iterator("sandbox"))
		std::cout << p << std::endl;
	fs::remove_all("sandbox");

	system("pause");
	return false;

}
