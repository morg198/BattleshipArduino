#ifndef ARRAYTOLONG_H
#define ARRAYTOLONG_H
#include <math.h>

long ArrayToLong(short field[GRIDLENGTH][GRIDHEIGHT], short gridLength, short gridHeight)
{
    long longToPush = 0;
    short totalLength = gridHeight * gridLength;
    short temp[totalLength];
    short i = 0, j = 0, k = 0;

    for(i = 0; i < gridHeight; i++)
    {
        for(j = 0; j < gridLength; j++)
            {
                temp[k] = field[j][i] ^ 1;
                k++;
            }
    }

    for(i = 0; i < totalLength; i++)
    {
        longToPush += temp[i] * pow(2, i);
    }

    return longToPush;
}

#endif // ARRAYTOLONG_H
