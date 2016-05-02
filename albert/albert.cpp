#include "albert.h"
#include <QDebug>
#include <string>

albert::albert()
{
    RELATIONS_COUNT = sizeof(relations) / sizeof(relations[0]);
    BINDS_COUNT = sizeof(binds) / sizeof(binds[0]);
    cnt = 0;
}


int albert::GetGroupItemValue(GROUP *group, ITEM_TYPE type)
{
    return group->itemValue[type];
}

int albert::FindGroupIdxByItem(GROUP *groups, ITEM_TYPE type, int value)   //返回5组答案中，类型type中，值是value的，是哪组答案
{
    for(int i = 0; i < GROUPS_COUNT; i++)
    {
        if(GetGroupItemValue(&groups[i], type) == value)
        {
            return i;
        }
    }

    return -1;
}

bool albert::CheckGroupBind(GROUP *groups, int groupIdx, ITEM_TYPE type, int value)   //判断第groupIdx组中的type类型的值是否等于value
{
    if(GetGroupItemValue(&groups[groupIdx], type) != value)
    {
        return false;
    }

    return true;
}

bool albert::CheckAllGroupsBind(GROUP *groups, BIND *binds)  //bind限定条件入口
{
    for(int i = 0; i < BINDS_COUNT; i++)    //一共有多少条bind，就比较多少次
    {
        int grpIdx = FindGroupIdxByItem(groups, binds[i].first_type, binds[i].first_val);  //先找5组答案中符合bind中的第一个条件的是哪项
        if(grpIdx != -1)  //如果第一个条件满足，再判断第二个条件
        {
            if(!CheckGroupBind(groups, grpIdx, binds[i].second_type, binds[i].second_val))
            {
                return false;
            }
        }
    }

    return true;
}

bool albert::CheckGroupRelation(GROUP *groups, int groupIdx, ITEM_TYPE type, int value)  //判断与第groupIdx个答案相邻的答案是否符合类型type的值为value
{
    if(groupIdx == 0)    //如果是第0个答案，那么相邻的只有第1个答案
    {
        if(GetGroupItemValue(&groups[groupIdx + 1], type) != value)
        {
            return false;
        }
    }
    else if(groupIdx == (GROUPS_COUNT - 1))    //如果是最后一个，相邻的取它的前一个
    {
        if(GetGroupItemValue(&groups[groupIdx - 1], type) != value)
        {
            return false;
        }
    }
    else     //如果不是两边的，那么就要算它的前一个和后一个
    {
        if( (GetGroupItemValue(&groups[groupIdx - 1], type) != value)
            && (GetGroupItemValue(&groups[groupIdx + 1], type) != value) )
        {
            return false;
        }
    }

    return true;
}

bool albert::CheckAllGroupsRelation(GROUP *groups, const RELATION *relations)   //寻找两组答案直接的关系是否满足要求
{
    for(int i = 0; i < RELATIONS_COUNT; i++)
    {
        int grpIdx = FindGroupIdxByItem(groups, relations[i].type, relations[i].val);   //按照要求中的第一组关系找到符合这组关系的答案的组号
        if(grpIdx != -1)   //如果有符合第一组关系的答案，再判断这个组的相邻组是否符合
        {
            if(!CheckGroupRelation(groups, grpIdx, relations[i].relation_type, relations[i].relation_val))
            {
                return false;
            }
        }
    }

    return true;
}

//传入比较的内容type，遍历前groupAsd组答案中该比较类型的值中，是否已经存在value
bool albert::IsGroupItemValueUsed(GROUP *groups, int groupAsd, ITEM_TYPE type, int value)
{
    for(int i = 0; i < groupAsd; i++)
    {
        if(groups[i].itemValue[type] == value)
        {
            return true;
        }
    }

    return false;
}

void albert::PrintGroupsNameTitle()
{
    QDebug deb = qDebug();
    for(int i = type_house; i <= type_cigaret; i++)
    {
        deb<<itemName[i];
    }
  //  deb << endl;
}

void albert::PrintSingleLineGroup(GROUP *group)
{
    QDebug deb = qDebug();
    for(int i = type_house; i <= type_cigaret; i++)
    {
        deb <<valueName[i][group->itemValue[i]];
    }
 //   deb << endl;
}

void albert::PrintAllGroupsResult(GROUP *groups, int groupCount)
{
    PrintGroupsNameTitle();
    for(int i = 0; i < groupCount; i++)
    {
        PrintSingleLineGroup(&groups[i]);
    }
    qDebug() << endl;
}

