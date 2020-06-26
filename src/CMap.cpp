#include "CMap.h"
#include "CApplication.h"
#include <ctype.h>
#include <iostream>
#include <ctime>

extern CApplication application;

void CMap::loadMap()            
{
    // no predef ROOM_HEIGHT othr. will be used 
    spawnPlayer(((int)(application.getGame()->getYMax() * 0.99) - 2) / 2, ((int)(application.getGame()->getXMax() * 0.633) - 2) / 2, m_selectedClass);
    return;
}

bool CMap::collisionDetect(std::pair<int, int> & pair)
{
    for (auto i: m_moveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    return false;
}

void CMap::demo_loadMapOriginal()
{
// no predef ROOM_HEIGHT or othr. will be used 
    spawnEnemy(((ROOM_HEIGHT - (ROOM_HEIGHT/5))/2), (ROOM_WIDTH - 2) / 2, BASILISK);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20)), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 1), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 2), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 5), STONE);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 7), TREE);
    spawnProp((ROOM_HEIGHT/2 + 2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 5), BUSH);
    spawnEnemy(((ROOM_HEIGHT - (ROOM_HEIGHT/7))/2), (ROOM_WIDTH - 2) / 2, NOONWRAITH);
    spawnEnemy(((ROOM_HEIGHT - (ROOM_HEIGHT/7))/2), (ROOM_WIDTH - 5) / 2, UNDEAD);

    return;
}

void CMap::demo_loadMapLoading()
{
    ifstream is;
    is.open("saveGame.txt");
    loadWithPlayer(is);
    catchPlayer();
}

void CMap::demo_loadMapSave()
{
    ofstream os;

    time_t t = time(0);
    struct tm * now = localtime( & t );

     char newFileName[50];

     strftime(newFileName, 50,"%c.txt",now);

     string text = newFileName;
     std::ofstream saveList;
     saveList.open("saves-list.txt");

     if(saveList.is_open())
     {
         saveList << text << std::endl;
     }

     saveList.close();

    os.open("saveGame.txt");
    saveWithPlayer(os);
    
    return;
}

void CMap::demo_loadMap()
{   
    
    return;
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

    return;
}

void CMap::moveableDoAction()
{
    for(auto i = ++m_moveableObjects.begin(); i != m_moveableObjects.end(); ++i)
    {
        (*i)->getAction();
    }

    return;
}

void CMap::spawnPlayer(int posY, int posX, player_class playerClass)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");

    switch (playerClass)
    {
        case PALADIN:
            m_player = (new CPlayerPaladin(posY, posX))->getPtr();
            break;
        case MAGE:
            m_player = (new CPlayerMage(posY, posX))->getPtr();
            break;
        case ROGUE:
            m_player = (new CPlayerRogue(posY, posX))->getPtr();
            break;
        case BUILDER:
            m_player = (new CBuilder(posY, posX))->getPtr();
        default:
            break;
    }
        
    m_moveableObjects.push_back(m_player);
    m_targets.push_back(m_player);

    if(playerClass == BUILDER)
        return;

    demo_loadMapOriginal();
    
    wrefresh(application.getGame()->getWindow());
    
    catchPlayer();

    return;
}

CPlayer* CMap::getPlayer() const            // not needed
{
    return m_player;
}

CGameObject* CMap::getTargetObject(std::pair<int, int> & pair) const
{
    for(auto i : m_targets)
    {
        if(i->getPos() == pair)
        {
            i->showStats();
            return i;
        }
    } 
    
    return nullptr;
}

void CMap::catchPlayer()
{
    if(m_selectedClass == BUILDER)
    {
        catchBuilder();
        return;
    }

    while (toupper(m_player->getAction()) != 'X')    
    {
        m_player->showStats();
        moveableDoAction();
        renderObjects();
        wrefresh(application.getGame()->getWindow());
        wrefresh(application.getGame()->getPlayerWindow());

    }   
    
    clear();
    refresh();

    return;
}

void CMap::catchBuilder()
{
    while (toupper(m_player->getAction()) != 'X')    
    {
        m_player->showStats();
        renderObjects();
        wrefresh(application.getGame()->getWindow());
        wrefresh(application.getGame()->getPlayerWindow());
    }   
    
    clear();
    refresh();

    return;    
}

