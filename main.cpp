#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "Mesh.h"
#include "Node.h"
#include "Texture_Loader.h"
#include "Texture_Manager.h"
#include "Viewport_Manager.h"
#include "stdio.h"
#include <vector>
#include "Bounding_Box.h"
#include "Utilities.h"

#define PI 3.14159265359

//Globals
Texture_Loader Tex_Loader;
Texture_Manager Tex_Man(20);


struct Zombie_Type
{
    public:
    int Zombie_Power;

    int Zombie_Move_Texture;
    int Zombie_Attack_Texture;

    int Zombie_Move_Tile_X;
    int Zombie_Move_Tile_Y;

    int Zombie_Attack_Tile_X;
    int Zombie_Attack_Tile_Y;

    int Zombie_Move_Tex_Width;
    int Zombie_Move_Tex_Height;

    int Zombie_Attack_Tex_Width;
    int Zombie_Attack_Tex_Height;

    int Zombie_Move_End_Tile;
    int Zombie_Attack_End_Tile;

    float Zombie_Speed;

    Zombie_Type(int Pow, int Move_Tex_ID,int Attack_Tex_ID, float Spd, int Move_Tile_X, int Move_Tile_Y, int Attack_Tile_X, int Attack_Tile_Y, int Move_T_Width, int Move_T_Height, int Attack_T_Width, int Attack_T_Height, int Move_End_Tile, int Attack_End_Tile)
    {
        Zombie_Power = Pow;
        Zombie_Speed = Spd;

        Zombie_Attack_Texture = Attack_Tex_ID;
        Zombie_Attack_Tile_X = Attack_Tile_X;
        Zombie_Attack_Tile_Y = Attack_Tile_Y;
        Zombie_Attack_Tex_Width = Attack_T_Width;
        Zombie_Attack_Tex_Height = Attack_T_Height;
        Zombie_Attack_End_Tile = Attack_End_Tile;
        Zombie_Move_Texture = Move_Tex_ID;
        Zombie_Move_Tile_X = Move_Tile_X;
        Zombie_Move_Tile_Y = Move_Tile_Y;
        Zombie_Move_Tex_Width = Move_T_Width;
        Zombie_Move_Tex_Height = Move_T_Height;
        Zombie_Move_End_Tile = Move_End_Tile;
    }
};

//Image_Data* Bitmap_1;

int Texture_1;
int Texture_2;
int Texture_3;
int Texture_4;
int Laser_Texture;
int Zombie_Texture;
int Fence_Texture;
int Zombie_Walk_Texture;
int Zombie_Attack_Texture;
int Zombie2_Walk_Texture;
int Zombie2_Attack_Texture;
int Road_Texture;

float rotation = 0;

float camera_x = 0;
float camera_y = 0;
float camera_zoom = 10;

float stage_size_x = 25;
float stage_size_y = 25;

float player_x = 0;
float player_y = 0;
float player_size_x = 1;
float player_size_y = 1;
float player_accel_x = 0;
float player_accel_y = 0;
float player_speed = 0.6;
int player_health = 300;
int player_score = 0;
int accel_direction = 0;

Node Player_Node;

vector<Node*> Zombies;
int Number_Of_Zombies = 0;

vector<Node*> Buildings;
int Number_Of_Buildings = 0;

vector<Vector2> Zombie_Spawn_Places;
int Number_Of_Spawn_Places = 0;

vector<Zombie_Type> Zombie_Types;
int Number_Of_Zombie_Types = 0;

vector<Node*> Fences;
int Number_Of_Fences = 0;

Mesh Splat_Quad;
int Splat_Texture;
vector<Node*> Splats;
int Number_Of_Splats;

Node Zombie_Node;

Node Ground_Node;
Node Building_Node;
Node Road_Node;

Mesh Player_Quad;
Mesh Zombie_Quad;
Mesh Ground_Quad;
Mesh Building_Mesh_1;
Mesh Building_Mesh_2;
Mesh Bullet_Quad;
Mesh Road_Quad;

Scene Scene_1;
Camera Camera_1;
Camera Camera_2;
Canvas Canvas_1;
//Text_UI Mouse_Location_Text(100);
Text_UI Other_Text(100);
Text_UI Score_Text(100);
//Box_UI Box_1;

Viewport_Manager V_M;

int Viewport_1;
int Viewport_2;
int Viewport_3;
int Viewport_4;

float ar = 1;
int lwidth;
int lheight;

bool left_pressed = false;
int mouse_x;
int mouse_y;

vector<Node*> Fire_Bullets;

int Zombie_Respawn_Time = 500;
int Fire_Ready_Time = 0;

int oldTimeSinceStart = 0;

int game_state = 0;
int high_score = 0;
bool game_end = false;

void mouse_left_pressed(int x, int y);

void Add_Spawn_Place(Vector2 place)
{
    Zombie_Spawn_Places.push_back(place);
    Number_Of_Spawn_Places++;
}

void Add_Zombie_Type(Zombie_Type T)
{
    Zombie_Types.push_back(T);
    Number_Of_Zombie_Types++;
}

int rand_int_range(int min_v, int max_v)
{
    return min_v + (rand() % (max_v - min_v + 1));
}

