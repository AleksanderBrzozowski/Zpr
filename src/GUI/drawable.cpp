#include "drawable.h"

Drawable::Drawable(unsigned int layer, bool ghost = false) {
    this->layer = layer;
    this->ghost = ghost;
}

Drawable::~Drawable() {

}

bool Drawable::isGhost() const {
    return ghost;
}

int Drawable::getLayer() const {
    return layer;
}


