#include "Entity.h"


// Animation Class //


void ANIM::SetAnim(int * newptr)
     {
     ptr = newptr;
     pos = 0;
     }


int ANIM::GetFrame()
     {
     if (ptr)
        {
        return ptr[pos];
        }

     return 0;
     }


void ANIM::Increment()
     {
     if (ptr)
        {
        pos++;

        if (ptr[pos] == -1)
           pos = ptr[pos + 1];
        }
     }



// Entity Class //

int ENTITY::Collide(float tx, float ty, float twidth, float theight)
    {
    if (tx + (twidth / 2) < x - (width / 2) ||
        tx - (twidth / 2) > x + (width / 2) ||
        ty + (theight / 2) < y - (height / 2) ||
        ty - (theight / 2) > y + (height / 2))
        return 0;

    return 1;
    }




// Pattern Class //


void PATTERN::SetEntity(PENTITY * pEnt)
    {
    pEntity = pEnt;
    }


void PATTERN::SetState(int num)
    {
    state = num;
    count = 0;
    }


int PATTERN::GetState()
    {
    return state;
    }


void PATTERN::SetMaxStates(int num)
    {
    maxstates = num;
    }


void PATTERN::SetCountMax(int num)
    {
    countmax = num;
    }


void PATTERN::Randomize()
    {
    state = random() % maxstates;
    count = 0;
    }


void PATTERN::Increment()
    {
    if (countmax)
       {
       count++;
       if (count >= countmax)
          pEntity->OnPatternChange();
       }
    }



// PEntity Class //


PENTITY::PENTITY()
    {
    Pattern.SetEntity(this);
    }


void PENTITY::OnPatternChange()
    {
    Pattern.Randomize();
    }

