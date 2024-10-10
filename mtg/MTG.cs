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
            // Get the number of players and check if it's valid (> 1)
            string numPlayersString = gui.MakeQuestion("game menu", "How many players will play?", false, new string[]{});

            int numPlayers;
            while (!int.TryParse(numPlayersString, out numPlayers) || numPlayers < 2)
            {
                gui.WriteMessage("game menu", "Invalid number of players. Please enter a number greater than 1.");
                numPlayersString = gui.MakeQuestion("game menu", "How many players will play?", false, new string[]{});
            }

            // Get the game format
            const string CONSTRUCTED_OPTION = "Constructed";
            const string LIMITED_OPTION = "Limited";
            const string COMMANDER_OPTION = "Commander";

            string[] options = {
                CONSTRUCTED_OPTION,
                LIMITED_OPTION,
                COMMANDER_OPTION
            };

            string formatString = gui.MakeQuestion("game menu", "Select the game format.", false, options);

            Format format;
            switch (formatString)
            {
                case CONSTRUCTED_OPTION:
                    format = Format.CONSTRUCTED;
                    break;
                case LIMITED_OPTION:
                    format = Format.LIMITED;
                    break;
                case COMMANDER_OPTION:
                default:
                    format = Format.COMMANDER;
                    break;
            }

            // Create the game
            Game game = new Game(numPlayers, format);
        }
    }
}