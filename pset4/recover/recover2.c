#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // Opens the rFile
    FILE* rFile = fopen("card.raw", "r");

    // Checks for errors in opening rFile and terminates program
    if (rFile == NULL)
    {
        printf("Error opening rFile");
        return 0;
    }

    // Sets the blocksize (depends on the filesystem)
    int blockSize = 512;

    // allocates space for buffer on heap
    uint8_t* buf = malloc(blockSize);

    // image counter
    int icount = 0;

    // write file
    FILE* wFile = NULL;

    // iterates through content of rFile in size buf
    while (fread(buf, blockSize, 1, rFile))
    {

        // Check if the first four bytes are JPG signature
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff
            && (buf[3] == 0xe0 || buf[3] == 0xe1))
        {
            // Close the file, if opened
            if (wFile != NULL)
                fclose(wFile);

            // Determine name of new file
            char filename[8];
            sprintf(filename, "%03d_2.jpg", icount);

            // Open new JPG for Writing
            wFile = fopen(filename, "w");

            // Iterates the filename icount
            icount++;
        }

        // Write blocksize to file
        if (wFile != NULL)
            fwrite(buf, blockSize, 1, wFile);
    }

    // Close the current file if exists
    if (wFile != NULL)
        fclose(wFile);

    // Frees buffer on heap
    free(buf);

    // Close read file
    fclose (rFile);

}