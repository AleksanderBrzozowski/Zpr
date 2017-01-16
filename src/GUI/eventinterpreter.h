#ifndef EVENTINTERPRETER_H
#define EVENTINTERPRETER_H

#include "../Point.h"
#include <memory>
#include <Map.h>
#include "drawable.h"
#include "cargui.h"
#include "roadgui.h"
#include "buildinggui.h"
#include "cameragui.h"
#include "qevent.h"

class EventInterpreter: public QObject {
    Q_OBJECT
public:
    enum class Option {setRoad, setCar, setFastCar, setBuilding, setCamera,
                       setHuman, doNothing};

    EventInterpreter();

    void mouseMoved(int x, int y);
    void mouseClicked(int x, int y);
    void steerCamera(int keyCode);
    void setMap(std::shared_ptr<Map> map);

    void snapToGridCenter(Point& point) const;
    void snapToGridIntersect(Point& point) const;
    std::shared_ptr<Drawable> setCurrentOption(Option option);
    Option getCurrentOption();
signals:
    void roadCreated(RoadGUI*);
    void drawableCreated(Drawable*);
    void cameraCreated(CameraGUI*);
private:
    enum class buildingSize {small, big, high, wide};
    Option currentOption;
    Point anchor;
    bool anchorValid;
    std::shared_ptr<Drawable> ghostObject;
    std::shared_ptr<RoadGUI> ghostRoad;
    std::shared_ptr<CameraGUI> ghostCamera;
    std::shared_ptr<Map> map;
};

#endif // EVENTINTERPRETER_H
