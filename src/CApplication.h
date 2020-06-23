#ifndef APPLICATION_H
#define APPLICATION_H

#include "CMenu.h"
#include "CGame.h"

class CApplication
{
    public:
        CApplication()
        {
            m_mainMenu->setOptions({"New Game", "Continue", "Save Game", "Load Game", "Quit"});
            m_playerSelect->setOptions({"paladin", "mage", "rogue", "BACK"});
            m_mapSelect->setOptions({"default world", "BACK"});
        }
        ~CApplication() = default;

        bool saveGame();
        bool loadGame();
        void loadMenu();
        void newGame();
        void endApplication();
        void run();

        const CGame* getGame() const;
        CGame* getGame();

        bool is_new;
        bool is_loaded;

        friend class CGame;

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


};

#endif