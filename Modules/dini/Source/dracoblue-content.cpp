#include "../Core/dracoblue-implementation.h"

namespace INIEngine::Module::Dini
{
    void dini_content::CreateKey(char *filename, char *key)
    {
        int key_len = strlen(key);

        char backup_filename[DINI_MODULE_MAX_FILENAME_SIZE] = {0};
        char buffer_a[DINI_MODULE_MAX_STRING_SIZE] = {0};

        sprintf(backup_filename, "%s.MODULE_BIN_PART", filename);
        FILE* file_read = fopen(filename, "r+b");
        FILE* file_write = fopen(backup_filename, "w+b");

        fread(buffer_a, sizeof(char), sizeof(buffer_a), file_read);
        fwrite(buffer_a, sizeof(char), strlen(buffer_a), file_write);

        fclose(file_read);
        fclose(file_write);
        /* */
        char file_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};
        char key_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};

        char buffer_d[DINI_MODULE_MAX_STRING_SIZE] = {0};
        FILE* file_read_b = fopen(filename, "r+b");
        int index = 0;
        while(fgets(buffer_d, sizeof(buffer_d), file_read_b))
        {
            strcpy(file_lines[index], buffer_d);
            file_lines[index][key_len] = '\0';
            index++;
        }
        fclose(file_read_b);

        FILE* file_write_C = fopen(filename, "a+b");
        bool exist = false;
        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            file_lines[i][strcspn(file_lines[i], "\r\n")] = 0;
            if(strcmp(file_lines[i], key) == 0)
            {
                exist = true;
            }
        }

        if(exist == false)
        {
            fprintf(file_write_C, "%s = NULL\n", key);
        }

        fclose(file_write_C);
        remove(backup_filename);
        return;
    }

    void dini_content::RemoveKey(char *filename, char *key)
    {
        int key_len = strlen(key);

        char backup_filename[DINI_MODULE_MAX_FILENAME_SIZE] = {0};
        char buffer_a[DINI_MODULE_MAX_STRING_SIZE] = {0};

        sprintf(backup_filename, "%s.MODULE_BIN_PART", filename);
        FILE* file_read = fopen(filename, "r+b");
        FILE* file_write = fopen(backup_filename, "w+b");

        fread(buffer_a, sizeof(char), sizeof(buffer_a), file_read);
        fwrite(buffer_a, sizeof(char), strlen(buffer_a), file_write);

        fclose(file_read);
        fclose(file_write);
        /* */
        char file_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};
        char key_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};

        char buffer_d[DINI_MODULE_MAX_STRING_SIZE] = {0};
        FILE* file_read_b = fopen(filename, "r+b");
        int index = 0;
        while(fgets(buffer_d, sizeof(buffer_d), file_read_b))
        {
            strcpy(file_lines[index], buffer_d);
            //file_lines[index][key_len] = '\0';
            if(strcmp(&buffer_d[key_len], key) == 0)
            {
                file_lines[index][0] = {0};
            }
            index++;
        }
        fclose(file_read_b);

        FILE* file_write_C = fopen(filename, "w+b");
        bool exist = false;
        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            file_lines[i][strcspn(file_lines[i], "\r\n")] = 0;
            if(strcmp(file_lines[i], key) == 0)
            {
                exist = true;
            }
        }

        if(exist == false)
        {
            fprintf(file_write_C, "%s = NULL\n", key);
        }

        fclose(file_write_C);
        remove(backup_filename);
        return;
    }

}
