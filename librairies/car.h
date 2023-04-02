#ifndef CAR_H
#define CAR_H

#include <place.h>

enum Orientation {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Car
{

public:

    explicit Car();

    Car(Place pos, Orientation orientation, unsigned int lenght);
    Car(Car const& car);


    //------------------------------------- Getters :
    const Place getPlace() const { return this->m_pos; }
    const int getLenght() const { return this->m_lenght; }
    const Orientation getOrientation() const { return this->m_orientation; }
    Orientation getOppositeOrientation(Orientation m_orientation);
    //------------------------------------------------

    bool operator== (const Car car) const;

private:

    bool orientationIsOpposed(Orientation orientationA, Orientation orientationB);

    //Actual details of the car
    Place m_pos;
    Orientation m_orientation;
    int m_lenght;

};

#endif // CAR_H
