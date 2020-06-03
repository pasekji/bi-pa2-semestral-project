#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <locale.h>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <stack>
#include <list>

#define ROOM_HEIGHT 50 
#define ROOM_WIDTH 100

enum body_part {HEAD, TORSO, ARMS, LEGS, HANDS, FEET};
enum item_type {WEAPON, ARMOR, CONSUMABLE, MISC};
enum player_class {PALADIN, MAGE, ROGUE};
enum enemy_type {UNDEAD, GHOUL, HELLHOUND, DRYAD, BASILISK, SIREN};    // UNDEAD - F ,BASILISK - ~ , GHOUL - G, HELLHOUND - E, DRYAD - Y, SIREN - %
enum attack_type {SLAIN, KICK, SPELL, BITE};                           // todo 
enum event_type {ATTACK, TALK, ITEM_PICKUP, ITEM_DISCARD, EQUIP, DEQUIP, GOTO};

char WALL = '#';
char VOID = '+';

using namespace std;

class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX)
        {
            getmaxyx(m_objectSpace, m_posY_Max, m_posX_Max);
        }
        CGameObject(WINDOW * objectSpace, int posY, int posX, char & objectForm) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX), m_objectForm(objectForm)
        {
            getmaxyx(m_objectSpace, m_posY_Max, m_posX_Max);
        }
        virtual ~CGameObject()
        {}
        virtual int getAction()
        {
            return 0;
        }
        virtual bool interactWith()
        {
            return false;
        }
        void objectRender();
        WINDOW * m_objectSpace;
        int m_posY, m_posX, m_posX_Max, m_posY_Max;
        char m_objectForm;
    
};

class CCharacter : public CGameObject
{
    protected:    
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        CCharacter(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {}
        ~CCharacter(){}

        int m_speed;
        int m_health;
        int m_energy;
        float m_chanceOfBlock;
};

class CDoor;

class CMap
{
    public:
        CMap() = default;
        ~CMap();    
        void loadMap();                                 // load all objects in map and render
        void demo_loadMap();                            // demo loadMap() for testing only
        bool loadMapFromFile(const string & pathToFile);
        bool openDoor(CDoor*);
        bool goToMap(CMap*);
        bool colisionDetect(int & p_posY, int & p_posX);
        int m_width, m_height;
        int m_yMax, m_xMax;
        WINDOW* m_mapWindow;

    private:
        string m_pathToFile;
        string m_locationName;
        CDoor* m_upperLayer;
        vector<CCharacter*> m_moveableObjects;
        vector<CGameObject*> m_imoveableObjects;
        map<pair<int, int>, CGameObject*> m_targets;
        map<CDoor, CMap*> m_layers;                     // current layer must be included too
        void spawnPlayer(int posY, int posX, player_class playerClass);           // (int posY, int posX)
        void spawnEnemy(int posY, int posX, enemy_type type);
        void spawnProp(int posY, int posX, char & objectForm);
        void renderObjects();                           // only new render of objects
        void moveableDoAction();                        // invoke action to change properties of instance. posX++ (once)
    
};

void CMap::loadMap()            
{
    spawnPlayer((ROOM_HEIGHT - 2) / 2, (ROOM_WIDTH - 2) / 2, PALADIN);
}

class CEvent;
class CGame
{
    public:
        CGame() = default;
        ~CGame() = default;
        int m_yMax, m_xMax;
        list<CEvent*> event_list;
        WINDOW* m_Window;
        CMap* m_currentMap = new CMap;
        void run();
        void endGame();
        bool saveGame();
        bool loadGame();

    private:
        void initGame();
        void renderSpace();
        void initMap();

};

class CProp : public CGameObject
{
    public:
        CProp(WINDOW* objectSpace, int posY, int posX, char & objectForm) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = objectForm;
        }
        ~CProp()
        {}

};

class CDoor : public CGameObject
{
    public:
        CDoor(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = 'D';
        }
        ~CDoor()
        {}

};

CGame game;

bool CMap::colisionDetect(int & p_posY, int & p_posX)
{
    for (auto i: m_moveableObjects)
    {
        if(make_pair(i->m_posY, i->m_posX) == make_pair(p_posY, p_posX))
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(make_pair(i->m_posY, i->m_posX) == make_pair(p_posY, p_posX))
            return true;
    }

    return false;
}

void CMap::demo_loadMap()
{
    spawnEnemy(20, (ROOM_WIDTH - 2) / 2, BASILISK);
    spawnProp(25, 95, WALL);
    spawnProp(25, 94, WALL);
    spawnProp(25, 93, WALL);

}

