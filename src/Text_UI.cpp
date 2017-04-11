#include "Text_UI.h"
#include <GL/glut.h>
#include "stdio.h"

Text_UI::Text_UI(int Buffer_Size)
{
    Text = new char[Buffer_Size];
    Position = Vector2(0,0);
    Text_Color = Color(1,1,1,1);
    Text_Font = GLUT_BITMAP_HELVETICA_12;
}

void Text_UI::Set_Text(const char* Your_Text)
{
    sprintf(Text, Your_Text);
}

Text_UI::~Text_UI()
{
    delete[] Text;
}

void Text_UI::Render_Text(int view_width, int view_height, int center_x, int center_y)
{
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-view_width/2, view_width/2, view_height/2, -view_height/2);

    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;

    glDisable( GL_DEPTH_TEST );

    glRasterPos2f( Position.X + center_x, Position.Y + center_y ) ; // center of screen. (-1,0) is center left.
    glColor4f(Text_Color.R, Text_Color.G, Text_Color.B, Text_Color.A);

    char * p = Text ;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) ) ;

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix() ; // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();
}
