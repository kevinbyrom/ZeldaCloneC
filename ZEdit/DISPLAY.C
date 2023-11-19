#include <Allegro.h>
#include "Display.h"
#include "Maps.h"
#include "Editor.h"
#include "Hero.h"

BITMAP * Buffer;
BITMAP * TileBuffer;
BITMAP * OverBmp[180];
BITMAP * DungeonBmp[180];
BITMAP * LinkBmp[16];

PALETTE OverPal;
PALETTE DungeonPal;

COLOR_MAP TransMap;

void LoadHeroBmp(void);
void DrawTiles(void);
void DrawWalk(void);
void DrawHero(void);
void DrawForeTiles(void);
void DrawGrid(void);
void DrawRectangle(BITMAP * bitmap, int left, int top, int right, int bottom, int fillcolor, int mode);



void InitDisplay(void)
    {
    BITMAP * OverPCX;

    int x, y;

    set_color_depth(8);
    set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);

    Buffer      = create_bitmap(320,200);
    TileBuffer  = create_bitmap(240,165);


    // LOAD THE OVERWORLD //

    OverPCX = load_bitmap("c:\\Zelda\\Overw.pcx", OverPal);

    for (y = 0; y < 10; y++)
        for (x = 0; x < 18; x++)
            {
            OverBmp[x + (y * 18)] = create_bitmap(15, 15);
            blit(OverPCX, OverBmp[x + (y * 18)], (x * 15) + (x + 1), (y * 15) + (y + 1), 0, 0, 15, 15);
            }

    // LOAD THE HERO SPRITES //

    LoadHeroBmp();

    create_trans_table(&TransMap, OverPal, 128, 128, 128, NULL);

    destroy_bitmap(OverPCX);
    }


void LoadHeroBmp(void)
     {
     PALETTE GamePal;
     BITMAP * LinkPCX;
     int x, y;

     LinkPCX = load_bitmap("c:\\Zelda\\LINK.PCX", GamePal);

     for (y = 0; y < 4; y++)
         for (x = 0; x < 4; x ++)
             {
             LinkBmp[x + (y * 4)] = create_bitmap(15, 15);
             blit(LinkPCX, LinkBmp[x + (y * 4)], (x * 15) + (x + 1), (y * 15) + (y + 1), 0, 0, 15, 15);
             }

     set_palette(GamePal);
     destroy_bitmap(LinkPCX);
     }


void DisplayLogic(void)
    {
    char strBuffer[20];

    show_mouse(NULL);

    clear(Buffer);
    clear(TileBuffer);

    DrawRectangle(Buffer, 0, 0, 319, 199, 1, RAISED);      // OUTER EDGE
    DrawRectangle(Buffer, 3, 3, 256, 181, 0, SUNKEN);      // MAP
    DrawRectangle(Buffer, 3, 184, 63, 195, 0, SUNKEN);     // X Y POS
    DrawRectangle(Buffer, 66, 184, 315, 195, 0, SUNKEN);   // VISIBLE MODES
    DrawRectangle(Buffer, 259, 3, 315, 44, 0, SUNKEN);     // TILE
    DrawRectangle(Buffer, 259, 47, 315, 88, 0, SUNKEN);    // GROUND
    DrawRectangle(Buffer, 259, 91, 315, 181, 0, SUNKEN);    // OPTIONS

    DrawTiles();
    DrawHero();
    DrawForeTiles();
    DrawWalk();
    DrawGrid();

    blit(TileBuffer, Buffer, 0, 0, 10, 10, 240, 165);

    // VISIBLE MODES //

    textout(Buffer, font, "F9", 68, 186, 4);
    textout(Buffer, font, "F10", 123, 186, 4);
    textout(Buffer, font, "F11", 189, 186, 4);
    textout(Buffer, font, "F12", 254, 186, 4);

    textout(Buffer, font, "TILE", 85, 186, 8);
    textout(Buffer, font, "FORE", 152, 186, 8);
    textout(Buffer, font, "WALK", 216, 186, 8);
    textout(Buffer, font, "GRID", 281, 186, 8);

    if (Editor.ShowTile)     textout(Buffer, font, "TILE", 85, 186, 15);
    if (Editor.ShowForeTile) textout(Buffer, font, "FORE", 152, 186, 15);
    if (Editor.ShowWalk)     textout(Buffer, font, "WALK", 216, 186, 15);
    if (Editor.ShowGrid)     textout(Buffer, font, "GRID", 281, 186, 15);

    // TILE //

    textout(Buffer, font, "F1", 263, 6, 4);
    textout(Buffer, font, "F3", 263, 33, 4);
    textout(Buffer, font, "<", 279, 33, 15);
    textout(Buffer, font, ">", 287, 33, 15);
    textout(Buffer, font, "F4", 295, 33, 4);

    // GROUND //

    draw_sprite(Buffer, OverBmp[Map.Ground], 279, 60);
    textout(Buffer, font, "GROUND", 264, 50, 15);
    textout(Buffer, font, "F5", 263, 77, 4);
    textout(Buffer, font, "<", 279, 77, 15);
    textout(Buffer, font, ">", 287, 77, 15);
    textout(Buffer, font, "F6", 295, 77, 4);

    // OPTIONS //

    textout(Buffer, font, "G", 268, 96, 4);
    textout(Buffer, font, "HOST", 276, 96, Hero.Ghost ? 14 : 8);
    textout(Buffer, font, "H", 272, 108, 4);
    textout(Buffer, font, "ERO", 280, 108, Editor.ShowHero ? 14 : 8);
    textout(Buffer, font, "S", 272, 120, 4);
    textout(Buffer, font, "AVE", 280, 120, 15);
    textout(Buffer, font, "L", 272, 132, 4);
    textout(Buffer, font, "OAD", 280, 132, 15);
    textout(Buffer, font, "4", 263, 144, 4);
    textout(Buffer, font, "6", 263, 152, 4);
    textout(Buffer, font, "8", 263, 160, 4);
    textout(Buffer, font, "2", 263, 168, 4);
    textout(Buffer, font, "L MAP", 273, 144, 15);
    textout(Buffer, font, "R MAP", 273, 152, 15);
    textout(Buffer, font, "U MAP", 273, 160, 15);
    textout(Buffer, font, "D MAP", 273, 168, 15);

    switch(Editor.Mode)
        {
        case MODE_TILE:
             // SHOW THE CURRENT TILE //
             textout(Buffer, font, "TILE", 281, 6, 15);
             draw_sprite(Buffer, OverBmp[Editor.Tile], 279, 16);
             break;

        case MODE_WALK:
             // SHOW THE CURRENT WALK //
             textout(Buffer, font, "WALK", 281, 6, 15);
             rectfill(Buffer, 279, 16, 294, 31, Editor.Walk);
             break;

        case MODE_FORE:
             // SHOW THE CURRENT FORETILE //
             textout(Buffer, font, "FORE", 281, 6, 15);
             draw_sprite(Buffer, OverBmp[Editor.ForeTile], 279, 16);
             break;
        }

    // SHOW THE MOUSE POSITION //

    textprintf(Buffer, font, 5, 186, 15, "%d - %d", Editor.MX, Editor.MY);

    show_mouse(Buffer);

    vsync();
    blit(Buffer, screen, 0, 0, 0, 0, 320, 200);
    }