void Add_Fence(float position_x, float position_y,float position_z, int length_count, float height, float per_length, int direction, float center_x, float center_z, int fence_texture)
{
    Mesh* F = new Mesh();
    for (int i = 0; i < length_count; i++)
    {
        if (direction == 0) {
        F->Add_Quad(Vertex(Vector(-center_x + per_length*i,0,-center_z + height), Color(1,1,1,1), 0,0),
                   Vertex(Vector(-center_x + per_length*i + per_length,0,-center_z + height), Color(1,1,1,1), 0,1),
                   Vertex(Vector(-center_x + per_length*i + per_length,0,-center_z), Color(1,1,1,1), 1,1),
                   Vertex(Vector(-center_x + per_length*i,0,-center_z), Color(1,1,1,1), 1,0), fence_texture);

            F->Add_Quad(Vertex(Vector(-center_x + per_length*i,0.1,-center_z + height), Color(1,1,1,1), 0,0),
                   Vertex(Vector(-center_x + per_length*i + per_length,0.1,-center_z + height), Color(1,1,1,1), 0,1),
                   Vertex(Vector(-center_x + per_length*i + per_length,-0.1,-center_z + height), Color(1,1,1,1), 1,1),
                   Vertex(Vector(-center_x + per_length*i,-0.1,-center_z + height), Color(1,1,1,1), 1,0), fence_texture);



        }
        else
        {
        F->Add_Quad(Vertex(Vector(0,-center_x + per_length*i,-center_z + height), Color(1,1,1,1), 0,0),
                   Vertex(Vector(0,-center_x + per_length*i + per_length,-center_z + height), Color(1,1,1,1), 0,1),
                   Vertex(Vector(0,-center_x + per_length*i + per_length,-center_z), Color(1,1,1,1), 1,1),
                   Vertex(Vector(0,-center_x + per_length*i,-center_z), Color(1,1,1,1), 1,0), fence_texture);

        F->Add_Quad( Vertex(Vector(0.1,-center_x + per_length*i,-center_z + height), Color(1,1,1,1), 0,0),
                   Vertex(Vector(0.1,-center_x + per_length*i + per_length,-center_z + height), Color(1,1,1,1), 0,1),
                   Vertex(Vector(-0.1,-center_x + per_length*i + per_length,-center_z + height), Color(1,1,1,1), 1,1),
                   Vertex(Vector(-0.1,-center_x + per_length*i,-center_z + height), Color(1,1,1,1), 1,0), fence_texture);


        }
    }

    Node* F_N = new Node();
    F_N->Enable_Culling = false;
    F_N->Render_Level = 2;
    F_N->Add_Mesh(*F, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    if (direction == 0)
        F_N->Collision_Box = Bounding_Box(Vector(-center_x,-0.1,-center_z), Vector(-center_x + per_length*length_count,0.1,-center_z +height));
    else
        F_N->Collision_Box = Bounding_Box(Vector(-0.1,-center_x,-center_z), Vector(0.1,-center_x + per_length*length_count,-center_z +height));

    F_N->Set_Position(Vector(position_x,position_y,position_z));

    Scene_1.Add_Node(F_N);
    Fences.push_back(F_N);
    Number_Of_Fences++;


}

void Add_Building(float position_x, float position_y)
{
    Node* B_N = new Node();
    B_N->Add_Mesh(Building_Mesh_1, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    B_N->Add_Mesh(Building_Mesh_2, Vector(0,0,1.25),Vector(0,0,0), Vector(1,1,1));
    B_N->Set_Position(Vector(position_x,position_y,1));
    B_N->Collision_Box = Bounding_Box(Vector(-1,-1,-1),Vector(1,1,1));
    B_N->Set_Position(Vector(position_x,position_y,1));
    B_N->Render_Level = 2;
    Buildings.push_back(B_N);
    Scene_1.Add_Node(B_N);
    Number_Of_Buildings++;
}

void Add_Splat(float position_x, float position_y, float position_z, float Time_To_Dissapear, float rot)
{
    Node* Splat_Node = new Node();
    Splat_Node->Render_Level = 2;
    Splat_Node->Add_Mesh(Splat_Quad, Vector(0,0,0), Vector(0,0,rot), Vector(1,1,1));
    Splat_Node->Set_Position(Vector(position_x,position_y,position_z));
    Splat_Node->Tag_Float_1 = Time_To_Dissapear;
    Splats.push_back(Splat_Node);
    Scene_1.Add_Node(Splat_Node);
    Number_Of_Splats++;
}

void Update_Splats(float delta_time)
{
    for (int I = Number_Of_Splats - 1; I>= 0; I--)
    {
        if (Splats[I]->Tag_Float_1 > 0)
        {
            Splats[I]->Tag_Float_1 = Splats[I]->Tag_Float_1 - delta_time;
        }
        else
        {
            Scene_1.Find_And_Delete_Node(Splats[I]);
            Splats.erase(Splats.begin() + I);
            Number_Of_Splats--;
        }
    }
}

void Add_Zombie(int pos_x,int pos_y, Zombie_Type T)
{
    Sprite_Mesh S_M = Sprite_Mesh(1.5,1.5,Texture_Animation(T.Zombie_Move_Texture,T.Zombie_Move_Tile_X,T.Zombie_Move_Tile_Y,T.Zombie_Move_Tex_Width,T.Zombie_Move_Tex_Height,0),true,20);
    S_M.Animations[0].End_Tile = T.Zombie_Move_End_Tile;
    S_M.Play_Animation();
    S_M.Loop_On = true;
    S_M.Add_Animation(Texture_Animation(T.Zombie_Attack_Texture, T.Zombie_Attack_Tile_X, T.Zombie_Attack_Tile_Y, T.Zombie_Attack_Tex_Width, T.Zombie_Attack_Tex_Height,0));

    Node* Zombie_Node = new Node();
    Zombie_Node->Render_Level = 1;

    Zombie_Node->Add_Sprite(S_M, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));

    Zombie_Node->Collision_Box = Bounding_Box(Vector(-0.25,-0.25,-0.25),Vector(0.25,0.25,0.25));
    Zombie_Node->Set_Position(Vector(pos_x,pos_y,0));

    Zombie_Node->Tag_Int_1 = T.Zombie_Power;
    Zombie_Node->Tag_Float_1 = T.Zombie_Speed;

    Zombies.push_back(Zombie_Node);
    Scene_1.Add_Node(Zombie_Node);
    Number_Of_Zombies++;
}

void Spawn_Zombie()
{
    int r_indx = rand_int_range(0, Number_Of_Zombie_Types -1);
    Zombie_Type T = Zombie_Types[r_indx];

    int r_s_indx = rand_int_range(0, Number_Of_Spawn_Places-1);
    Vector2 P = Zombie_Spawn_Places[r_s_indx];

    Add_Zombie(P.X, P.Y, T);
}

void Game_Over()
{
    game_state = 0;
    sprintf(Score_Text.Text, "Player High Score : %d", high_score);
    Other_Text.Set_Text("DEAD ! Press Space to Quit");
    game_end = true;
}

void Hurt()
{
    player_health = player_health - 10;
    if (player_health < 0){
        player_health = 0;
        if (player_score > high_score)
            high_score = player_score;
        Game_Over();
    }
}

void Update_Zombies(int delta_time)
{
    for (int i = Number_Of_Zombies -1; i >= 0; i--){
        Node* Zombie_Node = Zombies[i];

        float x2 = player_x - Zombie_Node->Position.X;
        float y2 = player_y - Zombie_Node->Position.Y;

        float r = 0;
        if (x2 >= 0)
            r = 90 + 180 + atan((float)y2/(float)x2) * 180.0 / PI;
        else
            r = 90 + atan((float)y2/(float)x2) * 180.0 / PI;

        if (x2 == 0)
        {
            if (y2 == 0)
            {
                r = 0;
            }
        }

        Zombie_Node->Rotation = Vector(0,0,r);
        Vector Pos = Zombie_Node->Position;
        float x = Pos.X + cos((r+90)*PI/180.0)*Zombie_Node->Tag_Float_1*(float)delta_time;
        float y = Pos.Y + sin((r+90)*PI/180.0)*Zombie_Node->Tag_Float_1*(float)delta_time;
        float z = Pos.Z;

        float d = (player_x - Pos.X) * (player_x - Pos.X) + (player_y - Pos.Y) * (player_y - Pos.Y);
        if (sqrt(d) < 1)
        {
            x = Pos.X;
            y = Pos.Y;

            if (Zombie_Node->Attached_Sprites[0].Current_Animation != 1)
                Zombie_Node->Attached_Sprites[0].Set_Current_Animation(1);

            if (Zombie_Node->Tag_Int_2 <= 0)
            {
                Hurt();
                Zombie_Node->Tag_Int_2 = 100;
            }
            else
            {
                Zombie_Node->Tag_Int_2 = Zombie_Node->Tag_Int_2 - 1;
            }
        }
        else
        {
            if (Zombie_Node->Attached_Sprites[0].Current_Animation != 0)
                Zombie_Node->Attached_Sprites[0].Set_Current_Animation(0);
        }


        float zombie_accel_x = (x - Pos.X);
        float zombie_accel_y = (y - Pos.Y);
        if (zombie_accel_x < 0) zombie_accel_x = -zombie_accel_x;
        if (zombie_accel_y < 0) zombie_accel_y = -zombie_accel_y;

        float total_deflection_x = 0;
        float total_deflection_y = 0;
        bool one_collision = false;

        for (int j = 0; j < Number_Of_Buildings; j++)
        {

            Collision2D_Result r = Buildings[j]->Collision_Box.Circle_Collision(Vector2(Pos.X, Pos.Y), Vector2(x, y), 0.4);

            if (r.Collision == true)
            {
                total_deflection_x = total_deflection_x + r.Out_Normal.X;
                total_deflection_y = total_deflection_y + r.Out_Normal.Y;
                one_collision = true;
            }

        }

        for (int j = 0; j < Number_Of_Zombies; j++)
        {
            if (i == j) break;
            Collision2D_Result r = Zombies[j]->Collision_Box.Circle_Collision(Vector2(Pos.X, Pos.Y), Vector2(x, y), 0.4);

            if (r.Collision == true)
            {
                total_deflection_x = total_deflection_x + r.Out_Normal.X;
                total_deflection_y = total_deflection_y + r.Out_Normal.Y;
                one_collision = true;
            }

        }

        for (int j = 0; j < Number_Of_Fences; j++)
        {

            Collision2D_Result r = Fences[j]->Collision_Box.Circle_Collision(Vector2(Pos.X, Pos.Y), Vector2(x, y), 0.4);

            if (r.Collision == true)
            {
                total_deflection_x = total_deflection_x + r.Out_Normal.X;
                total_deflection_y = total_deflection_y + r.Out_Normal.Y;
                one_collision = true;
            }

        }
        if (one_collision == true){
            x = Pos.X + total_deflection_x * zombie_accel_x * (float)delta_time;
            y = Pos.Y + total_deflection_y * zombie_accel_y * (float)delta_time;
            one_collision = false;
        }

        Zombie_Node->Set_Position(Vector(x,y,z));

        if (Zombie_Node->Tag_Int_1 <= 0) {
            Scene_1.Find_And_Delete_Node(Zombie_Node);
            player_score = player_score + 10;
            Zombies.erase(Zombies.begin() + i);
            Number_Of_Zombies--;

            //Create blood splat
            Add_Splat(x,y,0,100000,rand_int_range(0,359));
        }
    }
}

static void resize(int width, int height)
{
     ar = (float) width / (float) height;
     lwidth = width;
     lheight = height;

     /////////////////////////////////////////////////////////////////////////////////////
     V_M.Viewports[Viewport_1].Width = width;
     V_M.Viewports[Viewport_2].Height = height;
     Canvas_1.Set_Center(-width/2,-height/2 + 15);   //Left Top is the corner

     Camera_1.Aspect_Ratio = ar;
}

void Update_Bullets(float bullet_speed, int delta_time)
{
    if (Fire_Bullets.size() > 0)
    {
        for (int i = Fire_Bullets.size() - 1; i >= 0; i--)
        {
            Node* F = Fire_Bullets[i];
            if (F->Tag_Int_1 > 0)
            {
                F->Tag_Int_1 = F->Tag_Int_1 - 1;
                Vector P = F->Position;
                P.X = P.X + cos((F->Rotation.Z+90) * PI / 180.0) * bullet_speed * (float)delta_time;
                P.Y = P.Y + sin((F->Rotation.Z+90) * PI / 180.0) * bullet_speed * (float)delta_time;
                F->Set_Position(P);

                //Check collision
                for (int j = Number_Of_Zombies - 1; j >= 0; j--)
                {
                    if (F->Collision_Box.Check_Collision(Zombies[j]->Collision_Box) == true)
                    {
                        F->Tag_Int_1 = 0;
                        Zombies[j]->Tag_Int_1 = Zombies[j]->Tag_Int_1 - 20;
                        if (Zombies[j]->Tag_Int_1 < 0){
                            Zombies[j]->Tag_Int_1 = 0;
                        }
                        else
                        {
                            Add_Splat(P.X,P.Y,0,50000,rand_int_range(0,359));
                        }
                        break;
                    }
                }

                //Check collision Buildings
                for (int j = Number_Of_Buildings - 1; j >= 0; j--)
                {
                    if (F->Collision_Box.Check_Collision(Buildings[j]->Collision_Box) == true)
                    {
                        F->Tag_Int_1 = 0;
                        break;
                    }
                }

            }
            else
            {
                Scene_1.Find_And_Delete_Node(F);
                Fire_Bullets.erase(Fire_Bullets.begin() + i);
            }
        }
    }
}

static void display(void)
{
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;

    float player_new_x;
    float player_new_y;

    if (game_state == 1){

    player_accel_x = player_accel_x * 0.98;
    player_accel_y = player_accel_y * 0.98;

    if (accel_direction == 0)
    {
        player_new_x = player_x + cos((rotation+90)*PI/180.0) * player_accel_x * (float)deltaTime * player_speed;
        player_new_y = player_y + sin((rotation+90)*PI/180.0) * player_accel_y * (float)deltaTime * player_speed;
    }
    else if (accel_direction == 1)
    {
        player_new_x = player_x + cos((rotation)*PI/180.0) * player_accel_x * (float)deltaTime * player_speed;
        player_new_y = player_y + sin((rotation)*PI/180.0) * player_accel_y * (float)deltaTime * player_speed;

    }

    float total_deflection_x = 0;
    float total_deflection_y = 0;
    bool one_collision = false;

    for (int i = 0; i < Number_Of_Buildings; i++)
    {

        Collision2D_Result r = Buildings[i]->Collision_Box.Circle_Collision(Vector2(player_x, player_y), Vector2(player_new_x, player_new_y), 0.4);

        if (r.Collision == true)
        {
            total_deflection_x = total_deflection_x + r.Out_Normal.X;
            total_deflection_y = total_deflection_y + r.Out_Normal.Y;
            one_collision = true;
        }

    }


    for (int i = 0; i < Number_Of_Zombies; i++)
    {

        Collision2D_Result r = Zombies[i]->Collision_Box.Circle_Collision(Vector2(player_x, player_y), Vector2(player_new_x, player_new_y), 0.4);

        if (r.Collision == true)
        {
            total_deflection_x = total_deflection_x + r.Out_Normal.X;
            total_deflection_y = total_deflection_y + r.Out_Normal.Y;
            one_collision = true;
        }

    }


    for (int i = 0; i < Number_Of_Fences; i++)
    {

        Collision2D_Result r = Fences[i]->Collision_Box.Circle_Collision(Vector2(player_x, player_y), Vector2(player_new_x, player_new_y), 0.4);

        if (r.Collision == true)
        {
            total_deflection_x = total_deflection_x + r.Out_Normal.X;
            total_deflection_y = total_deflection_y + r.Out_Normal.Y;
            one_collision = true;
        }

    }


    if (one_collision == true){


    if (player_accel_x < 0) player_accel_x = -player_accel_x;
    if (player_accel_y < 0) player_accel_y = -player_accel_y;

    player_new_x = player_x + total_deflection_x * player_accel_x * (float)deltaTime * player_speed;
    player_new_y = player_y + total_deflection_y * player_accel_y * (float)deltaTime * player_speed;
    one_collision = false;
    }

    if (player_new_x > 50)
    {
        player_new_x = 50;
    }else if (player_new_x < -50)
    {
        player_new_x = -50;
    }

    if (player_new_y > 50)
    {
        player_new_y = 50;
    }else if (player_new_y < -50)
    {
        player_new_y = -50;
    }

    player_x = player_new_x;
    player_y = player_new_y;
    camera_x = player_x;
    camera_y = player_y;

    }

    Camera_1.Position = Vector(camera_x, camera_y, camera_zoom);
    Camera_1.Look_At = Vector(camera_x, camera_y, camera_zoom - 0.001);

    Player_Node.Set_Position(Vector(player_x, player_y, 1));
    Player_Node.Rotation = Vector(0,0,rotation);

    if (game_state == 1) {
    sprintf(Other_Text.Text, "Player Health : %d", player_health);
    sprintf(Score_Text.Text, "Player Score : %d", player_score);


    Update_Bullets(0.03, deltaTime);
    Update_Zombies(deltaTime);
    Update_Splats(deltaTime);

    if (Zombie_Respawn_Time < 0)
    {
        Spawn_Zombie();
        //Add_Zombie(rand_int_range(-10,10),rand_int_range(-10,10));
        Zombie_Respawn_Time = 200;
    }
    else
    {
        Zombie_Respawn_Time = Zombie_Respawn_Time - 1;
    }

    if (Fire_Ready_Time > 0)
    {
        Fire_Ready_Time = Fire_Ready_Time - deltaTime/20.0;
    }
    else
    {
        Fire_Ready_Time = 0;
    }

    if (left_pressed == true)
        mouse_left_pressed(mouse_x, mouse_y);
    }


    //////////////////////////////////////////////////////////////////////////////
    V_M.Render_All(Tex_Man, (float)deltaTime);

}



void Fire()
{
    if (Fire_Ready_Time > 0)
        return;

    Node* Fire_Node = new Node();
    Fire_Node->Add_Mesh(Bullet_Quad,Vector(0,0,0),Vector(0,0,0),Vector(1,1,1));
    Fire_Node->Position = Vector(camera_x - cos((rotation-45)*PI/180.0)*0.5,camera_y - sin((rotation-45)*PI/180.0)*0.5, 0.5);
    Fire_Node->Tag_ID = 1;
    Fire_Node->Tag_Int_1 = 150;
    Fire_Node->Rotation = Vector(0,0,rotation);
    Fire_Node->Collision_Box = Bounding_Box(Vector(-0.25,-0.25,-0.25),Vector(0.25,0.25,25));
    Scene_1.Add_Node(Fire_Node);
    Fire_Bullets.push_back(Fire_Node);

    Fire_Ready_Time = 15;
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'j':
            camera_x = camera_x - 0.1;
            break;
        case 'l':
            camera_x = camera_x + 0.1;
            break;
        case 'i':
            camera_y = camera_y + 0.1;
            break;
        case 'k':
            camera_y = camera_y - 0.1;
            break;
        case 'o':
            camera_zoom = camera_zoom - 0.1;
            break;
        case 'p':
            camera_zoom = camera_zoom + 0.1;
            break;
        case 'w':
            if (game_state == 1){
            accel_direction = 0;
            player_accel_x = player_accel_x + 0.001;
            player_accel_y = player_accel_y + 0.001;
            if (player_accel_x > 0.1)
                player_accel_x = 0.1;
            if (player_accel_y > 0.1)
                player_accel_y = 0.1;
            }
            break;
        case 's':
            if (game_state == 1){
            accel_direction = 0;
            player_accel_x = player_accel_x - 0.001;
            player_accel_y = player_accel_y - 0.001;
            if (player_accel_x < -0.1)
                player_accel_x = -0.1;
            if (player_accel_y < -0.1)
                player_accel_y = -0.1;
            }
            break;
        case 'd':
            if (game_state == 1){
            accel_direction = 1;
            player_accel_x = player_accel_x + 0.001;
            player_accel_y = player_accel_y + 0.001;
            if (player_accel_x > 0.1)
                player_accel_x = 0.1;
            if (player_accel_y > 0.1)
                player_accel_y = 0.1;
            }
            break;
        case 'a':
            if (game_state == 1){
            accel_direction = 1;
            player_accel_x = player_accel_x - 0.001;
            player_accel_y = player_accel_y - 0.001;
            if (player_accel_x < -0.1)
                player_accel_x = -0.1;
            if (player_accel_y < -0.1)
                player_accel_y = -0.1;
            break;
            }
        case 32:
            if (game_state == 0){
                if (game_end == true)
                {
                    exit(1);
                    break;
                }
                game_state = 1;
            }
            break;
    }

    glutPostRedisplay();
}

