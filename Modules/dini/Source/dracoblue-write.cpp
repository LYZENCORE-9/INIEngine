#include "../Core/dracoblue-implementation.h"

namespace INIEngine::Module::Dini
{
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
}
