#include "Sprite_Mesh.h"
#include "Texture_Animation.h"

Sprite_Mesh::Sprite_Mesh(float S_Width, float S_Height, Texture_Animation Anim, bool Anim_On, float Anim_Speed)
{
    Sprite_Width = S_Width;
    Sprite_Height = S_Height;
    //Animation = Anim;
    Texture_ID = Anim.Texture_ID;
    Animated = Anim_On;
    Animation_Speed = Anim_Speed;
    Animations.push_back(Anim);
    Current_Animation = 0;
}

void Sprite_Mesh::Play_Animation()
{
    if (Animated == false) return;
    if (Animation_Playing == false && Animation_Ended == false)
    {
        Animation_Playing = true;
    }
}
void Sprite_Mesh::Pause_Animation()
{
    if (Animated == false) return;
    if (Animation_Playing == true)
    {
        Animation_Playing = false;
    }
}

void Sprite_Mesh::Stop_Animation()
{
    if (Animated == false) return;
    Animation_Playing = false;
    Animation_Ended = false;
    Animations[Current_Animation].Current_Tile = 0;
}
void Sprite_Mesh::Set_Current_Animation(int ID)
{
    Current_Animation = ID;
    if (Current_Animation >= Animations.size())
    {
        Current_Animation = Animations.size() - 1;
    }
}

int Sprite_Mesh::Add_Animation(Texture_Animation T)
{
    Animations.push_back(T);
}


void Sprite_Mesh::Update_Animation(float elapsed_time)
{
    if (Animated == false) return;
    if (Animation_Playing == true)
    {
        passed_time = passed_time + elapsed_time*Animation_Speed;
        if (passed_time > Time_Per_Frame)
        {
            passed_time = 0;

            if (Animations[Current_Animation].End_Tile >= Animations[Current_Animation].Tile_Count)
                Animations[Current_Animation].End_Tile = Animations[Current_Animation].Tile_Count - 1;

            if (Animations[Current_Animation].Start_Tile > Animations[Current_Animation].End_Tile)
                Animations[Current_Animation].Start_Tile = Animations[Current_Animation].End_Tile;

            if (Animations[Current_Animation].Current_Tile >= Animations[Current_Animation].End_Tile - 1)
            {
                Animation_Playing = false;
                Animation_Ended = true;
            }
            else
            {
                Animations[Current_Animation].Current_Tile = Animations[Current_Animation].Current_Tile + 1;
            }
        }
    }
}

Sprite_Mesh::~Sprite_Mesh()
{
    //dtor
}
