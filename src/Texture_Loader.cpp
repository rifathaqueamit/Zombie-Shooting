#include "Texture_Loader.h"
#include <GL/glut.h>
#include <stdio.h>
#include "Color.h"

Texture_Loader::Texture_Loader()
{
    //ctor
}

Texture_Loader::~Texture_Loader()
{
    //dtor
}


int Texture_Loader::Load_Bitmap(char* Filename, Image_Data* Out_Image_Data)
{
    FILE *file;
    unsigned long size; //size of the image in bytes
    unsigned long i; //standard counter
    unsigned short int planes; //number of planes in Image(must be 1)
    unsigned short int bpp; //number of bits per pixel(must be 24)
    char temp; //temporary color storage for bgr-rgb conversion

    //make sure the file in here
    file = fopen(Filename, "rb");
    if(file==NULL)
    {
        printf("Can't open file!");
    }

   //seek through the bmp header, up to width/height
    fseek(file,18,SEEK_CUR);

    //read the width
    i = fread(&Out_Image_Data->Size_X,4,1,file);
    //read the height
    i = fread(&Out_Image_Data->Size_Y,4,1,file);
  //size = Out_Image_Data->Size_X* Out_Image_Data->Size_Y * 3;
    size = Out_Image_Data->Size_X * Out_Image_Data->Size_Y * 3;

    //read the plane
    fread(&planes, 2, 1, file);
    //read the bits per pixel
    fseek(file, 24, SEEK_CUR);
    //read the data
    char* read_data = (char*)malloc(size);
    Out_Image_Data->Data = (char*)malloc(size);

    //i=fread(Out_Image_Data->Data, size, 1, file);
    i = fread(read_data, size, 1, file);
    int id = 0;

    for(i=0;i<size;i+=3) //reverse all ol color bgr -> rgb
    {
        //temp = Out_Image_Data->Data[i];
        // Out_Image_Data->Data[i] = Out_Image_Data->Data[i+2];
        //Out_Image_Data->Data[i+2] = temp;
        temp = read_data[id];
        read_data[id] = read_data[id+2];
        read_data[id+2] = temp;

        Out_Image_Data->Data[i] = read_data[id];
        Out_Image_Data->Data[i+1] = read_data[id+1];
        Out_Image_Data->Data[i+2] = read_data[id+2];

        id = id + 3;
    }

    return 1;
}
