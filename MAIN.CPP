#include <Allegro.h>
#include <Time.h>
#include "Main.h"
#include "Globals.h"
#include "Input.h"
#include "EOcto.h"


BITMAP * HeroBmp[4][4];
BITMAP * SwordBmp[4][4];
BITMAP * OctoBmp[4][4];
BITMAP * MapBmp[57];


void LoadHeroBmp();
void LoadSwordBmp();
void LoadOctoBmp();
void LoadMapBmp();


int main()
    {
    BITMAP * Buffer;
    EOCTOROCK Octorock, Octorock2;

    // Initialization //

    allegro_init();
    install_keyboard();
    initialise_joystick();

    set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);

    Buffer = create_bitmap(320, 200);

    LoadHeroBmp();
    LoadSwordBmp();
    LoadOctoBmp();
    LoadMapBmp();

    srandom((int)time(NULL));

    Map.LoadMap("C:\\ZELDA\\MAP.MAP");

    while(!key[KEY_ESC])
        {
        clear(Buffer);

        Hero.DoLogic();
        Octorock.DoLogic();
        Octorock2.DoLogic();

        Map.DrawBack(Buffer);
        Hero.Draw(Buffer);
        Octorock.Draw(Buffer);
        Octorock2.Draw(Buffer);
        Map.DrawFront(Buffer);

        blit(Buffer, screen, 0, 0, 0, 0, 320, 200);
        }



    // De-Initialization //

    allegro_exit();

    destroy_bitmap(Buffer);

    return 1;
    }


void LoadHeroBmp()
     {
     int x, y;
     BITMAP * pcx;
     PALETTE GamePal;

     pcx = load_bitmap("C:\\ZELDA\\LINK.PCX", GamePal);
     set_palette(GamePal);

     for (y = 0; y < 4; y++)
         for (x = 0; x < 4; x++)
             {
             HeroBmp[y][x] = create_bitmap(15, 15);
             blit(pcx, HeroBmp[y][x], (x * 15) + (x + 1), (y * 15) + (y + 1),
                                      0, 0, 15, 15);
             }

     destroy_bitmap(pcx);
     }


void LoadSwordBmp()
     {
     int x, y;
     BITMAP * pcx;

     pcx = load_bitmap("C:\\ZELDA\\Sword.PCX", NULL);

     for (y = 0; y < 4; y++)
         for (x = 0; x < 4; x++)
             {
             SwordBmp[y][x] = create_bitmap(15, 15);
             blit(pcx, SwordBmp[y][x], (x * 15) + (x + 1), (y * 15) + (y + 1),
                                       0, 0, 15, 15);
             }

     destroy_bitmap(pcx);
     }


void LoadOctoBmp()
     {
     int x, y;
     BITMAP * pcx;

     pcx = load_bitmap("C:\\ZELDA\\Octo.PCX", NULL);

     for (y = 0; y < 4; y++)
         for (x = 0; x < 4; x++)
             {
             OctoBmp[y][x] = create_bitmap(15, 15);
             blit(pcx, OctoBmp[y][x], (x * 15) + (x + 1), (y * 15) + (y + 1),
                                       0, 0, 15, 15);
             }

     destroy_bitmap(pcx);
     }


void LoadMapBmp()
     {
     int x, y;
     BITMAP * pcx;

     pcx = load_bitmap("C:\\ZELDA\\OverW.PCX", NULL);

     for (y = 0; y < 3; y++)
         for (x = 0; x < 19; x++)
             {
             MapBmp[x + (y * 19)] = create_bitmap(15, 15);
             blit(pcx, MapBmp[x + (y * 19)], (x * 15) + (x + 1), (y * 15) + (y + 1),
                                       0, 0, 15, 15);
             }

     destroy_bitmap(pcx);
     }
