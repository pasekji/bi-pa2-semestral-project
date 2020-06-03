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
        void loadMenu();
            
    private:
        const std::vector<std::string> m_logo =     
        {
            " _   _ _____   _   _   ___  ___  ___ _____  ____________ _____",
            "| \\ | |  _  | | \\ | | / _ \\ |  \\/  ||  ___| | ___ \\ ___ \\  __ \\",
            "|  \\| | | | | |  \\| |/ /_\\ \\| .  . || |__   | |_/ / |_/ / |  \\/",
            "| . ` | | | | | . ` ||  _  || |\\/| ||  __|  |    /|  __/| | __ ",
            "| |\\  \\ \\_/ / | |\\  || | | || |  | || |___  | |\\ \\| |   | |_\\ \\",
            "\\_| \\_/\\___/  \\_| \\_/\\_| |_/\\_|  |_/\\____/  \\_| \\_\\_|    \\____/"
        };
        
        WINDOW* m_logoWindow;
        
};