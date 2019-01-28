#ifndef POINT_H
#define POINT_H

class Point
{
    public:
    float x;
    float y;
    Point() : x(0.0), y(0.0)
    {

    }
    Point(float _x, float _y)
    {
        this->x = _x;
        this->y = _y;
    }
    Point(const Point &inny)
    {
        this->x = inny.x;
        this->y = inny.y;
    }
    void mul(float _x, float _y)
    {
        this->x *= _x;
        this->y *= _y;
    }
    int getIntX() {   return int(this->x); }
    int getIntY() {   return int(this->y); }
};

#endif // POINT_H
