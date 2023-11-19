#ifndef __HERO_H
#define __HERO_H


#include <Allegro.h>
#include "Entity.h"


typedef struct
        {
        float x, y;
        int enabled;
        int useable;
        int power;
        } SWORD;


class HERO : public ENTITY
      {
      public:
             HERO();

             virtual void DoLogic();
             virtual void Draw(BITMAP * buffer);

      protected:
             int enabled;
             int busycount, busymax;
             SWORD Sword;

             virtual void ChangeAction(int);

             void EnableHero();
             void DisableHero(int);

             virtual void OnDamage(int amount, int type, int attackdir);
      };


#endif