static void mouse_move(int x,int y)
{
    if (game_state == 1){
    int x2 = lwidth/2 - x;
    int y2 = lheight/2 - y;

    if (x2 >= 0)
        rotation = 90 + atan((float)-y2/(float)x2) * 180.0 / PI;
    else
        rotation = 90 + 180 + atan((float)-y2/(float)x2) * 180.0 / PI;

    if (x2 == 0)
    {
        if (y2 == 0)
        {
            rotation = 0;
        }
    }
    }
    //sprintf(Mouse_Location_Text.Text, "Mouse Location : %d,%d", x,y);
}

static void idle(void)
{
    glutPostRedisplay();
}

static void mouse_motion(int x, int y)
{
    if (game_state == 1){
    int x2 = lwidth/2 - x;
    int y2 = lheight/2 - y;

    if (x2 >= 0)
        rotation = 90 + atan((float)-y2/(float)x2) * 180.0 / PI;
    else
        rotation = 90 + 180 + atan((float)-y2/(float)x2) * 180.0 / PI;

    //sprintf(Mouse_Location_Text.Text, "Mouse Location : %d,%d", x,y);
    }
}

void mouse_left_down(int x, int y)
{
    if (game_state == 1){
    mouse_x = x;
    mouse_y = y;

    mouse_left_pressed(x,y);
    }
}

