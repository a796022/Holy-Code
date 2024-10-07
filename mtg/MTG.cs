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
            gui.WriteBigDialog("Welcome to MTG Console, " + user.GetName() + "!");

            while (true)
            {
                const string CREATE_GAME_OPTION = "Create game";
                const string QUIT_OPTION = "Quit";

                string[] options = {
                    CREATE_GAME_OPTION,
                    QUIT_OPTION
                };

                string answer = gui.MakeQuestion("main menu", "Select an option", false, options);

                switch (answer)
                {
                    case CREATE_GAME_OPTION:
                        GameMenuLoop();
                        break;
                    case QUIT_OPTION:
                    default:
                        return;
                }
            }
        }

        private void GameMenuLoop()
        {
            Game game = new Game();

            string numPlayers = gui.MakeQuestion("game menu", "How many players will play?", false, new string[]{});

            // Check if the input is a valid number (greater than 1)
            int numPlayersInt;
            while (!int.TryParse(numPlayers, out numPlayersInt) || numPlayersInt < 2)
            {
                gui.WriteMessage("game menu", "Invalid number of players. Please enter a number greater than 1.");
                numPlayers = gui.MakeQuestion("game menu", "How many players will play?", false, new string[]{});
            }

            // Add the players to the game
            for (int i = 0; i < numPlayersInt; i++)
            {
                game.AddPlayer();
            }
        }
    }
}