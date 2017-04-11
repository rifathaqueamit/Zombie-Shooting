#ifndef TEXT_UI_H
#define TEXT_UI_H
#include "Vector2.h"
#include "Color.h"

class Text_UI
{
    public:
        Text_UI(int Buffer_Size);
        virtual ~Text_UI();

        char* Text;
        Vector2 Position;
        Color Text_Color;
        void* Text_Font;

        void Set_Text(const char* Your_Text);
        void Render_Text(int view_width, int view_height, int center_x, int center_y);
    protected:

    private:
};

#endif // TEXT_UI_H
