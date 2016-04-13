#include "item_state.h"
#include <QDebug>
const int monster_count = 3;
const int monk_count    = 3;

ACTION_DESCRIPTION actDesc[] =
{
    { ONE_MONSTER_GO ,            "One monster go over river"              },
    { TWO_MONSTER_GO ,            "Two monster go over river"              },
    { ONE_MONK_GO ,               "One monk go over river"                 },
    { TWO_MONK_GO ,               "Two monk go over river"                 },
    { ONE_MONSTER_ONE_MONK_GO ,   "One monster and one monk go over river" },
    { ONE_MONSTER_BACK ,          "One monster go back"                    },
    { TWO_MONSTER_BACK ,          "Two monster go back"                    },
    { ONE_MONK_BACK ,             "One monk go back"                       },
    { TWO_MONK_BACK ,             "Two monk go back"                       },
    { ONE_MONSTER_ONE_MONK_BACK , "One monster and one monk go back"       }
};

QString ItemState::GetActionDescription(ACTION_NAME act)
{
    int actCount = sizeof(actDesc) / sizeof(actDesc[0]);
    for(int i = 0; i < actCount; ++i)
    {
        if(actDesc[i].act == act)
        {
            return actDesc[i].description;
        }
    }

    return "Unknown action";
}

ItemState::ItemState()
{
    SetState(monster_count, monk_count, 0, 0, LOCAL);
    curAct = INVALID_ACTION_NAME;
}

ItemState::ItemState(const ItemState& state)
{
    SetState(state.local_monster, state.local_monk,
             state.remote_monster, state.remote_monk, state.boat);
    curAct = state.curAct;
}

ItemState& ItemState::operator=(const ItemState& state)
{
    SetState(state.local_monster, state.local_monk,
             state.remote_monster, state.remote_monk, state.boat);
    curAct = state.curAct;

    return *this;
}

bool ItemState::IsSameState(const ItemState& state) const
{
    return ( (local_monster == state.local_monster)
             && (local_monk == state.local_monk)
             && (remote_monster == state.remote_monster)
             && (remote_monk == state.remote_monk)
             && (boat == state.boat) );
}

void ItemState::SetState(int lmonster, int lmonk, int rmonster, int rmonk, BOAT_LOCATION bl)
{
    local_monster  = lmonster;
    local_monk     = lmonk;
    remote_monster = rmonster;
    remote_monk    = rmonk;
    boat           = bl;
}

void ItemState::PrintStates()
{
    qDebug() << GetActionDescription(curAct) << endl;
}

bool ItemState::IsFinalState()
{
    return ( (local_monster == 0) && (local_monk == 0)
             && (remote_monster == monster_count) && (remote_monk == monk_count)
             && (boat == REMOTE) );
}

bool ItemState::CanTakeAction(ACTION_EFFECTION& ae) const
{
    if(boat == ae.boat_to)        //船当前的位置和要去往的位置一样
        return false;
    if((local_monster + ae.move_monster) < 0 || (local_monster + ae.move_monster) > monster_count)
        return false;             //如果此岸的妖怪（和尚）不够移动出去，或 移回来的妖怪总和大于妖怪总数
    if((local_monk + ae.move_monk) < 0 || (local_monk + ae.move_monk) > monk_count)
        return false;

    return true;
}

bool ItemState::IsValidState()      //判断和尚数量必须比妖怪多
{
    if((local_monk > 0) && (local_monster > local_monk))
    {
        return false;
    }
    if((remote_monk > 0) && (remote_monster > remote_monk))
    {
        return false;
    }

    return true;
}


