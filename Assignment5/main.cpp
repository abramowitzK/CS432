// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include "Object.h"
#include "SMFMeshLoader.h"
int height = 500;
int width = 500;
float t = 0.0;
GLuint vao[1];
GLuint program[1];
Object* object;
enum Menu {
    Perspective = 0,
    Orthographic = 1
};
void init( void ) {
    SMFMeshLoader loader;
    loader.LoadFile("bunny.smf");
    // Create vertex array object
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    program[0] = InitShader( "vcubeshader.glsl", "fcubeshader.glsl" );
    //Using the same shader throughout. Don't need to ever change it for this assignment so we'll just set it here.
    glUseProgram(program[0]);
    object = new Object(loader.GetMesh("bunny.smf"));
    object->Init(program[0]);
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // white background
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
        case Menu::Perspective:
            object->SetPara(false);
            break;
        case Menu::Orthographic:
            object->SetPara(true);
            break;
    }
}
void update(){
    t += 1.0f;
    object->Update(t);
    glutPostRedisplay();
}
//Main window keyboard function
void keyboard( unsigned char key, int x, int y ) {
    switch ( key ) {
        //Cleanup any resources we allocated since we're exiting the application
        case 033: {
            delete object;
            exit(EXIT_SUCCESS);
            break;
        case 'r':
            object->IncreaseRadius();
            break;
        case 'R':
            object->DecreaseRadius();
            break;
        case 'h':
            object->IncreaseHeight();
            break;
        case 'H':
            object->DecreaseHeight();
            break;
        case 's':
            object->IncrementSpeed();
            break;
        case 'S':
            object->DecrementSpeed();
            break;
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
    glutIdleFunc(update);
    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Perspective", Menu::Perspective);
    glutAddMenuEntry("Orthographic", Menu::Orthographic);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();

    glutMainLoop();
    return 0;
}


