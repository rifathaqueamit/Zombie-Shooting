#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H
#include "Vector.h"
#include "Texture_Manager.h"
#include "Bounding_Box.h"

class Sprite_Node
{
    public:
        Sprite_Node();
        virtual ~Sprite_Node();

        Vector Position;
        Vector Rotation;
        Vector Scale;
        void Set_Position(Vector V);

        void Render(Texture_Manager& Tex_Man);
        int Tag_ID;
        int Tag_Int_1;
        int Tag_Int_2;
        float Tag_Float_1;
        bool Enable_Texturing;
        bool Enable_Culling;
        bool Enable_Depth_Check;
        int Render_Level;

        int Collision_Shape = 0; //0 = Bounding Box
        Bounding_Box Collision_Box;
        bool Update_Bounding_Box = true;

    protected:

    private:
};

#endif // SPRITE_NODE_H
