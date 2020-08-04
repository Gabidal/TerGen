#include <vector>
#include <iostream>

#include "Tile/Tile.h"
#include "Tile/Simplex/FastNoise.h"


#include "Tile/GL/glfw3.h"

using namespace std;
TerGen* t;
int Seed;
FastNoise* sm;
float Freq = 7.0;
float Rought = 2.0;
int TextAmount = 3;

float CX = 0.0;
float CY = 0.0;
float CZ = 0.0;

//FUNCTIONS:
int simplex(Chunk&, vector<long> input) {
    int r = pow(sm->GetPerlin(input[0] * Freq, input[1] * Freq, input[2] * Freq) + 1.0, Rought) / 2.0 * double(TextAmount);
    //int r = ((sm->noise(input[0] / 10000.0f, input[1] / 10000.0f, input[2] / 10000.0f) ) * 5000);
    return r;
}

void reshape()
{
    //if (height == 0 || width == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
    glEnable(GL_DEPTH_TEST);
    glFrustum(-(16.0/9), (16.0 / 9), -1, 1, 0.01, 1000);
    //glOrtho(-10, 10, -10, 10, 0, 1000);
    //gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 0.01, 1000);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, 1920, 1080);  //Use the whole window for rendering
}

int Get_Type(int x, int y, int z) {
    int cx = floor(x / t->Chunk_Size);
    int cy = floor(y / t->Chunk_Size);
    int cz = floor(z / t->Chunk_Size);

    int ix = x % t->Chunk_Size;
    int iy = y % t->Chunk_Size;
    int iz = z % t->Chunk_Size;

    Chunk& c = t->Chunks[cx + cy * t->Scale + cz * t->Scale * t->Scale];

    return c[ix + iy * t->Chunk_Size + iz * t->Chunk_Size * t->Chunk_Size].Type;
    //return t->Chunks[0][x + y * t->Chunk_Size + z * t->Chunk_Size * t->Chunk_Size].Type;
}

void Generate_Map(int chunk_amount, int chunk_scale, float Freq, float Rought, int TextAmount) {
    Freq = Freq;
    Rought = Rought;
    TextAmount = TextAmount;
    sm = new FastNoise();
    t = new TerGen(chunk_amount, chunk_scale);
    t->Add_Function(simplex);
    t->Apply_Functions();
}

void DrawCube(float red, float green, float blue, float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glLoadIdentity();
    glTranslatef(x - CX, y - CY, z - CZ);
    glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(red*0.5, green*0.5, blue*0.5);    // 
    glVertex3f(1.0f, 1.0f, -1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, -1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f(1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(red*0.5, green*0.5, blue*0.5);    // 
    glVertex3f(1.0f, -1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f(1.0f, -1.0f, -1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(red * 0.5, green * 0.5, blue * 0.5);    // 
    glVertex3f(1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(red * 0.5, green * 0.5, blue * 0.5);    // 
    glVertex3f(1.0f, -1.0f, -1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f, -1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f(1.0f, 1.0f, -1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(red*0.1, green * 0.1, blue * 0.1);    // 
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f, -1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f, -1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(red, green, blue);    // 
    glVertex3f(1.0f, 1.0f, -1.0f);    // Top Right Of The Quad (Right)
    glVertex3f(1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f(1.0f, -1.0f, -1.0f);    // Bottom Right Of The Quad (Right)
    glEnd();            // End Drawing The Cube
}

void Update() {
    for (int x = 0; x < t->Scale; x++)
        for (int y = 0; y < t->Scale; y++)
            for (int z = 0; z < t->Scale; z++)
                for (int ix = 0; ix < t->Chunk_Size; ix++)
                    for (int iy = 0; iy < t->Chunk_Size; iy++)
                        for (int iz = 0; iz < t->Chunk_Size; iz++) {
                            int type = Get_Type(ix + x * t->Scale, iy + y * t->Scale, iz + z * t->Scale);
                            if (type == 0) {
                                //void
                            }
                            if (type == 1) {
                                DrawCube(0.0, 1.0, 0.0, ix + x * t->Scale, iy + y * t->Scale, iz + z * t->Scale);
                            }
                            if (type == 2) {
                                DrawCube(0.5, 0.5, 0.5, ix + x * t->Scale, iy + y * t->Scale, iz + z * t->Scale);
                            }
                        }
    glFlush();
}



int main(int argc, char** argv) {

    Generate_Map(2, 16, 7.0, 2.0, 3);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    reshape();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        Update();

        int W = glfwGetKey(window, (int)'W');
        CZ += W * 0.01;
        int A = glfwGetKey(window, (int)'A');
        CX -= A * 0.01;
        int S = glfwGetKey(window, (int)'S');
        CZ -= S * 0.01;
        int D = glfwGetKey(window, (int)'D');
        CX += D * 0.01;
        int C = glfwGetKey(window, 0x20);
        CY += C * 0.01;
        int H = glfwGetKey(window, 0x10);
        CY -= H * 0.01;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

