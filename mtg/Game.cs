using System;

using GUI;

namespace MTG
{
    public class Game
    {
        List<Player> players;
        Format format;

        public Game(int numPlayers, Format format)
        {
            players = new List<Player>();
            for (int i = 0; i < numPlayers; i++)
            {
                players.Add(new Player(i));
            }

            this.format = format;
        }

        /* 100.1. These Magic rules apply to any Magic game with two or more
        players, including two-player games and multiplayer games. */
        public TypeGameByNumPlayers? GetTypeGameByNumPlayers()
        {
            if (players.Count == 2)
            {
                /* 100.1a A two-player game is a game that begins with only two
                players. */
                return TypeGameByNumPlayers.TWO_PLAYER_GAME;
            }
            else if (players.Count > 2)
            {
                /* 100.1b A multiplayer game is a game that begins with more
                than two players. See section 8, “Multiplayer Rules.” */
                return TypeGameByNumPlayers.MULTIPLAYER_GAME;
            }
            else
            {
                return null;
            }
        }
    }

    public class Player
    {
        private int id;
        
        public Player(int id)
        {
            this.id = id;
        }

        public int GetId()
        {
            return id;
        }
    }
}