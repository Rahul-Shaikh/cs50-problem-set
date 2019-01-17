#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int8_t is_jpg_start(uint8_t *buffer, int8_t flag);

int main(int argc, char *argv[])
{
    // ensures correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // opens the raw file
    char *in = argv[1];
    FILE *fptr = fopen(in, "rb");

    if (fptr == NULL)
    {
        fprintf(stderr, "%s file is not opened properly.\n", in);
        return 2;
    }

    // declares a buffer which will store temporary the block of memories 512B is one block
    uint8_t *buffer = malloc(sizeof(int8_t) * 512);
    int data_read = fread(buffer, 1, 512, fptr);
    int count = 0;

    // flag variable stores the information if i am in the jpeg file content or not
    int8_t flag = 0;
    flag = is_jpg_start(buffer, flag);

    // main program
    FILE *jpg = NULL;
    char *filename = malloc(sizeof(char) * 8);
    while(!feof(fptr))
    {
        if (count == 0 && flag == 1)
        {
            sprintf(filename, "%03i.jpg", count++);
            jpg = fopen(filename, "wb");
        }

        if (count != 0 && flag == 0)
        {
            fclose(jpg);
            sprintf(filename, "%03i.jpg", count++);
            jpg = fopen(filename, "wb");
            flag = 1;
        }

        if (flag)
        {
            fwrite(buffer, 1, data_read, jpg);
        }

        data_read = fread(buffer, 1, 512, fptr);
        flag = is_jpg_start(buffer, flag);
    }
    fclose(jpg);
    return 0;
}

int8_t is_jpg_start(uint8_t *buffer, int8_t flag)
{
    // changes flag according with encounter of jpeg files starting bytes
    if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
    {
        if (flag == 0) flag = 1;
        else flag = 0;
    }
    return flag;
}