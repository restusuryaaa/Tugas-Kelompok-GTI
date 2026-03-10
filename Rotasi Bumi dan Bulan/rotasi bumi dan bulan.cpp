#include <GL/glut.h>
#include <cmath>

float rotasiBumi = 0.0f;  // Rotasi Bumi pada porosnya
float orbitBulan = 0.0f;  // Pergerakan Bulan mengelilingi Bumi
float rotasiBulan = 0.0f; // Rotasi Bulan pada porosnya sendiri (Baru)

void drawCircle(float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (int i = 0; i <= 60; i++) {
        float angle = 2.0f * 3.14159f * i / 60;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // --- 1. BUMI (Pusat) ---
    glPushMatrix();
        glRotatef(rotasiBumi, 0, 0, 1); 
        drawCircle(0.2f, 0.2f, 0.5f, 1.0f); // Bumi
        
        // Garis penanda rotasi Bumi
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES); 
            glVertex2f(-0.2f, 0); glVertex2f(0.2f, 0); 
        glEnd();
    glPopMatrix();

    // --- 2. BULAN (Orbit & Rotasi Poros) ---
    glPushMatrix();
        glRotatef(orbitBulan, 0, 0, 1);   // 1. Orbit mengelilingi Bumi
        glTranslatef(0.6f, 0.0f, 0.0f);  // 2. Jarak dari Bumi
        
        glPushMatrix();                   // 3. Simpan posisi pusat Bulan
            glRotatef(rotasiBulan, 0, 0, 1); // 4. Rotasi pada poros Bulan
            drawCircle(0.06f, 0.8f, 0.8f, 0.8f); // Gambar Bulan
            
            // Garis penanda rotasi Bulan agar terlihat berputar
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex2f(-0.06f, 0); glVertex2f(0.06f, 0);
            glEnd();
        glPopMatrix();                    // 5. Kembali dari rotasi poros
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int) {
    rotasiBumi += 1.5f; 
    orbitBulan += 0.8f; 
    rotasiBulan += 3.0f; // Bulan berotasi lebih cepat agar terlihat jelas

    if (rotasiBumi > 360) rotasiBumi -= 360;
    if (orbitBulan > 360) orbitBulan -= 360;
    if (rotasiBulan > 360) rotasiBulan -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotasi Bumi dan Rotasi Bulan");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