void DrawTiles(void)
     {
     int x, y;

     if (!Editor.ShowTile)
        return;

     for (y = 0; y < 11; y++)
         for (x = 0; x < 16; x++)
             {
             blit(OverBmp[Map.Ground], TileBuffer, 0, 0, x * 15, y * 15, 15, 15);

             if (Map.Tile[x + (y * 16)])
                 draw_sprite(TileBuffer, OverBmp[Map.Tile[x + (y * 16)]], x * 15, y * 15);
             }
     }


void DrawHero(void)
     {
     if (!Editor.ShowHero)
        return;

     if (Hero.Ghost)
        {
        color_map = &TransMap;
        draw_trans_sprite(TileBuffer, LinkBmp[Hero.pAnim[Hero.Anim]], Hero.X - 7, Hero.Y - 7);
        }
     else
        draw_sprite(TileBuffer, LinkBmp[Hero.pAnim[Hero.Anim]], Hero.X - 7, Hero.Y - 7);
     }

void DrawForeTiles(void)
     {
     int x, y;

     if (!Editor.ShowForeTile)
        return;

     for (y = 0; y < 11; y++)
         for (x = 0; x < 16; x++)
             {
             if (Map.ForeTile[x + (y * 16)])
                 draw_sprite(TileBuffer, OverBmp[Map.ForeTile[x + (y * 16)]], x * 15, y * 15);
             }
     }


void DrawWalk(void)
     {
     int x, y;

     if (!Editor.ShowWalk)
        return;

     for (y = 0; y < 33; y++)
         for (x = 0; x < 48; x++)
             {
             if (Map.Walk[x + (y * 48)])
                rectfill(TileBuffer, x * 5, y * 5, (x * 5) + 4, (y * 5) + 4, Map.Walk[x + (y * 48)]);
             }
     }


void DrawGrid(void)
     {
     int x, y;

     if (!Editor.ShowGrid)
        return;

     for (y = 0; y < 11; y++)
         for (x = 0; x < 16; x++)
             {
             rect(TileBuffer, x * 15, y * 15, (x * 15) + 14, (y * 15) + 14, 1);
             }
     }


void DestroyDisplay(void)
     {
     int i;

     for (i = 0; i < 180; i++)
         destroy_bitmap(OverBmp[i]);

     destroy_bitmap(Buffer);
     destroy_bitmap(TileBuffer);

     for (i = 0; i < 16; i++)
         destroy_bitmap(LinkBmp[i]);
     }


void DrawRectangle(BITMAP * bitmap, int left, int top, int right, int bottom, int fillcolor, int mode)
     {
     rectfill(bitmap, left, top, right, bottom, fillcolor);

     if (mode == RAISED)
        {
        line(bitmap, left + 1, bottom, right, bottom, 9);
        line(bitmap, right, top + 1, right, bottom, 9);
        line(bitmap, left, top, left, bottom, 11);
        line(bitmap, left, top, right, top, 11);
        line(bitmap, left + 2, bottom - 1, right - 1, bottom - 1, 11);
        line(bitmap, right - 1, top + 2, right - 1, bottom - 1, 11);
        }
     else if (mode == SUNKEN)
        {
        line(bitmap, left, bottom, right, bottom, 9);
        line(bitmap, right, top, right, bottom, 9);
        line(bitmap, left + 1, top + 1, right - 1, top + 1, 9);
        line(bitmap, left + 1, top + 1, left + 1, bottom - 1, 9);
        rect(bitmap, left, top, right - 1, bottom - 1, 11);
        }
     }

