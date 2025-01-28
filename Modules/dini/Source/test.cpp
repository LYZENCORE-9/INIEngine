#include "../Core/dracoblue-implementation.h"

using namespace INIEngine::Module::Dini;


int main()
{
	dini_file file = dini_file();
	file.FileCreate((char*)"test.txt");
	return 0;
}
