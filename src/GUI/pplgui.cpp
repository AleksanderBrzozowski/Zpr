#include "pplgui.h"

/**PROPERTIES INITIALIZATION**/
const int PplGUI::RADIUS = 5;

const int PplGUI::PEN_WIDTH = 2;
const Qt::PenStyle PplGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle PplGUI::PEN_CAP = Qt::SquareCap;
const Qt::PenJoinStyle PplGUI::PEN_JOIN = Qt::RoundJoin;
const QColor PplGUI::PEN_COLOR = Qt::black;
const QColor PplGUI::GHOST_PEN_COLOR = QColor(0, 0, 0, 127);

const QPen PplGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE,
                   PEN_CAP, PEN_JOIN);
const QPen PplGUI::GHOST_PEN(GHOST_PEN_COLOR, PEN_WIDTH, PEN_STYLE,
                   PEN_CAP, PEN_JOIN);

const Qt::BrushStyle PplGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor PplGUI::BRUSH_COLOR = QColor(255, 105, 97);
const QColor PplGUI::GHOST_BRUSH_COLOR = QColor(255, 105, 97, 127);

const QBrush PplGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);
const QBrush PplGUI::GHOST_BRUSH(GHOST_BRUSH_COLOR, BRUSH_STYLE);

const int PplGUI::SPEED = 4;
const int PplGUI::OFFSET = GridGUI::SIZE/2 - RoadGUI::SIDEWALK_WIDTH/2;

/*!
 * \brief PplGUI::PplGUI. Constructor.
 * \param pplRect - Rectangle in which human object will be drawn.
 * \param ghost - Bool flag tells whether object is ghost object.
 * \details Constructs human visualization object based on QRect object
 * given as argument.
 */
PplGUI::PplGUI(QRect pplRect, bool ghost) :
    Drawable(ghost), pplRect(pplRect){

}

/*!
 * \brief PplGUI::PplGUI. Constructor.
 * \param x - Position X of human.
 * \param y - Position Y of human.
 * \param ghost - Bool flag tells whether object is ghost object.
 * \details Constructs human visualization based on X and Y position given as
 * arguments.
 */
PplGUI::PplGUI(unsigned int x, unsigned int y, bool ghost) :
    Drawable(ghost),
    pplRect(x - RADIUS/2, y - RADIUS/2,
            RADIUS, RADIUS) {

}

PplGUI::~PplGUI() {

}

/*!
 * \brief PplGUI::setTo.
 * \param x - New X position.
 * \param y - New Y positoin.
 * \details Method moves human to position given with x and y arguments.
 * Position given as arguments is center of object.
 */
void PplGUI::setTo(unsigned int x, unsigned int y) {
    pplRect.setCoords(x - RADIUS/2, y - RADIUS/2,
                      x + RADIUS/2, y + RADIUS/2);
}

/*!
 * \brief PplGUI::draw.
 * \param painter - Reference to painter object.
 * \details Function draws object using painter given as an arrgument.
 * It uses brushes and pens defined in object, and base its choice on
 * whether object is ghost object or not.
 */
void PplGUI::draw(QPainter &painter) const {
    if (isGhost()) {
        painter.setPen(GHOST_PEN);
        painter.setBrush(GHOST_BRUSH);
    } else {
        painter.setPen(PEN);
        painter.setBrush(BRUSH);
    }
    painter.drawEllipse(pplRect);
}

/*!
 * \brief PplGUI::intersects
 * \param rectangle - QRect object that is being checked for intersection.
 * \return Bool value whether rectangles intersects.
 * \details Function checks whether current object's rectangle and rectangle
 * given as argument intersects and returns bool value.
 */
bool PplGUI::intersects(QRect &rectangle) const {
    return pplRect.intersects(rectangle);
}
