#ifndef GENERATOR_H
#define GENERATOR_H

#include "GLobalDefines.h"

void GenerateShip(short shipLocations[GRIDLENGTH][GRIDHEIGHT]);
void ZeroGrid(short shipLocations[GRIDLENGTH][GRIDHEIGHT]);
void GenerateShips(short count, short shipLocations[GRIDLENGTH][GRIDHEIGHT]);

void GenerateShip(short shipLocations[GRIDLENGTH][GRIDHEIGHT])
{
    short shipX = 0, shipY = 0;
    short valid = 0;

    //These determine if ship is vertical(1) or horizontal(0)
    short ship = rand() % 2;


    if (ship == 1)      //Vertical ship
    {
        while(valid == 0)
        {
            valid = 1;
            shipX = rand() % GRIDLENGTH;
            shipY = rand() % (GRIDHEIGHT-1);

            if(shipLocations[shipX][shipY] == 1 || shipLocations[shipX][shipY + 1] == 1)
                valid = 0;
        }
        shipLocations[shipX][shipY + 1] = 1;
        shipLocations[shipX][shipY] = 1;
    }
    else                //Horizontal ship
    {
        while(valid == 0)
        {
            valid = 1;
            shipX = rand() % (GRIDLENGTH-1);
            shipY = rand() % GRIDHEIGHT;

            if(shipLocations[shipX][shipY] == 1 || shipLocations[shipX + 1][shipY] == 1)
                valid = 0;
        }
        shipLocations[shipX + 1][shipY] = 1;
        shipLocations[shipX][shipY] = 1;
    }


}

void ZeroGrid(short shipLocations[GRIDLENGTH][GRIDHEIGHT])
{
    int i, j;

    for(i = 0; i < GRIDHEIGHT; i++)
    {
        for(j = 0; j < GRIDLENGTH; j++)
            shipLocations[j][i] = 0;
    }
}

void GenerateShips(short count, short shipLocations[GRIDLENGTH][GRIDHEIGHT])
{
    short i;
    ZeroGrid(shipLocations);

    for (i = 0; i < count; i++)
    {
        GenerateShip(shipLocations);
    }
}

#endif // GENERATOR_H
