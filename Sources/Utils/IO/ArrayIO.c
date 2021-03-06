#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ArrayIO.h"

Int32Array1D ArrayIO_Int32Array1D_ConstructFromStream(FILE *stream)
{
    int ret;
    Int32Array1D array;

    /* Read array size */
    ret = fread(&array.size, sizeof(int32_t), 1, stream);
    assert(ret == 1);

    /* Create array */
    array = Int32Array1D_Construct(array.size);

    /* Read array data */
    ret = fread(Int32Array1D_GetStorage(&array), sizeof(int32_t), array.size, stream);
    assert(ret == array.size);

    return array;
}

void ArrayIO_Int32Array1D_Printf(const Int32Array1D *me)
{
    printf("\nInt32Array1D");
    printf(" (%d)", me->size);

    for (int i=0; i < me->size && i < 8; i++)
    {
        printf("\n  %5d,", me->data[i]);
    }
}

UInt8Array2D ArrayIO_UInt8Array2D_ConstructFromFile(const char *filename)
{
    int ret;
    UInt8Array2D array;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    array = ArrayIO_UInt8Array2D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return array;
}

UInt8Array2D ArrayIO_UInt8Array2D_ConstructFromStream(FILE *stream)
{
    int ret;
    UInt8Array2D array;

    /* Read array size X, Y */
    ret = fread(&array.sizeX, sizeof(int32_t), 2, stream);
    assert(ret == 2);

    /* Create array */
    array = UInt8Array2D_Construct(array.sizeX, array.sizeY);

    /* Read array data */
    ret = fread(UInt8Array2D_GetStorage(&array), sizeof(uint8_t), array.sizeX * array.sizeY, stream);
    assert(ret == array.sizeX * array.sizeY);

    return array;
}

void ArrayIO_UInt8Array2D_Printf(const UInt8Array2D *me)
{
    printf("\nUInt8Array2D");
    printf(" (%dx%d)", me->sizeX, me->sizeY);

    for (int i=0; i < me->sizeX && i < 8; i++)
    {
        printf("\n");
        for (int j=0; j < me->sizeY && j < 8; j++)
        {
            printf(" %5d,", me->data[i][j]);
        }
        printf(" ...");
    }
}

FloatArray2D ArrayIO_FloatArray2D_ConstructFromFile(const char *filename)
{
    int ret;
    FloatArray2D array;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    array = ArrayIO_FloatArray2D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return array;
}

FloatArray2D ArrayIO_FloatArray2D_ConstructFromStream(FILE *stream)
{
    int ret;
    FloatArray2D array;

    /* Read array size X, Y */
    ret = fread(&array.sizeX, sizeof(int32_t), 2, stream);
    assert(ret == 2);

    /* Create array */
    array = FloatArray2D_Construct(array.sizeX, array.sizeY);

    /* Read array data */
    ret = fread(FloatArray2D_GetStorage(&array), sizeof(float), array.sizeX * array.sizeY, stream);
    assert(ret == array.sizeX * array.sizeY);

    return array;
}

void ArrayIO_FloatArray2D_Printf(const FloatArray2D *me)
{
    printf("\nUInt8Array2D");
    printf(" (%dx%d)", me->sizeX, me->sizeY);

    for (int i=0; i < me->sizeX && i < 8; i++)
    {
        printf("\n");
        for (int j=0; j < me->sizeY && j < 8; j++)
        {
            printf(" %f,", me->data[i][j]);
        }
        printf(" ...");
    }
}

PointArray2D ArrayIO_Point2D_ConstructFromFile(const char *filename)
{
    int ret;
    PointArray2D array;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    array = ArrayIO_PointArray2D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return array;
}

PointArray2D ArrayIO_PointArray2D_ConstructFromStream(FILE *stream)
{
    int ret;
    PointArray2D array;

    /* Read array size X */
    ret = fread(&array.size, sizeof(int32_t), 1, stream);
    assert(ret == 1);

    /* Create array */
    array = PointArray2D_Construct(array.size);

    for (int i=0; i< array.size; i++)
    {
       int32_t length;
       ret = fread(&length, sizeof(int32_t), 1, stream);

       assert(ret == 1);
       PointArray1D *row = PointArray2D_ConstructRow(&array, i,length);
       int *data = calloc(length, sizeof(int32_t) * 2);
       assert(data != NULL);
       ret = fread(data, sizeof(int32_t) * 2, length, stream);
       Point * array = PointArray1D_GetStorage(row);
       for (int i = 0; i < length; i++)
       {
           array[i].x = data[i * 2];
           array[i].y = data[i * 2+1];
       }
       free(data);
       assert(ret == length);
    }

    return array;
}

void ArrayIO_PointArray2D_Printf(const PointArray2D *me)
{
    printf("\nPointArray2D");
    printf(" (%dx)", me->size);

    for (int i=0; i < me->size && i < 8; i++)
    {
        PointArray1D *inner = me->data[i];
        printf("\n (%d)", inner->size);
        
        for (int j=0; j < inner->size && j < 8; j++)
        {
            printf(" (%d, %d),", inner->data[j].x, inner->data[j].y);
        }
        printf(" ...");
    }
}

Int16Array3D ArrayIO_Int16Array3D_ConstructFromFile(const char *filename)
{
    int ret;
    Int16Array3D array;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    array = ArrayIO_Int16Array3D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return array;
}

Int16Array3D ArrayIO_Int16Array3D_ConstructFromStream(FILE *stream)
{
    int ret;
    Int16Array3D array;

    /* Read array size X, Y, Z */
    ret = fread(&array.sizeX, sizeof(int32_t), 3, stream);
    assert(ret == 3);

    /* Create array */
    array = Int16Array3D_Construct(array.sizeX, array.sizeY, array.sizeZ);

    /* Read array data */
    ret = fread(Int16Array3D_GetStorage(&array), sizeof(int16_t), array.sizeX * array.sizeY * array.sizeZ, stream);
    assert(ret == array.sizeX * array.sizeY * array.sizeZ);

    return array;
}

void ArrayIO_Int16Array3D_Printf(const Int16Array3D *me)
{
    printf("\nInt16Array3D");
    printf(" (%dx%dx%d)", me->sizeX, me->sizeY, me->sizeZ);

    for (int i=0; i < me->sizeX && i < 8; i++)
    {
        for (int j=0; j < me->sizeY && j < 8; j++)
        {
            printf("\n  i=%d, j=%d: ", i, j);
            for (int k=0; k < me->sizeZ; k++)
                printf(" %5d,", me->data[i][j][k]);
            printf(" ...");
        }
    }
}

UInt8Array2D ArrayIO_UInt8Array2D_Transpose(const UInt8Array2D *input)
{
    UInt8Array2D output = UInt8Array2D_Construct(input->sizeY, input->sizeY);
    
    for(int y = 0; y < input->sizeY; y++) 
    {
        for(int x = 0; x < input->sizeX; x++) 
        {
            output.data[y][x] = input->data[x][y];
        }
    }
    
    return output;
}

