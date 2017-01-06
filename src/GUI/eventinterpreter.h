#ifndef EVENTINTERPRETER_H
#define EVENTINTERPRETER_H

#include "../Point.h"
#include <memory>
#include "drawable.h"
#include "cargui.h"
#include "roadgui.h"
#include "../TrafficControl.h"

class EventInterpreter: public QObject {
    Q_OBJECT
public:
    enum class Option {setRoad, setCar, setFastCar, doNothing};

    EventInterpreter();

    void mouseMoved(int x, int y);
    void mouseClicked(int x, int y);
    void setTrafficControl(std::shared_ptr<TrafficControl> tc);

    void snapToGrid(Point& point);
    std::shared_ptr<Drawable> setCurrentOption(Option option);
    Option getCurrentOption();
signals:
    void roadCreated(RoadGUI*);
    void drawableCreated(Drawable*);
private:
    Option currentOption;
    Point anchor;
    bool hasAnchor;
    std::shared_ptr<Drawable> ghostObject;
    std::shared_ptr<RoadGUI> ghostRoad;
    std::shared_ptr<TrafficControl> trafficControl;
};

#endif // EVENTINTERPRETER_H
