#ifndef __INPUT_H
#define __INPUT_H

class INPUT
      {
      public:
             INPUT();

             void Poll();
             int A();
             int B();
             int Left();
             int Right();
             int Up();
             int Down();

      protected:
                int key_A,
                    key_B,
                    key_left,
                    key_right,
                    key_up,
                    key_down;
      };

extern INPUT Input;

#endif
