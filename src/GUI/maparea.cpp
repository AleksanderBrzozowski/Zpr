#include "maparea.h"

MapArea::MapArea(QWidget *parent) : QWidget(parent), roadID(0), displayGrid(false) {

    connect(&eventInterpreter, &EventInterpreter::drawableCreated, this, &MapArea::registerDrawable);
    connect(&eventInterpreter, &EventInterpreter::roadCreated, this, &MapArea::registerRoad);
    connect(&eventInterpreter, &EventInterpreter::cameraCreated, this, &MapArea::registerCamera);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(196, 195, 208));
    setAutoFillBackground(true);
    setPalette(pal);

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

MapArea::~MapArea() {
    for (const auto &drawable : movableMap)
        delete drawable.second;

    for (const auto &road : roadMap)
        delete road.second;
}

void MapArea::setCar(const unsigned int id, const unsigned int x, const unsigned int y,
                     const bool fast) {
    if (movableMap[id] == nullptr) {
        movableMap[id] = new CarGUI(2, x, y, fast);
    } else {
        movableMap[id]->setTo(x, y);
    }
    update();
}

void MapArea::setPpl(const unsigned int id, const unsigned int x, const unsigned int y) {
    if (movableMap[id] == nullptr) {
        movableMap[id] = new PplGUI(2, x, y);
    } else {
        movableMap[id]->setTo(x, y);
    }
    update();
}

void MapArea::removeObject(const unsigned int id) {
    if (movableMap[id] != nullptr) {
        delete movableMap[id];
        movableMap.erase(id);
    }
}

void MapArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (const auto &road : roadMap) {
        road.second->drawSidewalk(painter);
    }

    for (const auto &drawable : roadMap) {
            drawable.second->draw(painter);
    }
    for (const auto &drawable : movableMap) {
            drawable.second->draw(painter);
    }
    for (const auto &drawable : objectMap) {
        drawable->draw(painter);
    }
    for (const auto &drawable : cameraMap) {
        drawable->draw(painter);
    }


    if(ghost != nullptr)
        ghost->draw(painter);

    if(displayGrid)
        GridGUI(1, width(), height()).draw(painter);

  //  QWidget::paintEvent(event);
}

void MapArea::snapToGrid(Point &point) {
    int x = point.getX() / GridGUI::SIZE;
    int y = point.getY() / GridGUI::SIZE;
    point.setX(x * GridGUI::SIZE + GridGUI::SIZE/2);
    point.setY(y * GridGUI::SIZE + GridGUI::SIZE/2);
}



void MapArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        eventInterpreter.mouseClicked(event->x(), event->y());
        event->accept();
    }
}

void MapArea::mouseMoveEvent(QMouseEvent *event) {
    eventInterpreter.mouseMoved(event->x(), event->y());
    event->accept();
    update();
}

void MapArea::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key == Qt::Key_Escape)
        setCurrentOption(EventInterpreter::Option::doNothing);
    else if (key == Qt::Key_Up || key == Qt::Key_Down ||
             key == Qt::Key_Left || key == Qt::Key_Right)
        eventInterpreter.steerCamera(key);
    else
        QWidget::keyPressEvent(event);
	update();
    event->accept();

}

void MapArea::registerCamera(CameraGUI *cam) {
    cameraMap.push_back(cam);
    update();
}

void MapArea::createRoad(Point end1, Point end2) {
    roadMap[++roadID] = new RoadGUI(3, end1, end2);
    update();
}


void MapArea::toggleGrid() {
    displayGrid = !displayGrid;
    update();
}

void MapArea::setCurrentOption(EventInterpreter::Option option) {
    ghost = eventInterpreter.setCurrentOption(option);
}

void MapArea::registerRoad(RoadGUI *road) {
    roadMap[++roadID] = road;
    update();
}

void MapArea::registerDrawable(Drawable *drawable) {
    objectMap.push_back(drawable);
    update();
}

void MapArea::setMap(std::shared_ptr<Map> map) {
    eventInterpreter.setMap(map);
}
