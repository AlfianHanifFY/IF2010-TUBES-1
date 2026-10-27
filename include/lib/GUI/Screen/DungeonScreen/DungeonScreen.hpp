#ifndef DUNGEONSCREEN_HPP
#define DUNGEONSCREEN_HPP

#include <iostream>
using namespace std;

#include "../Screen.hpp"

class DungeonScreen : public Screen
{
private:
    Button EscapeBtn;
    Button LogBtn;
    Button ItemBtn;
    Button SkillBtn;
    Button AttackBtn;
    Button CancelBtn;
    Button CharBtn;
    Button UseBtn;
    Button Skill1Btn;
    Button Skill2Btn;

    Texture2D BackPack;
    Texture2D SkillPack;
    Unit *selectedUnit;
    map<string, bool> toggle;

    Animation CharAnim;
    Animation SummonAnim;
    vector<Animation *> mobAnimations;

    bool playerTurn;
    bool enemyTurn;

    string profilePath;

    bool isAction = false;
    float actionTimer = 0.0f;
    float actionDuration = 0.5;

    float endTimer = 0.0f;
    float endDuration = 0.5;

    int selectedEnemyPos;

    PopUp popUp;
    vector<string> log;
    map<string, Button> ItemSlot;

    vector<string> info;

    Item *currentItem;

    Skill *currenSkill;

    bool getPrize;

    Sound atkSound;

    bool end = false;

    Texture2D bg;

public:
    DungeonScreen(GameState &GameState);
    virtual ~DungeonScreen();

    void setToggle(string name);
    bool isToggle();
    void Draw();
};

#endif
