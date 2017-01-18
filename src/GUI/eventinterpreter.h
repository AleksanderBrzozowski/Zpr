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

/*!
 * \brief The EventInterpreter class.
 * \details Object responsible for interpretating user input.
 * It has field that remebers current tool chosen by user and
 * using that can interpret maouse and keyboard events properly.
 */
class EventInterpreter: public QObject {
    Q_OBJECT
public:
    /*!
     * \brief The Option enum.
     * \details Enum class describing current tool.
     */
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
    Option currentOption;
    Point anchor;
    bool anchorValid;
    std::shared_ptr<Drawable> ghostObject;
    std::shared_ptr<RoadGUI> ghostRoad;
    std::shared_ptr<CameraGUI> ghostCamera;
    std::shared_ptr<Map> map;
};

#endif // EVENTINTERPRETER_H
