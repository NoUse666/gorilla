#include "glwidget.hh"
#include <QKeyEvent>

GLuint vs_a, fs_a, prog_a;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
    speedX = 0;
    speedY = 0;
    speedZ = 0;
    this->setMouseTracking(true);
}

GLWidget::~GLWidget()
{
    //delete mpControl;
}

float colors[][3] = {{1.f, 1.f, 1.f}, //white
                     {0.f, 1.f, 1.f},
                     {1.f, 0.f, 1.f},
                     {1.f, 1.f, 0.f},
                     {0.f, 0.f, 1.f},
                     {0.f, 1.f, 0.f},
                     {1.f, 0.f, 0.f},
                     {.5f, 1.f, 1.f},
                     {1.f, .5f, 1.f},
                     {1.f, 1.f, .5f},
                     {.5f, .5f, 1.f},
                     {.5f, 1.f, .5f},
                     {1.f, .5f, .5f},
                     {.5f, .5f, .5f},
                     {0.f, .5f, 1.f},
                     {0.f, 1.f, .5f},
                     {.5f, 0.f, 1.f},
                     {1.f, 0.f, .5f},
                     {.5f, 1.f, 0.f},
                     {1.f, .5f, 0.f}
                    };

void GLWidget::initializeGL()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);

    int argc = 1;
    char *argv[] = {""};

    glutInit( &argc, argv );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Perspektivische Darstellung
    gluPerspective(45.0,16.f/9.f ,0.1f,250.f);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);

    glEnable( GL_LIGHTING );

    //glEnable ( GL_LINE_SMOOTH );

    glEnable( GL_DEPTH_CLAMP );

    glEnable ( GL_COLOR_MATERIAL ) ;

    glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );

    glEnable(GL_MULTISAMPLE);

    glViewport(0,0,1280,720);

    string shaderCode = readFromFile("shader.vsh");

    GLint err = glewInit();

    if (err != GLEW_OK )
        exit(1);
    else if (!GLEW_VERSION_1_2_1)
        exit(1);

    const char* code = shaderCode.c_str();

    prog_a = glCreateProgram();

    vs_a = glCreateShader( GL_VERTEX_SHADER );


}

clock_t t1 = clock(), t2 = clock();

void GLWidget::paintGL()
{

    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    resizeGL( 1280, 720 );

    //glRotatef(-90.f, 1.f, 0.f, 0.f);
    vec3 d = mpControl->getCamera()->getDirection();
    vec3 p = mpControl->getCamera()->getPosition();
    d = d + p;
    vec3 u = mpControl->getCamera()->getUp();

    float light[4] = {-45.f,100.f,45.f,1.f};

    gluLookAt( p.x, p.y, p.z, d.x, d.y, d.z, u.x, u.y, u.z );

    glTranslatef( x,y,z );

    glLightfv(GL_LIGHT1, GL_POSITION, light );



    // draw ground plate
    glBegin( GL_QUADS );
    glColor3f( 0.3f, 0.3f, 0.3f );
    glVertex3f( -20.f, 0.f, -20.f );
    glVertex3f( -20.f, 0.f, 20.f );
    glVertex3f( 20.f, 0.f, 20.f );
    glVertex3f( 20.f, 0.f, -20.f );
    glEnd();

    for (vector<Building*>::iterator it = mpControl->getBuildings()->begin(); it != mpControl->getBuildings()->end(); it++ )
    {
        Building *g = (Building*)*it;
        g->draw();
    }

    for (vector<Gorilla*>::iterator it = mpControl->getGorillas()->begin(); it != mpControl->getGorillas()->end(); it++ )
    {
        Gorilla *g = (Gorilla*)*it;
        g->draw();
    }

    for (vector<Banana*>::iterator it = mpControl->getBananas()->begin(); it != mpControl->getBananas()->end(); it++ )
    {
        Banana *b = (Banana*)*it;
        b->draw();
    }

    drawWind( mpControl->getPhysics()->getWind() );

    glFlush();
    glPopMatrix();

    //printText( QString( "test" ) );

    t2 = clock();
    float dT = (float)(t2-t1)/(float)CLOCKS_PER_SEC;

    update();
    mpControl->update( dT );

    t1 = t2;

}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Perspektivische Darstellung
    gluPerspective(45.0,(float)w/h ,0.1f,200.f);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::printText( QString text )
{

    QPainter painter(this);
    QFontMetrics metrics = QFontMetrics(font());
    int border = qMax(4, metrics.leading());

    QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125),
                               Qt::AlignCenter | Qt::TextWordWrap, text);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.fillRect(QRect(0, 0, width(), rect.height() + 2*border),
              QColor(0, 0, 0, 127));
    painter.setPen(Qt::white);
    painter.fillRect(QRect(0, 0, width(), rect.height() + 2*border),
               QColor(0, 0, 0, 127));
    painter.drawText((width() - rect.width())/2, border,
               rect.width(), rect.height(),
               Qt::AlignCenter | Qt::TextWordWrap, text);
    painter.end();
}

void GLWidget::mousePressEvent(QMouseEvent *pMouseEvent)
{
    mpControl->mousePressEvent(pMouseEvent);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
    mpControl->mouseReleaseEvent(pMouseEvent);
}

int xc=-1, yc=-1;
void GLWidget::mouseMoveEvent(QMouseEvent *pMouseEvent)
{
    if (xc==-1)
    {
        xc = pMouseEvent->globalX();
        yc = pMouseEvent->globalY();
    }

    QPoint *oRelative = new QPoint(pMouseEvent->globalX() - xc, pMouseEvent->globalY() - yc);
    mpControl->mouseMoveEvent(pMouseEvent, *oRelative);
    xc = pMouseEvent->globalX();
    yc = pMouseEvent->globalY();
}

void GLWidget::wheelEvent(QWheelEvent *pWheelEvent)
{
    mpControl->wheelEvent(pWheelEvent);
}

void GLWidget::addBuilding( Building *_b )
{
    mpControl->addBuilding( _b );
}

Gorilla *GLWidget::getActiveGorilla()
{
    return mpControl->getActiveGorilla();
}

void GLWidget::drawWind(vec3 wind)
{
    vec3 pos = getActiveGorilla()->getPos()+vec3( 0,0.6f,0 );
    vec3 start = pos - wind/10;
    vec3 ende = start + wind/5;

    vec3 l = ende + rotateY( -wind, 30.f ).normalize()*wind.length()*0.05f;
    vec3 r = ende + rotateY( -wind, -30.f ).normalize()*wind.length()*0.05f;

    glColor3f( 0.f,0.f,1.f );
    glBegin( GL_LINES );
    glVertex3f( start.x, start.y, start.z );
    glVertex3f( ende.x, ende.y, ende.z );
    glVertex3f( ende.x, ende.y, ende.z );
    glVertex3f( l.x, l.y, l.z );
    glVertex3f( ende.x, ende.y, ende.z );
    glVertex3f( r.x, r.y, r.z );
    glEnd();
}


