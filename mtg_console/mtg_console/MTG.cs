using System;

using GUI;

namespace MTG
{
    public class MTG
    {
        private GUI.GUI gui;
        private User user;
        private string decksListsDir;

        public MTG()
        {
            gui = new GUI.GUI();
            user = new User();

            string homeDir = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
            decksListsDir = Path.Combine(homeDir, ".local", "share", "mtg", "decks");
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
            int numPlayers = GetNumPlayers();

            // Get the game format
            Format format = GetGameFormat();

            // Create the game
            Game game;
            try
            {
                game = new Game(numPlayers, format);
            }
            catch (ArgumentException e)
            {
                gui.StartBigDialog();
                gui.WriteBigDialogLine("An error occurred while creating the game.");
                gui.WriteBigDialogLine(e.Message);
                gui.EndBigDialog();
                return;
            }

            // Choose the deck (for now, the bots will have the same deck as you)
            if (format != Format.LIMITED)
            {
                string? deckFile = GetDeckFile();
                if (deckFile == null)
                {
                    return;
                }
                else
                {
                    string deck = System.IO.File.ReadAllText(deckFile);
                    Status status = new Status(StatusCode.OK);

                    // Set the deck for each player
                    for (int i = 0; i < numPlayers; i++)
                    {
                        status = game.SetPlayerDeck(i, deck);
                    }

                    if (status.GetStatusCode() != StatusCode.OK)
                    {
                        if (status.GetStatusCode() == StatusCode.CARD_NOT_FOUND)
                        {
                            List<string>? notFoundCards = status.GetInfo();

                            gui.StartBigDialog();
                            gui.WriteBigDialogLine("The following cards were not found:");
                            foreach (string card in notFoundCards)
                            {
                                gui.WriteBigDialogLine("  - " + card);
                            }
                            gui.EndBigDialog();
                        }
                    }
                    else
                    {
                        status = game.CheckDeckRestrictions(0);
                        if (status.GetStatusCode() != StatusCode.OK)
                        {
                            if (status.GetStatusCode() == StatusCode.LESS_THAN_60_CARDS)
                            {
                                gui.StartBigDialog();
                                gui.WriteBigDialogLine("The main deck must have at least 60 cards.");
                                gui.EndBigDialog();
                            }

                            if (status.GetStatusCode() == StatusCode.MORE_THAN_4_COPIES)
                            {
                                gui.StartBigDialog();
                                gui.WriteBigDialogLine("The main deck and sideboard can't have more than 4 copies of the same card.");
                                gui.WriteBigDialogLine("There are more than 4 copies of the following cards:");
                                foreach (string card in status.GetInfo())
                                {
                                    gui.WriteBigDialogLine("  - " + card);
                                }
                                gui.EndBigDialog();
                            }
                        }
                    }
                }
            }

            // Start the game
            Status status2 = game.Start();
            if (status2.GetStatusCode() != StatusCode.OK)
            {
                if (status2.GetStatusCode() == StatusCode.DECK_NOT_PREPARED)
                {
                    List<string> notPreparedPlayer = status2.GetInfo();

                    gui.StartBigDialog();
                    gui.WriteBigDialogLine("The following player have not selected their deck:");
                    foreach (string player in notPreparedPlayer)
                    {
                        gui.WriteBigDialogLine("  - " + player);
                    }
                    gui.EndBigDialog();
                }
                else
                {
                    gui.StartBigDialog();
                    gui.WriteBigDialogLine("An error occurred while starting the game.");
                    gui.EndBigDialog();
                }

                return;
            }
        }

        private int GetNumPlayers()
        {
            string numPlayersString = gui.MakeQuestion("game menu", "How many players will play?", false, new string[]{});

            int numPlayers;
            while (!int.TryParse(numPlayersString, out numPlayers) || numPlayers < 2)
            {
                gui.WriteMessage("game menu", "Invalid number of players. Please enter a number greater than 1.");
                numPlayersString = gui.MakeQuestion("game menu", "How many players will play?", false, new string[]{});
            }

            return numPlayers;
        }

        private Format GetGameFormat()
        {
            const string CONSTRUCTED_OPTION = "Constructed";
            const string LIMITED_OPTION = "Limited";
            const string COMMANDER_OPTION = "Commander";

            string[] formatOptions = {
                CONSTRUCTED_OPTION,
                LIMITED_OPTION,
                COMMANDER_OPTION
            };

            string formatString = gui.MakeQuestion("game menu", "Select the game format.", false, formatOptions);

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

            return format;
        }

        private string? GetDeckFile()
        {
            const string REFRESH_DECKS_LIST_OPTION = "(Action): refresh decks list";
            const string CANCEL_OPTION = "(Action): cancel";
            string deck = "";

            do {
                string[] decksList = LoadDecksList();
                string[] deckOptions = new string[decksList.Length + 2];
                deckOptions[0] = REFRESH_DECKS_LIST_OPTION;
                deckOptions[1] = CANCEL_OPTION;
                for (int i = 0; i < decksList.Length; i++)
                {
                    deckOptions[i + 2] = Path.GetFileName(decksList[i]);
                }

                deck = gui.MakeQuestion("game menu", "Select your deck.", false, deckOptions);

                if (deck == CANCEL_OPTION)
                {
                    return null;
                }
            } while (deck == REFRESH_DECKS_LIST_OPTION);

            return Path.Combine(decksListsDir, deck);
        }

        private string[] LoadDecksList()
        {
            // Get the decks list and check it exists (if not, create it)
            if (!Directory.Exists(decksListsDir))
            {
                Directory.CreateDirectory(decksListsDir);
            }

            return Directory.GetFiles(decksListsDir);
        }
    }
}