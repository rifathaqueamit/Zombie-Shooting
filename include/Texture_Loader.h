#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <GL/glut.h>
#include "Color.h"

struct Image_Data
{
        unsigned long Size_X;
        unsigned long Size_Y;
        char *Data;
};

class Texture_Loader
{
    public:
        Texture_Loader();
        virtual ~Texture_Loader();

        int Load_Bitmap(char *Filename, Image_Data *Out_Image_Data);

    protected:

    private:
};

#endif // TEXTURE_LOADER_H
