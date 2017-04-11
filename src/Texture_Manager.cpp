#include "Texture_Manager.h"
#include "SOIL.h"

Texture_Manager::Texture_Manager(int Number_Of_Textures)
{
    Max_Textures = Number_Of_Textures;
    glGenTextures(Max_Textures,Textures);
    Tex_Count = 0;
}

Texture_Manager::~Texture_Manager()
{
    //dtor
}

int Texture_Manager::Add_Texture(char* File_Name)
{
    GLuint tex_2d = SOIL_load_OGL_texture
	(
		File_Name,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[Tex_Count] = tex_2d;

	Mag_Filter[Tex_Count] = GL_LINEAR;
	Min_Filter[Tex_Count] = GL_LINEAR;
	WrapS[Tex_Count] = GL_REPEAT;
	WrapT[Tex_Count] = GL_REPEAT;

	Tex_Count++;
	return Tex_Count - 1;
}

int Texture_Manager::Add_Texture(Image_Data* Data)
{
    glBindTexture(GL_TEXTURE_2D,Textures[Tex_Count]);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Data->Size_X,Data->Size_Y,0,GL_RGB,GL_UNSIGNED_BYTE,Data->Data);

    Mag_Filter[Tex_Count] = GL_LINEAR;
	Min_Filter[Tex_Count] = GL_LINEAR;
	WrapS[Tex_Count] = GL_REPEAT;
	WrapT[Tex_Count] = GL_REPEAT;

    Tex_Count++;
    return Tex_Count-1;
}

void Texture_Manager::Set_MAG_Filter(int ID, GLint Parameter)
{
    Mag_Filter[ID] = Parameter;

    //glBindTexture(GL_TEXTURE_2D,Textures[ID]);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Parameter);
}

void Texture_Manager::Set_MIN_Filter(int ID, GLint Parameter)
{
    Min_Filter[ID] = Parameter;

    //glBindTexture(GL_TEXTURE_2D,Textures[ID]);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Parameter);
}

void Texture_Manager::Set_WRAP(int ID, GLint Wrap_T, GLint Wrap_S)
{
    WrapS[ID] = Wrap_S;
    WrapT[ID] = Wrap_T;
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
}

GLuint Texture_Manager::Get_Texture(int ID)
{
    return Textures[ID];
}

void Texture_Manager::Enable_Texturing()
{
    glEnable(GL_TEXTURE_2D);
}

void Texture_Manager::Disable_Texturing()
{
    glDisable(GL_TEXTURE_2D);
}

void Texture_Manager::Set_Current_Texture(int ID)
{
    glBindTexture(GL_TEXTURE_2D, Textures[ID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mag_Filter[ID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Min_Filter[ID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS[ID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT[ID]);
}
