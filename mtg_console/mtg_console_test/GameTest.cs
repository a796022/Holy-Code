using Xunit;

using MTG;

namespace mtg_console_test;

public class GameTest
{
    [Fact]
    public void TestGetTypeGameByNumPlayers()
    {
        Game game = new Game(2, Format.CONSTRUCTED);
        Assert.Equal(TypeGameByNumPlayers.TWO_PLAYER_GAME, game.GetTypeGameByNumPlayers());
    }

    [Fact]
    public void TestStatusDeckConstruction()
    {
        // Create the game
        Game game = new Game(2, Format.CONSTRUCTED);

        // Create a normal deck of 60 cards
        string deckList = @"
            //Main
            1 Eiganjo Castle
            1 Eiganjo, Seat of the Empire
            4 Ghost Quarter
            4 Hallowed Fountain
            1 Island
            4 Plains
            4 Seachrome Coast
            2 Volatile Fault
            4 Aether Vial
            4 Giver of Runes
            4 Path to Exile
            4 Leonin Arbiter
            2 Pippin, Guard of the Citadel
            4 Unsettled Mariner
            4 White Orchid Phantom
            2 Archon of Emeria
            2 Skyclave Apparition
            4 Spell Queller
            2 Teferi, Time Raveler
            3 Tishana's Tidebinder

            //Sideboard
            1 Drannith Magistrate
            2 Lavinia, Azorius Renegade
            4 Sanctifier en-Vec
            3 Suncleanser
            2 Aven Interrupter
            2 The Battle of Bywater
            1 Linvala, Keeper of Silence
        ";

        // Set the deck
        Status status = game.SetPlayerDeck(0, deckList);

        // Check
        Assert.Equal(StatusCode.OK, status.GetStatusCode());
        Assert.Null(status.GetInfo());
    }
}