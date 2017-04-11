#ifndef TEXTURE_ANIMATION_H
#define TEXTURE_ANIMATION_H


class Texture_Animation
{
    public:
        Texture_Animation();
        Texture_Animation(int Tex_ID, int X_Count, int Y_Count, int T_Width, int T_Height, int Curr_Tile);
        virtual ~Texture_Animation();

        int Texture_ID;
        int Tile_X_Count = 1;
        int Tile_Y_Count = 1;
        int Current_Tile = 0;
        int Tile_Count;
        int Start_Tile = 0;
        int End_Tile = 0;
        int Tex_Width = 64;
        int Tex_Height = 64;

        void Set_Tiling(int X_Count, int Y_Count);
    protected:

    private:
};

#endif // TEXTURE_ANIMATION_H
