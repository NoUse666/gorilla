#ifndef GLWIDGET_HH
#define GLWIDGET_HH

#include "includes.hh"
#include "gorilla.hh"
#include "building.hh"
#include "banana.hh"
#include "control.hh"
#include "mainwindow.hh"

class Field;
class Control;
class MainWindow;
class Gorilla;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void printText( QString text );

    inline void setX(float d) { x = d; }
    inline float getX() { return x; }
    inline void setY(float d) { y = d; }
    inline float getY() { return y; }
    inline void setZ(float d) { z = d; }
    inline float getZ() { return z; }

    void accelerate(float dx, float dy, float dz, bool stop);

    inline void setControl(Control *control) { mpControl = control; }

    inline void setWindow( MainWindow *w ) { mWindow = w; }

    void addBuilding( Building *_b );

    inline Gorilla *getActiveGorilla();

    void drawWind( vec3 wind );

    void mousePressEvent(QMouseEvent *pMouseEvent);
    void mouseReleaseEvent(QMouseEvent *pMouseEvent);
    void mouseMoveEvent(QMouseEvent *pMouseEvent);
    void wheelEvent(QWheelEvent *pWheelEvent);
    void createShaderProgram(GLuint &vs, GLuint &fs, GLuint &prog, const std::string &vsFileName, const std::string &fsFileName);
    void setupShaderUniforms(GLuint _program, int _scene);
private:

    MainWindow *mWindow;

    Control *mpControl;

    float x;
    float y;
    float z;
    float speedX, speedY, speedZ;

};

#endif // GLWIDGET_HH
