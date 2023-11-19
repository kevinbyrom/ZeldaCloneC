#ifndef __Maps_H
#define __Maps_H


#define MODE_TILE       0
#define MODE_WALK       1
#define MODE_FORE       2

#define LEFT           0
#define RIGHT          1
#define UP             2
#define DOWN           3


typedef struct
    {
    char Name[13];
    int StartX, StartY;
    } MAPTYPE;

typedef struct
    {
    int Tile[176];
    int ForeTile[176];
    int Walk[1584];
    int Ground;

    int RepX, RepY;

    int StartColor, EndColor;

    MAPTYPE ThisMap, LeftMap, RightMap, UpMap, DownMap, SubMap;
    } MAP;

extern MAP Map;

void InitMap(void);
int CanMove(int x, int y, int dx, int dy, int dir, int step);

#endif
