#ifndef ALBERT_H
#define ALBERT_H
#include <cassert>
#include <QString>
const int GROUPS_ITEMS = 5;
const int GROUPS_COUNT = 5;

enum ITEM_TYPE {type_house,type_nation,type_drink,type_pet,type_cigaret};

class BIND
{
public:
    ITEM_TYPE first_type;
    int first_val;
    ITEM_TYPE second_type;
    int second_val;
    BIND();
    BIND(ITEM_TYPE first_type,int first_val,ITEM_TYPE second_type,int second_val)
    {
        this->first_type = first_type;
        this->first_val = first_val;
        this->second_type = second_type;
        this->second_val = second_val;
    }
};

class RELATION
{
public:
    ITEM_TYPE type;
    int val;
    ITEM_TYPE relation_type;
    int relation_val;
    RELATION();
    RELATION(ITEM_TYPE first_type,int first_val,ITEM_TYPE second_type,int second_val)
    {
        this->type = first_type;
        this->val = first_val;
        this->relation_type = second_type;
        this->relation_val = second_val;
    }
};


typedef struct tagGroup
{
    int itemValue[5];
}GROUP;


class albert
{
public:
    albert();
    enum color {COLOR_BLUE,COLOR_RED,COLOR_GREEN,COLOR_YELLOW,COLOR_WHITE};
    enum nation {NATION_NORWAY,NATION_DANMARK,NATION_SWEDEND,NATION_ENGLAND,NATION_GERMANY};
    enum drink {DRINK_TEA,DRINK_WATER,DRINK_COFFEE,DRINK_BEER,DRINK_MILK};
    enum pet {PET_HORSE,PET_CAT,PET_BIRD,PET_FISH,PET_DOG};
    enum cigaret {CIGARET_BLENDS,CIGARET_DUNHILL,CIGARET_PRINCE,CIGARET_PALLMALL,CIGARET_BLUEMASTER};
    int FindGroupIdxByItem(GROUP *groups, ITEM_TYPE type, int value);
    int GetGroupItemValue(GROUP *group, ITEM_TYPE type);
    bool CheckAllGroupsBind(GROUP *groups, BIND *binds);
    bool CheckGroupBind(GROUP *groups, int groupIdx, ITEM_TYPE type, int value);
    bool CheckGroupRelation(GROUP *groups, int groupIdx, ITEM_TYPE type, int value);
    bool CheckAllGroupsRelation(GROUP *groups, const RELATION *relations);
    bool IsGroupItemValueUsed(GROUP *groups, int groupAsd, ITEM_TYPE type, int value);
    void PrintAllGroupsResult(GROUP *groups, int groupCount);
    void PrintSingleLineGroup(GROUP *group);
    void PrintGroupsNameTitle();
    int cnt;
    void DoGroupsfinalCheck(GROUP *groups);
    void EnumPeopleCigerts(GROUP *groups, int groupIdx);
    void ArrangePeopleCigert(GROUP *groups);
    void EnumPeoplePats(GROUP *groups, int groupIdx);
    void ArrangePeoplePet(GROUP *groups);
    void EnumPeopleDrinks(GROUP *groups, int groupIdx);
    void ArrangePeopleDrinks(GROUP *groups);
    void EnumHouseNations(GROUP *groups, int groupIdx);
    void ArrangeHouseNations(GROUP *groups);
    void EnumHouseColors(GROUP *groups, int groupIdx);
    void test_Checkfunctions();

/*    const BIND binds[8] =
    {
        { type_house, COLOR_RED, type_nation, NATION_ENGLAND },
        { type_nation, NATION_SWEDEND, type_pet, PET_DOG },
        { type_nation, NATION_DANMARK, type_drink, DRINK_TEA },
        { type_house, COLOR_GREEN, type_drink, DRINK_COFFEE },
        { type_cigaret, CIGARET_PALLMALL, type_pet, PET_BIRD },
        { type_house, COLOR_YELLOW, type_cigaret, CIGARET_DUNHILL },
        { type_cigaret, CIGARET_BLUEMASTER, type_drink, DRINK_BEER },
        { type_nation, NATION_GERMANY, type_cigaret, CIGARET_PRINCE }
    };*/

    BIND binds[8] =
    {
    BIND( type_house, COLOR_RED, type_nation, NATION_ENGLAND ),
    BIND( type_nation, NATION_SWEDEND, type_pet, PET_DOG ),
    BIND( type_nation, NATION_DANMARK, type_drink, DRINK_TEA ),
    BIND( type_house, COLOR_GREEN, type_drink, DRINK_COFFEE ),
    BIND( type_cigaret, CIGARET_PALLMALL, type_pet, PET_BIRD ),
    BIND( type_house, COLOR_YELLOW, type_cigaret, CIGARET_DUNHILL ),
    BIND( type_cigaret, CIGARET_BLUEMASTER, type_drink, DRINK_BEER ),
    BIND( type_nation, NATION_GERMANY, type_cigaret, CIGARET_PRINCE )
    };
    RELATION relations[4] =
    {
        RELATION( type_cigaret, CIGARET_BLENDS, type_pet, PET_CAT ),
        RELATION( type_pet, PET_HORSE, type_cigaret, CIGARET_DUNHILL ),
        RELATION( type_nation, NATION_NORWAY, type_house, COLOR_BLUE ),
        RELATION( type_cigaret, CIGARET_BLENDS, type_drink, DRINK_WATER )
    };
    //QString itemName[5] = { "房子", "国家", "饮料", "宠物", "烟"};
    QString itemName[5]= { "房子", "国家", "饮料", "宠物", "烟"};
    QString valueName[5][5] =
    {
        { "蓝色", "红色", "绿色", "黄色", "白色" },
        { "挪威", "丹麦", "瑞士", "英国", "德国" },
        { "茶", "水", "咖啡", "啤酒", "牛奶" },
        { "马", "猫", "鸟", "鱼", "狗" },
        { "Blends", "Dunhill", "Prince", "PallMall", "BlueMaster" }
    };
    int BINDS_COUNT;
    int RELATIONS_COUNT;
};

#endif // ALBERT_H
