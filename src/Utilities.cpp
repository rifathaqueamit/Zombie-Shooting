#include "Vector.h"
#include "Utilities.h"
#include <GL/glut.h>
#include <stdio.h>
#include "Ray.h"
#include "Camera.h"
#include "Vector2.h"
#include <math.h>

Vector Utilities::Get_Normal(Vector V1, Vector V2, Vector V3){
	float Ux,Uy,Uz;

	Ux = V2.X-V1.X;
	Uy = V2.Y-V1.Y;
	Uz = V2.Z-V1.Z;

	float Vx, Vy, Vz;

	Vx = V3.X-V1.X;
	Vy = V3.Y-V1.Y;
	Vz = V3.Z-V1.Z;

	float Nx,Ny,Nz;

	Nx = Uy*Vz - Uz*Vy;
	Ny = Uz*Vx - Ux*Vz;
	Nz = Ux*Vy - Uy*Vx;

	return Vector(Nx,Ny,Nz);
}

void Utilities::Draw_Text(){
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;

    glDisable( GL_DEPTH_TEST );

    glRasterPos2f( 0,0 ) ; // center of screen. (-1,0) is center left.
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    char buf[300];
    sprintf( buf, "Oh hello" ) ;

    const char * p = buf ;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) ) ;

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix() ; // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();

}

float Utilities::Vector2_Dot(Vector2 a, Vector2 b)
{
    return a.X*b.X + a.Y*b.Y;
}

bool Utilities::line_circle_intersection(Vector2 l1, Vector2 l2, Vector2 center, float r)
{
Vector2 dir = Vector2(l2.X - l1.X, l2.Y - l1.Y);
Vector2 f = Vector2(l1.X - center.X, l1.Y - center.Y);

float a = Vector2_Dot( dir, dir ) ;
float b = 2* Vector2_Dot( f, dir ) ;
float c = Vector2_Dot( f , f) - r*r ;

float discriminant = b*b-4*a*c;
if( discriminant < 0 )
{

}
else
{
  discriminant = sqrt( discriminant );
  float t1 = (-b - discriminant)/(2*a);
  float t2 = (-b + discriminant)/(2*a);
  if( t1 >= 0 && t1 <= 1 )
  {
    return true ;
  }
  if( t2 >= 0 && t2 <= 1 )
  {
    return true ;
  }
  return false ;
}

return false;

}

