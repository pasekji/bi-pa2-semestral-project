#ifndef APPLICATION_H
#define APPLICATION_H

#include "CMenu.h"
#include "CGame.h"
#include <memory>

class CApplication
{
    public:
        CApplication();
        ~CApplication() = default;

        bool saveGame();
        bool loadGame();
        void loadMenu();
        void newGame();
        void endApplication();
        void run();

        const std::shared_ptr<CGame> getGame() const;
        std::shared_ptr<CGame> getGame();

        friend class CGame;

    private:
        int m_yMax, m_xMax;
        std::shared_ptr<CMenu> m_mainMenu = std::make_shared<CMenu>();
        std::shared_ptr<CMenu> m_playerSelect = std::make_shared<CMenu>();
        std::shared_ptr<CMenu> m_mapSelect = std::make_shared<CMenu>();
        std::shared_ptr<CMenu> m_loadGames = std::make_shared<CMenu>();
        std::shared_ptr<CGame> m_game = std::make_shared<CGame>();
        void initMainMenu();
        void initPlayerSelect();
        void initMapSelect();
        void initLoadGames();
        void initApplication();


};

#endif