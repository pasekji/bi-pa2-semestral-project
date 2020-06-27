#include "CApplication.h"

CApplication::CApplication()
{
    m_mainMenu->setOptions({"New Game", "Continue", "Save Game", "Load Game", "Quit"});
    m_playerSelect->setOptions({"paladin", "mage", "rogue", "BACK"});
    m_mapSelect->setOptions({"default world", "map builder", "BACK"});
}

void CApplication::initApplication()
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

const CGame* CApplication::getGame() const
{
    return m_game;
}

CGame* CApplication::getGame()
{
    return m_game;
}

void CApplication::initMainMenu()
{
    if(!m_mainMenu->is_init)
        m_mainMenu->initMenu();
    else
        m_mainMenu->loadMenu();
    

    while(m_mainMenu->getAction() == 0);

    clear();
    
    switch(m_mainMenu->getSelected())
    {
        case 0:
            initPlayerSelect();          
            break;
        case 1:
            if(m_game->is_init)
                m_game->run();
            initMainMenu();
            break;
        case 2:                                                  // save game 
            if(m_game->is_init)
                m_game->getMap()->demo_loadMapSave();
            initMainMenu();
            break;
        case 3:                                                 // load game
            initLoadGames();
            initMainMenu();
            break;
        case 4:
            endApplication();
        default:
            break;
    }

    return;
}


void CApplication::initPlayerSelect()
{
    if(!m_playerSelect->is_init)
        m_playerSelect->initMenu();
    else
        m_playerSelect->loadMenu();
    

    while(m_playerSelect->getAction() == 0);

    clear();
    
    switch(m_playerSelect->getSelected())
    {
        case 0:
            m_game->getMap()->m_selectedClass = PALADIN; 
            initMapSelect();          
            break;
        case 1:
            m_game->getMap()->m_selectedClass = MAGE;
            initMapSelect();
            break;
        case 2:
            m_game->getMap()->m_selectedClass = ROGUE;
            initMapSelect();
            break;
        case 3:
            initMainMenu();
            break;

        default:
            break;
    }

    return;
}


void CApplication::initMapSelect()
{
    if(!m_mapSelect->is_init)
        m_mapSelect->initMenu();
    else
        m_mapSelect->loadMenu();
    

    while(m_mapSelect->getAction() == 0);

    clear();
    
    switch(m_mapSelect->getSelected())
    {
        case 0:
            m_game->run();
            initMainMenu();          
            break;

        case 1:
            m_game->m_build = true;
            m_game->run();
            initMainMenu();
            break;
            
        case 2:
            initPlayerSelect();
            break;

        default:
            break;
    }

    return;
}

void CApplication::initLoadGames()
{
    if(!m_loadGames->is_init)
    {
        m_loadGames->setOptions(loadOptions("saves-list.txt"));
        m_loadGames->initMenu();
    }
    else
    {
        m_loadGames->loadMenu();
    }

    while(m_loadGames->getAction() == 0);

    clear();

    return;
}

std::vector<std::string> CApplication::loadOptions(const std::string & filename) const
{    
    ifstream is;
    is.open(filename);
    size_t optionsSize;
    is >> optionsSize;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::vector<std::string> options;
    for (unsigned i = 0; i < optionsSize; i++)
    {
        std::string option;
        std::getline(is, option);
        options.push_back(option);
    }
    
    options.push_back("BACK");
    is.close();

    return options;
}
