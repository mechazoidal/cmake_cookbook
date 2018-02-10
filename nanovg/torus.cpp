// An OpenGL3 Exmaple: glew, glfw and nanovg.
// 2D and 3D in same scene. Torus is drawn with static display list.
 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "GL/glew.h"

#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"
 
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

 
// Event Handlers

struct Mouse {
    float x;
    float y;
};

struct Mouse mouse = {0,0};
bool isTracking = false;

static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

static void OnMouseMove(GLFWwindow* window, double x, double y)
{
    mouse.x = x;
    mouse.y = y;
}

static void OnMouseDown(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        isTracking = !isTracking;
    }
}

static void OnResize(GLFWwindow * window, int w, int h){
    glfwSetWindowSize(window, w,h);
}


// Draw

static void drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius)
{
    static double PI = 3.1415926535897932384626433832795;

    double majorStep = 2.0 * PI / numMajor;
    double minorStep = 2.0 * PI / numMinor;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (int i = 0; i < numMajor; ++i) {

        double a0 = i * majorStep;
        double a1 = a0 + majorStep;
        GLdouble x0 = cos(a0);
        GLdouble y0 = sin(a0);
        GLdouble x1 = cos(a1);
        GLdouble y1 = sin(a1);

        glBegin(GL_TRIANGLE_STRIP);

            for (int j = 0; j <= numMinor; ++j) {
                double b = j * minorStep;
                GLdouble c = cos(b);
                GLdouble r = minorRadius * c + majorRadius;
                GLdouble z = minorRadius * sin(b);

                glNormal3d(x0 * c, y0 * c, z / minorRadius);
                glTexCoord2d(i / (GLdouble) numMajor, j / (GLdouble) numMinor);
                glVertex3d(x0 * r, y0 * r, z);

                glNormal3d(x1 * c, y1 * c, z / minorRadius);
                glTexCoord2d((i + 1) / (GLdouble) numMajor, j / (GLdouble) numMinor);
                glVertex3d(x1 * r, y1 * r, z);
            }

        glEnd();
    }
}


int main(){

    GLFWwindow * window;
    NVGcontext *vg;

    int width = 800;
    int height = 600;  
    
    if (!glfwInit()) {
        printf("Could not initialize glfw.\n");
        return -1; 
    } 

    // Initialize window
    window = glfwCreateWindow(width, height, "solidmcp", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }        
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        printf("Could not initialize glew.\n");
        return -1;
    }
    glGetError();

    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
        printf("Could not initialize nanovg.\n");
        return -1;
    }
    // FIXME should insert this at compile time using fc-config and cmake macro
    //int font = nvgCreateFont(vg, "font", "../example/Roboto-Regular.ttf");
    int font = nvgCreateFont(vg, "font", "/usr/local/share/fonts/roboto/Roboto-Regular.ttf");
    if (font < 0) {
        printf("nvgCreateFont() failed\n");
        return -1;
    }

    //callbacks
    glfwSetKeyCallback(window, OnKeyDown);
    glfwSetWindowSizeCallback(window, OnResize);
    glfwSetCursorPosCallback(window, OnMouseMove );
    glfwSetMouseButtonCallback(window, OnMouseDown );

    glfwSwapInterval(1);

    while( !glfwWindowShouldClose(window)){  

        // set viewport
        glfwGetFramebufferSize(window, &width, &height);

        float ratio = (float) width / height;
        glViewport(0,0,width,height); 

        glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();        
        gluPerspective(60, ratio, .1, 100);
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity(); 
        gluLookAt(0,0,5, 0, 0, -1, 0, 1, 0);     

        if(isTracking) {
            glRotatef(mouse.x, 0, 1, 0);
            glRotatef(mouse.y, 1, 0, 0);
        }

        // Draw Stuff
        drawTorus(20, 10, 1, 0.5);

        nvgBeginFrame(vg, width, height, ratio);
            // Reset polygon mode
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            nvgFontSize(vg, 100);
            nvgFontFace(vg, "font");
            nvgFillColor(vg, nvgRGBA(0, 0, 255, 255));
            nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
            nvgText(vg, 10, 10, "OpenGL2 Exmaple", NULL);

        nvgEndFrame(vg);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    nvgDeleteGL2(vg);
    glfwTerminate();
    glfwDestroyWindow(window);
    return 0;
}
