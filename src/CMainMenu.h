#include "CMenu.h"

class CMainMenu : public CMenu
{
    public:
        CMainMenu();

        ~CMainMenu()
        {}

        unsigned int getAction();

        void renderMenu();
        void initMenu();
    
    private:
        std::vector<std::string> m_logo;
        WINDOW* m_logoWindow;
        
};