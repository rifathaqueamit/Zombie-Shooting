#ifndef VIEWPORT_MANAGER_H
#define VIEWPORT_MANAGER_H
#include <vector>
#include "Rectangle.h"
#include "Scene.h"
#include "Camera.h"
#include "Canvas.h"

class Viewport_Manager
{
    public:
        Viewport_Manager();
        virtual ~Viewport_Manager();

        vector<Rectangle2D> Viewports;
        vector<Scene*> Viewports_Scene;
        vector<Camera*> Viewports_Camera;
        vector<Canvas*> Viewports_Canvas;

        int Add_Viewport(Rectangle2D R, Scene* V_Scene, Camera* V_Camera,Canvas* V_Canvas);
        void Render_All(Texture_Manager& Tex_Man, float elapsed_time);
        void Render_Viewport(Texture_Manager& Tex_Man,Rectangle2D R, Scene* V_Scene, Camera* V_Camera,Canvas* V_Canvas, float elapsed_time);
    protected:

    private:
};

#endif // VIEWPORT_MANAGER_H
