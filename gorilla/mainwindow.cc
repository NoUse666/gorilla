#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gorilla.hh"
#include "glwidget.hh"
#include <iostream>
#include <QKeyEvent>

const int NUM_BUILDINGS = 48;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    mpControl = new Control(ui->widget);

    srand(time(NULL));

    Building **buildings;

    bool buildingsTaken[NUM_BUILDINGS];

    buildings = new Building*[NUM_BUILDINGS];
    for (int i=0; i<NUM_BUILDINGS; i++)
    {
        bool collide = false;
        buildingsTaken[i] = false;
        do
        {
            vec3 pos;
            pos.x = (float)(rand()%30) - 15;
            pos.z = (float)(rand()%30) - 15;
            pos.y = 0;
            float w = (float)(rand()%3)+2;
            float d = (float)(rand()%3) + 2;
            float h = (float)(rand()%10) + 5;
            float r = (float)(rand()%64) / 255 + 0.3f;
            float g = (float)(rand()%64) / 255 + 0.3f;
            float b = (float)(rand()%64) / 255 + 0.3f;
            vec3 color = vec3(r,g,b);
            buildings[i] = Building::getBuilding(w, h, d, pos, color);
            for (int j=0; j<i; j++)
            {
                collide = buildings[i]->collide(buildings[j]);
                if (collide)
                    j=i;
            }
        } while (collide);
        mpControl->addBuilding( buildings[i] );
    }

    Gorilla **gorilla = new Gorilla *[4];
    for (int i=0; i<4; i++ )
    {
        int p; bool tooClose=false;
        int k=1;
        do
        {
            p = rand()%NUM_BUILDINGS;
            for ( int j=0; j<i; j++ )
            {
                tooClose = (buildings[p]->getPos() + vec3(0,1.f,0)*buildings[p]->getHeight() - gorilla[j]->getPos()).length() < 15.f - (k%5) ;
                if (tooClose) j = i;
            }
            k++;
        } while (buildingsTaken[p] || tooClose);
        buildingsTaken[p] = true;
        vec3 pos = buildings[p]->getPos();
        pos.y = buildings[p]->getHeight();
        gorilla[i] = new Gorilla();
        gorilla[i]->setPos(pos);
        gorilla[i]->setColor(.5f, 0.3f, 0.f);
        mpControl->addGorilla( gorilla[i] );
    }

    gorilla[0]->setActive( true );

    ui->widget->repaint();
    ui->widget->setControl(mpControl);

    setWindowTitle( "Gorilla " );

    setMouseTracking(true);
    ui->widget->setWindow( this );

    gorilla[0]->moveCameraTo( mpControl->getCamera() );

}

MainWindow::~MainWindow()
{
    delete mpControl;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        qApp->quit();
    else
        mpControl->keyPressed(event);

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    mpControl->keyReleased(event);
}

