#include <Allegro.h>
#include <Math.h>
#include "Maps.h"
#include "Display.h"
#include "Editor.h"
#include "Hero.h"


#define ROUND(x) (int)(fmod(x + 1, 1) >= .5 ? ceil(x) : floor(x))

MAP Map;


void InitMap(void)
     {
     memset(&Map, 0, sizeof(MAP));
     }



int CanMove(int x, int y, int dx, int dy, int dir, int step)
    {
    int TileX1, TileY1;
    int index;

    if (Hero.Ghost)
       return 1;

    switch(dir)
        {
        case LEFT:
            for (index = y - dy; index <= y + dy; index+= dy)
                {
                TileX1 = ROUND((x - dx - step) / 5);
                TileY1 = ROUND(index / 5);

                if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
                   if (Map.Walk[TileX1 + (TileY1 * 48)])
                      return 0;
                }

            break;


        case RIGHT:
            for (index = y - dy; index <= y + dy; index += dy)
                {
                TileX1 = ROUND((x + dx + step) / 5);
                TileY1 = ROUND(index / 5);

                if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
                   if (Map.Walk[TileX1 + (TileY1 * 48)])
                      return 0;
                }

            break;


        case UP:
            for (index = x - dx; index <= x + dx; index += dx)
                {
                TileX1 = ROUND(index / 5);
                TileY1 = ROUND((y - dy - step) / 5);

                if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
                   if (Map.Walk[TileX1 + (TileY1 * 48)])
                      return 0;
                }

            break;


        case DOWN:
            for (index = x - dx; index <= x + dx; index += dx)
                {
                TileX1 = ROUND(index / 5);
                TileY1 = ROUND((y + dy + step) / 5);

                if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
                   if (Map.Walk[TileX1 + (TileY1 * 48)])
                       return 0;
                }

            break;
        }

    return 1;
    }


