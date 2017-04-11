#include "Texture_Animation.h"

Texture_Animation::Texture_Animation()
{
    Texture_ID = -1;
    Tile_X_Count = 1;
    Tile_Y_Count = 1;
    Current_Tile = 0;
    Tile_Count = 1;
    Start_Tile = 0;
    End_Tile = 0;
    Tex_Width = 64;
    Tex_Height = 64;
}

Texture_Animation::Texture_Animation(int Tex_ID, int X_Count, int Y_Count, int T_Width, int T_Height, int Curr_Tile)
{
    Texture_ID = Tex_ID;
    Tile_X_Count = X_Count;
    Tile_Y_Count = Y_Count;
    Current_Tile = Curr_Tile;
    Tile_Count = Tile_X_Count * Tile_Y_Count;
    Start_Tile = 0;
    End_Tile = Tile_Count - 1;
    Tex_Width = T_Width;
    Tex_Height = T_Height;
}

void Texture_Animation::Set_Tiling(int X_Count, int Y_Count)
{
    Tile_X_Count = X_Count;
    Tile_Y_Count = Y_Count;
    Tile_Count = Tile_X_Count * Tile_Y_Count;
    if (Current_Tile >= Tile_Count){
        Current_Tile = Tile_Count - 1;
    }
    if (End_Tile >= Tile_Count)
    {
        End_Tile = Tile_Count - 1;
    }
}

Texture_Animation::~Texture_Animation()
{
    //dtor
}
