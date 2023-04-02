#include "car.h"

Car::Car() = default;

Car::Car(Place pos, Orientation orientation, unsigned int longueur):
                m_pos(pos), m_orientation(orientation), m_lenght(longueur) {}

Car::Car(Car const &car)
                : m_pos(car.m_pos), m_lenght(car.m_lenght),
                m_orientation(car.m_orientation) {}


bool Car::orientationIsOpposed(Orientation orientationA, Orientation orientationB) {
    return this->getOppositeOrientation(orientationA) == orientationB;
}

Orientation Car::getOppositeOrientation(Orientation orientation) {
    switch(orientation){
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
    }
    return orientation; // CAS IMPOSSIBLE
}

bool Car::operator==(const Car car) const {
    if(car.m_orientation != this->m_orientation)
        return false;
    else if(this->m_lenght != car.m_lenght)
        return false;
    return this->m_pos == car.m_pos;
}