void CMap::spawnEnemy(int posY, int posX, enemy_type type)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");
    
    CEnemy* enemy;
    enemy = (new CEnemy(posY, posX, type))->getPtr();
    m_moveableObjects.push_back(enemy);
    m_targets.push_back(enemy);

    return;
}

void CMap::spawnProp(int posY, int posX, prop_type type)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");

    CProp* prop;
    prop.reset(new CProp(posY, posX, type));
    m_imoveableObjects.push_back(prop);

    return;
}

CLoot* CMap::spawnLoot(int posY, int posX)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
        throw std::invalid_argument("received overlapping coordinates with other object");

    CLoot* loot;
    loot = (new CLoot(posY, posX))->getPtr();    
    m_imoveableObjects.push_back(loot);
    m_targets.push_back(loot);

    return loot;
}

void CMap::staticCamera(direction & dir, int & steps)
{
    switch (dir)
    {
        case UP:
            camera_objectsDown(steps);
            renderObjects();
            break;
    
        case DOWN:
            camera_objectsUp(steps);
            renderObjects();
            break;
        
        case LEFT:
            camera_objectsRight(steps);
            renderObjects();
            break;

        case RIGHT:
            camera_objectsLeft(steps);
            renderObjects();
            break;
        
        default:
            break;
    }

    return;
}

void CMap::camera_objectsDown(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveDown(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveDown(steps);
    }

    return;
}

void CMap::camera_objectsUp(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveUp(steps);    
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveUp(steps);
    }

    return;
}

void CMap::camera_objectsRight(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveRight(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveRight(steps);
    }

    return;
}

void CMap::camera_objectsLeft(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveLeft(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveLeft(steps);
    }

    return;  
}

void CMap::saveWithPlayer(ofstream& os)
{
    m_player->save(os);
    save(os);
}

void CMap::save(ofstream& os)
{
    os << m_moveableObjects.size()-1 << endl;
    for (unsigned i = 1; i < m_moveableObjects.size(); i++)
    {
        m_moveableObjects[i]->save(os);
    }
    os << m_imoveableObjects.size() << endl;
    for (unsigned i = 0; i < m_imoveableObjects.size(); i++)
    {
        m_imoveableObjects[i]->save(os);
    }
    os << m_targets.size()-1 << endl;
    for (unsigned i = 1; i < m_targets.size(); i++)
    {
        m_targets[i]->save(os);
    }
}

void CMap::loadWithPlayer(ifstream& is)
{
    m_player = std::dynamic_pointer_cast<CPlayer>(loadCharacter(is));
    m_moveableObjects.push_back(m_player);
    m_targets.push_back(m_player);
    loadWOPlayer(is);

    catchPlayer();
}

void CMap::loadWOPlayer(ifstream& is)
{
    size_t moveableObjectsSize;
    is >> moveableObjectsSize;
    for (unsigned i = 0; i < moveableObjectsSize; i++)
    {
        shared_ptr<CCharacter> obj = loadCharacter(is);
        if (obj != nullptr)
            m_moveableObjects.push_back(obj);
    }
    size_t imoveableObjectsSize;
    is >> imoveableObjectsSize;
    for (unsigned i = 0; i < imoveableObjectsSize; i++)
    {
        shared_ptr<CGameObject> obj = loadGameObject(is);
        if (obj != nullptr)
            m_imoveableObjects.push_back(obj);
    }
    size_t targetsSize;
    is >> targetsSize;
    for (unsigned i = 0; i < targetsSize; i++)
    {
        shared_ptr<CGameObject> obj = loadGameObject(is);
        if (obj != nullptr)
            m_targets.push_back(obj);
    }
}

void CMap::buildMap()
{
    m_selectedClass = BUILDER;
    spawnPlayer(((int)(application.getGame()->getYMax() * 0.99) - 2) / 2, ((int)(application.getGame()->getXMax() * 0.633) - 2) / 2, m_selectedClass);
    catchBuilder();

    return;
}