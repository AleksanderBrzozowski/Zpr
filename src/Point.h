//
// Created by Aleksander on 29.10.2016.
//

#ifndef ZPR_POINT_H
#define ZPR_POINT_H


class Point {

private:
    int x,y;
public:
    Point(int x, int y);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;
};


#endif //ZPR_POINT_H
