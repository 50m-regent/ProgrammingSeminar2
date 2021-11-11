void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(0, 1);
    glVertex2d(0, 0);
    glVertex2d(1, 0);
    glEnd();
    glColor3d(1.0, 1.0, 0.0);
    glRasterPos2d(0, 0);
    gluteBitmapCharacter(
        GLUT_BITMAP_8_BY_13, '0'
    );
    glFlush();
}