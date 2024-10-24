using System.Text.RegularExpressions;

namespace MTG
{
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
}