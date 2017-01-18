#include "drawable.h"

/*!
 * \brief Drawable::Drawable. Constructor.
 * \param ghost - bool flag tells whether object is ghost object.
 */
Drawable::Drawable(bool ghost = false) : ghost(ghost) {
}

/*!
 * \brief Drawable::~Drawable. Virtual destructor.
 */
Drawable::~Drawable() {

}

/*!
 * \brief Drawable::isGhost.
 * \return boolean whether object is ghost object.
 */
bool Drawable::isGhost() const {
    return ghost;
}



