#include "IEM-dracoblue-ini.h"

using namespace INIEngine::Module::Dini;


int main()
{
    dini_file file = dini_file();
    file.FileCreate((char*)"test.txt");
    std::cout << "\n Operation of dini_file has executed !";

    return 0;
}
