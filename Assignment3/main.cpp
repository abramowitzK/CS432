// First new GL program
// Just makes a red triangle
// Kyle Abramowitz edit - Now also draws a square and a regular polygon
#include "Angel.h"
#include "RegularPolygon.h"
#include "Ellipsoid.h"
#include <random>
#include <iostream>
//A global update ticks counter
int globalTime = 0;
//Handles to each of the windows and subwindows we created
int window1;
int window2;
int subwindow;
//Width and heigh of the window
int height = 500;
int width = 500;
//Flag to check if animation is paused or not
bool paused = false;
//Colors set globally and manipulated by callback functions
vec4 window2Color = vec4(1.0);
vec4 subWindowColor = vec4(1.0);
vec4 squareColor = vec4(1.0);
//Menu enums
typedef enum
{
    START = 0,
    STOP = 1,
    SQUARE_COLORS = 2,
    MM_WHITE = 3,
    MM_RED = 4,
    MM_GREEN = 5

} MainMenu;
typedef enum
{
    RED = 0,
    GREEN = 1,
    BLUE = 2
} SubWindowMenu;
GLuint vao[3];
//Global vectors of geometry for each window
std::vector<Shape*> shapes;
std::vector<Shape*> window2Shapes;
std::vector<Shape*> subWindowShapes;
GLuint program[3];
void init( void ) {
    srand(time(0));
    std::cout << "The subwindow has a right click menu to change its clear color" << std::endl;
    std::cout << "The main window has a menu to start and stop animation and change the color of the white squares" << std::endl;
    std::cout << "The secondary takes keyboard input (r,b,g,y,o,p,w) to change color of objects (only when that window is focused)" << std::endl;
    std::cout << "Clicking will allow you to create a breathing circle in the main window" << std::endl;
    // Create vertex array objects
    glGenVertexArrays( 3, vao );

    // Create the squares for the main window
    shapes.push_back(new RegularPolygon(4, vec4(1.0f), vec2(0.0f, -0.25f), 0.6f));
    shapes.push_back(new RegularPolygon(4, vec4(0.0f), vec2(0.0f, -0.25f), 0.5f));
    shapes.push_back(new RegularPolygon(4, vec4(1.0f), vec2(0.0f, -0.25f), 0.4f));
    shapes.push_back(new RegularPolygon(4, vec4(0.0f), vec2(0.0f, -0.25f), 0.3f));
    shapes.push_back(new RegularPolygon(4, vec4(1.0f), vec2(0.0f, -0.25f), 0.2f));
    shapes.push_back(new RegularPolygon(4, vec4(0.0f), vec2(0.0f, -0.25f), 0.1f));

    // Create the circle and the triangle for window 2
    window2Shapes.push_back(new RegularPolygon(3, window2Color, vec2(-0.5f, 0.0f), 0.4f));
    window2Shapes.push_back(new Ellipsoid(window2Color, vec2(0.5, 0.0), 0.5, true, 1.0f, true));

    //Create the ellipse for the subwindow
    subWindowShapes.push_back(new Ellipsoid(vec4(0.5, 0.75, 0.95, 1.0), vec2(0.0, 0.0), 0.5, true, 0.6f, false));
    //Initialize (create vbos and buffer data)
    // Main window geometry
    glBindVertexArray( vao[0] );
    glutSetWindow(window1);
    for(Shape * s : shapes) {
        s->Init(0);
    }
    program[0] = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram(program[0]);

    //Window 2 geometry
    glBindVertexArray( vao[1] );
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
    glutSetWindow(window2);
    glUseProgram(program[1]);
    program[1] = InitShader( "vshader21.glsl", "fshader21.glsl" );
    for(auto s : window2Shapes) {
        s->Init(0);
    }
    //Sub window geometry
    glBindVertexArray( vao[2] );
    glutSetWindow(subwindow);
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
    glUseProgram(program[2]);
    program[2] = InitShader( "vshader21.glsl", "fshader21.glsl" );
    for(auto s : subWindowShapes) {
        s->Init(0);
    }
    glClearColor( 0.0, 1.0, 1.0, 1.0 ); // black background
}
//Main window display function
void display( void ) {
    glBindVertexArray(vao[0]);
    glutSetWindow(window1);
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    for(Shape * s : shapes) {
        s->Draw(program[0]);
    }
    glFlush();
    glutSwapBuffers();
}
//Window 2 display function
void display2() {
    glBindVertexArray(vao[1]);
    glutSetWindow(window2);
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto s : window2Shapes) {
        s->Draw(program[1]);
    }
    glFlush();
    glutSwapBuffers();
}
//subwindow display function
void subDisplay() {
    glBindVertexArray(vao[2]);
    glutSetWindow(subwindow);
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto s : subWindowShapes) {
        s->Draw(program[2]);
    }
    glFlush();
    glutSwapBuffers();
}
//Main window keyboard function
void keyboard( unsigned char key, int x, int y ) {
    switch ( key ) {
        //Cleanup any resources we allocated since we're exiting the application
    case 033:
		for (auto shape : shapes){
			delete shape;
        }
        for(auto shape : window2Shapes) {
            delete shape;
        }
        for(auto shape : subWindowShapes) {
            delete shape;
        }
        exit( EXIT_SUCCESS );
    }
}
//Window 2 keyboard function
void keyboard2(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            window2Color = vec4(1.0,0.0,0.0,1.0);
            break;
        case 'g':
            window2Color = vec4(0.0,1.0,0.0,1.0);
            break;
        case 'b':
            window2Color = vec4(0.0,0.0,1.0,1.0);
            break;
        case 'y':
            window2Color = vec4(1.0,1.0,0.0,1.0);
            break;
        case 'o':
            window2Color = vec4(1.0,0.5,0.0,1.0);
            break;
        case 'p':
            window2Color = vec4(1.0,0.0,1.0,1.0);
            break;
        case 'w':
            window2Color = vec4(1.0,1.0,1.0,1.0);
            break;
    }
    for(auto shape : window2Shapes) {
        shape->SetColor(window2Color);
    }
    glutSetWindow(window2);
    glBindVertexArray(vao[1]);
    for (auto shape : window2Shapes) {
        shape->Update(-globalTime);
    }
    glutPostWindowRedisplay(window2);
}
//Update function for everybody
void update() {
    if(!paused) {
        glutSetWindow(window1);
        glBindVertexArray(vao[0]);
        for (auto shape : shapes) {
            shape->Update(globalTime);
        }
        glutPostWindowRedisplay(window1);
        glutSetWindow(window2);
        glBindVertexArray(vao[1]);
        for (auto shape : window2Shapes) {
            shape->Update(-globalTime);
        }
        glutPostWindowRedisplay(window2);
        glutPostWindowRedisplay(subwindow);
        globalTime += 1;
    }
}
//Menu callback for subwindow
void subWindowMenu(int option) {
    switch (option) {
        case SubWindowMenu::RED:
            subWindowColor = vec4(1.0, 0.0,0.0,1.0);
            break;
        case SubWindowMenu::GREEN:
            subWindowColor = vec4(0.0, 1.0,0.0,1.0);
            break;
        case SubWindowMenu::BLUE:
            subWindowColor = vec4(0.0, 0.0,1.0,1.0);
            break;
    }
    glutSetWindow(subwindow);
    glClearColor(subWindowColor.x,subWindowColor.y,subWindowColor.z,subWindowColor.w);
}
//Main window menu callback
void mainMenu(int option) {
    switch (option) {
        case MainMenu::START:
            paused = false;
            break;
        case MainMenu::STOP:
            paused = true;
            break;
    }
}
//callback for sub menu of main window menu
void subMainMenu(int option) {
    switch (option) {
        case MainMenu::MM_WHITE:
            squareColor = vec4(1.0);
            break;
        case MainMenu::MM_RED:
            squareColor = vec4(1.0,0.0,0.0,1.0);
            break;
        case MainMenu::MM_GREEN:
            squareColor = vec4(0.0,1.0,0.0,1.0);
            break;
    }
    for(unsigned int i = 0; i < 6; i++) {
        glutSetWindow(window1);
        if(i%2 == 0) {
            //only want to set squares who are colored white
            shapes[i]->SetColor(squareColor);
            shapes[i]->Update(globalTime);
        }
        glutPostWindowRedisplay(window1);
    }
}
//Main window mouse function for creating circles
void mainWindowMouse(int button, int state, int x, int y) {
    y = height - y;
    float transformedX = (float)((x - width)*(2.0)/((float)width) + 1.0);
    float transformedY = (float)((y - height)*(2.0)/((float)height) + 1.0);
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //On mouse up, create a circle
        glutSetWindow(window1);
        glBindVertexArray(vao[0]);
        shapes.push_back(new Ellipsoid(vec4((float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX, 1.0f), vec2(transformedX,transformedY), 0.2, true, 1.0, true));
        shapes[shapes.size()-1]->Init(0);
        for (auto shape : shapes) {
            shape->Update(globalTime);
        }
        glutPostWindowRedisplay(window1);
    }
}
//main function
int main( int argc, char **argv ) {
    //Set glut state
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize( height, width );

    //create window 1 and init glew
    window1 = glutCreateWindow( "Shapes" );
    glewExperimental=GL_TRUE;
    glewInit();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( update );
    glutMouseFunc( mainWindowMouse );
    //Create main menu
    int subMenu = glutCreateMenu(subMainMenu);
    glutAddMenuEntry("White", MainMenu::MM_WHITE);
    glutAddMenuEntry("Red", MainMenu::MM_RED);
    glutAddMenuEntry("Green", MainMenu::MM_GREEN);
    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Stop Animation", MainMenu::STOP);
    glutAddMenuEntry("Start Animation", MainMenu::START);
    glutAddSubMenu("Square Colors", subMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //create window2
    window2 = glutCreateWindow("window 2");
    glutSetWindow(window2);
    glutIdleFunc(update);
    glutDisplayFunc(display2);
    glutKeyboardFunc(keyboard2);
    //create sub window
    subwindow = glutCreateSubWindow(window1, 0, 0, 150, 100);
    glutDisplayFunc(subDisplay);
    glutSetWindow(subwindow);
    glutCreateMenu(subWindowMenu);
    glutAddMenuEntry("Red", SubWindowMenu::RED);
    glutAddMenuEntry("Green", SubWindowMenu::GREEN);
    glutAddMenuEntry("Blue", SubWindowMenu::BLUE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //Init geometry and graphics
    init();

    glutMainLoop();
    return 0;
}


