#include <Allegro.h>
#include "Display.h"
#include "Input.h"
#include "Maps.h"
#include "Editor.h"
#include "Hero.h"

int main(void)
    {
    allegro_init();
    install_keyboard();
    install_mouse();

    InitDisplay();
    InitMap();
    InitHero();

    Editor.Mode = MODE_TILE;
    Editor.Tile = 0;
    Editor.Walk = 0;
    Editor.ShowTile     = 1;
    Editor.ShowForeTile = 1;
    Editor.ShowWalk     = 1;
    Editor.ShowGrid     = 1;
    Editor.ShowHero     = 1;
    Editor.End = 0;

    set_palette(OverPal);

    while(!Editor.End)
        {
        InputLogic();
        HeroLogic();
        DisplayLogic();
        }

    allegro_exit();
    return 1;
    }

