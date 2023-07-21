#include "config.h"

char* read_config(const char* path)
{
    FILE *f = fopen(path, "r");
    
    if(f == NULL)
    {
        printf("Error while opening read_config file");
        return NULL;
    }

    //reads the file one byte (character) at a time
    char* data = malloc(sizeof(char));
    uint8_t size = 1;
    uint8_t pos = 0;
    char c;

    while((c = fgetc(f)) != '*') 
    {
        data[pos++] = c;

        if(pos == size)
        {
            size++;
            data = realloc(data, size * sizeof(char));
        }
    }

    if(pos == 0)
    {
        free(data);
        fclose(f);
        return NULL;
    }

    data = realloc(data, (size + 1) * sizeof(char));
    data[size - 1] = '\0';

    fclose(f);

    return data;
}

void write_config(const char* path, char* data)
{
    FILE *f = fopen(path, "w");
    const char PORT_END = '*';

    if(strlen(data) != 0)
        fwrite(data, strlen(data), 1, f);

    fwrite(&PORT_END, 1, 1, f);

    fclose(f);
}
