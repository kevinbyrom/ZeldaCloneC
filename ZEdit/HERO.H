#ifndef __Hero_H
#define __Hero_H

#define STANDING       0
#define RUNNING        1
#define SWORD_ATTACK   2
#define ITEM_ATTACK    3
#define HURT           4
#define HOLDINGITEM    5
#define RAFT           6
#define FLUTE          7

typedef struct
    {
    int X, Y;
    int DestX, DestY;
    int Speed;

    int Action;
    int Dir;
    int Anim;
    int * pAnim;

    int CurItem;
    int Swordless;

    int HurtCount;
    int SwordCount;
    int ItemCount;

    int Ghost;
    } HERO;


extern HERO Hero;


void InitHero(void);
void HeroLogic(void);

void ChangeHeroAction(int action, int dir);

#endif

