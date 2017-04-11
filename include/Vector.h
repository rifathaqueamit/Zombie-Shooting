#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    public:
        Vector();
        Vector(float x_val, float y_val, float z_val);
        virtual ~Vector();

        float X;
        float Y;
        float Z;
    protected:

    private:
};

#endif // VECTOR_H
