#ifndef BOX_UI_H
#define BOX_UI_H
#include "Vector2.h"
#include "Color.h"

class Box_UI
{
    public:
        Box_UI();
        virtual ~Box_UI();

        Vector2 Position;
        Vector2 Size;

        Color Box_Color;

        bool Draw_Box = true;

        void Render_Box(int view_width, int view_height, int center_x, int center_y);
    protected:

    private:
};

#endif // BOX_UI_H
