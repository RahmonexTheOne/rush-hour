#include "car.h"

Car::Car() = default;

Car::Car(Place place, Orientation orientation, unsigned int lenght):
                m_place(place), m_orientation(orientation), m_lenght(lenght) {}

Car::Car(Car const &car)
                : m_place(car.m_place), m_lenght(car.m_lenght),
                m_orientation(car.m_orientation) {}



//------------------------------------------------------- Orientation functions :
bool Car::orientationIsOpposed(Orientation orientationA, Orientation orientationB) {
    if(this->getOppositeOrientation(orientationA) == orientationB){
        return true;
    }
    else{
        return false;
    }
}
//----------------

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
    return orientation;
}

//--------------------------------------------------------------------------------------


//--------------------------------------------------------Move Car :
void Car::move(Orientation orientation, unsigned int nbPlaces) {
    if(this->m_orientation == orientation ||
       this->getOppositeOrientation(orientation) == this->m_orientation){
        switch(orientation){
            case UP:
                this->m_place.setRow(this->m_place.getRow() - nbPlaces);
                break;
            case DOWN:
                this->m_place.setRow(this->m_place.getRow() + nbPlaces);
                break;
            case RIGHT:
                this->m_place.setColumn(this->m_place.getColumn() + nbPlaces);
                break;
            case LEFT:
                this->m_place.setColumn(this->m_place.getColumn() - nbPlaces);
                break;
        }
    }
}

//-------------------------------------------------------------------------


//------------------------------------- check if the place is occupied :
bool Car::isOccupied(Place place) {
    switch(this->m_orientation){
        case UP:
            for(int x = this->m_place.getRow(); x < this->m_place.getRow() + this->m_lenght; x++){
                if(place.getRow() == x && place.getColumn() == this->m_place.getColumn())
                    return true;
            }
            break;
        case DOWN:
            for(int x = this->m_place.getRow();x > this->m_place.getRow() - this->m_lenght;x--){
                if(place.getRow() == x && place.getColumn() == this->m_place.getColumn())
                    return true;
            }
            break;
        case RIGHT:
            for(int y = this->m_place.getColumn();y > this->m_place.getColumn() - this->m_lenght;y--){
                if(place.getRow() == this->m_place.getRow() && place.getColumn() == y)
                    return true;
            }
            break;
        case LEFT:
            for(int y = this->m_place.getColumn();y < this->m_place.getColumn() + this->m_lenght;y++){
                if(place.getRow() == this->m_place.getRow() && place.getColumn() == y)
                    return true;
            }
            break;
    }
    return false;
}
//--------------------------------------------------------------------------






bool Car::operator==(const Car car) const {
    if(car.m_orientation != this->m_orientation)
        return false;
    else if(this->m_lenght != car.m_lenght)
        return false;
    return this->m_place == car.m_place;
}




//---------------------------Function to check the first corrdinates in the first place and the last :
Place Car::getFirstPlace(Orientation orientation) {
    return orientationIsOpposed(this->m_orientation, orientation)
           ? this->getLastPlace(this->m_orientation) : this->m_place;
}

Place Car::getLastPlace(Orientation orientation) {
    if(orientationIsOpposed(this->m_orientation, orientation))
        return this->m_place;
    else if(this->m_orientation == orientation){
        switch(this->m_orientation){
            case UP:return {this->m_place.getRow() + this->m_lenght - 1,this->m_place.getColumn()};
            case DOWN: return {this->m_place.getRow() - this->m_lenght - 1,this->m_place.getColumn()};
            case RIGHT: return {this->m_place.getRow(),this->m_place.getColumn() - this->m_lenght - 1};
            case LEFT: return {this->m_place.getRow(),this->m_place.getColumn() + this->m_lenght - 1};
        }
    }
    return this->m_place;
}

//----------------------------------------------------------------------------------------------------
