#include <Allegro.h>
#include <stdio.h>
#include "Main.h"
#include "Map.h"


int MAP::LoadMap(char * strFile)
    {
    FILE * fp;

    fp = fopen(strFile, "rb");

    if (fp)
       {
       fread(Tile.Back, sizeof(Tile.Back), 1, fp);
       fread(Tile.Front, sizeof(Tile.Front), 1, fp);
       fread(Walk, sizeof(Walk), 1, fp);

       fclose(fp);

       return 1;
       }

    return 0;
    }



void MAP::DrawBack(BITMAP * buffer)
    {
    int x, y;

    for (y = 0; y < 10; y++)
        for (x = 0; x < 16; x++)
            draw_sprite(buffer, MapBmp[Tile.Back[x + (y * 16)]], x * 15, y * 15);
    }


void MAP::DrawFront(BITMAP * buffer)
    {
    int x, y;

    for (y = 0; y < 10; y++)
        for (x = 0; x < 16; x++)
            if (Tile.Front[x + (y * 16)])
               draw_sprite(buffer, MapBmp[Tile.Front[x + (y * 16)]], x * 15, y * 15);
    }