void CMap::renderObjects()
{
    for(auto i: m_moveableObjects)
    {
        i->objectRender();
    }

    for(auto i: m_imoveableObjects)
    {
        i->objectRender();
    }
}

void CMap::moveableDoAction()
{
    for(auto i: m_moveableObjects)      // do action except first position -> player position <- no need 
    {
        i->getAction();
    }
}

class CItem
{
    protected:
        item_type m_type;
        string m_name;
        string m_lable;
        size_t m_price;
        size_t m_useability;            // count of possible uses

        virtual bool itemApply() = 0;

        CItem(item_type type, const string & name, const string & lable, size_t price, size_t useability) : m_type(type), m_name(name), m_lable(lable), m_price(price), m_useability(useability)
        {}
        virtual ~CItem()
        {}

};

class CWeapon : public CItem
{
    public:
        CWeapon(const string & name, const string & lable, size_t price, size_t useability, int damage, int chance_of_hit, player_class compatible) : CItem(WEAPON, name, lable, price, useability)
        {
            m_damage = damage;
            m_chance_of_hit = chance_of_hit;
            m_compatible = compatible;
        }
        ~CWeapon()
        {}
        bool itemApply();

    private:
        player_class m_compatible;
        int m_damage;
        float m_chance_of_hit;
};

class CArmor : public CItem
{
    public:
        CArmor(const string & name, const string & lable, size_t price, size_t useability, int armor, int chance_of_block, body_part body) : CItem(ARMOR, name, lable, price, useability)
        {
            m_armor = armor;
            m_chance_of_block = chance_of_block;
            m_body = body;
        }
        ~CArmor()
        {}
        bool itemApply();

    private:
        body_part m_body;
        int m_armor;
        float m_chance_of_block;
};

class CConsumable : public CItem        // could be stackable
{
    public:
        CConsumable(const string & name, const string & lable, const string & id, size_t price, size_t useability, int healthSource, int energySource, int sideEffect) : CItem(CONSUMABLE, name, lable, price, useability)
        {
            m_healthSource = healthSource;
            m_energySource = energySource;
            m_sideEffect = sideEffect;
            m_id = id;
        }
        ~CConsumable()
        {}
        bool itemApply();
        string m_id;

    private:
        int m_healthSource;
        int m_energySource;
        int m_sideEffect;           // item could be toxic -> negative values

};

class CMisc : public CItem          // could be stackable
{
    public:
        CMisc(const string & name, const string & lable, const string & id, size_t price) : CItem(MISC, name, lable, price, 0)
        {
            m_id = id;
        }
        ~CMisc()
        {}
        bool itemApply()            // these items can't be applied f.e. - bone 
        {
            return false;
        }
        string m_id;

};

class CInventory            // map of stacks
{
    public:
        CInventory(size_t size) : m_size(size)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                m_keys.push_back(i);
                m_contents[i];
            }

            m_it = m_keys.begin();
        }

        void incrementItr();
        void decrementItr();
        void useItem();
        void dumpItem();
        void pickUpItem();
        void loadItemsAfterSave();
        void saveItems();
        void getSize();

    private:
        size_t m_size;
        vector<size_t> m_keys;
        vector<size_t>::iterator m_it;
        map<size_t, pair<string, stack<CItem*>>> m_contents;

};

class CChest : public CGameObject
{
    public:
        CChest(WINDOW* objectSpace, int posY, int posX, size_t size) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = 'H';
            m_size = size;
            for (size_t i = 0; i < m_size; ++i)
            {
                m_keys.push_back(i);
                m_contents[i];
            }

            m_it = m_keys.begin();
        }
        vector<size_t>::iterator m_it;
        bool is_empty();
        bool is_full();
        void loadContents();
        void popItem();
        void pushItem(CItem * item);

    private:
        size_t m_size;
        vector<size_t> m_keys;
        map<size_t, CItem*> m_contents;
};

class CPlayer : public CCharacter
{
    public:
        player_class m_class;
        CInventory* m_inventory;
        map<body_part, CArmor*> m_armor;
        void changeForm(const char& objectForm);
        
        CPlayer(WINDOW* objectSpace, int posY, int posX, player_class playerClass) : CCharacter(objectSpace, posY, posX)
        {
            m_objectForm = '^';
            m_speed = 1;
            m_class = playerClass;

            switch (playerClass)
            {
                case PALADIN:
                    m_inventorySize = 20;
                    break;
                case MAGE:
                    m_inventorySize = 15;
                    break;
                case ROGUE:
                    m_inventorySize = 10;
                    break;
                default:
                    break;
            }
            m_inventory = new CInventory(m_inventorySize);
            keypad(m_objectSpace, true);
        }

