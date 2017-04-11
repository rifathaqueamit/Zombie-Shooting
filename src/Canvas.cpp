#include "Canvas.h"
#include "Text_UI.h"
//#include "Box_UI.h"

Canvas::Canvas()
{
    canvas_center_x = 0;
    canvas_center_y = 0;
    canvas_width = 800;
    canvas_height = 600;
}

Canvas::~Canvas()
{
    //dtor
}

int Canvas::Add_Text_UI(Text_UI* T)
{
    UI_Texts.push_back(T);
    return UI_Texts.size() - 1;
}

//int Canvas::Add_Box_UI(Box_UI* T)
//{
//    UI_Boxes.push_back(T);
//    return UI_Boxes.size() - 1;
//}

void Canvas::Render_All(int view_width, int view_height)
{
    int s_x, s_y;
    if (use_viewport_size == true)
    {
        s_x = view_width;
        s_y = view_height;
    }
    else
    {
        s_x = canvas_width;
        s_y = canvas_height;
    }

   // for (int i = 0; i < UI_Boxes.size(); i++)
    //{
   //     UI_Boxes[i]->Render_Box(s_x,s_y,canvas_center_x,canvas_center_y);
   // }


    for (int i = 0; i < UI_Texts.size(); i++)
    {
        UI_Texts[i]->Render_Text(s_x,s_y,canvas_center_x,canvas_center_y);
    }
}

Text_UI* Canvas::Get_Text_UI(int ID)
{
    return UI_Texts[ID];
}

//Box_UI* Canvas::Get_Box_UI(int ID)
//{
//    return UI_Boxes[ID];
//}


void Canvas::Set_Center(int x, int y)
{
    canvas_center_x = x;
    canvas_center_y = y;
}

void Canvas::Set_Size(int width, int height)
{
    canvas_width = width;
    canvas_height = height;
}

