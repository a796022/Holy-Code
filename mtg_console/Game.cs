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
        public List<string> SetPlayerDeck(int playerId, string deckList)
        {
            // Divide the deckList into a list of strings, one for each line
            List<string> deck = new List<string>(deckList.Split('\n'));

            // Remove all the empty lines
            deck.RemoveAll(item => item == "");

            return SetPlayerDeck(playerId, deck);
        }

        /* 100.2. To play, each player needs their own deck of traditional Magic
        cards, small items to represent any tokens and counters, and some way to
        clearly track life totals. */
        public List<string> SetPlayerDeck(int playerId, List<string> deck)
        {
            List<Card> cards = new List<Card>();
            List<Card> sideboard = new List<Card>();
            List<string> notFoundCards = new List<string>();
            string linePattern = @"^(\d+)(x?)\s+(.*)";
            string tagPattern = @"^(#|//)(.*)";
            string cardAssignment = "main deck";

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

            return notFoundCards;
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
    }

    public class Player
    {
        private int id;
        private List<Card> mainDeck;
        private List<Card> sideboard;
        
        public Player(int id)
        {
            this.id = id;
            mainDeck = new List<Card>();
            sideboard = new List<Card>();
        }

        public int GetId()
        {
            return id;
        }

        public void SetMainDeck(List<Card> mainDeck)
        {
            this.mainDeck = mainDeck;
        }

        public void SetSideboard(List<Card> sideboard)
        {
            this.sideboard = sideboard;
        }
    }

    public class Card
    {
        /* 100.2a [...] A constructed deck may contain any number of basic land
        cards and no more than four of any card with a particular English name
        other than basic land cards. [...] */
        private string completeName;
        private TypeLine typeLine1;
        private TypeLine? typeLine2;

        public Card(string completeName = "", string typeLine = "")
        {
            this.completeName = completeName;
            
            // Parse the type line
            string doubleCardPattern = @"^(.*) // (.*)$";
            Match match = Regex.Match(typeLine, doubleCardPattern);
            if (match.Success)
            {
                typeLine1 = new TypeLine(match.Groups[1].Value);
                typeLine2 = new TypeLine(match.Groups[2].Value);
            }
            else
            {
                typeLine1 = new TypeLine(typeLine);
                typeLine2 = null;
            }
        }
    }

    public class TypeLine
    {
        private List<Type> types;
        private List<Supertype> supertypes;

        public TypeLine(string typeLine)
        {
            string typeSupertype;
            string? subtype;

            types = new List<Type>();
            supertypes = new List<Supertype>();

            // Divide the typeLine into type/supertype and subtype
            string[] typeLineParts = typeLine.Split(" — ");
            if (typeLineParts.Length == 2)
            {
                typeSupertype = typeLineParts[0];
                subtype = typeLineParts[1];
            }
            else
            {
                typeSupertype = typeLine;
                subtype = null;
            }

            // Get the types and supertypes
            string[] typeSupertypeParts = typeSupertype.Split(" ");
            foreach (string part in typeSupertypeParts)
            {
                if (TypeLineDictionary.types.ContainsKey(part))
                {
                    types.Add(TypeLineDictionary.types[part]);
                }
                else if (TypeLineDictionary.supertypes.ContainsKey(part))
                {
                    supertypes.Add(TypeLineDictionary.supertypes[part]);
                }
            }
        }

        public List<Type> GetTypes()
        {
            return types;
        }

        public List<Supertype> GetSupertypes()
        {
            return supertypes;
        }
    }

    public static class TypeLineDictionary {
        public static readonly Dictionary<string, Type> types = new Dictionary<string, Type>()
        {
            { "Artifact", Type.ARTIFACT },
            { "Battle", Type.BATTLE },
            { "Conspiracy", Type.CONSPIRACY },
            { "Creature", Type.CREATURE },
            { "Dungeon", Type.DUNGEON },
            { "Enchantment", Type.ENCHANTMENT },
            { "Instant", Type.INSTANT },
            { "Kindred", Type.KINDRED },
            { "Land", Type.LAND },
            { "Phenomenon", Type.PHENOMENON },
            { "Plane", Type.PLANE },
            { "Planeswalker", Type.PLANESWALKER },
            { "Scheme", Type.SCHEME },
            { "Sorcery", Type.SORCERY },
            { "Vanguard", Type.VANGUARD }
        };

        public static readonly Dictionary<string, Supertype> supertypes = new Dictionary<string, Supertype>()
        {
            { "Basic", Supertype.BASIC },
            { "Legendary", Supertype.LEGENDARY },
            { "Ongoing", Supertype.ONGOING },
            { "Snow", Supertype.SNOW },
            { "World", Supertype.WORLD }
        };
    }
}