#include "maparea.h"

MapArea::MapArea(QWidget *parent) :
    QWidget(parent), curOption(optionSetRoad), maxID(0), displayGrid(false) {

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(pal);
}

MapArea::~MapArea() {
    for (const auto &drawable : objectMap)
        delete drawable.second;
}

void MapArea::setCar(int id, int x, int y) {
    if (objectMap[id] == nullptr) {
        objectMap[id] = new CarGUI(2, x, y);
    } else {
        objectMap[id]->setTo(x, y);
    }
    setMaxID(id);
    update();
}

void MapArea::setPpl(int id, int x, int y) {
    if (objectMap[id] == nullptr) {
        objectMap[id] = new PplGUI(2, x, y);
    } else {
        objectMap[id]->setTo(x, y);
    }
    setMaxID(id);
    update();
}


void MapArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (const auto &drawable : objectMap) {
        if(drawable.second->getLayer() == 3)
            drawable.second->draw(painter);
    }
    for (const auto &drawable : objectMap) {
        if(drawable.second->getLayer() == 2)
            drawable.second->draw(painter);
    }

    if(displayGrid)
        GridGUI(1, width(), height()).draw(painter);

    QWidget::paintEvent(event);
}

void MapArea::snapToGrid(Point &point) {
    int x = point.getX() / GUI::GRID_SIZE;
    int y = point.getY() / GUI::GRID_SIZE;
    point.setX(x * GUI::GRID_SIZE + GUI::GRID_SIZE/2);
    point.setY(y * GUI::GRID_SIZE + GUI::GRID_SIZE/2);
}

void MapArea::mouseReleaseEvent(QMouseEvent *event) {
    static bool isSecond = false;
    static Point firstPoint;
    switch (curOption) {
        case optionSetRoad:
            if(!isSecond) {
                firstPoint = Point(event->x(), event->y());
                snapToGrid(firstPoint);
                isSecond = true;
            } else {
                Point secondPoint(event->x(), event->y());
                snapToGrid(secondPoint);
                createRoad(firstPoint, secondPoint);
                isSecond = false;
            }
            break;
        case optionSetCar:
            setCar(100, event->x(), event->y());
            isSecond = false;
            break;
        default:
            isSecond = false;
            break;
    }
    event->accept();
}

void MapArea::createRoad(Point end1, Point end2) {
    objectMap[++maxID] = new RoadGUI(3, end1, end2);
    update();
}

void MapArea::setMaxID(int id) {
    if (id > maxID)
        maxID = id;
}

void MapArea::toggleGrid() {
    displayGrid = !displayGrid;
    update();
}

void MapArea::setCurOption(Option option) {
    curOption = option;
}

