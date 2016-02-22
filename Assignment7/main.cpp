// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include "Object.h"
#include "SMFMeshLoader.h"
#include "BezierPointReader.h"
int height = 500;
int width = 500;
float t = 0.0;
bool stop = false;
GLuint vao[1];
GLuint program[1];
Object* object;
enum Menu {
    ShineyRed = 0,
    DullGreen = 1,
    MatteBlue = 2,
    Phong = 3,
    Gouraud = 4,
    Stop = 5,
    Start = 6,
    Perspective = 7,
    Orthographic = 8
};
void init( void ) {
    std::cout << "This program displays a 3D bunny. Camera rotates around bunny." << std::endl;
    std::cout << "Press r to increase the radius of rotation. R (shift r) to decrease" << std::endl;
    std::cout << "Press s to increase the speed of rotation. S (shift S) to decrease" << std::endl;
    std::cout << "Press h to increase the height. H (shift h) to decrease" << std::endl;
    std::cout << "Right click for a menu to change from perspective to ortho and to start and stop the animaiton" << std::endl;
    std::cout << "Right click to change materials (shiney red, dull green, matteblue (slightly shiney)" << std::endl;
    std::cout << "NOTE: Incrementing speed will cause the object to jump a bit. It still correctly increases speed though" << std::endl;
    std::cout << "Press c to increase the radius of the object light. C (shift c) to decrease" << std::endl;
    std::cout << "Press l to increase height of the object light. L (shift l) to decrease" << std::endl;
    std::cout << "Press a to increase light angle around cylinder. A (shift a) to decrease" << std::endl;

    BezierPointReader loader;
    loader.LoadFile("controlPoints.txt");
    // Create vertex array object
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    program[0] = InitShader( "vcubeshader.glsl", "fcubeshader.glsl" );
    //Using the same shader throughout. Don't need to ever change it for this assignment so we'll just set it here.
    glUseProgram(program[0]);
    object = new Object(loader.GetMesh(100));
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
        case Menu::Phong:
            object->SetGouraud(false);
            break;
        case Menu::Gouraud:
            object->SetGouraud(true);
            break;
        case Menu::ShineyRed:
            object->SetMat(1);
            break;
        case Menu::DullGreen:
            object->SetMat(2);
            break;
        case Menu::MatteBlue:
            object->SetMat(3);
            break;
        case Menu::Start:
            stop = false;
            object->Start();
            break;
        case Menu::Stop:
            stop = true;
            object->Stop();
            break;
        case Menu::Perspective:
            object->SetPara(false);
            break;
        case Menu::Orthographic:
            object->SetPara(true);
            break;
    }
}
void update() {
    if (!stop) {
        t += 1.0f;
    }
    object->Update(t);
    glutPostRedisplay();
}
//Main window keyboard function
void keyboard( unsigned char key, int x, int y ) {
    switch ( key ) {
        //Cleanup any resources we allocated since we're exiting the application
        case 033:
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
            case 'a':
                object->IncrementAngle();
                break;
            case 'A':
                object->DecrementAngle();
                break;
            case 'l':
                object->IncrementHeight();
                break;
            case 'L':
                object->DecrementHeight();
                break;
            case 'c':
                object->IncrementLightRadius();
                break;
            case 'C':
                object->DecrementLightRadius();
                break;
    }
    update();
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
    glutAddMenuEntry("Shiney Red", Menu::ShineyRed);
    glutAddMenuEntry("Dull Green", Menu::DullGreen);
    glutAddMenuEntry("MatteBlue", Menu::MatteBlue);
    glutAddMenuEntry("Gouraud", Menu::Gouraud);
    glutAddMenuEntry("Phong", Menu::Phong);
    glutAddMenuEntry("Start Camera Rotation", Menu::Start);
    glutAddMenuEntry("Stop Camera Rotation", Menu::Stop);
    glutAddMenuEntry("Perspective", Menu::Perspective);
    glutAddMenuEntry("Orthographic", Menu::Orthographic);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();

    glutMainLoop();
    return 0;
}


