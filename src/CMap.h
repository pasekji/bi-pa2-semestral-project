#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "CGameObject.h"
#include "CCharacter.h"
#include "CPlayer.h"
#include "CPlayerPaladin.h"
#include "CPlayerRogue.h"
#include "CPlayerMage.h"
#include "CEnemy.h"
#include "CProp.h"
#include <fstream>

using namespace std;

class CMap
{
    public:
        CMap() = default;
        ~CMap() = default;    
        void loadMap();                                 // load all objects in map and render
        void demo_loadMap();                            // demo loadMap() for testing only
        void demo_loadMapOriginal();
        void demo_loadMapLoading();
        void demo_loadMapSave();
        bool loadMapFromFile(const std::string & pathToFile);
        bool collisionDetect(std::pair<int, int> & pair);
        void staticCamera(direction & dir, int & steps);
        int m_width, m_height;

        std::shared_ptr<CPlayer> getPlayer() const;

        std::shared_ptr<CGameObject> getTargetObject(std::pair<int, int> & pair) const;

        void catchPlayer();
        void save(ofstream& os);
        void loadWithPlayer(ifstream& is);
        void loadWOPlayer(ifstream& is);
        std::shared_ptr<CLoot> spawnLoot(int posY, int posX);
        
        void saveWithPlayer(ofstream& os);

        player_class m_selectedClass;
        friend class CPlayerPaladin;

    private:
        std::shared_ptr<CPlayer> m_player;
        std::vector<std::shared_ptr<CCharacter>> m_moveableObjects;
        std::vector<std::shared_ptr<CGameObject>> m_imoveableObjects;
        std::vector<std::shared_ptr<CGameObject>> m_targets;
        void spawnPlayer(int posY, int posX, player_class playerClass);           // (int posY, int posX)
        void spawnEnemy(int posY, int posX, enemy_type type);
        void spawnProp(int posY, int posX, prop_type type);
        void renderObjects();                           // only new render of objects
        void moveableDoAction();                        // invoke action to change properties of instance. posX++ (once)
        void camera_objectsUp(int & steps);
        void camera_objectsDown(int & steps);
        void camera_objectsLeft(int & steps);
        void camera_objectsRight(int & steps);
    
};

#endif