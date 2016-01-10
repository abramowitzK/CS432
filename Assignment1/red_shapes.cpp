// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "include/Angel.h"
#include "Shape.h"
#include <vector>
const int NumPoints = 3 + 6 + 15;

//--------------------------------------------------------------------------
std::vector<Shape*> shapes;
GLuint program;
void
init( void )
{
    shapes.push_back(new Shape(4, vec4(0.3f), vec2(0.0f), 0.5f));
    shapes.push_back(new Shape(4, vec4(0.4f), vec2(0.5f), 0.3f));
    shapes.push_back(new Shape(4, vec4(0.7f), vec2(-0.5f), 0.3f));
    shapes.push_back(new Shape(4, vec4(0.3f), vec2(-0.5f, 0.5), 0.3f));
    shapes.push_back(new Shape(4, vec4(0.3f), vec2(0.5f, -0.5), 0.3f));
    for(Shape* s : shapes)
    {
        s->Init();
    }
    // Load shaders and use the resulting shader program
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    for(Shape* s : shapes)
    {
        s->Draw(program);
    }
    glFlush();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );

    glutCreateWindow( "Red Triangle" );
    glewExperimental=GL_TRUE;
    glewInit();
    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
