#ifndef CANVAS_H
#define CANVAS_H
#include <vector>
#include "Text_UI.h"
//#include "Box_UI.h"

using namespace std;

class Canvas
{
    public:
        Canvas();
        virtual ~Canvas();

        vector<Text_UI*> UI_Texts;
       // vector<Box_UI*> UI_Boxes;

        Text_UI* Get_Text_UI(int ID);
        int Add_Text_UI(Text_UI* T);

      //  Box_UI* Get_Box_UI(int ID);
      //  int Add_Box_UI(Box_UI* T);

        void Render_All(int view_width, int view_height);
        void Set_Center(int x, int y);
        void Set_Size(int width, int height);

        int canvas_width;
        int canvas_height;
        int canvas_center_x;
        int canvas_center_y;
        bool use_viewport_size = true;

    protected:

    private:
};

#endif // CANVAS_H
