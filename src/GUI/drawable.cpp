#include "drawable.h"

Drawable::Drawable(unsigned int layer) {
    this->layer = layer;
}

Drawable::~Drawable() {

}

int Drawable::getLayer() {
    return layer;
}


