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
#include "CBuilder.h"
#include <fstream>
#include <set>

using namespace std;

class CMap
{
    public:
        CMap() = default;
        ~CMap()
        {
            delete m_player;
            std::set<CGameObject*> mnozina;
            for(auto i = ++m_moveableObjects.begin(); i != m_moveableObjects.end(); ++i)
            {
                mnozina.insert(*i);
                //delete *i;
            }

            for(auto i = ++m_targets.begin(); i != m_targets.end(); ++i)
            {
                mnozina.insert(*i);
                //delete *i;
            }

            for(auto i : m_imoveableObjects)
                mnozina.insert(i);

            for (auto i : mnozina)
                delete i;

        }
        void loadMap();                                 // load all objects in map and render
        void demo_loadMap();                            // demo loadMap() for testing only
        void demo_loadMapOriginal();
        void demo_loadMapLoading();
        void demo_loadMapSave();
        bool loadMapFromFile(const std::string & pathToFile);
        bool collisionDetect(std::pair<int, int> & pair);
        void staticCamera(direction & dir, int & steps);
        int m_width, m_height;

        CPlayer* getPlayer() const;

        CGameObject* getTargetObject(std::pair<int, int> & pair) const;

        void catchPlayer();
        void save(ofstream& os);
        void loadWithPlayer(ifstream& is);
        void loadWOPlayer(ifstream& is);
        CLoot* spawnLoot(int posY, int posX);
        
        void saveWithPlayer(ofstream& os);

        void buildMap();

        player_class m_selectedClass;
        friend class CBuilder;

    private:
        CPlayer* m_player;
        std::vector<CCharacter*> m_moveableObjects;
        std::vector<CGameObject*> m_imoveableObjects;
        std::vector<CGameObject*> m_targets;
        void catchBuilder();
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