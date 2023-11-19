#include <Allegro.h>
#include "Hero.h"
#include "Main.h"
#include "Input.h"


#define HERO_DEAD       0
#define HERO_STAND      1
#define HERO_RUNLEFT    2
#define HERO_RUNRIGHT   3
#define HERO_RUNUP      4
#define HERO_RUNDOWN    5
#define HERO_ATTACK     6



static int StandAnim[]  = { 0, -1, 0 };
static int RunAnim[]    = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1, 0 };
static int AttackAnim[] = { 3, -1, 0 };

HERO::HERO()
     {
     x = 0;
     y = 0;
     width = 15;
     height = 15;
     speed = 1;
     dir = 3;

     Anim.SetAnim(StandAnim);

     ChangeAction(HERO_STAND);

     Sword.enabled = 0;
     Sword.useable  = 1;
     Sword.power   = 1;

     EnableHero();
     }



void HERO::DoLogic()
     {
     Input.Poll();

     if (enabled)
        {
        if (Input.A())
           {
           ChangeAction(HERO_ATTACK);
           }
        else if (Input.Left())
           {
           MoveLeft();
           ChangeAction(HERO_RUNLEFT);
           }
        else if (Input.Right())
           {
           MoveRight();
           ChangeAction(HERO_RUNRIGHT);
           }
        else if (Input.Up())
           {
           MoveUp();
           ChangeAction(HERO_RUNUP);
           }
        else if (Input.Down())
           {
           MoveDown();
           ChangeAction(HERO_RUNDOWN);
           }
        else
           {
           ChangeAction(HERO_STAND);
           }
        }

     Anim.Increment();

     if (busymax)
        {
        busycount++;
        if (busycount >= busymax)
           EnableHero();
        }
     }


void HERO::Draw(BITMAP * buffer)
     {
     stretch_sprite(buffer, HeroBmp[dir][Anim.GetFrame()], int(x - (width / 2)), int(y - (height / 2)), width, height);

     if (Sword.enabled)
        draw_sprite(buffer, SwordBmp[dir][Sword.power], int(Sword.x - (width / 2)), int(Sword.y - (height / 2)));
     }


void HERO::ChangeAction(int newaction)
     {
     if (newaction == action)
        return;

     action = newaction;
     Sword.enabled = 0;

     switch(newaction)
         {
         case HERO_STAND:
              Anim.SetAnim(StandAnim);
              break;

         case HERO_RUNLEFT:
              dir = 0;
              Anim.SetAnim(RunAnim);
              break;

         case HERO_RUNRIGHT:
              dir = 1;
              Anim.SetAnim(RunAnim);
              break;

         case HERO_RUNUP:
              dir = 2;
              Anim.SetAnim(RunAnim);
              break;

         case HERO_RUNDOWN:
              dir = 3;
              Anim.SetAnim(RunAnim);
              break;

         case HERO_ATTACK:
              Anim.SetAnim(AttackAnim);
              Sword.enabled = 1;

              DisableHero(30);

              if (dir == 0)
                 {
                 Sword.x = x - width;
                 Sword.y = y;
                 }
              else if (dir == 1)
                 {
                 Sword.x = x + width;
                 Sword.y = y;
                 }
              else if (dir == 2)
                 {
                 Sword.x = x;
                 Sword.y = y - height;
                 }
              else if (dir == 3)
                 {
                 Sword.x = x;
                 Sword.y = y + height;
                 }

              break;
         }
     }


void HERO::EnableHero()
     {
     busymax = 0;
     enabled = 1;

     switch(action)
         {
         case HERO_ATTACK:
              ChangeAction(HERO_STAND);
              DisableHero(60);
              break;
         }
     }


void HERO::DisableHero(int delay)
     {
     busycount = 0;
     busymax   = delay;
     }



void HERO::OnDamage(int amount, int type, int attackdir)
     {
     health--;

     if (health <= 0)
        ChangeAction(HERO_DEAD);
     }
