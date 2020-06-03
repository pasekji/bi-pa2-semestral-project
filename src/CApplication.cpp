#include "CApplication.h"

void CApplication::initApplication()
{
    setlocale(LC_ALL, "");

    // ncurses start and setting
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // get screen size
    getmaxyx(stdscr, m_yMax, m_xMax);

    return;
}

void CApplication::run()
{
    initApplication();
    initMainMenu();

    return;
}

void CApplication::endApplication()
{
    curs_set(0);
    refresh();
    endwin();

    return;    
}

CGame & CApplication::getGame()
{
    return m_game;
}

const CGame & CApplication::getGame() const
{
    return m_game;
}

CMainMenu & CApplication::getMainMenu()
{
    return m_mainMenu;
}

const CMainMenu & CApplication::getMainMenu() const
{
    return m_mainMenu;
}

void CApplication::initMainMenu()
{
    if(!m_mainMenu.is_init)
        m_mainMenu.initMenu();
    else
        m_mainMenu.loadMenu();
    

    while(m_mainMenu.getAction() == 0);

    clear();

    switch(m_mainMenu.getSelected())
    {
        case 0:
            m_game.run(); 
            initMainMenu();          
            break;
        case 1:
            m_game.run();
            initMainMenu();
            break;
        case 2:
            endApplication();
        default:
            break;
    }

    return;
}
