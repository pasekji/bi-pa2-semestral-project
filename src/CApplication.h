#include "CMainMenu.h"
#include "CGame.h"

class CApplication
{
    public:
        CApplication() = default;
        ~CApplication() = default;
        //int menuAction();
        bool saveGame();
        bool loadGame();
        void loadMenu();
        void newGame();
        void endApplication();
        void run();

        CGame & getGame();
        const CGame & getGame() const;

        CMainMenu & getMainMenu();
        const CMainMenu & getMainMenu() const;

        //WINDOW* m_menuWindow;
        int m_yMax, m_xMax;

        bool is_new;
        bool is_loaded;

        friend class CGame;

    private:
        CMainMenu m_mainMenu;
        CNewGameMenu m_newMenu;
        CLoadGameMenu m_loadMenu;
        CGame m_game;
        void initMainMenu();
        //void renderMenu();
        void initApplication();


};