#ifndef EVENTINTERPRETER_H
#define EVENTINTERPRETER_H

#include "../Point.h"
#include <memory>
#include "drawable.h"
#include "cargui.h"
#include "roadgui.h"

class EventInterpreter: public QObject {
    Q_OBJECT
public:
    enum class Option {optionSetRoad, optionSetCar, optionDoNothing};

    EventInterpreter();

    void mouseMoved(int x, int y);
    void mouseClicked(int x, int y);

    void snapToGrid(Point& point);
    std::shared_ptr<Drawable> setCurrentOption(Option option);
signals:
    void roadCreated(RoadGUI*);
    void drawableCreated(Drawable*);
private:
    Option currentOption;
    Point anchor;
    bool hasAnchor;
    std::shared_ptr<Drawable> ghostObject;
    std::shared_ptr<RoadGUI> ghostRoad;
};

#endif // EVENTINTERPRETER_H
