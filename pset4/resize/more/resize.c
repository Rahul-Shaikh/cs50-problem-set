// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensuring valid usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // storing the factor
    float f;
    sscanf(argv[1], "%f", &f);

    // ensures valid values of factor
    if (f < 0.0 || f > 100.0)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\nf must be between 0 and 100\n");
        return 1;
    }

    // if input okay then the program starts
    char *infile = argv[2];
    char *outfile = argv[3];
    FILE *inptr;
    FILE *outptr;

    // checks if the input file is opened fine
    if ((inptr = fopen(infile, "r")) == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // checks if the output file is created fine
    if ((outptr = fopen(outfile, "w")) == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // BITMAPFILEHEADER and BITMAPINFOHEADER read and write
    BITMAPFILEHEADER bf, bf_new;
    BITMAPINFOHEADER bi, bi_new;

    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bi.biSize != 40 || bf.bfOffBits != 54 || bf.bfType != 0x4d42 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    bf_new = bf; bi_new = bi;

    bi_new.biWidth = (int) floor(bi.biWidth * f);
    bi_new.biHeight = (int) floor(bi.biHeight * f);

    // calculating padding of new and old files
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_new.biSizeImage = abs(bi_new.biHeight) * (bi_new.biWidth * sizeof(RGBTRIPLE) + padding_new);
    bf_new.bfSize = 54 + bi_new.biSizeImage;

    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // resizing the image

    // storing the values in an array
    int rows = abs(bi.biHeight);

    RGBTRIPLE **inp = malloc(sizeof(RGBTRIPLE*) * rows);
    inp[0] = malloc(sizeof(RGBTRIPLE) * rows * bi.biWidth);
    for (int i = 1; i < rows; i++) inp[i] = inp[0] + i * bi.biWidth;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE temp;
            fread(&temp, sizeof(RGBTRIPLE), 1, inptr);
            inp[i][j] = temp;
        }

        // skips padding
        fseek(inptr, padding, SEEK_CUR);
    }

    int rows_new = abs(bi_new.biHeight);

    RGBTRIPLE **out = malloc(sizeof(RGBTRIPLE*) * rows_new);
    out[0] = malloc(sizeof(RGBTRIPLE) * rows_new * bi_new.biWidth);
    for (int i = 1; i < rows_new; i++) out[i] = out[0] + i * bi_new.biWidth;

    for (int i = 0; i < rows_new; i++)
    {
        for (int j = 0; j < bi_new.biWidth; j++)
        {
            out[i][j] = inp[(int) floorf(i/f)][(int) floorf(j/f)];
            fwrite(&out[i][j], sizeof(RGBTRIPLE), 1, outptr);
        }

        for (int k = 0; k < padding_new; k++) fputc(0x00, outptr);
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}