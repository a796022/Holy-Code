using System;

using GUI;

namespace MTG
{
    public class MTG
    {
        private GUI.GUI gui;
        private User user;

        public MTG()
        {
            gui = new GUI.GUI();
            user = new User();
        }

        public void MainMenuLoop()
        {
            gui.SayWelcome(user.GetName());

            while (true)
            {
                const string QUIT_OPTION = "Quit";

                string[] options = {
                    QUIT_OPTION
                };

                string answer = gui.MakeQuestion("Select an option", false, options);

                switch (answer)
                {
                    case QUIT_OPTION:
                    default:
                        return;
                }
            }
        }
    }
}