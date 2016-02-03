// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include "Object.h"
int height = 500;
int width = 500;
GLuint vao[1];
GLuint program[1];
Object* object;

enum {
    SCALE = 0,
    ROTATE = 1,
    TRANSLATE = 2
};
int mode = SCALE;
void init( void ) {
    std::cout << "This program displays a 3D cube with an orthographic projection." << std::endl;
    std::cout << "Right click to open a menu to select a transformation." << std::endl;
    std::cout << "Press q to decrease transformation in X direction and Q (shift q) to increase " << std::endl;
    std::cout << "Press w to decrease transformation in Y direction and w (shift w) to increase " << std::endl;
    std::cout << "Press e to decrease transformation in Z direction and E (shift e) to increase " << std::endl;
    std::cout << "Press r to reset all transformations." << std::endl;

    // Create vertex array object
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    program[0] = InitShader( "vcubeshader.glsl", "fcubeshader.glsl" );
    //Using the same shader throughout. Don't need to ever change it for this assignment so we'll just set it here.
    glUseProgram(program[0]);
    object = new Object();
    object->Init(program[0]);
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}
//Main window display function
void display( void ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window
    object->Draw(program[0]);
    glFlush();
    glutSwapBuffers();
}

void mainMenu(int option){

    switch (option){
        case SCALE :
            mode = SCALE;
            break;
        case ROTATE:
            mode = ROTATE;
            break;
        case TRANSLATE:
            mode = TRANSLATE;
            break;
    }
}
//Main window keyboard function
void keyboard( unsigned char key, int x, int y ) {
    switch ( key ) {
        //Cleanup any resources we allocated since we're exiting the application
        case 033: {
            delete object;
            exit(EXIT_SUCCESS);
        }
        case 'w': {
            if(mode == SCALE){
                object->Scale(0.0,0.05,0.0);
            } else if (mode == ROTATE){
                object->RotateY(2.0f);
            } else {
                object->Translate(0.0,0.05,0.0);
            }
            break;
        }
        case 'W': {
            if(mode == SCALE){
                object->Scale(0.0,-0.05,0.0);
            } else if (mode == ROTATE){
                object->RotateY(-2.0f);
            } else {
                object->Translate(0.0,-0.05,0.0);
            }
            break;
        }
        case 'q': {
            if(mode == SCALE){
                object->Scale(0.05,0.0,0.0);
            } else if (mode == ROTATE){
                object->RotateX(2.0f);
            } else {
                object->Translate(0.05,0.0,0.0);
            }
            break;
        }
        case 'Q': {
            if(mode == SCALE){
                object->Scale(-0.05,0.0,0.0);
            } else if (mode == ROTATE){
                object->RotateX(-2.0f);
            } else {
                object->Translate(-0.05,0.0,0.0);
            }
            break;
        }
        case 'e': {
            if(mode == SCALE){
                object->Scale(0.0,0.0,0.05);
            } else if (mode == ROTATE){
                object->RotateZ(2.0f);
            } else {
                object->Translate(0.0,0.0,0.05);
            }
            break;
        }
        case 'E': {
            if(mode == SCALE){
                object->Scale(0.0,0.0,-0.05);
            } else if (mode == ROTATE){
                object->RotateZ(-2.0f);
            } else {
                object->Translate(0.0,0.0,-0.05);
            };
            break;
        }
        case 'r':{
            //Reset all transforms;
            object->Reset();
        }
    }
    glutPostRedisplay();
}
//main function
int main( int argc, char **argv ) {
    //Set glut state
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize( height, width );

    //create window 1 and init glew
    glutCreateWindow( "Cube" );
    glewExperimental=GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Scale", SCALE);
    glutAddMenuEntry("Rotate", ROTATE);
    glutAddMenuEntry("Translate", TRANSLATE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();

    glutMainLoop();
    return 0;
}