        ~CPlayer()
        {}

    protected:
        size_t m_inventorySize;
        string m_playerName;

};

class CPlayerPaladin : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        CPlayerPaladin(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX, PALADIN)
        {}

        ~CPlayerPaladin()
        {}

    private:
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack();
        bool paladinSpecialAbility();           // knockout the enemy for x rounds ?? 
};

class CPlayerMage : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        CPlayerMage(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX, MAGE)
        {}

        ~CPlayerMage()
        {}

    private:
        int m_mana;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        attack_type m_secondaryAttackType;
        bool magePrimaryAttack();
        bool mageSecondaryAttack();
        bool mageSpecialAbility();
};

class CPlayerRogue : public CPlayer
{
    public:
        int getAction() override;
        bool interactWith() override;
        CPlayerRogue(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX, ROGUE)
        {}

        ~CPlayerRogue()
        {}
    
    private:
        int m_agility;
        float m_chanceOfDoubleHit;
        attack_type m_primaryAttackType;
        bool roguePrimaryAttack();
        void rogueSpecialAbility();     // jump over x spaces in direction of player
};

class CEnemy : public CCharacter
{
    public:
        enemy_type m_type;
        void enemyDead();
        int getAction() override;
        bool interactWith() override;

        // enemy demo testing constructor
        CEnemy(WINDOW* objectSpace, int posY, int posX, enemy_type type) : CCharacter(objectSpace, posY, posX)
        {
            switch (type)
            {
                case BASILISK:
                    m_objectForm = '~';
                    m_type = BASILISK;
                    break;
                case UNDEAD:
                    m_objectForm = 'F';
                    m_type = UNDEAD;
                    break;
                case GHOUL:
                    m_objectForm = 'G';
                    m_type = GHOUL;
                case HELLHOUND:
                    m_objectForm = 'E';
                    m_type = HELLHOUND;
                case DRYAD:
                    m_objectForm = 'Y';
                    m_type = DRYAD;
                case SIREN:
                    m_objectForm = '%';
                    m_type = SIREN;
                default:
                    break;
            }
            m_speed = 1;
        }

        ~CEnemy()
        {}

    private:
        int m_force;
        attack_type m_primaryAttackType;
        CChest * m_loot;                            // will generate loot chest after death
        bool primaryAttack();

};

class CEvent
{
    public:
        CEvent(CGameObject* source, CGameObject* target, event_type type) : m_source(source), m_target(target), m_type(type)
        {}
        virtual ~CEvent();
        virtual void print() const;
        virtual void updateObjects();
        void pushToDisplay() const;
        CGameObject* m_source;
        CGameObject* m_target;
        event_type m_type;
};

class CAttack : public CEvent
{
    public:
        CAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CEvent(source, target, ATTACK)
        {}
        ~CAttack()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        attack_type m_attackType;
        int m_force;
        int m_healthLost;
        bool m_hit;
};

class CTalk : public CEvent
{
    public:
        CTalk(CGameObject* source, CGameObject* target) : CEvent(source, target, TALK)
        {}
        ~CTalk()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        string m_greeting;
        string m_answer;

};

class CPickup : public CEvent
{
    public:
        CPickup(CPlayer* source, CGameObject* target) : CEvent(source, target, ITEM_PICKUP)
        {}
        ~CPickup()
        {}
        void print() const override;
        void updateObjects() override;
    
    private:
        CItem* m_item;
        bool m_success;

};

class CDiscard : public CEvent
{
    public:
        CDiscard(CPlayer* source, CGameObject* target, CItem* item) : CEvent(source, target, ITEM_DISCARD)
        {
            m_item = item;
        }
        CDiscard(CPlayer* source, CItem* item) : CEvent(source, nullptr, ITEM_DISCARD)
        {
            m_item = item;
        }
        ~CDiscard()
        {}
        void print() const override;
        void updateObjects() override;
        
    private:
        CItem* m_item;
        bool m_success;

};

class CEquip : public CEvent
{
    public:
        CEquip(CPlayer* source, CItem* item) : CEvent(source, nullptr, EQUIP)
        {
            m_item = item;
        }
        ~CEquip()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        CItem* m_item;
        bool m_success;
};

class CDequip : public CEvent
{
    public:
        CDequip(CPlayer* source, CItem* item) : CEvent(source, nullptr, DEQUIP)
        {
            m_item = item;
        }
        ~CDequip()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        CItem* m_item;
        bool m_success;
};

