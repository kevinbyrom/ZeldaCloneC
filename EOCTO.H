#ifndef __EOCTO_H
#define __EOCTO_H

#include "Entity.h"


class EOCTOROCK : public PENTITY
      {
      public:
             EOCTOROCK();

             virtual void DoLogic();
             virtual void Draw(BITMAP *);

             virtual void OnPatternChange();

      protected:
                virtual void ChangeAction(int);
      };

#endif
