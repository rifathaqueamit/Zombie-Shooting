#include "Bounding_Box.h"
#include "Vector.h"
#include "Utilities.h"
#include <math.h>

Bounding_Box::Bounding_Box()
{
    Min = Vector(0,0,0);
    Max = Vector(0,0,0);
}

Collision2D_Result Bounding_Box::Circle_Collision(Vector2 Circle_Center_Old, Vector2 Circle_Center_New, float Circle_Radius)
{
    float player_new_x = Circle_Center_New.X;
    float player_new_y = Circle_Center_New.Y;

    float player_dir_x = player_new_x - Circle_Center_Old.X;
    float player_dir_y = player_new_y - Circle_Center_Old.Y;

    float radius = Circle_Radius;

    Collision2D_Result R;

    for (int i = 0; i < 4; i++)
    {

        Vector2 L1;
        Vector2 L2;

        if (i == 0)
        {
        L1 = Vector2(Min.X + Position.X,Min.Y + Position.Y);
        L2 = Vector2(Min.X + Position.X,Max.Y + Position.Y);
        }else if (i == 1)
        {
        L1 = Vector2(Min.X+ Position.X,Min.Y+ Position.Y);
        L2 = Vector2(Max.X+ Position.X,Min.Y+ Position.Y);
        }else if (i == 2)
        {
        L1 = Vector2(Max.X+ Position.X,Min.Y+ Position.Y);
        L2 = Vector2(Max.X+ Position.X,Max.Y+ Position.Y);
        } else if (i == 3)
        {
        L1 = Vector2(Max.X+ Position.X,Max.Y+ Position.Y);
        L2 = Vector2(Min.X+ Position.X,Max.Y+ Position.Y);
        }

        bool interse = Utilities::line_circle_intersection(L1,L2,Vector2( Circle_Center_Old.X, Circle_Center_Old.Y), radius);

        if (interse == true)
        {
            float dx = L2.X-L1.X;
            float dy = L2.Y-L1.Y;

            Vector2 normal1 = Vector2(-dy,dx);
            Vector2 normal2 = Vector2(dy,-dx);

            float d =( Circle_Center_Old.X - L1.X)*(L2.Y-L1.Y) - ( Circle_Center_Old.Y-L1.Y)*(L2.X-L1.X);

            normal1.X = -normal1.X;
            normal1.Y = -normal1.Y;
            normal2.X = -normal2.X;
            normal2.Y = -normal2.Y;

            Vector2 wall_dir;

            if (d >= 0){
                wall_dir = Vector2(player_dir_x - normal2.X, player_dir_y - normal2.Y);
            }
            else
            {
                wall_dir = Vector2(player_dir_x - normal1.X, player_dir_y - normal1.Y);
            }

            float mag = sqrt(wall_dir.X*wall_dir.X + wall_dir.Y*wall_dir.Y);
            wall_dir.X = wall_dir.X / mag;
            wall_dir.Y = wall_dir.Y / mag;

            R.Collision = true;
            R.L1 = L1;
            R.L2 = L2;
            R.Line_Index = i;
            R.Out_Normal = wall_dir;

            return R;
        }
    }

    R.Collision = false;
    R.L1 = Vector2(0,0);
    R.L2 = Vector2(0,0);
    R.Line_Index = -1;
    R.Out_Normal = Vector2(0,0);

    return R;
}

bool Bounding_Box::Check_Collision(Bounding_Box B2)
{
    Vector P1 = Position;
    Vector P2 = B2.Position;

    if (Max.X + P1.X >= B2.Min.X + P2.X && Min.X + P1.X <= B2.Max.X + P2.X)
    {
       if (Max.Y + P1.Y >= B2.Min.Y + P2.Y && Min.Y + P1.Y <= B2.Max.Y + P2.Y)
       {
             if (Max.Z + P1.Z >= B2.Min.Z + P2.Z && Min.Z + P1.Z <= B2.Max.Z + P2.Z)
             {
                 return true;
             }
       }
    }

    return false;
}

Bounding_Box::Bounding_Box(Vector Min_V, Vector Max_V)
{
    Min = Min_V;
    Max = Max_V;
}

Bounding_Box::~Bounding_Box()
{
    //dtor
}