class CGoto : public CEvent
{
    public:
        CGoto(CPlayer* source, CDoor* door) : CEvent(source, door, GOTO)
        {}
        ~CGoto()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        CDoor* m_door;
        CMap* m_mapFrom;
        CMap* m_mapTo;
};

int CEnemy::getAction()     // just demo testing
{
    int action = rand() % 5;
    int tmppos;
    switch (action) 
    {
        case 0:
            break;
        case 1:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY - m_speed, m_posX))
                moveUp();
            break;
        case 2:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY + m_speed, m_posX))
                moveDown();
            break;
        case 3:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX - (m_speed + 1)))
                moveLeft();
            break;
        case 4:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX + (m_speed + 1)))
                moveRight();
        default:
            break;
    }

    return action;
}

void CPlayer::changeForm(const char& objectForm)
{
    m_objectForm = objectForm;
}

void CCharacter::moveUp()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY -= m_speed;
    if (m_posY < 1)
    {
        m_posY = 1;
    }
}

void CCharacter::moveDown()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY += m_speed;
    if (m_posY > m_posY_Max - 2)            // because of the border -> border is m_posY_Max - 1, so one spot before the border is m_posY_Max - 2
    {                                   
        m_posY = m_posY_Max - 2;
    }
}

void CCharacter::moveLeft()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX -= (m_speed + 1);
    if (m_posX < 1)
    {
        m_posX = 1;
    }
}

void CCharacter::moveRight()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX += (m_speed + 1);
    if (m_posX > m_posX_Max - 2)
    {
        m_posX = m_posX_Max - 2;
    }
}

int CPlayerPaladin::getAction()
{
    int move = wgetch(m_objectSpace);
    int tmppos;
    switch (move) 
    {
        case KEY_UP:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY - m_speed, m_posX))
                moveUp();
            changeForm('^');
            break;
        case KEY_DOWN:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY + m_speed, m_posX))
                moveDown();
            changeForm('v');
            break;
        case KEY_LEFT:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX - (m_speed + 1)))
                moveLeft();
            changeForm('<');
            break;
        case KEY_RIGHT:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX + (m_speed + 1)))
                moveRight();
            changeForm('>');
            break;
        default:
            break;
    }
    return move;
}

void CGameObject::objectRender()
{ 
    mvwaddch(m_objectSpace, m_posY, m_posX, m_objectForm);
}

bool CPlayerPaladin::interactWith()
{
    //TODO
    return false;
}

bool CEnemy::interactWith()
{
    //TODO
    return false;
}

void CGame::initGame() 
{
    setlocale(LC_ALL, "");

    // ncurses start and setting
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    halfdelay(1);

    // get screen size
    getmaxyx(stdscr, m_yMax, m_xMax);

}

void CGame::run() 
{
    initGame();
    // TODO : render menu etc etc...

    // just for test
    initMap();

}

void CGame::initMap()
{
    // load paramets Y,X if box or not and pass to renderSpace for new WINDOW
    renderSpace();
    m_currentMap->m_mapWindow = m_Window;
    m_currentMap->loadMap();
}

void CGame::renderSpace() 
{
    // create a window for player
    m_Window = newwin(ROOM_HEIGHT, ROOM_WIDTH, (m_yMax - ROOM_HEIGHT) / 2, (m_xMax - ROOM_WIDTH) / 2);
    box(m_Window, 0, 0);
    refresh();
    wrefresh(m_Window);
}

void CMap::spawnPlayer(int posY, int posX, player_class playerClass)
{
    CPlayer* player;
    switch (playerClass)
    {
        case PALADIN:
            player = new CPlayerPaladin(m_mapWindow, posY, posX);
            break;
        case MAGE:
            break;
        case ROGUE:
            break;
        default:
            break;
    }
    m_moveableObjects.push_back(player);
    demo_loadMap();
    wrefresh(m_mapWindow);

    do
    {
        player->objectRender();
        moveableDoAction();
        renderObjects();
        wrefresh(m_mapWindow);
    } while (player->getAction() != 'x');
    
    game.endGame();

}

void CMap::spawnEnemy(int posY, int posX, enemy_type type)
{
    CEnemy* enemy = new CEnemy(m_mapWindow, posY, posX, type);
    m_moveableObjects.push_back(enemy);
}

void CMap::spawnProp(int posY, int posX, char & objectForm)
{
    CProp* prop = new CProp(m_mapWindow, posY, posX, objectForm);
    m_imoveableObjects.push_back(prop);
}

void CGame::endGame()
{
    curs_set(0);
    refresh();
    endwin();
}

int main(int argc, char ** argv)
{
    game.run();

    return 0;
}