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
    const Place getPlace() const { return this->m_place; }
    const int getLenght() const { return this->m_lenght; }
    const Orientation getOrientation() const { return this->m_orientation; }
    Orientation getOppositeOrientation(Orientation m_orientation);
    Place getFirstPlace(Orientation orient);
    Place getLastPlace(Orientation orient);

    //------------------------------------------------

    bool operator== (const Car car) const;
    void move(Orientation orient, unsigned int lenght);
    bool isOccupied(Place place);

private:

    //Check if the orientation of the car is opposed
    bool orientationIsOpposed(Orientation orientationA, Orientation orientationB);
    //Actual details of the car
    Place m_place;
    Orientation m_orientation;
    int m_lenght;

};

#endif // CAR_H
