#ifndef __MAP_H
#define __MAP_H

#include <Allegro.h>

typedef struct
        {
        int Back[160],
            Front[160];
        } TILE;


class MAP
      {
      public:
             int LoadMap(char *);

             void DrawBack(BITMAP *);
             void DrawFront(BITMAP *);

      private:
              TILE Tile;
              int Walk[480];
      };


#endif
