using System;

using GUI;

namespace MTG
{
    public class Game
    {
        List<Player> players;

        public Game()
        {
            players = new List<Player>();
        }

        public int AddPlayer()
        {
            Player player = new Player(players.Count);
            players.Add(player);
            return player.GetId();
        }

        public typeGameByNumPlayers? GetTypeGameByNumPlayers()
        {
            if (players.Count == 2)
            {
                return typeGameByNumPlayers.TWO_PLAYER_GAME;
            }
            else if (players.Count > 2)
            {
                return typeGameByNumPlayers.MULTIPLAYER_GAME;
            }
            else
            {
                return null;
            }
        }

        public void Start()
        {
            Console.WriteLine("Game started!");
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