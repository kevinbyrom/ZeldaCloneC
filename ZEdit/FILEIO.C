#include <Allegro.h>
#include <Stdio.h>
#include <Conio.h>
#include "FileIO.h"
#include "Maps.h"


void SaveMap(MAP * pMap)
     {
     FILE * fp;
     char filename[12];


     GetMapName(filename);

     if (!filename[0])
        return;


     fp = fopen(filename, "wb");

     if (fp)
         {
         //fwrite(pMap, sizeof(MAP), 1, fp);
         fwrite(pMap->Tile, sizeof(pMap->Tile), 1, fp);
         fwrite(pMap->ForeTile, sizeof(pMap->ForeTile), 1, fp);
         fwrite(pMap->Walk, sizeof(pMap->Walk), 1, fp);
         fclose(fp);
         }

     }


void LoadMap(MAP * pMap)
     {
     FILE * fp;
     char filename[12];


     GetMapName(filename);

     if (!filename[0])
        return;


     fp = fopen(filename, "rb");

     if (fp)
         {
         fread(pMap, sizeof(MAP), 1, fp);
         fclose(fp);
         }
     }


void GetMapName(char * string)
     {
     static char MapName[12];
     int Pos, EndLoop;
     BITMAP * NBuffer;


     NBuffer = create_bitmap(320, 200);
     memset(MapName, 0, 12);
     EndLoop = 0;

     while(!EndLoop)
         {
         clear_keybuf();

         for (Pos = 0; Pos < 7; Pos++)
             {
             clear(NBuffer);
             textout(NBuffer, font, "LAST NAME :", 0, 0, 3);
             textout(NBuffer, font, string, 0, 8, 3);
             textout(NBuffer, font, "ENTER MAP NAME :", 0, 24, 5);
             textout(NBuffer, font, MapName, 0, 32, 15);
             blit(NBuffer, screen, 0, 0, 0, 0, 320, 200);

             MapName[Pos] = readkey();

             clear_keybuf();
             }

         MapName[7]  = '.';
         MapName[8]  = 'M';
         MapName[9]  = 'A';
         MapName[10] = 'P';
         MapName[11] = 0;

         clear(NBuffer);
         textout(NBuffer, font, MapName, 0, 0, 15);
         textout(NBuffer, font, "IS THIS CORRECT? (Y/N)", 0, 8, 5);
         blit(NBuffer, screen, 0, 0, 0, 0, 320, 200);

         clear_keybuf();
         while(!keypressed()){}

         if (key[KEY_Y])
            EndLoop = 1;
         else if (key[KEY_ESC])
            {
            EndLoop = 1;
            memset(MapName, 0, 12);
            }
         else
            memset(MapName, 0, 12);
         }

     destroy_bitmap(NBuffer);

     strcpy(string, MapName);
     }

