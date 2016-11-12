#ifndef MAPAREA_H
#define MAPAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include "drawable.h"
#include "cargui.h"
#include "pplgui.h"
#include "gridgui.h"
#include "roadgui.h"
#include "../Point.h"

class MapArea : public QWidget
{
    Q_OBJECT
public:
    enum Option {optionSetRoad, optionSetCar};
    explicit MapArea(QWidget *parent = 0);
    ~MapArea();

    void paintEvent(QPaintEvent *event);

    void setCar(int id, int x, int y);
    void setPpl(int id, int x, int y);
    void createRoad(Point end1, Point end2);

    void snapToGrid(Point &point);
    void setMaxID(int id);
    void setCurOption(Option option);

    void mouseReleaseEvent(QMouseEvent *event) override;
signals:

public slots:
    void toggleGrid();

private:
    int maxID;
    std::map<int, Drawable*> objectMap;
    Option curOption;
    bool displayGrid;



};

#endif // MAPAREA_H
