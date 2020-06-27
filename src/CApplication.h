#ifndef APPLICATION_H
#define APPLICATION_H

#include "CMenu.h"
#include "CGame.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

class CApplication
{
    public:
        CApplication();
        ~CApplication()
        {
            delete m_mainMenu;
            delete m_playerSelect;
            delete m_mapSelect;
            delete m_loadGames;
            if(m_game->is_init)
                delete m_game;
        }

        bool saveGame();
        bool loadGame();
        void loadMenu();
        void newGame();
        void endApplication();
        void run();

        const CGame* getGame() const;
        CGame* getGame();

        friend class CGame;
        friend class CMap;

    private:
        int m_yMax, m_xMax;
        CMenu* m_mainMenu = new CMenu();
        CMenu* m_playerSelect = new CMenu();
        CMenu* m_mapSelect = new CMenu();
        CMenu* m_loadGames = new CMenu();
        CGame* m_game = new CGame();
        void initMainMenu();
        void initPlayerSelect();
        void initMapSelect();
        void initLoadGames();
        void initApplication();

        std::vector<std::string> loadOptions(const std::string & filename) const;

        std::vector<std::string> m_loadGameOptions;


};

#endif