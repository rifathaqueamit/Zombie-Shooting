#include "Viewport_Manager.h"
#include "Rectangle.h"
#include "Scene.h"
#include "Camera.h"
#include "Utilities.h"
#include "Canvas.h"

Viewport_Manager::Viewport_Manager()
{
    //ctor
}

Viewport_Manager::~Viewport_Manager()
{
    //dtor
}

int Viewport_Manager::Add_Viewport(Rectangle2D R, Scene* V_Scene, Camera* V_Camera,Canvas* V_Canvas)
{
    Viewports.push_back(R);
    Viewports_Scene.push_back(V_Scene);
    Viewports_Camera.push_back(V_Camera);
    Viewports_Canvas.push_back(V_Canvas);
    return Viewports.size() - 1;
}

void Viewport_Manager::Render_Viewport(Texture_Manager& Tex_Man, Rectangle2D R, Scene* V_Scene, Camera* V_Camera,Canvas* V_Canvas, float elapsed_time)
{
    glViewport(R.X, R.Y, R.Width, R.Height);

    glMatrixMode(GL_PROJECTION);
    if (V_Camera->Projection_Type == 0){
        glLoadIdentity();
        gluPerspective(V_Camera->Field_Of_View, V_Camera->Aspect_Ratio, V_Camera->Near, V_Camera->Far);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(V_Camera->Position.X,V_Camera->Position.Y,V_Camera->Position.Z,V_Camera->Look_At.X,V_Camera->Look_At.Y,V_Camera->Look_At.Z,V_Camera->Up.X,V_Camera->Up.Y,V_Camera->Up.Z);

    //Get max render level
    int m = 0;
    for (int I = 0; I < V_Scene->Nodes.size(); I++)
    {
        if (m < V_Scene->Nodes[I]->Render_Level)
        {
            m = V_Scene->Nodes[I]->Render_Level;
        }
    }

    //Render all nodes according to render level
    for (int J = m; J >= 0; J--)
    {
          for (int I = 0; I < V_Scene->Nodes.size(); I++)
          {
             if (V_Scene->Nodes[I]->Render_Level == J) {
                Node* N = V_Scene->Nodes[I];
                N->Render(Tex_Man, elapsed_time);
             }
          }
    }



    V_Canvas->Render_All(R.Width, R.Height);
}

void Viewport_Manager::Render_All(Texture_Manager& Tex_Man, float elapsed_time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int I;
    for (I = 0; I < Viewports.size(); I++)
    {
        Render_Viewport(Tex_Man,Viewports[I], Viewports_Scene[I], Viewports_Camera[I],Viewports_Canvas[I],elapsed_time);
    }

    glFlush();
    glutSwapBuffers();
}
