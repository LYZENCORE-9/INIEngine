#include "../Core/dracoblue-implementation.h"

namespace INIEngine::Module::Dini
{
    bool dini_file::FileCreate(char* filename)
    {
        FILE* handle;
        if ((handle = fopen(filename, "r"))) {
            fclose(handle);
            return false;
        }

        handle = fopen(filename, "w");
        fclose(handle);
        return true;

    }

    bool dini_file::FileExists(char* filename)
    {
        FILE* handle;
        if((handle = fopen(filename, "r")))
        {
            return true;
        }
        return false;
    }

    bool dini_file::FileDelete(char* filename)
    {
        if(remove(filename) == 0)
        {
            return true;
        }
        return false;
    }

    bool dini_file::FileRemove(char* filename)
    {
        if(remove(filename) == 0)
        {
            return true;
        }
        return false;
    }
}
