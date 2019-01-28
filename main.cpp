#include "mainwindow.h"
#include "point.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <vector>
#include <cmath>
using namespace std;

const int Padding = 10;

class Wykres
{
    public:
    QPixmap PixMap;
    QPainter* painter;
    int w, h;
    Wykres(int szerokosc, int wysokosc)
    {
        w = szerokosc;
        h = wysokosc;
        PixMap = QPixmap(w, h);
        PixMap.fill(Qt::white); // Tło - białe

        painter = new QPainter(&PixMap);

        //Osie
        SetPen(3, Qt::blue);
        painter->drawLine(0, h/2, w, h/2); // Oś OX
        painter->drawLine(w/6, 0, w/6, h); // Oś OY

        // Tu mżna rysować strzałki
    }

    void SetPen(int szerokosc, Qt::GlobalColor color)
    {
        QPen pen( color);
        pen.setWidth(szerokosc);
        painter->setPen(pen);
    }

    void RysujDane(vector<Point> dane)
    {
        SetPen(2, Qt::red);

        Point maxDane;
        for(int i=0; i < dane.size(); i++)
        {
            if(maxDane.x < abs(dane[i].x))  maxDane.x = abs(dane[i].x);

            if(maxDane.y < abs(dane[i].y))  maxDane.y = abs(dane[i].y);
        }
        float skalaX = 0.9*(5.0*w/6.0)/maxDane.x;
        float skalaY = 0.8*(h/2.0)/maxDane.y;

        int BaseX = int(w/6.0);
        int BaseY = int(h/2.0);

        for(int i=1; i < dane.size(); i++)
        {
            Point ostatni(dane[i-1]);
            Point aktualny(dane[i]);

            //Skalowanie
            ostatni.mul(skalaX, skalaY);
            aktualny.mul(skalaX, skalaY);

            //Rysowanie
            painter->drawLine(BaseX+ ostatni.getIntX(), BaseY - ostatni.getIntY(), BaseX + aktualny.getIntX(), BaseY - aktualny.getIntY());
        }
    }

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QPixmap qp = QPixmap(620, 320);
    qp.fill(Qt::black); // Tło - białe

    //Jakieś punkty
    vector<Point> tab;
    Point buff;

    //Gnerowanie sin
    for(int i = 0; i <= 50; i++)
    {
        buff.x = i*2*M_PI/50.0;
        buff.y = sin(buff.x);
        tab.push_back(buff);
    }

    // Wyświetlanie
    Wykres sinusoida(600, 300);
    sinusoida.RysujDane(tab);
    //qp = sinusoida.PixMap.copy(Padding, Padding, sinusoida.w + Padding, sinusoida.h + Padding);
    QPainter p( &qp );
    p.drawPixmap( Padding, Padding, sinusoida.PixMap );

    if(qp.isNull())
    {
        printf("Yes its null\n");
    }
    else
    {
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(qp);
        scene.addItem(item);
    }

    view.show();

    return a.exec();
}