void albert::DoGroupsfinalCheck(GROUP *groups)   //输入参数是一种推理结果
{
    cnt++;   //答案的数量
    //if((cnt % 1000000) == 0)
      //  qDebug() << cnt;

    if(CheckAllGroupsBind(groups, binds) && CheckAllGroupsRelation(groups, relations))   //判断答案是否满足规划出的8种限制条件，为了不用if而设计的数据结构
    {
        PrintAllGroupsResult(groups, GROUPS_COUNT);
    }
}

void albert::EnumPeopleCigerts(GROUP *groups, int groupIdx)   //和宠物排列一样，这里主人抽烟的情况也是全排列
{
    if(groupIdx == GROUPS_COUNT) /*递归终止条件*/    //共有5！种
    {
        DoGroupsfinalCheck(groups);         //递归一直嵌套到这里，这里有4!*4!*4!*5!*5!种答案
        return;
    }

    for(int i = CIGARET_BLENDS; i <= CIGARET_BLUEMASTER; i++)
    {
        if(!IsGroupItemValueUsed(groups, groupIdx, type_cigaret, i))
        {
            groups[groupIdx].itemValue[type_cigaret] = i;

            EnumPeopleCigerts(groups, groupIdx + 1);
        }
    }
}

void albert::ArrangePeopleCigert(GROUP *groups)
{
    EnumPeopleCigerts(groups, 0);
}

void albert::EnumPeoplePats(GROUP *groups, int groupIdx)
{
    if(groupIdx == GROUPS_COUNT) /*递归终止条件*/    //没有任何条件约束的，主人宠物全排列一共有5！种情况
    {
        ArrangePeopleCigert(groups);
        return;
    }

    for(int i = PET_HORSE; i <= PET_DOG; i++)
    {
        if(!IsGroupItemValueUsed(groups, groupIdx, type_pet, i))
        {
            groups[groupIdx].itemValue[type_pet] = i;

            EnumPeoplePats(groups, groupIdx + 1);
        }
    }
}

void albert::ArrangePeoplePet(GROUP *groups)
{
    /*这里没有可用规则*/
    EnumPeoplePats(groups, 0);
}

void albert::EnumPeopleDrinks(GROUP *groups, int groupIdx)
{
    if(groupIdx == GROUPS_COUNT) /*递归终止条件*/        //5个房子里的人喝饮料有5！种情况满足此if
    {
        /*应用规则(8)：住在中间那个房子里的人喝牛奶；*/
        if(groups[2].itemValue[type_drink] == DRINK_MILK)    //只有这种情况时，才进行下一种递归寻找，这种情况有4！
        {
            ArrangePeoplePet(groups);
        }
        return;
    }

    for(int i = DRINK_TEA; i <= DRINK_MILK; i++)
    {
        if(!IsGroupItemValueUsed(groups, groupIdx, type_drink, i))
        {
            groups[groupIdx].itemValue[type_drink] = i;
            EnumPeopleDrinks(groups, groupIdx + 1);
        }
    }
}

void albert::ArrangePeopleDrinks(GROUP *groups)
{
    /*这里没有可用规则*/
    EnumPeopleDrinks(groups, 0);  //这个可以直接在遍历国家里面调用
}

/*遍历国家*/
void albert::EnumHouseNations(GROUP *groups, int groupIdx)    //这个过程和给房子赋值相同
{
    if(groupIdx == GROUPS_COUNT) /*递归终止条件*/    //每当后4所房子主人的民族确定了之后，就进行下一次，共4！种答案
    {
        ArrangePeopleDrinks(groups);
        return;
    }

    for(int i = NATION_NORWAY; i <= NATION_GERMANY; i++)
    {
        if(!IsGroupItemValueUsed(groups, groupIdx, type_nation, i))
        {
            groups[groupIdx].itemValue[type_nation] = i;

            EnumHouseNations(groups, groupIdx + 1);
        }
    }
}

void albert::ArrangeHouseNations(GROUP *groups)
{
    /*应用规则(9)：挪威人住在第一个房子里面；*/
    groups[0].itemValue[type_nation] = NATION_NORWAY;   //该条件是定死的，所以只需要找后面的4组答案
    EnumHouseNations(groups, 1); /*从第二个房子开始*/
}


