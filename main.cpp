#include "SOIL.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <ctime>


int channel=0;

class display
{
private:
    static int pcScore;
    static int playerScore;
    int mousex=0;
    static int windowWidth;
    static int windowHeight;
    static float XSpeed;
    static float YSpeed;
    float ballspeed=4;
public:
    struct Shape
    {
        float left,top,right,bottom;    
    };
    Shape ball={120,120,140,140};
    Shape player_1={0,870,70,880};
    Shape PC={0,30,70,20};
    Shape background={0,0,1600,1600};
    Shape wall;
    display(){}
    display(int, char**);
    ~display(){}
    void run();
    static void render();
    void drawRectangle(Shape,GLuint);
    int Wall(Shape, Shape);
    bool PLayer(Shape,Shape);
    bool AI(Shape, Shape);
    static void mouseMotion(int , int );
    void stop(unsigned char, int, int);
    static void reshape (int , int );
    void setting(void);
    void stop();
    static void close(unsigned char, int, int);
    static void Timer(int v);
    static void text(char*,int,int);
    static void loadTexture(GLuint* texture, char* path);
};

float display::XSpeed=3;
float display::YSpeed=3;
int display::windowHeight=1600;
int display::windowWidth=900;

int display::pcScore=0;
int display::playerScore=0;
display test;

void display::Timer(int v)
{
    test.ball.left+=XSpeed;
    test.ball.right+=XSpeed;
    test.ball.top+=YSpeed;
    test.ball.bottom+=YSpeed;
    glutTimerFunc(1,Timer,0);
}


display::display(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition(0,0);
    glutCreateWindow("pong");
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutTimerFunc(1,Timer,1);
    glutKeyboardFunc(close);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMotion);    
}


void display::reshape (int w, int h)
{
	test.windowWidth =w ;
	test.windowHeight =h ;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, w, h, 0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

}

void display::run()
{
    glutMainLoop();
}

void display::drawRectangle(Shape shap, GLuint texture)
{
    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,texture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glDisable(GL_QUADS);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(shap.left,shap.bottom);
    glTexCoord2f(1,0);
    glVertex2f(shap.right,shap.bottom);
    glTexCoord2f(0,1);
    glVertex2f(shap.right,shap.top);
    glTexCoord2f(1,1);
    glVertex2f(shap.left,shap.top);
    glTexCoord2f(0,1);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

}

int display::Wall(Shape ball, Shape wall)
{
    if(ball.right>=wall.right){
        return 1;
    }
    if(ball.left<=wall.left){
        return 2;
    }
    if(ball.top<=wall.top){
        return 3;
    }
    if(ball.bottom>=wall.bottom){
        return 4;
    }
}

void display::stop()
{
    std::cout<<"Game Over"<<std::endl;
    std::cout<<"Player had "<<playerScore<<std::endl;
    std::cout<<"Computer had "<<pcScore<<std::endl;
    exit(0);
}

bool display::PLayer(Shape ball,Shape player)
{
    if(ball.bottom >=player.top && ball.left>=player.left&&ball.right<=player.right)
    {
        return true;
    }
    return false;
}

bool display::AI(Shape ball,Shape PC)
{
    if(ball.top <=PC.bottom && ball.left>=PC.left&&ball.right<=PC.right)
    {
        return true;
    }
    return false;
}

void display::mouseMotion(int x, int y)
{
    test.mousex=x;
}

void display::close(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
    }
}

int PCturns=0;
int Playerturns=0;

void display::loadTexture(GLuint* texture, char* path)
{
    *texture=SOIL_load_OGL_texture(path,SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_MULTIPLY_ALPHA);
}

void display::render()
{
    std::srand(std::time(NULL));
    int random=rand()%100;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    test.wall.left=test.wall.top=0;
    test.wall.right=test.windowWidth;
    test.wall.bottom=test.windowHeight;
    GLuint texture;
    if(test.Wall(test.ball,test.wall)==1)
    {
        XSpeed=-test.ballspeed;
    }
    if(test.Wall(test.ball,test.wall)==2)
    {
        XSpeed=test.ballspeed;
    }
    if(test.Wall(test.ball,test.wall)==3)
    {
        YSpeed=+test.ballspeed;
    }
    if(test.Wall(test.ball,test.wall)==4)
    {
        YSpeed=-test.ballspeed;
    }
    loadTexture(&texture,"grass.jpeg");
    test.drawRectangle(test.background,texture);
    loadTexture(&texture,"baseball.jpeg");
    test.drawRectangle(test.ball,texture);
    loadTexture(&texture,"baseballbat.jpeg");
    test.drawRectangle(test.PC,texture);
    test.drawRectangle(test.player_1,texture);
    test.PC.left=test.ball.left+random-20;
    test.PC.right=test.ball.right+random+40;
    test.player_1.left=test.mousex-20;
    test.player_1.right=test.mousex+40;
    PCturns=0;
    Playerturns=0;
    if(test.PLayer(test.ball,test.player_1)==true)
    {
            YSpeed=-test.ballspeed;
            Playerturns=1;
    }
    if(test.AI(test.ball,test.PC)==true)
    {
            YSpeed=+test.ballspeed;
            PCturns=1;
    }
    if(Playerturns==0&&test.Wall(test.ball,test.wall)==3){
        playerScore++;
    }
    if(PCturns==0&&test.Wall(test.ball,test.wall)==4){
        pcScore++;
    }
    std::cout<<"Player has "<<playerScore<<std::endl;
    std::cout<<"Computer has "<<pcScore<<std::endl;
    if(pcScore==5||playerScore==5)
        {
            test.stop();
        }

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    display pong(argc,argv);
    pong.run();
}