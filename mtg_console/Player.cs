namespace MTG
{
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
}