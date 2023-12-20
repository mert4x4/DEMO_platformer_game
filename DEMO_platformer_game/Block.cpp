#include "Entity.cpp"

class Block : public Entity {
public:
    
    using Entity::Entity;

    Block(SDL_Surface* screenSurface, float x, float y, int w, int h) : Entity(screenSurface, x, y, w, h) {

        this->setColor(56, 79, 12);
    }

};