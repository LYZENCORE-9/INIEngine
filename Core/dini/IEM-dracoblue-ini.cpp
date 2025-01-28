#include "IEM-dracoblue-ini.h"


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

    void dini_write::WriteString(char *filename, char *key, char *value)
    {
        int key_len = strlen(key);
        int value_len = strlen(value);

        char backup_filename[DINI_MODULE_MAX_FILENAME_SIZE] = {0};
        char backup_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};

        sprintf(backup_filename, "%s.MODULE_BIN_PART", filename);

        FILE* file_read = fopen(filename, "r+b");
        FILE* file_write = fopen(backup_filename, "w+b");

        fread(backup_buffer, sizeof(char), sizeof(backup_buffer), file_read);
        fwrite(backup_buffer, sizeof(char), strlen(backup_buffer), file_write);

        fclose(file_read);
        fclose(file_write);
        /* */

        FILE* file_read_a = fopen(backup_filename, "r+b");

        char key_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_a[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char buffer_old_value[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_editedline[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char file_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};
        while(fgets(buffer_a, sizeof(buffer_a), file_read_a))
        {

            if(key_len + value_len + 2 < DINI_MODULE_MAX_STRING_SIZE && buffer_a[key_len+1] == '=')
            {
                strcpy(key_buffer, buffer_a);
                key_buffer[key_len] = '\0';
                if(strcmp(key, key_buffer) == 0)
                {
                    strcpy(buffer_old_value, &buffer_a[key_len+3]);
                    sprintf(buffer_editedline, "%s = %s", key, value);

                }
            }
        }
        fclose(file_read_a);
        /* */

        char buffer_b[DINI_MODULE_MAX_STRING_SIZE] = {0};
        int index = 0;

        FILE* file_read_b = fopen(backup_filename, "r+b");
        while(fgets(buffer_b, sizeof(buffer_b), file_read_b))
        {
            strcpy(file_lines[index], buffer_b);
            index++;
        }
        fclose(file_read_b);
        /* */

        char buffer_oldline[DINI_MODULE_MAX_STRING_SIZE] = {0};
        buffer_oldline[key_len+3+value_len] = '\0';

        sprintf(buffer_oldline, "%s = %s", key, buffer_old_value);

        /* */

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            if(strcmp(file_lines[i], buffer_oldline) == 0)
            {
                strcpy(file_lines[i], buffer_editedline);
            }
        }

        FILE* file_write_C = fopen(filename, "wb");

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            file_lines[i][strcspn(file_lines[i], "\r\n")] = 0;
            if(file_lines[i][0] != '\0')
            {
                fprintf(file_write_C, "%s\n", file_lines[i]);
            }
        }
        fclose(file_write_C);

        remove(backup_filename);
        return;

    }

    void dini_write::WriteInt(char *filename, char *key, int *value)
    {
        char value_char[11];
        itoa(*value, value_char, 10);
        int key_len = strlen(key);
        int value_len = strlen(value_char);

        char backup_filename[DINI_MODULE_MAX_FILENAME_SIZE] = {0};
        char backup_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};

        sprintf(backup_filename, "%s.MODULE_BIN_PART", filename);

        FILE* file_read = fopen(filename, "r+b");
        FILE* file_write = fopen(backup_filename, "w+b");

        fread(backup_buffer, sizeof(char), sizeof(backup_buffer), file_read);
        fwrite(backup_buffer, sizeof(char), strlen(backup_buffer), file_write);

        fclose(file_read);
        fclose(file_write);
        /* */

        FILE* file_read_a = fopen(backup_filename, "r+b");

        char key_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_a[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char buffer_old_value[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_editedline[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char file_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};
        while(fgets(buffer_a, sizeof(buffer_a), file_read_a))
        {

            if(key_len + value_len + 2 < DINI_MODULE_MAX_STRING_SIZE && buffer_a[key_len+1] == '=')
            {
                strcpy(key_buffer, buffer_a);
                key_buffer[key_len] = '\0';
                if(strcmp(key, key_buffer) == 0)
                {
                    strcpy(buffer_old_value, &buffer_a[key_len+3]);
                    sprintf(buffer_editedline, "%s = %s", key, value_char);

                }
            }
        }
        fclose(file_read_a);
        /* */

        char buffer_b[DINI_MODULE_MAX_STRING_SIZE] = {0};
        int index = 0;

        FILE* file_read_b = fopen(backup_filename, "r+b");
        while(fgets(buffer_b, sizeof(buffer_b), file_read_b))
        {
            strcpy(file_lines[index], buffer_b);
            index++;
        }
        fclose(file_read_b);
        /* */

        char buffer_oldline[DINI_MODULE_MAX_STRING_SIZE] = {0};
        buffer_oldline[key_len+3+value_len] = '\0';

        sprintf(buffer_oldline, "%s = %s", key, buffer_old_value);

        /* */

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            if(strcmp(file_lines[i], buffer_oldline) == 0)
            {
                strcpy(file_lines[i], buffer_editedline);
            }
        }

        FILE* file_write_C = fopen(filename, "wb");

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            file_lines[i][strcspn(file_lines[i], "\r\n")] = 0;
            if(file_lines[i][0] != '\0')
            {
                fprintf(file_write_C, "%s\n", file_lines[i]);
            }
        }
        fclose(file_write_C);

        remove(backup_filename);
        return;
    }

    void dini_write::WriteFloat(char *filename, char *key, float *value)
    {
        char value_char[100];
        gcvt(*value, 7, value_char);

        int key_len = strlen(key);
        int value_len = strlen(value_char);

        char backup_filename[DINI_MODULE_MAX_FILENAME_SIZE] = {0};
        char backup_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};

        sprintf(backup_filename, "%s.MODULE_BIN_PART", filename);

        FILE* file_read = fopen(filename, "r+b");
        FILE* file_write = fopen(backup_filename, "w+b");

        fread(backup_buffer, sizeof(char), sizeof(backup_buffer), file_read);
        fwrite(backup_buffer, sizeof(char), strlen(backup_buffer), file_write);

        fclose(file_read);
        fclose(file_write);
        /* */

        FILE* file_read_a = fopen(backup_filename, "r+b");

        char key_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_a[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char buffer_old_value[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_editedline[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char file_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};
        while(fgets(buffer_a, sizeof(buffer_a), file_read_a))
        {

            if(key_len + value_len + 2 < DINI_MODULE_MAX_STRING_SIZE && buffer_a[key_len+1] == '=')
            {
                strcpy(key_buffer, buffer_a);
                key_buffer[key_len] = '\0';
                if(strcmp(key, key_buffer) == 0)
                {
                    strcpy(buffer_old_value, &buffer_a[key_len+3]);
                    sprintf(buffer_editedline, "%s = %s", key, value_char);

                }
            }
        }
        fclose(file_read_a);
        /* */

        char buffer_b[DINI_MODULE_MAX_STRING_SIZE] = {0};
        int index = 0;

        FILE* file_read_b = fopen(backup_filename, "r+b");
        while(fgets(buffer_b, sizeof(buffer_b), file_read_b))
        {
            strcpy(file_lines[index], buffer_b);
            index++;
        }
        fclose(file_read_b);
        /* */

        char buffer_oldline[DINI_MODULE_MAX_STRING_SIZE] = {0};
        buffer_oldline[key_len+3+value_len] = '\0';

        sprintf(buffer_oldline, "%s = %s", key, buffer_old_value);

        /* */

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            if(strcmp(file_lines[i], buffer_oldline) == 0)
            {
                strcpy(file_lines[i], buffer_editedline);
            }
        }

        FILE* file_write_C = fopen(filename, "wb");

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            file_lines[i][strcspn(file_lines[i], "\r\n")] = 0;
            if(file_lines[i][0] != '\0')
            {
                fprintf(file_write_C, "%s\n", file_lines[i]);
            }
        }
        fclose(file_write_C);

        remove(backup_filename);
        return;
    }

    void dini_write::WriteBool(char *filename, char *key, bool *value)
    {
        int key_len = strlen(key);
        int value_len = 1;

        char backup_filename[DINI_MODULE_MAX_FILENAME_SIZE] = {0};
        char backup_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};

        sprintf(backup_filename, "%s.MODULE_BIN_PART", filename);

        FILE* file_read = fopen(filename, "r+b");
        FILE* file_write = fopen(backup_filename, "w+b");

        fread(backup_buffer, sizeof(char), sizeof(backup_buffer), file_read);
        fwrite(backup_buffer, sizeof(char), strlen(backup_buffer), file_write);

        fclose(file_read);
        fclose(file_write);
        /* */

        FILE* file_read_a = fopen(backup_filename, "r+b");

        char key_buffer[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_a[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char buffer_old_value[DINI_MODULE_MAX_STRING_SIZE] = {0};
        char buffer_editedline[DINI_MODULE_MAX_STRING_SIZE] = {0};

        char file_lines[DINI_MODULE_MAX_FILE_LINES][DINI_MODULE_MAX_STRING_SIZE] = {0};
        while(fgets(buffer_a, sizeof(buffer_a), file_read_a))
        {

            if(key_len + value_len + 2 < DINI_MODULE_MAX_STRING_SIZE && buffer_a[key_len+1] == '=')
            {
                strcpy(key_buffer, buffer_a);
                key_buffer[key_len] = '\0';
                if(strcmp(key, key_buffer) == 0)
                {
                    strcpy(buffer_old_value, &buffer_a[key_len+3]);
                    if(*value == true)
                    {
                        sprintf(buffer_editedline, "%s = 1", key);
                    }
                    else if(*value == false)
                    {
                        sprintf(buffer_editedline, "%s = 0", key);
                    }

                }
            }
        }
        fclose(file_read_a);
        /* */

        char buffer_b[DINI_MODULE_MAX_STRING_SIZE] = {0};
        int index = 0;

        FILE* file_read_b = fopen(backup_filename, "r+b");
        while(fgets(buffer_b, sizeof(buffer_b), file_read_b))
        {
            strcpy(file_lines[index], buffer_b);
            index++;
        }
        fclose(file_read_b);
        /* */

        char buffer_oldline[DINI_MODULE_MAX_STRING_SIZE] = {0};
        buffer_oldline[key_len+3+value_len] = '\0';

        sprintf(buffer_oldline, "%s = %s", key, buffer_old_value);

        /* */

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            if(strcmp(file_lines[i], buffer_oldline) == 0)
            {
                strcpy(file_lines[i], buffer_editedline);
            }
        }

        FILE* file_write_C = fopen(filename, "wb");

        for(int i = 0; i < DINI_MODULE_MAX_FILE_LINES; i++)
        {
            file_lines[i][strcspn(file_lines[i], "\r\n")] = 0;
            if(file_lines[i][0] != '\0')
            {
                fprintf(file_write_C, "%s\n", file_lines[i]);
            }
        }
        fclose(file_write_C);

        remove(backup_filename);
        return;
    }

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
