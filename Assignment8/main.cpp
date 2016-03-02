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
Object* object[3];
GLuint fbo;
GLuint depth;
enum Menu {
};
void init( void ) {
    std::cout << "This displays 3 triangle meshes, (5k bunny, 60k bunny, 50k dragon)" << std::endl;
    std::cout << "The light source is attached to the camera" << std::endl;
    std::cout << "Clicking on an object will change it's color to black. Only one object can be selected at a time" << std::endl;
    std::cout << "Press a to rotate the camera around the object" << std::endl;
    std::cout << "Press r to increase the radius of rotation. R (shift r) to decrease" << std::endl;
    std::cout << "Minimum radius is 15 and you will not be able to decrease beyond that" << std::endl;
    SMFMeshLoader loader = SMFMeshLoader();
    loader.LoadFile("dragon-50000.smf");
    loader.LoadFile("bunny.smf");
    loader.LoadFile("bound-bunny_5k.smf");
    // Create vertex array object
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    program[0] = InitShader( "vcubeshader.glsl", "fcubeshader.glsl" );
    //Using the same shader throughout. Don't need to ever change it for this assignment so we'll just set it here.
    glUseProgram(program[0]);
    object[0] = new Object(loader.GetMesh("dragon-50000.smf"));
    object[0]->Translate(5.0f, -1.0f, 0.0f);
    object[0]->Scale(3.0,3.0,3.0);
    object[0]->SetColor(0);
    object[1] = new Object(loader.GetMesh("bunny.smf"));
    object[1]->Scale(15.0,15.0,15.0);
    object[1]->Translate(0.0,-2.0,0.0);
    object[1]->SetColor(1);
    object[2] = new Object(loader.GetMesh("bound-bunny_5k.smf"));
    object[2]->Scale(1.5,1.5,1.5);
    object[2]->Translate(-5.0f, 0.0f, 0.0f);
    object[2]->SetColor(2);
    for(auto obj : object){
        obj->Init(program[0]);
    }

    glGenRenderbuffers(1, &depth);
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}
//Main window display function
void display( void ) {
    glClearColor(1.0,1.0,1.0,1.0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window
    for(auto obj : object){
        obj->Draw(program[0]);
    }
    glFlush();
    glutSwapBuffers();
}

void mainMenu(int option){

}
void mouse(int button,int state,int x,int y){
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        GLuint tex, depth;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0 , GL_RGBA, GL_FLOAT, NULL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        glGenTextures(1, &depth);
        glBindTexture(GL_TEXTURE_2D, depth);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto obj : object) {
            obj->DrawToFBO(program[0]);
        }
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glFlush();
        std::vector<GLfloat > data(4);
        glReadPixels(x, 500-y, 1, 1, GL_RGBA, GL_FLOAT, data.data());
        for(auto obj : object){
            obj->Unselect();
        }
        if(data[0] > 0.1 && data[1] < 0.1)
            object[0]->Select();
        else if (data[1] > 0.1)
            object[1]->Select();
        else if (data[2] > 0.1)
            object[2]->Select();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glutPostRedisplay();
    }
}
void update() {
    if (!stop) {
        t += 1.0f;
    }
    for(auto obj : object){
        obj->Update(t);
    }
    glutPostRedisplay();
}
//Main window keyboard function
void keyboard( unsigned char key, int x, int y ) {
    switch ( key ) {
        //Cleanup any resources we allocated since we're exiting the application
        case 033:
            for(auto obj : object)
                delete obj;
            exit(EXIT_SUCCESS);
            break;
        case 'r':
            for(auto obj : object){
                obj->IncreaseRadius();
            }
            break;
        case 'R':
            for(auto obj : object){
                obj->DecreaseRadius();
            }
            break;
        case 'a':
            for(auto obj : object){
                obj->IncreaseAngle();
            }
            break;
    }
    update();
}
void resize(int,int){
    glutReshapeWindow(width,height);
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
    glutMouseFunc(mouse);
    glutReshapeFunc(resize);
    init();

    glutMainLoop();
    return 0;
}


