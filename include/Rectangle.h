#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H


class Rectangle2D
{
    public:
        Rectangle2D();
        Rectangle2D(float x_val, float y_val, float width_val, float height_val);
        virtual ~Rectangle2D();

        float X;
        float Y;
        float Width;
        float Height;
    protected:

    private:
};

#endif // RECTANGLE2D_H
