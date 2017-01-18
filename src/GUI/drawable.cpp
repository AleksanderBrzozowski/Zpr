#include "drawable.h"

Drawable::Drawable(bool ghost = false) : ghost(ghost) {
}

Drawable::~Drawable() {

}

bool Drawable::isGhost() const {
    return ghost;
}



