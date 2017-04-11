#ifndef SPRITE_MESH_H
#define SPRITE_MESH_H
#include "Texture_Animation.h"
#include <vector>
using namespace std;

class Sprite_Mesh
{
    public:
        Sprite_Mesh(float S_Width, float S_Height, Texture_Animation Anim, bool Anim_On, float Anim_Speed);
        virtual ~Sprite_Mesh();

        float Sprite_Width;
        float Sprite_Height;

        bool Animated = false;

        int Texture_ID;
        //Texture_Animation Animation;

        bool Animation_On = false;
        float Animation_Speed = 1;
        float Time_Per_Frame = 1000;
        bool Loop_On = true;

        bool Animation_Playing = false;
        bool Animation_Ended = false;

        void Play_Animation();
        void Pause_Animation();
        void Stop_Animation();
        void Update_Animation(float elapsed_time);

        vector<Texture_Animation> Animations;
        int Current_Animation = 0;
        void Set_Current_Animation(int ID);
        int Add_Animation(Texture_Animation T);

    protected:

    private:
        float passed_time = 0;
};

#endif // SPRITE_MESH_H
