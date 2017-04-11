#include "Sprite_Node.h"

#include "Node.h"
#include "Vector.h"
#include <vector>
#include <GL/glut.h>

Sprite_Node::Sprite_Node()
{
    Position = Vector(0,0,0);
    Rotation = Vector(0,0,0);
    Scale = Vector(1,1,1);

    Enable_Texturing = true;
    Enable_Culling = true;
    Tag_ID = 0;
    Tag_Int_1 = 0;
    Tag_Float_1 = 0;
    Tag_Int_2 = 0;
    Render_Level = 0;
    Enable_Depth_Check = true;
    Collision_Box = Bounding_Box(Vector(-0.5,-0.5,-0.5),Vector(0.5,0.5,0.5));
}

void Sprite_Node::Set_Position(Vector V)
{
    Position = V;
    Collision_Box.Position = V;
}


void Sprite_Node::Render(Texture_Manager& Tex_Man)
{
    //for (int I = 0; I < Mesh_Count; I++)
    //{
        glPushMatrix();

        //Node Transform
        glTranslatef(Position.X, Position.Y, Position.Z);

        glRotatef(Rotation.Z, 0.0f, 0.0f, 1.0f);
        glRotatef(Rotation.Y, 0.0f, 1.0f, 0.0f);
        glRotatef(Rotation.X, 1.0f, 0.0f, 0.0f);

        glScalef(Scale.X, Scale.Y, Scale.Z);

        //Attached Mesh Transform

               if (Enable_Texturing == true)
               {

                   Tex_Man.Disable_Texturing();
               }

               if (Enable_Culling == false)
               {
                   glEnable(GL_CULL_FACE);
               }

               if (Enable_Depth_Check == false)
               {
                   glEnable(GL_DEPTH_TEST);
               }
        glPopMatrix();
    //}

}

Sprite_Node::~Sprite_Node()
{
    //dtor
}