/* 遍历房子颜色*/
void albert::EnumHouseColors(GROUP *groups, int groupIdx)     //程序入口，多重遍历中的一个
{
    if(groupIdx == GROUPS_COUNT) /*递归终止条件*/         //一共5所房子，每当5组房子都有颜色后，就要进入下一个递归来赋值民族了，共有4！种答案
    {
        ArrangeHouseNations(groups);
        return;
    }

    for(int i = COLOR_BLUE; i <= COLOR_YELLOW; i++)
    {
        if(!IsGroupItemValueUsed(groups, groupIdx, type_house, i))   //检查生成的组中，该颜色是否用过
        {
            groups[groupIdx].itemValue[type_house] = i;     //没用过的颜色，就赋值这个颜色
            if(i == COLOR_GREEN) //应用线索(4)：绿房子紧挨着白房子，在白房子的左边；
            {
                groups[++groupIdx].itemValue[type_house] = COLOR_WHITE;  //限制条件1，绿房子和白房子相邻
            }

            EnumHouseColors(groups, groupIdx + 1);   //递归调用，赋值下一个房子的颜色
            if(i == COLOR_GREEN)        //如果i是绿色，因为它同时赋值了白色，所以回退的时候，要把groupIdx减回去
            {
                groupIdx--;
            }
        }
    }
}

/*void albert::test_Checkfunctions()
{
    GROUP groups[GROUPS_COUNT] =
    {
        {COLOR_YELLOW, NATION_NORWAY, DRINK_WATER, PET_CAT, CIGARET_DUNHILL},
        {COLOR_BLUE, NATION_DANMARK, DRINK_TEA, PET_HORSE, CIGARET_BLENDS},
        {COLOR_RED, NATION_ENGLAND, DRINK_MILK, PET_BIRD, CIGARET_PALLMALL},
        {COLOR_GREEN, NATION_GERMANY, DRINK_COFFEE, PET_FISH, CIGARET_PRINCE},
        {COLOR_WHITE, NATION_SWEDEND, DRINK_BEER, PET_DOG, CIGARET_BLUEMASTER}
    };
    Q_ASSERT(CheckAllGroupsBind(groups, binds));
    Q_ASSERT(CheckAllGroupsRelation(groups, relations));

    GROUP groups2[GROUPS_COUNT] =
    {
        {COLOR_YELLOW, NATION_DANMARK, DRINK_WATER, PET_CAT, CIGARET_DUNHILL},
        {COLOR_BLUE, NATION_NORWAY, DRINK_TEA, PET_HORSE, CIGARET_BLENDS},
        {COLOR_RED, NATION_ENGLAND, DRINK_MILK, PET_BIRD, CIGARET_PALLMALL},
        {COLOR_GREEN, NATION_GERMANY, DRINK_COFFEE, PET_FISH, CIGARET_PRINCE},
        {COLOR_WHITE, NATION_SWEDEND, DRINK_BEER, PET_DOG, CIGARET_BLUEMASTER}
    };

    Q_ASSERT(!CheckAllGroupsBind(groups2, binds));
    Q_ASSERT(!CheckAllGroupsRelation(groups2, relations));

    GROUP groups3[GROUPS_COUNT] =
    {
        {COLOR_YELLOW, NATION_NORWAY, DRINK_WATER, PET_CAT, CIGARET_DUNHILL},
        {COLOR_BLUE, NATION_DANMARK, DRINK_TEA, PET_BIRD, CIGARET_BLENDS},
        {COLOR_RED, NATION_ENGLAND, DRINK_MILK, PET_HORSE, CIGARET_PALLMALL},
        {COLOR_GREEN, NATION_GERMANY, DRINK_COFFEE, PET_FISH, CIGARET_PRINCE},
        {COLOR_WHITE, NATION_SWEDEND, DRINK_BEER, PET_DOG, CIGARET_BLUEMASTER}
    };

    Q_ASSERT(!CheckAllGroupsBind(groups3, binds));
    Q_ASSERT(!CheckAllGroupsRelation(groups3, relations));
}

*/
/*

绿房子紧挨着白房子，在白房子的左边；

住在中间那个房子里的人喝牛奶；

挪威人住在第一个房子里面；

           国家           房子           宠物           饮料           香烟
           挪威           黄色             猫         矿泉水        Dunhill
           丹麦           蓝色             马             茶         Blends
           英国           红色             鸟           牛奶       PallMall
           德国           绿色             鱼           咖啡         Prince
           瑞典           白色             狗           啤酒     BlueMaster
*/






