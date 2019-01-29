#ifndef WKRES_H
#define WKRES_H

#include "point.h"

#include <vector>
#include <cmath>
#include <string>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsPixmapItem>

using namespace std;

class Wykres : public QObject
{
    Q_OBJECT

    public:
    QPixmap PixMap;
    QPainter* painter;
    int w, h, scale;

    vector<Point> dane;

    Wykres(int szerokosc, int wysokosc)
    {
        w = szerokosc;
        h = wysokosc;
        scale = 100;

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

    void PobierzDane(vector<Point> _dane)
    {
        this->dane = _dane;
    }

    void Rysuj()
    {
        Point maxDane;
        for(int i=0; i < round(scale*dane.size()/100); i++)
        {
            if(maxDane.x < abs(dane[i].x))  maxDane.x = abs(dane[i].x);

            if(maxDane.y < abs(dane[i].y))  maxDane.y = abs(dane[i].y);
        }
        float skalaX = 0.9*(5.0*w/6.0)/maxDane.x;
        float skalaY = 0.8*(h/2.0)/maxDane.y;

        int BaseX = int(w/6.0);
        int BaseY = int(h/2.0);

        int valY = round(maxDane.y);
        int posY = int(skalaY*valY);

        SetPen(3, Qt::blue);
        painter->setFont( QFont("Arial", 10) );
        for(int i =-1; i < 2; i+= 2)
        {
            painter->drawLine(BaseX - 5, BaseY + (i*(-1)*posY), BaseX + 5,BaseY + (i*(-1)*posY));
            painter->drawText( QPoint(BaseX + 9, BaseY + (i*(-1)*posY) + 5), to_string(i*valY).c_str() );
        }

        int l10 = floor(log10 (maxDane.x));

        if(pow(10, l10)*2.0 > maxDane.x)    l10 = (l10 == 0 ? 0 : l10-1);
        int skok = pow(10, l10);

        for(int i = skok; i < (maxDane.x); i+=skok )
        {
            painter->drawLine(BaseX + skalaX*i, BaseY - 5, BaseX + skalaX*i,BaseY + 5);
            painter->drawText( QPoint(BaseX + skalaX*i - 5, BaseY - 9), to_string(i).c_str() );
        }

        SetPen(2, Qt::red);
        for(int i=1; i < round(scale*dane.size()/100); i++)
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

    public slots:
    void setScale(int value)
    {
        this->scale = value;
        this->Rysuj();
    }
};

#endif // WKRES_H
