#ifndef APPLICATION_H
#define APPLICATION_H

#include "CMainMenu.h"
#include "CGame.h"

class CApplication
{
    public:
        CApplication() = default;
        ~CApplication() = default;

        bool saveGame();
        bool loadGame();
        void loadMenu();
        void newGame();
        void endApplication();
        void run();

        const CGame & getGame() const;

        const CMainMenu & getMainMenu() const;

        bool is_new;
        bool is_loaded;

        friend class CGame;

    private:
        int m_yMax, m_xMax;
        CMainMenu m_mainMenu;
        CNewGameMenu m_newMenu;
        CLoadGameMenu m_loadMenu;
        CGame m_game;
        void initMainMenu();
        void initApplication();


};

#endif