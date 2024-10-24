using System;
using System.Text.RegularExpressions;

namespace MTG
{
    public class Game
    {
        private List<Player> players;
        private Format format;

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

        /* 100.2. To play, each player needs their own deck of traditional Magic
        cards, small items to represent any tokens and counters, and some way to
        clearly track life totals. */
        public Status SetPlayerDeck(int playerId, string deckList)
        {
            // Divide the deckList into a list of strings, one for each line
            List<string> deck = new List<string>(deckList.Split('\n'));

            // Trim all the strings
            deck = deck.ConvertAll(d => d.Trim());

            // Remove all the empty lines
            deck.RemoveAll(item => item == "");

            return SetPlayerDeck(playerId, deck);
        }

        /* 100.2. To play, each player needs their own deck of traditional Magic
        cards, small items to represent any tokens and counters, and some way to
        clearly track life totals. */
        public Status SetPlayerDeck(int playerId, List<string> deck)
        {
            List<Card> cards = new List<Card>();
            List<Card> sideboard = new List<Card>();
            List<string> notFoundCards = new List<string>();
            string linePattern = @"^(\d+)(x?)\s+(.*)";
            string tagPattern = @"^(#|//)(.*)";
            string cardAssignment = "main deck";
            Status status = new Status(StatusCode.OK, null);

            foreach (string card in deck)
            {
                int numCopies = 1;
                string cardName = card.Trim();

                // Replace all the multiple spaces with a space
                cardName = Regex.Replace(cardName, @"\s+", " ");

                Match match = Regex.Match(card, linePattern);
                if (match.Success)
                {
                    numCopies = int.Parse(match.Groups[1].Value);
                    cardName = match.Groups[3].Value;
                }
                else
                {
                    match = Regex.Match(card, tagPattern);
                    if (match.Success)
                    {
                        string tagText = match.Groups[2].Value.Trim().ToLower();
                        if (tagText == "sideboard")
                        {
                            cardAssignment = "sideboard";
                        }
                        else if (tagText == "maybeboard")
                        {
                            cardAssignment = "maybeboard";
                        }
                        else if (tagText == "tokens" || tagText == "token")
                        {
                            cardAssignment = "tokens";
                        }
                        else
                        {
                            cardAssignment = "main deck";
                        }

                        continue;
                    }
                }

                if (cardAssignment == "tokens" || cardAssignment == "maybeboard")
                {
                    continue;
                }

                for (int i = 0; i < numCopies; i++)
                {
                    if (CardsDictionary.cards.ContainsKey(cardName))
                    {
                        if (cardAssignment == "main deck")
                        {
                            cards.Add(CardsDictionary.cards[cardName]);
                        }
                        else if (cardAssignment == "sideboard")
                        {
                            sideboard.Add(CardsDictionary.cards[cardName]);
                        }
                    }
                    else
                    {
                        notFoundCards.Add(cardName);
                    }
                }
            }

            SetPlayerMainDeck(playerId, cards);

            if (notFoundCards.Count > 0)
            {
                status = new Status(StatusCode.CARD_NOT_FOUND, notFoundCards);
            }

            return status;
        }

        /* 100.2. To play, each player needs their own deck of traditional Magic
        cards, small items to represent any tokens and counters, and some way to
        clearly track life totals. */
        public void SetPlayerMainDeck(int playerId, List<Card> deck)
        {
            foreach (Player player in players)
            {
                if (player.GetId() == playerId)
                {
                    player.SetMainDeck(deck);
                    break;
                }
            }
        }

        public void SetPlayerSideboard(int playerId, List<Card> sideboard)
        {
            foreach (Player player in players)
            {
                if (player.GetId() == playerId)
                {
                    player.SetSideboard(sideboard);
                    break;
                }
            }
        }

        public Status CheckDeckRestrictions(int playerId)
        {
            Player player = players[playerId];
            List<Card> mainDeck = player.GetMainDeck();
            List<Card> sideboard = player.GetSideboard();
            Status status = new Status(StatusCode.OK, null);

            /* 100.2a In constructed play (a way of playing in which each player
            creates their own deck ahead of time), each deck has a minimum deck
            size of 60 cards. [...] */
            if (format == Format.CONSTRUCTED)
            {
                if (mainDeck.Count < 60)
                {
                    status = new Status(StatusCode.LESS_THAN_60_CARDS, null);
                }
            }

            return status;
        }
    }
}