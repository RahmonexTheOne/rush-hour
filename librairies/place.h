#ifndef PLACE_H
#define PLACE_H

//This class defines the places in the parking (board)
class Place
{

public:

    explicit Place();

    Place(int row, int column);
    Place(Place const& place);
    bool operator== (const Place place) const;



    //-------------------------------Getters:
    const int getRow() const { return this->place_row;};
    const int getColumn() const { return this->place_column; };
    //-------------------------------------------------



    //--------------------------------Setters
    void setRow(int row) { this->place_row = row; }
    void setColumn(int column) { this->place_column = column; }
    //-------------------------------------------------------



private:
    int place_row;
    int place_column;
};

#endif // PLACE_H
