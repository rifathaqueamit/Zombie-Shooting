#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <Texture_Loader.h>

using namespace std;

class Texture_Manager
{
    public:
        Texture_Manager(int Number_Of_Texture);
        virtual ~Texture_Manager();

        GLuint Textures[100];

        //Texture Params
        GLint Mag_Filter[100];
        GLint Min_Filter[100];
        GLint WrapT[100];
        GLint WrapS[100];


        int Add_Texture(Image_Data* Img);
        int Add_Texture(char* File_Name);

        GLuint Get_Texture(int ID);

        void Set_MAG_Filter(int ID, GLint Parameter);
        void Set_MIN_Filter(int ID, GLint Parameter);
        void Set_WRAP(int ID, GLint Wrap_T, GLint Wrap_S);

        void Enable_Texturing();
        void Disable_Texturing();
        void Set_Current_Texture(int ID);

    protected:

    private:
        int Max_Textures;
        int Tex_Count;
};

#endif // TEXTURE_MANAGER_H
