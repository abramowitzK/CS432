// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include "RegularPolygon.h"
#include "Ellipsoid.h"
#include "Triangle.h"
#include <iostream>
const int NumPoints = 3 + 6 + 15;

//--------------------------------------------------------------------------
std::vector<Shape *> shapes;
GLuint program;
void
init( void )
{
    std::cout << "This program has no interaction" << std::endl;
    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );

    shapes.push_back(new RegularPolygon(4, vec4(1.0f), vec2(0.0f, -0.25f), 0.6f));
    shapes.push_back(new RegularPolygon(4, vec4(0.0f), vec2(0.0f, -0.25f), 0.5f));
    shapes.push_back(new RegularPolygon(4, vec4(1.0f), vec2(0.0f, -0.25f), 0.4f));
    shapes.push_back(new RegularPolygon(4, vec4(0.0f), vec2(0.0f, -0.25f), 0.3f));
    shapes.push_back(new RegularPolygon(4, vec4(1.0f), vec2(0.0f, -0.25f), 0.2f));
    shapes.push_back(new RegularPolygon(4, vec4(0.0f), vec2(0.0f, -0.25f), 0.1f));
    shapes.push_back(new Ellipsoid(vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.75f, 0.75f), 0.25f, true, 1.0));
    shapes.push_back(new Ellipsoid(vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(-0.75f, 0.75f), 0.25f, false, 0.6));
    shapes.push_back(new Triangle( vec4(0.0f, 0.0f, 1.0f, 1.0f),vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f),  0.25f, vec2(0.0f, 0.75f)));
    for(Shape * s : shapes)
    {
        s->Init();
    }
    // Load shaders and use the resulting shader program
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    for(Shape * s : shapes)
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
		for (auto shape : shapes)
			delete shape;
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
    glutInitWindowSize( 500, 500 );

    glutCreateWindow( "Shapes" );
    glewExperimental=GL_TRUE;
    glewInit();
    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
