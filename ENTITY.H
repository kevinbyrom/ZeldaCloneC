#ifndef __ENTITY_H
#define __ENTITY_H

#include <Allegro.h>



class ANIM
      {
      public:
             void SetAnim(int *);
             int GetFrame();
             void Increment();

      protected:
                int * ptr;
                int pos;
      };




class ENTITY
      {
      public:
             int Collide(float tx, float ty, float twidth, float theight);
             virtual void DoLogic(){}
             virtual void Draw(BITMAP * buffer){}

      protected:
             float x,
                   y,
                   width,
                   height,
                   speed;

             int dir,
                 action,
                 solid,
                 transparent,
                 visible;

             int health,
                 armor;

             ANIM Anim;

             void MoveLeft()    { x -= speed; }
             void MoveRight()   { x += speed; }
             void MoveUp()      { y -= speed; }
             void MoveDown()    { y += speed; }

             virtual void ChangeAction(int){}
             virtual void OnDamage(int amount, int type, int attackdir){}
      };


class PENTITY;

class PATTERN
      {
      public:
             void SetEntity(PENTITY *);
             void SetState(int);
             int GetState();
             void SetMaxStates(int);
             void SetCountMax(int);

             void Randomize();

             void Increment();

      protected:
                PENTITY * pEntity;

                int state,
                    maxstates,
                    count,
                    countmax;
      };


class PENTITY : public ENTITY
      {
      public:
             PENTITY();

             virtual void OnPatternChange();

      protected:
                PATTERN Pattern;
      };

#endif
