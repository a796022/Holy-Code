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
        }
    }
}