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
}