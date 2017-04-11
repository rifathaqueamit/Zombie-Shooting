#ifndef MATRIX4X4_H
#define MATRIX4X4_H


class Matrix4x4
{
    public:
        Matrix4x4();
        virtual ~Matrix4x4();

        float M11;
        float M12;
        float M13;
        float M14;
        float M21;
        float M22;
        float M23;
        float M24;
        float M31;
        float M32;
        float M33;
        float M34;
        float M41;
        float M42;
        float M43;
        float M44;

        ///////////////////////////////////////////////////////////////
        //11    12      13      14
        //21    22      23      24
        //31    32      33      34
        //41    42      43      44
        //////////////////////////////////////////////////////////////

        void Make_Identity();
        void Translate(float X, float Y, float Z);
        void Multiply_Matrix(float* Mat4x4);
        float* Get_Matrix();
    protected:

    private:
};

#endif // MATRIX4X4_H
