#include "../Core/dracoblue-implementation.h"

namespace INIEngine::Module::Dini
{
    void dini_read::ReadString(char *filename, char *key, char *value)
    {
        int key_len = strlen(key);

        FILE* file = fopen(filename, "r+b");
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file))
        {
            if(key_len+3 < 255 && buffer[key_len+1] == '=')
            {
                buffer[key_len] = '\0';
                if(strcmp(key, buffer) == 0)
                {
                    strcpy(value, &buffer[key_len+2+1]);
                }
            }
        }
        return;
    }

    void dini_read::ReadInt(char *filename, char *key, int *value)
    {
        int key_len = strlen(key);
        char value_char[11];

        FILE* file = fopen(filename, "r+b");
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file))
        {
            if(key_len+3 < 255 && buffer[key_len+1] == '=')
            {
                buffer[key_len] = '\0';
                if(strcmp(key, buffer) == 0)
                {
                    strcpy(value_char, &buffer[key_len+2+1]);
                    *value = atoi(value_char);
                }
            }
        }
        return;
    }

    void dini_read::ReadFloat(char *filename, char *key, float *value)
    {
        int key_len = strlen(key);
        char value_char[11];

        FILE* file = fopen(filename, "r+b");
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file))
        {
            if(key_len+3 < 255 && buffer[key_len+1] == '=')
            {
                buffer[key_len] = '\0';
                if(strcmp(key, buffer) == 0)
                {
                    strcpy(value_char, &buffer[key_len+2+1]);
                    *value = atof(value_char);
                }
            }
        }
        return;
    }

    void dini_read::ReadBool(char *filename, char *key, bool *value)
    {
        int key_len = strlen(key);
        char value_char[1];

        FILE* file = fopen(filename, "r+b");
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file))
        {
            if(key_len+3 < 255 && buffer[key_len+1] == '=')
            {
                buffer[key_len] = '\0';
                if(strcmp(key, buffer) == 0)
                {
                    strcpy(value_char, &buffer[key_len+2+1]);
                }
            }
        }

        if(strcmp(value_char, "1") == 0)
        {
            *value = true;
        }
        else if(strcmp(value_char, "0") == 0)
        {
            *value = false;
        }
        return;
    }
}
