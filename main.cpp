#include "mainwindow.h"
#include "point.h"
#include "wykres.h"
#include <QApplication>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QObject>

using namespace std;

const int Padding = 10;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap qp = QPixmap(620, 350);
    qp.fill(Qt::black); // Tło - białe

    //Jakieś punkty
    vector<Point> tab;
    Point buff;

    //Gnerowanie sin
    for(int i = 0; i <= 500; i++)
    {
        buff.x = i*3*M_PI/500.0;
        buff.y = sin(buff.x);
        tab.push_back(buff);
    }

    // Wyświetlanie
    Wykres sinusoida(600, 300);
    sinusoida.PobierzDane(tab);
    sinusoida.Rysuj();

    //qp = sinusoida.PixMap.copy(Padding, Padding, sinusoida.w + Padding, sinusoida.h + Padding);
    QPainter p( &qp );
    p.drawPixmap( Padding, Padding + 30, sinusoida.PixMap );

    QSlider Suwak(Qt::Horizontal);
    Suwak.setRange(1, 100);
    QObject::connect(&Suwak, SIGNAL(valueChanged(int)), &sinusoida, SLOT(setScale(int)));

    QGraphicsScene scene;
    QGraphicsPixmapItem item(qp);
    scene.addItem(&item);
    scene.addWidget(&Suwak);

    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}
