#ifndef ITEMSTATE_H
#define ITEMSTATE_H

#pragma once
#include <QString>

typedef enum tagBoatLocation
{
    LOCAL = 0,
    REMOTE
}BOAT_LOCATION;

typedef enum tagActionName
{
    ONE_MONSTER_GO = 0,
    TWO_MONSTER_GO,
    ONE_MONK_GO,
    TWO_MONK_GO,
    ONE_MONSTER_ONE_MONK_GO,
    ONE_MONSTER_BACK,
    TWO_MONSTER_BACK,
    ONE_MONK_BACK,
    TWO_MONK_BACK,
    ONE_MONSTER_ONE_MONK_BACK,
    INVALID_ACTION_NAME,
}ACTION_NAME;

typedef struct tagActionEffection
{
    ACTION_NAME act;      //主要是为了显示
    BOAT_LOCATION boat_to; //船移动的方向
    int move_monster; //此次移动的妖怪数量
    int move_monk; //此次移动的和尚数量
}ACTION_EFFECTION;

typedef struct tagActionDescription
{
    ACTION_NAME act;
    const char *description; //相应动作的人类语言描述
}ACTION_DESCRIPTION;

class ItemState
{
public:
    ItemState();
    ItemState(const ItemState& state);
    ItemState& operator=(const ItemState& state);
    bool IsSameState(const ItemState& state) const;
    void SetState(int lmonster, int lmonk, int rmonster, int rmonk, BOAT_LOCATION bl);
    QString GetActionDescription(ACTION_NAME act);
    void PrintStates();
    bool IsFinalState();
    bool CanTakeAction(ACTION_EFFECTION& ae) const;
    bool IsValidState();

    int local_monster;
    int local_monk;
    int remote_monster;
    int remote_monk;
    BOAT_LOCATION boat; /*LOCAL or REMOTE*/
    ACTION_NAME curAct;
};

#endif // ITEMSTATE_H
