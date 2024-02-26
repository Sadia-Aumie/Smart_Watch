#include <GL/glut.h>
#include <ctime>
#include <cmath>

// Function to draw the clock
void drawClock() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Get current time
    time_t currentTime = time(nullptr);
    struct tm *localTime = localtime(&currentTime);
    int hours = localTime->tm_hour % 12; // Convert to 12-hour format
    int minutes = localTime->tm_min;
    int seconds = localTime->tm_sec;

    // Draw clock circle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0); // White color
    glVertex2f(0.0, 0.0); // Center of the clock
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159265f / 180.0f;
        float x = 0.5 * cos(angle);
        float y = 0.5 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw clock hands
    glLineWidth(2.0);

    // Hour hand
    glColor3f(0.0, 0.0, 0.0); // Black color
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.3 * cos((hours % 12 + minutes / 60.0) * 30 * 3.14159265 / 180),
               0.3 * sin((hours % 12 + minutes / 60.0) * 30 * 3.14159265 / 180));
    glEnd();

    // Minute hand
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.4 * cos(minutes * 6 * 3.14159265 / 180),
               0.4 * sin(minutes * 6 * 3.14159265 / 180));
    glEnd();

    // Second hand
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.4 * cos(seconds * 6 * 3.14159265 / 180),
               0.4 * sin(seconds * 6 * 3.14159265 / 180));
    glEnd();

    glFlush();
}

// Function to update the clock every second
void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000, update, 0);
}

// Function to handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Clock");

    glutDisplayFunc(drawClock);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0); // Start the timer

    glutMainLoop();
    return 0;
}
