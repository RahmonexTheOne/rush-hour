#include "place.h"

Place::Place() {
}

Place::Place(int row, int column)
          : place_row(row), place_column(column){}

Place::Place(Place const &src) {
    this->place_row = src.getRow();
    this->place_column = src.getColumn();
}

bool Place::operator==(const Place src) const {
    return this->place_row == src.place_row && this->place_column == src.place_column;
}
