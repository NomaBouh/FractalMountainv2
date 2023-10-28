#include <GL/glut.h>
#include "PerlinNoise.h" // Assurez-vous que votre classe PerlinNoise est définie ici

const int WIDTH = 800;
const int HEIGHT = 600;
const int GRID_SIZE = 100;
float terrain[GRID_SIZE][GRID_SIZE];

PerlinNoise pn;

void generateTerrain() {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            double value = 0;
            double freq = 0.1; // Fréquence initiale
            double amp = 10.0; // Amplitude initiale

            // Superposez quelques octaves pour un effet fractal
            for (int o = 0; o < 4; o++) {
                value += pn.noise(x * freq, y * freq) * amp;
                freq *= 2; // Double la fréquence à chaque octave
                amp *= 0.5; // Réduit l'amplitude de moitié à chaque octave
            }

            terrain[x][y] = value;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int x = 0; x < GRID_SIZE - 1; x++) {
        for (int y = 0; y < GRID_SIZE - 1; y++) {

            // Premier triangle
            glBegin(GL_LINES);

            glVertex3f(x, y, terrain[x][y]);
            glVertex3f(x + 1, y, terrain[x + 1][y]);

            glVertex3f(x + 1, y, terrain[x + 1][y]);
            glVertex3f(x, y + 1, terrain[x][y + 1]);

            glVertex3f(x, y + 1, terrain[x][y + 1]);
            glVertex3f(x, y, terrain[x][y]);

            glEnd();

            // Deuxième triangle
            glBegin(GL_LINES);

            glVertex3f(x + 1, y, terrain[x + 1][y]);
            glVertex3f(x + 1, y + 1, terrain[x + 1][y + 1]);

            glVertex3f(x + 1, y + 1, terrain[x + 1][y + 1]);
            glVertex3f(x, y + 1, terrain[x][y + 1]);

            glVertex3f(x, y + 1, terrain[x][y + 1]);
            glVertex3f(x + 1, y, terrain[x + 1][y]);

            glEnd();
        }
    }
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Montagne fractale avec le bruit de Perlin");
    glEnable(GL_DEPTH_TEST);
    glOrtho(0, GRID_SIZE, 0, GRID_SIZE, -20, 20);
    glRotatef(45, 1, 0, 0); // Vue en angle pour mieux voir la 3D
    glTranslatef(0, 0, -15);  // Éloignez la caméra de 15 unités
    generateTerrain();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
