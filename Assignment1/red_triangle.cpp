// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include <cmath>
const int NumPoints = 3 + 6 + 15;

//--------------------------------------------------------------------------

void
init( void )
{
    // Specifiy the vertices for a triangle
    vec2 vertices[NumPoints] = {
        vec2( -1.0, -1.0 ), 
        vec2( 0.0, -1.0 ), 
        vec2(-0.5, 0.0 ),
    // Verticies for a square -- Kyle Edit
        vec2(1.0, 1.0),
        vec2(0.0, 1.0),
        vec2(0.0, 0.0),
        vec2(0.0, 0.0),
        vec2(1.0, 0.0),
        vec2(1.0, 1.0)
    };
    // Verticies for a pentagon -- Kyle Edit
    vec2 temp[5];
    float xCenter = -0.5;
    float yCenter = 0.5;
    float r = 0.5;
    int numSides = 5;
    vec2 center = vec2(xCenter, yCenter);
    //General equation for points on a polygon given center and radius r
    for(int i = 0; i < numSides; i++){
        temp[i] = vec2((xCenter + r * cos(2*M_PI * i/ numSides - 60.0)),( yCenter + r * sin(2*M_PI * i/ numSides - 60.0 ))) ;
    }
    //Treating the pentagon as 5 triangles...
    // Could probably do this as an array but figuring out the indices got messy so this works as well.
    //Triangle 1
    vertices[9] = temp[0];
    vertices[10] = temp[1];
    vertices[11] = center;
    //Triangle 2
    vertices[12] = temp[1];
    vertices[13] = temp[2];
    vertices[14] = center;
    //Triangle 3
    vertices[15] = temp[2];
    vertices[16] = temp[3];
    vertices[17] = center;

   //Triangle 4
    vertices[18] = temp[3];
    vertices[19] = temp[4];
    vertices[20] = center;

   //Triangle 5
    vertices[21] = temp[4];
    vertices[22] = temp[0];
    vertices[23] = center;


    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );


    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    glDrawArrays( GL_TRIANGLES, 0, 3);    // draw the points
    glDrawArrays( GL_TRIANGLES, 3, 6);
    glDrawArrays( GL_TRIANGLES, 9, 15);
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
