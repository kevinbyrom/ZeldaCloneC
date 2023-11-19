// THIS IS A STRIPPED DOWN VERSION OF HERO.C INCLUDED IN ZELDA.EXE //
#include <Allegro.h>
#include <Math.h>
#include "Hero.h"
#include "Maps.h"
#include "Editor.h"

#define ROUND(x) (int)(fmod(x + 1, 1) >= .5 ? ceil(x) : floor(x))

void AdjustHeroMove(void);

HERO Hero;

// ANIMATION ARRAYS

int StandLeftAnim[] = {8, -1, 0};
int StandRightAnim[] = {12, -1, 0};
int StandUpAnim[] = {4, -1, 0};
int StandDownAnim[] = {0, -1, 0};

int RunLeftAnim[] = {8,8,9,9,9,9,9,8,8,10,10,10,10,10,-1,0};
int RunRightAnim[] = {12,12,13,13,13,13,13,12,12,14,14,14,14,14,-1,0};
int RunUpAnim[] = {4,4,5,5,5,5,5,4,4,6,6,6,6,6,-1,0};
int RunDownAnim[] = {0,0,1,1,1,1,1,0,0,2,2,2,2,2,-1,0};


// FUNCTIONS //

void InitHero(void)
     {
     Hero.X = 100;
     Hero.Y = 100;
     Hero.Speed = 1;
     Hero.Action = STANDING;
     Hero.Dir = DOWN;
     Hero.pAnim = StandDownAnim;
     Hero.Anim = 0;
     Hero.Ghost = 0;
     }


void HeroLogic(void)
     {

     // Increment the hero animation //
     Hero.Anim++;
     if (Hero.pAnim[Hero.Anim] == -1)
        Hero.Anim = Hero.pAnim[Hero.Anim + 1];


     switch(Hero.Action)
         {
         case RUNNING:

             if (CanMove(Hero.X, Hero.Y, 6, 6, Hero.Dir, Hero.Speed))
                 {
                 switch(Hero.Dir)
                     {
                     case LEFT:
                         Hero.X -= Hero.Speed;
                         break;

                     case RIGHT:
                         Hero.X += Hero.Speed;
                         break;

                     case UP:
                         Hero.Y -= Hero.Speed;
                         break;

                     case DOWN:
                         Hero.Y += Hero.Speed;
                         break;
                     }

                 if (Hero.X < 0)        Hero.X = 0;
                 if (Hero.X > 239)      Hero.X = 230;
                 if (Hero.Y < 0)        Hero.Y = 0;
                 if (Hero.Y > 164)      Hero.Y = 164;
                 }
             else
                 AdjustHeroMove();
             break;
         }
     }


void ChangeHeroAction(int action, int dir)
   {
   if (action == Hero.Action && dir == Hero.Dir)
       return;


   Hero.Action = action;
   Hero.Dir    = dir;
   Hero.Anim = 0;


   switch(Hero.Action)
       {

       // RUNNING //

       case RUNNING:

           switch(Hero.Dir)
               {
               case LEFT:
                   Hero.pAnim =  RunLeftAnim;
                   break;

               case RIGHT:
                   Hero.pAnim =  RunRightAnim;
                   break;

               case UP:
                   Hero.pAnim =  RunUpAnim;
                   break;

               case DOWN:
                   Hero.pAnim =  RunDownAnim;
                   break;
               }
           break;

       // STANDING //

       case STANDING:

           switch(Hero.Dir)
               {
               case LEFT:
                   Hero.pAnim =  StandLeftAnim;
                   break;

               case RIGHT:
                   Hero.pAnim =  StandRightAnim;
                   break;

               case UP:
                   Hero.pAnim =  StandUpAnim;
                   break;

               case DOWN:
                   Hero.pAnim =  StandDownAnim;
                   break;
               }
           break;
       }
   }


