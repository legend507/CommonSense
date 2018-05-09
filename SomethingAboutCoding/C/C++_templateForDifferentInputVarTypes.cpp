#include <cstdio>
#include <string>

/*---------------------START: getFormatString -----------------------*/
/*
The following funcs gives a small trick to print different types of var into a file.
*/
template <typename T> char const* getFormatString();
template <> char const* getFormatString<int>() { return "%d\t"; }
template <> char const* getFormatString<float>() { return "%5.5f\t"; }
template <> char const* getFormatString<double>() { return "%15.10lf\t"; }
template <> char const* getFormatString<std::string>() { return "%s\t"; }

template <typename T>
void WriteToFile(std::string a, const T *img, const int x, const int y) {
	FILE *pFile;
	const char * c = a.c_str();
	fopen_s(&pFile, c, "w");
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			fprintf(pFile, getFormatString<T>(), img[i*y + j]);
		fprintf(pFile, "\n");
	}
	fclose(pFile);
}
/*---------------------END: getFormatString -----------------------*/

int main()
{
	int img1[] = { 1, 1, 1, 1 };
	float img2[] = { 1, 1, 1, 1 };
	double img3[] = { 1, 1, 1, 1 };
	std::string img4[] = { "1", "1", "2", "3" };
	WriteToFile("int.img", img1, 2, 2);
	WriteToFile("float.img", img2, 2, 2);
	WriteToFile("double.img", img3, 2, 2);
	WriteToFile("string.img", img4, 2, 2);

	return 0;
}