void mouse_left_pressed(int x, int y)
{
    if (game_state == 1){
    Fire();
    }
}

void mouse_left_up(int x, int y)
{

}

static void mouse_func(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse_x = x;
        mouse_y = y;
        mouse_left_down(x,y);
        left_pressed = true;

        //Fire();
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        left_pressed = false;
        mouse_left_up(x,y);
    }
}
/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Zombie Shooting");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutPassiveMotionFunc(mouse_move);
    glutMotionFunc(mouse_motion);
    glutMouseFunc(mouse_func);
    glutIdleFunc(idle);

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_ALPHA_TEST);

    //glDepthMask(GL_TRUE);

    ///////////////////////////////////////////////////////////////////////
    //Load a sample bitmap
    ///////////////////////////////////////////////////////////////////////
   // Bitmap_1 = (Image_Data*) malloc(sizeof(Image_Data));
   //  if (Tex_Loader.Load_Bitmap("C:\\Users\\Amit\\Desktop\\floor.bmp", Bitmap_1) == 0)
   // {
   //      return 0;
   // }
    //delete[] Bitmap_1->Data;

    ///////////////////////////////////////////////////////////////////////
    //Add Texture
    ///////////////////////////////////////////////////////////////////////
    //Texture_2 = Tex_Man.Add_Texture(Bitmap_1);
   // Tex_Man.Set_MAG_Filter(Texture_2, GL_LINEAR);
    //Tex_Man.Set_MIN_Filter(Texture_2, GL_LINEAR);
    //////////////////////////////////////////////////////////////////////////////////
    Scene_1 = Scene();

    Camera_1 = Camera();

    Canvas_1 = Canvas();

    //Mouse_Location_Text.Set_Text("Mouse Location : ");
    //Mouse_Location_Text.Position = Vector2(0,0);


    Other_Text.Set_Text("Press Space to Start");
    Other_Text.Position = Vector2(0,50);
   // Other_Text.Text_Color = Color(1,1,1,1);

    Score_Text.Set_Text("Zombie Shooter By Rifat Haque Amit");
    Score_Text.Position = Vector2(0,0);

    //Canvas_1.Add_Text_UI(&Mouse_Location_Text);
    Canvas_1.Add_Text_UI(&Other_Text);
    Canvas_1.Add_Text_UI(&Score_Text);
    //Canvas_1.Add_Box_UI(&Box_1);

   // Camera_2 = Camera();

    //Camera_2.Position = Vector(0,-4,5);
    //Camera_2.Look_At = Vector(0,0,0);

    V_M = Viewport_Manager();
    Viewport_1 = V_M.Add_Viewport(Rectangle2D(0,0,800,600), &Scene_1, &Camera_1, &Canvas_1);
   // Viewport_2 = V_M.Add_Viewport(Rectangle2D(640/2,0,640/2,480/2), &Scene_1, &Camera_1, &Canvas_1);
    //Viewport_3 = V_M.Add_Viewport(Rectangle2D(0,480/2,640/2,480/2), &Scene_1, &Camera_2, &Canvas_1);
    //Viewport_4 = V_M.Add_Viewport(Rectangle2D(640/2,480/2,640/2,480/2), &Scene_1, &Camera_2, &Canvas_1);
    //////////////////////////////////////////////////////////////////////////////////
    Texture_1 = Tex_Man.Add_Texture("player_shotgun.png");
    Texture_2 = Tex_Man.Add_Texture("grass_1.jpg");
    Texture_3 = Tex_Man.Add_Texture("building.bmp");
    Texture_4 = Tex_Man.Add_Texture("roof_2.jpg");
    Laser_Texture = Tex_Man.Add_Texture("Green_laser.png");
    Zombie_Texture = Tex_Man.Add_Texture("Zombie_1.png");
    Fence_Texture = Tex_Man.Add_Texture("fence.png");
    Splat_Texture = Tex_Man.Add_Texture("blood_splat.png");
    Zombie_Walk_Texture = Tex_Man.Add_Texture("zombie_walk.png");
    Zombie_Attack_Texture = Tex_Man.Add_Texture("zombie_attack.png");
    Zombie2_Walk_Texture = Tex_Man.Add_Texture("zombie_walk_2.png");
    Zombie2_Attack_Texture = Tex_Man.Add_Texture("zombie_attack_2.png");

    Road_Texture = Tex_Man.Add_Texture("road.jpg");

    Tex_Man.Set_WRAP(Texture_2, GL_REPEAT, GL_REPEAT);
    Tex_Man.Set_WRAP(Texture_4, GL_REPEAT, GL_REPEAT);
    Tex_Man.Set_WRAP(Zombie_Walk_Texture, GL_REPEAT, GL_REPEAT);



    /////////////////////////////////////////////////////////////////////////
    Player_Quad = Mesh();
    Player_Quad.Add_Quad(Vertex(Vector(-0.5,-0.5,0), Color(1,1,1,1), 0, 0),Vertex(Vector(0.5,-0.5,0), Color(1,1,1,1), 0, 1),Vertex(Vector(0.5,0.5,0), Color(1,1,1,1), 1, 1),Vertex(Vector(-0.5,0.5,0), Color(1,1,1,1), 1, 0),Texture_1);
    ///////////////////////////////////////////////////////////////////////
    Zombie_Quad = Mesh();
    Zombie_Quad.Add_Quad(Vertex(Vector(-0.5,-0.5,0), Color(1,1,1,1), 0, 0),Vertex(Vector(0.5,-0.5,0), Color(1,1,1,1), 0, 1),Vertex(Vector(0.5,0.5,0), Color(1,1,1,1), 1, 1),Vertex(Vector(-0.5,0.5,0), Color(1,1,1,1), 1, 0),Zombie_Texture);
    //////////////////////////////////////////////////////////////////////
    Ground_Quad = Mesh();
    Ground_Quad.Add_Quad(Vertex(Vector(-70,-70,0), Color(1,1,1,1), 0, 0),Vertex(Vector(70,-70,0), Color(1,1,1,1), 0, 30),Vertex(Vector(70,70,0), Color(1,1,1,1), 30, 30),Vertex(Vector(-70,70,0), Color(1,1,1,1), 30, 0),Texture_2);

    Road_Quad = Mesh();
    Road_Quad.Add_Quad(Vertex(Vector(-70,-4,0), Color(1,1,1,1), 0, 0),Vertex(Vector(70,-4,0), Color(1,1,1,1), 30, 0),Vertex(Vector(70,4,0), Color(1,1,1,1), 30, 1),Vertex(Vector(-70,4,0), Color(1,1,1,1), 0, 1),Road_Texture);


    Bullet_Quad = Mesh();
    Bullet_Quad.Add_Quad(Vertex(Vector(-0.25,-0.25,0), Color(1,1,1,1), 0, 0),Vertex(Vector(0.25,-0.25,0), Color(1,1,1,1), 0, 1),Vertex(Vector(0.25,0.25,0), Color(1,1,1,1), 1, 1),Vertex(Vector(-0.25,0.25,0), Color(1,1,1,1), 1, 0),Laser_Texture);

    Splat_Quad = Mesh();
    Splat_Quad.Add_Quad(Vertex(Vector(-0.5,-0.5,0), Color(1,1,1,1), 0, 0),Vertex(Vector(0.5,-0.5,0), Color(1,1,1,1), 0, 1),Vertex(Vector(0.5,0.5,0), Color(1,1,1,1), 1, 1),Vertex(Vector(-0.5,0.5,0), Color(1,1,1,1), 1, 0), Splat_Texture);

    //////////////////////////////////////////////////////////////////////////
    Building_Mesh_1 = Mesh();
    Building_Mesh_1.Create_Box(2,2,2,Color(1,1,1,1),Texture_3);
    //////////////////////////////////////////////////////////////////////////
    Building_Mesh_2 = Mesh();
    Building_Mesh_2.Create_Box(2,2,0.5,Color(1,1,1,1),Texture_4);
    //////////////////////////////////////////////////////////////////////////
    Player_Node = Node();
    Player_Node.Add_Mesh(Player_Quad, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    //////////////////////////////////////////////////////////////////////////
    //Zombie_Node = Node();
    //Zombie_Node.Add_Mesh(Zombie_Quad, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    //Zombie_Node.Set_Position(Vector(2,0,0));
    //Zombie_Node.Collision_Box = Bounding_Box(Vector(-0.25,-0.25,-0.25),Vector(0.25,0.25,0.25));
    ///////////////////////////////////////////////////////////////////////////
    Ground_Node = Node();
    Ground_Node.Render_Level = 2;
    Ground_Node.Add_Mesh(Ground_Quad, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    ///////////////////////////////////////////////////////////////////////////
    Road_Node = Node();
    Road_Node.Render_Level = 2;
    Road_Node.Add_Mesh(Road_Quad, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    Road_Node.Add_Mesh(Road_Quad, Vector(0,0,0), Vector(0,0,90), Vector(1,1,1));
    Road_Node.Add_Mesh(Road_Quad, Vector(0,45,0), Vector(0,0,0), Vector(1,1,1));
    Road_Node.Add_Mesh(Road_Quad, Vector(45,0,0), Vector(0,0,90), Vector(1,1,1));
    Road_Node.Add_Mesh(Road_Quad, Vector(0,-45,0), Vector(0,0,0), Vector(1,1,1));
    Road_Node.Add_Mesh(Road_Quad, Vector(-45,0,0), Vector(0,0,90), Vector(1,1,1));
    ///////////////////////////////////////////////////////////////////////////
    Scene_1.Add_Node(&Ground_Node);
    Scene_1.Add_Node(&Road_Node);

    Add_Fence(3.5,3.5,-0.5,10,1,1,0,0,0,Fence_Texture);
    Add_Fence(3.5,3.5,-0.5,10,1,1,1,0,0,Fence_Texture);

    Add_Fence(-3.5,-3.5,-0.5,10,1,1,0,10,0,Fence_Texture);
    Add_Fence(-3.5,-3.5,-0.5,10,1,1,1,10,0,Fence_Texture);

    Add_Fence(3.5,-3.5,-0.5,10,1,1,0,0,0,Fence_Texture);
    Add_Fence(3.5,-3.5,-0.5,10,1,1,1,10,0,Fence_Texture);

    Add_Fence(-3.5,3.5,-0.5,10,1,1,0,10,0,Fence_Texture);
    Add_Fence(-3.5,3.5,-0.5,10,1,1,1,0,0,Fence_Texture);


    //Player_Node.Enable_Depth_Check = false;
    Scene_1.Add_Node(&Player_Node);

    Add_Building(5,5);
    Add_Building(7,5);
    Add_Building(5,7);
    Add_Building(5,-5);
    Add_Building(7,-5);
    Add_Building(5,-7);

    Add_Building(-5,5);
    Add_Building(-7,5);
    Add_Building(-5,7);
    Add_Building(-5,-5);
    Add_Building(-7,-5);
    Add_Building(-5,-7);

    for (int b = 0; b < 5; b++)
    {
        for (int c = 0; c < 5; c++)
        {
            Add_Building(15 + b*5,15 + c*5);
             Add_Building(-15 - b*5,15 + c*5);
              Add_Building(15 + b*5,-15 - c*5);
               Add_Building(-15 - b*5,-15 - c*5);
        }
    }

    Add_Spawn_Place(Vector2(0,45));
    Add_Spawn_Place(Vector2(45,45));
    Add_Spawn_Place(Vector2(45,0));
    Add_Spawn_Place(Vector2(45,-45));

    Add_Spawn_Place(Vector2(0,-45));
    Add_Spawn_Place(Vector2(-45,-45));
    Add_Spawn_Place(Vector2(-45,0));
    Add_Spawn_Place(Vector2(-45,-45));

    Add_Spawn_Place(Vector2(-23,24));
    Add_Spawn_Place(Vector2(25,23));
    Add_Spawn_Place(Vector2(26,-24));
    Add_Spawn_Place(Vector2(-27,-24));


    Add_Zombie_Type(Zombie_Type(50, Zombie_Walk_Texture,Zombie_Attack_Texture, 0.0016,3,6,3,3,864,1866,954,882,16,8));
    Add_Zombie_Type(Zombie_Type(150, Zombie_Walk_Texture,Zombie_Attack_Texture, 0.0008,3,6,3,3,864,1866,954,882,16,8));
    Add_Zombie_Type(Zombie_Type(100, Zombie2_Walk_Texture,Zombie2_Attack_Texture, 0.0032,3,6,3,3,864,1866,954,882,16,8));
    Add_Zombie_Type(Zombie_Type(300, Zombie2_Walk_Texture,Zombie2_Attack_Texture, 0.0016,3,6,3,3,864,1866,954,882,16,8));

    /*
    Sprite_Mesh S_M = Sprite_Mesh(1.5,1.5,Texture_Animation(Zombie_Walk_Texture,3,6,864,1866,0),true,20);
    S_M.Animation.End_Tile = 16;

    S_M.Play_Animation();
    S_M.Loop_On = true;

    Node* Sprite_Node = new Node();
    Sprite_Node->Add_Sprite(S_M, Vector(0,0,0), Vector(0,0,0), Vector(1,1,1));
    Scene_1.Add_Node(Sprite_Node);
    */

    //Scene_1.Add_Node(&Building_Node);
    //Scene_1.Add_Node(&Zombie_Node);
    //////////////////////////////////////////////////////////////////////////
    //Add_Zombie(0,0);
    game_state = 0;

    glutMainLoop();

    return EXIT_SUCCESS;
}