void AdjustHeroMove(void)
   {
   int TileX1, TileY1;

   switch(Hero.Dir)
       {
       case LEFT:
           // UPPER LEFT //

           TileX1 = ROUND((Hero.X - 6 - Hero.Speed) / 5);
           TileY1 = ROUND((Hero.Y - 6) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[TileX1 + ((Hero.Y / 5) * 48)] &&
                     !Map.Walk[TileX1 + (((Hero.Y + 6) / 5) * 48)])
                     {
                     Hero.Y += Hero.Speed;
                     return;
                     }
                 }

           // LOWER LEFT //

           TileX1 = ROUND((Hero.X - 6 - Hero.Speed) / 5);
           TileY1 = ROUND((Hero.Y + 6) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[TileX1 + ((Hero.Y / 5) * 48)] &&
                     !Map.Walk[TileX1 + (((Hero.Y - 6) / 5) * 48)])
                     {
                     Hero.Y -= Hero.Speed;
                     return;
                     }
                 }
           break;

       case RIGHT:
           // UPPER RIGHT //

           TileX1 = ROUND((Hero.X + 6 + Hero.Speed) / 5);
           TileY1 = ROUND((Hero.Y - 6) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[TileX1 + ((Hero.Y / 5) * 48)] &&
                     !Map.Walk[TileX1 + (((Hero.Y + 6) / 5) * 48)])
                     {
                     Hero.Y += Hero.Speed;
                     return;
                     }
                 }

           // LOWER RIGHT //

           TileX1 = ROUND((Hero.X + 6 + Hero.Speed) / 5);
           TileY1 = ROUND((Hero.Y + 6) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[TileX1 + ((Hero.Y / 5) * 48)] &&
                     !Map.Walk[TileX1 + (((Hero.Y - 6) / 5) * 48)])
                     {
                     Hero.Y -= Hero.Speed;
                     return;
                     }
                 }
           break;

       case UP:
           // LEFTMOST UP //

           TileX1 = ROUND((Hero.X - 6) / 5);
           TileY1 = ROUND((Hero.Y - 6 - Hero.Speed) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[(Hero.X / 5) + (TileY1 * 48)] &&
                     !Map.Walk[((Hero.X + 5) / 5) + (TileY1 * 48)])
                     {
                     Hero.X += Hero.Speed;
                     return;
                     }
                 }

           // RIGHTMOST UP //

           TileX1 = ROUND((Hero.X + 6) / 5);
           TileY1 = ROUND((Hero.Y - 6 - Hero.Speed) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[(Hero.X / 5) + (TileY1 * 48)] &&
                     !Map.Walk[((Hero.X - 6) / 5) + (TileY1 * 48)])
                     {
                     Hero.X -= Hero.Speed;
                     return;
                     }
                 }
           break;

       case DOWN:
           // LEFTMOST DOWN //

           TileX1 = ROUND((Hero.X - 6) / 5);
           TileY1 = ROUND((Hero.Y + 6 + Hero.Speed) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[(Hero.X / 5) + (TileY1 * 48)] &&
                     !Map.Walk[((Hero.X + 5) / 5) + (TileY1 * 48)])
                     {
                     Hero.X += Hero.Speed;
                     return;
                     }
                 }

           // RIGHTMOST DOWN //

           TileX1 = ROUND((Hero.X + 6) / 5);
           TileY1 = ROUND((Hero.Y + 6 + Hero.Speed) / 5);

           if (TileX1 >= 0 && TileX1 < 48 && TileY1 >= 0 && TileY1 < 33)
              if (Map.Walk[TileX1 + (TileY1 * 48)])
                 {
                 if (!Map.Walk[(Hero.X / 5) + (TileY1 * 48)] &&
                     !Map.Walk[((Hero.X - 6) / 5) + (TileY1 * 48)])
                     {
                     Hero.X -= Hero.Speed;
                     return;
                     }
                 }
           break;
       }
   }

