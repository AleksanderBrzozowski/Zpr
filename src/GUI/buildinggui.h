#ifndef BUILDINGGUI_H
#define BUILDINGGUI_H

#include "drawable.h"
#include "gridgui.h"
/*!
 * \brief The BuildingGUI class. Class holds info about look of building in GUI.
 * \details Function holds information necessary to draw building in GUI. It implements
 * virtual functions from base class, so it will be drawn properly.
 */
class BuildingGUI : public Drawable
{
public:
    BuildingGUI(QRect buildingRect,  bool ghost = false);
    BuildingGUI(unsigned int x, unsigned int y,
                unsigned int width = GridGUI::SIZE, unsigned int height = GridGUI::SIZE,
                bool ghost = false);
    ~BuildingGUI();
    void draw(QPainter &painter) const override;
    void setTo(unsigned int x, unsigned int y) override;
    bool intersects(QRect &rectangle) const override;


    /**PROPERTIES**/
    static const int PEN_WIDTH;
    static const Qt::PenStyle PEN_STYLE;
    static const Qt::PenCapStyle PEN_CAP;
    static const Qt::PenJoinStyle PEN_JOIN;

    static const QColor PEN_COLOR;
    static const QColor GHOST_PEN_COLOR;

    static const QPen PEN;
    static const QPen GHOST_PEN;


    static const Qt::BrushStyle BRUSH_STYLE;
    static const QColor BRUSH_COLOR;

    static const QColor GHOST_BRUSH_COLOR;

    static const QBrush BRUSH;
    static const QBrush GHOST_BRUSH;

private:
    QRect buildingRect;
};

#endif // BUILDINGGUI_H
