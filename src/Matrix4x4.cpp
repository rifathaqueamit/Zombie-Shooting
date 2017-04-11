#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
    //ctor
}

Matrix4x4::~Matrix4x4()
{
    //dtor
}

void Matrix4x4::Make_Identity()
{
    M11 = 1;
    M22 = 1;
    M33 = 1;
    M44 = 1;
    M12 = M13 = M14 = M21 = M23 = M24 = M31 = M32 = M34 = M41 = M42 = M43 = 0;
}

float* Matrix4x4::Get_Matrix()
{
    float* Mat_Array = new float[16];
    Mat_Array[0] = M11;
    Mat_Array[1] = M12;
    Mat_Array[2] = M13;
    Mat_Array[3] = M14;
    Mat_Array[4] = M21;
    Mat_Array[5] = M22;
    Mat_Array[6] = M23;
    Mat_Array[7] = M24;
    Mat_Array[8] = M31;
    Mat_Array[9] = M32;
    Mat_Array[10] = M33;
    Mat_Array[11] = M34;
    Mat_Array[12] = M41;
    Mat_Array[13] = M42;
    Mat_Array[14] = M43;
    Mat_Array[15] = M44;
    return Mat_Array;
}

void Matrix4x4::Multiply_Matrix(float* M)
{

}
