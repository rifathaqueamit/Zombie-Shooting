#include "Box_UI.h"
#include <GL/glut.h>
#include "stdio.h"

Box_UI::Box_UI()
{
    Position = Vector2(0,0);
    Box_Color = Color(1,0,0,1);
    Size = Vector2(100,100);
}

Box_UI::~Box_UI()
{
    //dtor
}

void Box_UI::Render_Box(int view_width, int view_height, int center_x, int center_y)
{
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-view_width/2, view_width/2, view_height/2, -view_height/2);

    glMatrixMode(GL_MODELVIEW) ;
    glPushMatrix();
    glLoadIdentity();

    //glDisable( GL_DEPTH_TEST );

    //glRasterPos2f( Position.X + center_x, Position.Y + center_y ) ; // center of screen. (-1,0) is center left.
    glColor4f(Box_Color.R, Box_Color.G, Box_Color.B, Box_Color.A);
    glTranslatef(0,0,-5);
    glBegin(GL_QUADS);
        glVertex2f(-Size.X/2,-Size.Y/2);
        glVertex2f(Size.X/2,-Size.Y/2);
        glVertex2f(Size.X/2,Size.Y/2);
        glVertex2f(-Size.X/2,Size.Y/2);
    glEnd();

    //glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix() ; // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();
}
