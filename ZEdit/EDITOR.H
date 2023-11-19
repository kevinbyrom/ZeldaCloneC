#ifndef __Editor_H
#define __Editor_H

typedef struct
    {
    int Mode;
    int Tile;
    int ForeTile;
    int Walk;
    int ShowTile;
    int ShowForeTile;
    int ShowWalk;
    int ShowGrid;
    int ShowHero;
    int MX, MY;
    int End;
    } EDITOR;

extern EDITOR Editor;

#endif

