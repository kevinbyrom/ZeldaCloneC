#include <Allegro.h>
#include "Main.h"
#include "EOcto.h"


#define OCTO_STAND            0
#define OCTO_RUNLEFT          1
#define OCTO_RUNRIGHT         2
#define OCTO_RUNUP            3
#define OCTO_RUNDOWN          4


static int StandAnim[]  = { 0, -1, 0 };
static int RunAnim[]    = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1, 0 };


EOCTOROCK::EOCTOROCK()
    {
    x = 160;
    y = 100;
    width = 15;
    height = 15;
    speed = .5;

    dir = 3;

    Anim.SetAnim(StandAnim);

    Pattern.SetMaxStates(6);
    Pattern.SetCountMax(100);
    Pattern.SetState(-1);
    }



void EOCTOROCK::DoLogic()
     {
     switch(action)
         {
         case OCTO_RUNLEFT:
              MoveLeft();
              break;

         case OCTO_RUNRIGHT:
              MoveRight();
              break;

         case OCTO_RUNUP:
              MoveUp();
              break;

         case OCTO_RUNDOWN:
              MoveDown();
              break;
         }

     Anim.Increment();
     Pattern.Increment();

     if (x < 0)         x = 0;
     if (x > 319)       x = 319;
     if (y < 0)         y = 0;
     if (y > 199)       y = 199;
     }



void EOCTOROCK::Draw(BITMAP * buffer)
     {
     draw_sprite(buffer, OctoBmp[dir][Anim.GetFrame()], int(x - (width / 2)), int(y - (height / 2)));
     }



void EOCTOROCK::ChangeAction(int newaction)
     {
     if (newaction == action)
        return;

     action = newaction;

     switch(newaction)
         {
         case OCTO_STAND:
              Anim.SetAnim(StandAnim);
              break;

         case OCTO_RUNLEFT:
              dir = 0;
              Anim.SetAnim(RunAnim);
              break;

         case OCTO_RUNRIGHT:
              dir = 1;
              Anim.SetAnim(RunAnim);
              break;

         case OCTO_RUNUP:
              dir = 2;
              Anim.SetAnim(RunAnim);
              break;

         case OCTO_RUNDOWN:
              dir = 3;
              Anim.SetAnim(RunAnim);
              break;
         }
     }


void EOCTOROCK::OnPatternChange()
     {
     int pat;

     Pattern.Randomize();
     pat = Pattern.GetState();

     switch(pat)
         {
         case 0:
              ChangeAction(OCTO_RUNLEFT);
              break;

         case 1:
              ChangeAction(OCTO_RUNRIGHT);
              break;

         case 2:
              ChangeAction(OCTO_RUNUP);
              break;

         case 3:
              ChangeAction(OCTO_RUNDOWN);
              break;

         default:
              ChangeAction(OCTO_STAND);
              break;
         }
     }
