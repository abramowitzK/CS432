// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include "Object.h"
#include "SMFMeshLoader.h"
int height = 500;
int width = 500;
float t = 0.0;
bool stop = false;
GLuint vao[1];
GLuint program[1];
Object* object;
enum Menu {
    Perspective = 0,
    Orthographic = 1,
    Start = 2,
    Stop = 3
};
void init( void ) {
    std::cout << "This program displays a 3D bunny. Camera rotates around bunny." << std::endl;
    std::cout << "There are 2 point lights in the scene. One at (0.75,0.0,0.75) and one at (-0.75,0.0, -0.75)" << std::endl;
    std::cout << "Press r to increase the radius of rotation. R (shift r) to decrease" << std::endl;
    std::cout << "Press s to increase the speed of rotation. S (shift S) to decrease" << std::endl;
    std::cout << "Press h to increase the height. H (shift h) to decrease" << std::endl;
    std::cout << "Right click for a menu to change from perspective to ortho and to start and stop the animaiton" << std::endl;
    std::cout << "NOTE: Incrementing speed will cause the object to jump a bit. It still correctly increases speed though" << std::endl;

    SMFMeshLoader loader;
    loader.LoadFile("cow-100.smf");
    // Create vertex array object
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    program[0] = InitShader( "vcubeshader.glsl", "fcubeshader.glsl" );
    //Using the same shader throughout. Don't need to ever change it for this assignment so we'll just set it here.
    glUseProgram(program[0]);
    object = new Object(loader.GetMesh("cow-100.smf"));
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
        case Menu::Start:
            stop = false;
            object->Start();
            break;
        case Menu::Stop:
            stop = true;
            object->Stop();
            break;
    }
}
void update(){
    if(!stop)
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
    glutCreateWindow( "Bunny Simulator 2016" );
    glewExperimental=GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutIdleFunc(update);
    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Perspective", Menu::Perspective);
    glutAddMenuEntry("Orthographic", Menu::Orthographic);
    glutAddMenuEntry("Start", Menu::Start);
    glutAddMenuEntry("Stop", Menu::Stop);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();

    glutMainLoop();
    return 0;
}


