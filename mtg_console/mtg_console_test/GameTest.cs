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

        // Create a normal deck of 61 cards
        string deckList = @"
            //Main
            1 Eiganjo Castle
            1 Eiganjo, Seat of the Empire
            4 Ghost Quarter
            4 Hallowed Fountain
            1 Island
            5 Plains
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
    }

    [Fact]
    public void TestNotFoundCard()
    {
        // Create the game
        Game game = new Game(2, Format.CONSTRUCTED);

        // Create a normal deck of 60 cards with a card that doesn't exist
        string deckList = @"
            //Main
            1 Eiganjo Castle
            1 Eiganjo, Seat of the Empire
            4 Ghost Quarter
            4 Hallowed Fountain
            1 <*_*>
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
        Assert.Equal(StatusCode.CARD_NOT_FOUND, status.GetStatusCode());

        List<string> correctAnswer = new List<string> { "<*_*>" };
        Assert.Equal(correctAnswer, status.GetInfo());
    }

    [Fact]
    public void TestNotFoundCardSideboard()
    {
        // Create the game
        Game game = new Game(2, Format.CONSTRUCTED);

        // Create a normal deck of 60 cards with a card that doesn't exist in the sideboard
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
            1 <*_*>
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
        Assert.Equal(StatusCode.CARD_NOT_FOUND, status.GetStatusCode());

        List<string> correctAnswer = new List<string> { "<*_*>" };
        Assert.Equal(correctAnswer, status.GetInfo());
    }
    
    [Fact]
    public void TestLess60CardsMainDeck()
    {
        // Create the game
        Game game = new Game(2, Format.CONSTRUCTED);

        // Create a deck of 59 cards
        string deckList = @"
            //Main
            1 Eiganjo Castle
            1 Eiganjo, Seat of the Empire
            4 Ghost Quarter
            4 Hallowed Fountain
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

        // Set the deck and check the restrictions
        game.SetPlayerDeck(0, deckList);
        Status status = game.CheckDeckRestrictions(0);

        // Check
        Assert.Equal(StatusCode.LESS_THAN_60_CARDS, status.GetStatusCode());
    }

    [Fact]
    public void TestMoreThan4CopiesMainDeck()
    {
        // Create the game
        Game game = new Game(2, Format.CONSTRUCTED);

        // Create a deck with 5 copies of a card (Ghost Quarter)
        string deckList = @"
            //Main
            1 Eiganjo Castle
            1 Eiganjo, Seat of the Empire
            5 Ghost Quarter
            4 Hallowed Fountain
            1 Island
            3 Plains
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

        // Set the deck and check the restrictions
        game.SetPlayerDeck(0, deckList);
        Status status = game.CheckDeckRestrictions(0);

        // Check
        Assert.Equal(StatusCode.MORE_THAN_4_COPIES, status.GetStatusCode());

        List<string> correctAnswer = new List<string> { "Ghost Quarter" };
        Assert.Equal(correctAnswer, status.GetInfo());
    }

    [Fact]
    public void TestMoreThan4CopiesMainDeckPlusSideboard()
    {
        // Create the game
        Game game = new Game(2, Format.CONSTRUCTED);

        // Create a deck with 5 copies of a card between the main deck and sideboard (Ghost Quarter)
        string deckList = @"
            //Main
            1 Eiganjo Castle
            1 Eiganjo, Seat of the Empire
            4 Ghost Quarter
            4 Hallowed Fountain
            2 Island
            3 Plains
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
            1 Ghost Quarter
            2 Lavinia, Azorius Renegade
            4 Sanctifier en-Vec
            3 Suncleanser
            2 Aven Interrupter
            2 The Battle of Bywater
            1 Linvala, Keeper of Silence
        ";

        // Set the deck and check the restrictions
        game.SetPlayerDeck(0, deckList);
        Status status = game.CheckDeckRestrictions(0);

        // Check
        Assert.Equal(StatusCode.MORE_THAN_4_COPIES, status.GetStatusCode());

        List<string> correctAnswer = new List<string> { "Ghost Quarter" };
        Assert.Equal(correctAnswer, status.GetInfo());
    }
}