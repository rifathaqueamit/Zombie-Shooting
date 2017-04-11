#include "Node.h"

#include "Vector.h"
#include "Mesh.h"
#include <vector>
#include <GL/glut.h>
//#include "Sprite_Mesh.h"

Node::Node()
{
    Position = Vector(0,0,0);
    Rotation = Vector(0,0,0);
    Scale = Vector(1,1,1);
    Mesh_Count = 0;
    Sprites_Count = 0;
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

void Node::Set_Sprite_Animation_End_Callback(void (*callback) (int))
{
    anim_end_callback = callback;
}

void Node::Set_Position(Vector V)
{
    Position = V;
    Collision_Box.Position = V;
}
void Node::Add_Mesh(Mesh m, Vector Pos, Vector Rot, Vector Scl)
{
    Attached_Meshes.push_back(m);
    Attached_Mesh_Position.push_back(Pos);
    Attached_Mesh_Rotation.push_back(Rot);
    Attached_Mesh_Scaling.push_back(Scl);
    Mesh_Count++;
}

void Node::Add_Sprite(Sprite_Mesh m, Vector Pos, Vector Rot, Vector Scl)
{
    Attached_Sprites.push_back(m);
    Sprite_Position.push_back(Pos);
    Sprite_Rotation.push_back(Rot);
    Sprite_Scaling.push_back(Scl);
    Sprites_Count++;
}

void Node::Render(Texture_Manager& Tex_Man, float elapsed_time)
{
    ////////////////////////////////////////////////////////////////////////
    //All Meshes
    /////////////////////////////////////////////////////////////////////////
    for (int I = 0; I < Mesh_Count; I++)
    {
        Mesh* M = &Attached_Meshes[I];

        glPushMatrix();

        //Node Transform
        glTranslatef(Position.X, Position.Y, Position.Z);

        glRotatef(Rotation.Z, 0.0f, 0.0f, 1.0f);
        glRotatef(Rotation.Y, 0.0f, 1.0f, 0.0f);
        glRotatef(Rotation.X, 1.0f, 0.0f, 0.0f);

        glScalef(Scale.X, Scale.Y, Scale.Z);

        //Attached Mesh Transform
        Vector P = Attached_Mesh_Position[I];
        Vector R = Attached_Mesh_Rotation[I];
        Vector S = Attached_Mesh_Scaling[I];

        glTranslatef(P.X, P.Y, P.Z);

        glRotatef(R.Z, 0.0f, 0.0f, 1.0f);
        glRotatef(R.Y, 0.0f, 1.0f, 0.0f);
        glRotatef(R.X, 1.0f, 0.0f, 0.0f);

        glScalef(S.X, S.Y, S.Z);

        if (M->Primitive_Type == GL_TRIANGLES)
        {
            int ID = 0;
            for (int K = 0; K < M->Face_Count; K++)
            {
                if (Enable_Texturing == true)
                {
                Tex_Man.Enable_Texturing();
                Tex_Man.Set_Current_Texture(M->Mesh_Textures[K]);
                }

                if (Enable_Culling == false)
                {
                    glDisable(GL_CULL_FACE);
                }

                if (Enable_Depth_Check == false)
                {
                    glDisable(GL_DEPTH_TEST);
                }

                glBegin(GL_TRIANGLES);

               Vertex V1 = M->Mesh_Vertices[M->Mesh_Indices[ID]];
               Vertex V2 = M->Mesh_Vertices[M->Mesh_Indices[ID+1]];
               Vertex V3 = M->Mesh_Vertices[M->Mesh_Indices[ID+2]];

               Vector N1 = M->Mesh_Normals[ID];
               Vector N2 = M->Mesh_Normals[ID+1];
               Vector N3 = M->Mesh_Normals[ID+2];

               glNormal3f(N1.X, N1.Y, N1.Z);

               glTexCoord2f(V1.U, V1.V);
               glColor4f(V1.V_Color.R,V1.V_Color.G, V1.V_Color.B, V1.V_Color.A);
               glVertex3f(V1.V_Position.X, V1.V_Position.Y, V1.V_Position.Z);
                glNormal3f(N2.X, N2.Y, N2.Z);
               glTexCoord2f(V2.U, V2.V);
               glColor4f(V2.V_Color.R,V2.V_Color.G, V2.V_Color.B, V2.V_Color.A);
               glVertex3f(V2.V_Position.X, V2.V_Position.Y, V2.V_Position.Z);
                 glNormal3f(N3.X, N3.Y, N3.Z);
               glTexCoord2f(V3.U, V3.V);
              glColor4f(V3.V_Color.R,V3.V_Color.G, V3.V_Color.B, V3.V_Color.A);
               glVertex3f(V3.V_Position.X, V3.V_Position.Y, V3.V_Position.Z);

               ID=ID+3;

               glEnd();

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
            }

        }

        glPopMatrix();
    }

    //////////////////////////////////////////////////////////////////////////
    //All Sprites
    ////////////////////////////////////////////////////////////////////////

    for (int I = 0; I < Sprites_Count; I++)
    {
        Sprite_Mesh* S_M = &Attached_Sprites[I];

        glPushMatrix();

        //Node Transform
        glTranslatef(Position.X, Position.Y, Position.Z);

        glRotatef(Rotation.Z, 0.0f, 0.0f, 1.0f);
        glRotatef(Rotation.Y, 0.0f, 1.0f, 0.0f);
        glRotatef(Rotation.X, 1.0f, 0.0f, 0.0f);

        glScalef(Scale.X, Scale.Y, Scale.Z);

        //Attached Sprite Transform
        Vector P = Sprite_Position[I];
        Vector R = Sprite_Rotation[I];
        Vector S = Sprite_Scaling[I];

        glTranslatef(P.X, P.Y, P.Z);

        glRotatef(R.Z, 0.0f, 0.0f, 1.0f);
        glRotatef(R.Y, 0.0f, 1.0f, 0.0f);
        glRotatef(R.X, 1.0f, 0.0f, 0.0f);

        glScalef(S.X, S.Y, S.Z);


        if (Enable_Texturing == true)
        {
            Tex_Man.Enable_Texturing();
            if (S_M->Animated == false)
                Tex_Man.Set_Current_Texture(S_M->Texture_ID);
            else
                Tex_Man.Set_Current_Texture(S_M->Animations[S_M->Current_Animation].Texture_ID);
        }

        if (Enable_Culling == false)
        {
            glDisable(GL_CULL_FACE);
        }

        if (Enable_Depth_Check == false)
        {
            glDisable(GL_DEPTH_TEST);
        }

        float hw = S_M->Sprite_Width/2;
        float hh = S_M->Sprite_Height/2;

        int Curr_Tile = S_M->Animations[S_M->Current_Animation].Current_Tile;
        int Tile_X = S_M->Animations[S_M->Current_Animation].Tile_X_Count;
        int Tile_Y = S_M->Animations[S_M->Current_Animation].Tile_Y_Count;
        int T_W = S_M->Animations[S_M->Current_Animation].Tex_Width;
        int T_H = S_M->Animations[S_M->Current_Animation].Tex_Height;
        int Tile_W = T_W / Tile_X;
        int Tile_H = T_H / Tile_Y;

        int X1,Y1,X2,Y2;

        int Row = (Curr_Tile)/Tile_X;
        int Col = Curr_Tile - (Row*Tile_X);

        X1 = Col * Tile_W;
        X2 = X1 + Tile_W;
        Y1 = Row * Tile_H;
        Y2 = Y1 + Tile_H;

        float NX1,NX2,NY1,NY2;

        NX1 = (float)X1 / (float)T_W;
        NX2 = (float)X2 / (float)T_W;
        NY1 = (float)Y1 / (float)T_H;
        NY2 = (float)Y2 / (float)T_H;

        NY1 = 1 - NY1;
        NY2 = 1 - NY2;

        glBegin(GL_QUADS);

        glColor4f(1,1,1,1);
        glNormal3f(0,0,1);

        glTexCoord2f(NX1,NY1);
        glVertex3f(-hw,-hh,0);

        glTexCoord2f(NX1,NY2);
        glVertex3f(hw,-hh,0);

        glTexCoord2f(NX2,NY2);
        glVertex3f(hw,hh,0);

        glTexCoord2f(NX2,NY1);
        glVertex3f(-hw,hh,0);

        glEnd();

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

        S_M->Update_Animation(elapsed_time);
        if (S_M->Animation_Ended == true)
        {
            if (anim_end_callback != NULL)
            {
                (*anim_end_callback)(I);
            }

            if (S_M->Loop_On == true)
            {
                S_M->Animation_Playing = true;
                S_M->Animation_Ended = false;
                S_M->Animations[S_M->Current_Animation].Current_Tile = S_M->Animations[S_M->Current_Animation].Start_Tile;
            }
        }

    }

}

Node::~Node()
{
    //dtor
}
