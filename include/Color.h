#ifndef COLOR_H
#define COLOR_H


class Color
{
    public:
        Color();
        Color(float r, float g, float b, float a);
        virtual ~Color();

        float R;
        float G;
        float B;
        float A;
    protected:

    private:
};

#endif // COLOR_H
