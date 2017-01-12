#ifndef EVENTINTERPRETER_H
#define EVENTINTERPRETER_H

#include "../Point.h"
#include <memory>
#include "drawable.h"
#include "cargui.h"
#include "roadgui.h"
#include "buildinggui.h"
#include "cameragui.h"
#include "qevent.h"
#include "../TrafficControl.h"

class EventInterpreter: public QObject {
    Q_OBJECT
public:
    enum class Option {setRoad, setCar, setFastCar, setBuilding, setCamera, doNothing};

    EventInterpreter();

    void mouseMoved(int x, int y);
    void mouseClicked(int x, int y);
    void steerCamera(int keyCode);
    void setTrafficControl(std::shared_ptr<TrafficControl> tc);

    void snapToGridCenter(Point& point) const;
    void snapToGridIntersect(Point& point) const;
    std::shared_ptr<Drawable> setCurrentOption(Option option);
    Option getCurrentOption();
signals:
    void roadCreated(RoadGUI*);
    void drawableCreated(Drawable*);
private:
    enum class buildingSize {small, big, high, wide};
    Option currentOption;
    Point anchor;
    bool anchorValid;
    std::shared_ptr<Drawable> ghostObject;
    std::shared_ptr<RoadGUI> ghostRoad;
    std::shared_ptr<CameraGUI> ghostCamera;
    std::shared_ptr<TrafficControl> trafficControl;
};

#endif // EVENTINTERPRETER_H
