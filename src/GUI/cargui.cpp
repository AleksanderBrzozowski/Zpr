#include "cargui.h"


/**PROPERTIES INITIALIZATION**/
const int CarGUI::WIDTH = 8;
const int CarGUI::HEIGHT = 8;

const int CarGUI::PEN_WIDTH = 2;
const Qt::PenStyle CarGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle CarGUI::PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle CarGUI::PEN_JOIN = Qt::RoundJoin;

const QColor CarGUI::PEN_COLOR = QColor(0, 0, 0);
const QColor CarGUI::GHOST_PEN_COLOR = QColor(0, 0, 0, 127);

const QPen CarGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE,
                           PEN_CAP, PEN_JOIN);
const QPen CarGUI::GHOST_PEN(GHOST_PEN_COLOR, PEN_WIDTH,
                           PEN_STYLE, PEN_CAP, PEN_JOIN);

const Qt::BrushStyle CarGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor CarGUI::BRUSH_COLOR = QColor(27,133,184);
const QColor CarGUI::FAST_BRUSH_COLOR = QColor(119, 221, 119);
const QColor CarGUI::GHOST_BRUSH_COLOR = QColor(27,133,184, 127);
const QColor CarGUI::FAST_GHOST_BRUSH_COLOR = QColor(119, 221, 119, 127);

const QBrush CarGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);
const QBrush CarGUI::FAST_BRUSH(FAST_BRUSH_COLOR, BRUSH_STYLE);
const QBrush CarGUI::GHOST_BRUSH(GHOST_BRUSH_COLOR, BRUSH_STYLE);
const QBrush CarGUI::FAST_GHOST_BRUSH(FAST_GHOST_BRUSH_COLOR, BRUSH_STYLE);

const unsigned int CarGUI::CAR_SPEED = 3;
const unsigned int CarGUI::FAST_CAR_SPEED = 5;


/*!
 * \brief CarGUI::CarGUI.
 * \param carRect - QRect object on which car look is based.
 * \param fast - Bool flag whether car is fast car or not.
 * \param ghost - Bool flag whether object is ghost object or not.
 * \details Constructs object based on QRect object given as argument.
 */
CarGUI::CarGUI(QRect carRect, bool fast, bool ghost) :
    Drawable(ghost), carRect(carRect), fast(fast) {

}

/*!
 * \brief CarGUI::CarGUI.
 * \param x - Position X.
 * \param y - Position Y.
 * \param fast - Bool flag whether car is fast car or not.
 * \param ghost - Bool flag whether object is ghost object or not.
 * \details Constructs object based on X and Y position given as arguments.
 * Size of such car is defined in object fields.
 */
CarGUI::CarGUI(unsigned int x, unsigned int y, bool fast, bool ghost) :
    Drawable(ghost), fast(fast),
    carRect(x - WIDTH/2, y - HEIGHT/2,
            WIDTH, HEIGHT) {

}

CarGUI::~CarGUI() {

}

/*!
 * \brief CarGUI::setTo.
 * \param x - Position X.
 * \param y - Position Y.
 * \details Function sets car object to position given as arguments.
 */
void CarGUI::setTo(unsigned int x, unsigned int y) {
    carRect.setCoords(x - WIDTH/2, y - HEIGHT/2,
                      x + WIDTH/2, y + HEIGHT/2);
}

/*!
 * \brief CarGUI::draw.
 * \param painter - Reference to painter object.
 * \details Function draws object using painter given as an arrgument.
 * It uses brushes and pens defined in object, and base its choice on
 * whether object is ghost object or not.
 */
void CarGUI::draw(QPainter &painter) const {
    if(!isGhost()) {
        painter.setPen(PEN);
        if (!fast)
            painter.setBrush(BRUSH);
        else
            painter.setBrush(FAST_BRUSH);
    } else {
        painter.setPen(GHOST_PEN);
        if (!fast)
            painter.setBrush(GHOST_BRUSH);
        else
            painter.setBrush(FAST_GHOST_BRUSH);
    }
    painter.drawRect(carRect);
}

/*!
 * \brief CarGUI::intersects
 * \param rectangle - QRect object that is being checked for intersection.
 * \return Bool value whether rectangles intersects.
 * \details Function checks whether current object's rectangle and rectangle
 * given as argument intersects and returns bool value.
 */
bool CarGUI::intersects(QRect &rectangle) const {
    return carRect.intersects(rectangle);
}
