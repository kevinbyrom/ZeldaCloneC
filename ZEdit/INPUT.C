#include <Allegro.h>
#include "Input.h"
#include "Maps.h"
#include "FileIO.h"
#include "Editor.h"
#include "Hero.h"


void InputLogic(void)
     {
     int x, y;

     // HERO KEYPRESSES //

     if (key[KEY_LEFT])
        ChangeHeroAction(RUNNING, LEFT);
     else if (key[KEY_RIGHT])
        ChangeHeroAction(RUNNING, RIGHT);
     else if (key[KEY_UP])
        ChangeHeroAction(RUNNING, UP);
     else if (key[KEY_DOWN])
        ChangeHeroAction(RUNNING, DOWN);
     else
        ChangeHeroAction(STANDING, Hero.Dir);


     // MENU KEYPRESSES //

     if (keypressed())
        {
        if (key[KEY_ESC])
           Editor.End = 1;

        if (key[KEY_S])
           {
           SaveMap(&Map);
           return;
           }


        if (key[KEY_L])
           {
           LoadMap(&Map);
           return;
           }


        if (key[KEY_F1])
           {
           Editor.Mode++;
           if (Editor.Mode > 2)
              Editor.Mode = 0;

           clear_keybuf();
           }

        if (key[KEY_F3])
           {
           switch(Editor.Mode)
               {
               case MODE_TILE:
                   Editor.Tile--;
                   if (Editor.Tile < 0)
                      Editor.Tile = 0;
                   break;

               case MODE_WALK:
                   Editor.Walk--;
                   if (Editor.Walk < 0)
                       Editor.Walk = 0;
                   break;

               case MODE_FORE:
                   Editor.ForeTile--;
                   if (Editor.ForeTile < 0)
                       Editor.ForeTile = 0;
                   break;
               }

           clear_keybuf();
           }


        if (key[KEY_F4])
           {
           switch(Editor.Mode)
               {
               case MODE_TILE:
                   Editor.Tile++;
                   if (Editor.Tile >= 180)
                       Editor.Tile = 179;
                   break;

               case MODE_WALK:
                   Editor.Walk++;
                   if (Editor.Walk >= 16)
                       Editor.Walk = 0;
                   break;

               case MODE_FORE:
                   Editor.ForeTile++;
                   if (Editor.ForeTile >= 180)
                       Editor.ForeTile = 179;
                   break;
               }

           clear_keybuf();
           }


        if (key[KEY_F5])
           {
           Map.Ground--;

           if (Map.Ground < 0)
              Map.Ground = 0;

           clear_keybuf();
           }

        if (key[KEY_F6])
           {
           Map.Ground++;

           if (Map.Ground >= 180 )
              Map.Ground = 179;

           clear_keybuf();
           }

        if (key[KEY_G])
           {
           Hero.Ghost = !Hero.Ghost;
           clear_keybuf();
           }

        if (key[KEY_H])
           {
           Editor.ShowHero = !Editor.ShowHero;
           clear_keybuf();
           }

        if (key[KEY_F9])
           {
           Editor.ShowTile = !Editor.ShowTile;
           clear_keybuf();
           }

        if (key[KEY_F10])
           {
           Editor.ShowForeTile = !Editor.ShowForeTile;
           clear_keybuf();
           }

        if (key[KEY_F11])
           {
           Editor.ShowWalk = !Editor.ShowWalk;
           clear_keybuf();
           }

        if (key[KEY_F12])
           {
           Editor.ShowGrid = !Editor.ShowGrid;
           clear_keybuf();
           }

        if (key[KEY_4])
           GetMapName(Map.LeftMap.Name);

        if (key[KEY_6])
           GetMapName(Map.RightMap.Name);

        if (key[KEY_8])
           GetMapName(Map.UpMap.Name);

        if (key[KEY_2])
           GetMapName(Map.DownMap.Name);

        if (key[KEY_5])
           GetMapName(Map.SubMap.Name);
        }

     if (mouse_b & 1)
        {
        if (mouse_x >= 10 && mouse_x < 250 && mouse_y >= 10 && mouse_y < 175)
           {
           if (Editor.Mode == MODE_TILE)
              {
              x = (float)(mouse_x - 10) / 15;
              y = (float)(mouse_y - 10) / 15;

              if (x >= 0 && x < 16 && y >= 0 && y < 11)
                 Map.Tile[x + (y * 16)] = Editor.Tile;
              }

           else if (Editor.Mode == MODE_WALK)
              {
              x = (float)(mouse_x - 10) / 5;
              y = (float)(mouse_y - 10) / 5;

              if (x >= 0 && x < 48 && y >= 0 && y < 33)
                 Map.Walk[x + (y * 48)] = Editor.Walk;
              }

           else if (Editor.Mode == MODE_FORE)
              {
              x = (float)(mouse_x - 10) / 15;
              y = (float)(mouse_y - 10) / 15;

              if (x >= 0 && x < 16 && y >= 0 && y < 11)
                 Map.ForeTile[x + (y * 16)] = Editor.ForeTile;
              }
           }
        }


     if (mouse_x >= 10 && mouse_x < 250 && mouse_y >= 10 && mouse_y < 175)
        {
        if (Editor.Mode == MODE_TILE || Editor.Mode == MODE_FORE)
           {
           Editor.MX = (float)(mouse_x - 10) / 15;
           Editor.MY = (float)(mouse_y - 10) / 15;
           }
        else if (Editor.Mode == MODE_WALK)
           {
           Editor.MX = (float)(mouse_x - 10) / 5;
           Editor.MY = (float)(mouse_y - 10) / 5;
           }
        }
     }

