#include "buildinggui.h"

/**PROPERTIES INITIALIZE**/
const int BuildingGUI::PEN_WIDTH = 2;
const Qt::PenStyle BuildingGUI::PEN_STYLE = Qt::SolidLine;
const Qt::PenCapStyle BuildingGUI::PEN_CAP = Qt::RoundCap;
const Qt::PenJoinStyle BuildingGUI::PEN_JOIN = Qt::RoundJoin;

const QColor BuildingGUI::PEN_COLOR = QColor(0, 0, 0, 255);
const QColor BuildingGUI::GHOST_PEN_COLOR = QColor(0, 0, 0, 127);

const QPen BuildingGUI::PEN(PEN_COLOR, PEN_WIDTH, PEN_STYLE, PEN_CAP, PEN_JOIN);
const QPen BuildingGUI::GHOST_PEN(GHOST_PEN_COLOR, PEN_WIDTH, PEN_STYLE, PEN_CAP, PEN_JOIN);


const Qt::BrushStyle BuildingGUI::BRUSH_STYLE = Qt::SolidPattern;
const QColor BuildingGUI::BRUSH_COLOR = QColor(255, 179, 71);

const QColor BuildingGUI::GHOST_BRUSH_COLOR = QColor(255, 179, 71, 127);

const QBrush BuildingGUI::BRUSH(BRUSH_COLOR, BRUSH_STYLE);
const QBrush BuildingGUI::GHOST_BRUSH(GHOST_BRUSH_COLOR, BRUSH_STYLE);

/*!
 * \brief BuildingGUI::BuildingGUI. Constructor
 * \param buildingRect - QRect object on which building is based.
 * \param ghost - flag wheter created object is ghost object or not.
 * \details Creates BuildingGUI object based on QRect object.
 */
BuildingGUI::BuildingGUI(QRect buildingRect, bool ghost) :
    Drawable(ghost), buildingRect(buildingRect) {

}

/*!
 * \brief BuildingGUI::BuildingGUI. Constructor
 * \param x - position X of center of top left grid of building.
 * \param y - position Y of center of top left grid of building.
 * \param width - building's width.
 * \param height - building's height.
 * \param ghost - flag whether object is ghost object.
 * \details Creates building based on X, Y position and width and height parameters.
 * Building's top left corner is moved from the X, Y position by half of grid size
 * towartds top left.
 */
BuildingGUI::BuildingGUI(unsigned int x, unsigned int y,
                         unsigned int width, unsigned int height, bool ghost) :
    Drawable(ghost), buildingRect(x - GridGUI::SIZE/2, y - GridGUI::SIZE/2, width, height) {

}

BuildingGUI::~BuildingGUI() {

}

/*!
 * \brief BuildingGUI::draw.
 * \param painter - Reference to painter object.
 * \details Function draws object using painter given as an argument.
 * It uses brushes, and pens defined in object, and base its choice on
 * whether it is ghost object or not.
 */
void BuildingGUI::draw(QPainter &painter) const {
    if(!isGhost()) {
        painter.setPen(PEN);
        painter.setBrush(BRUSH);
    } else {
        painter.setPen(GHOST_PEN);
        painter.setBrush(GHOST_BRUSH);
    }
    painter.drawRect(buildingRect);
}

/*!
 * \brief BuildingGUI::setTo.
 * \param x - position X of center of top left grid of building.
 * \param y - position Y of center of top left grid of building.
 * \details Function moves object to point given as arguments.
 */
void BuildingGUI::setTo(unsigned int x, unsigned int y) {
    buildingRect.moveTo(x - GridGUI::SIZE/2, y - GridGUI::SIZE/2);
}

/*!
 * \brief BuildingGUI::intersects.
 * \param rectangle - QRect object that is being checked for intersection.
 * \return Bool value whether rectangles intersects.
 * \details Function checks whether current building's rectangle and rectangle
 * given as argument intersects and returns bool value.
 */
bool BuildingGUI::intersects(QRect &rectangle) const {
    return buildingRect.intersects(rectangle);
}
