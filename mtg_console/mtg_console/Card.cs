using System.Text.RegularExpressions;

namespace MTG
{
    public class Card
    {
        /* 100.2a [...] A constructed deck may contain any number of basic land
        cards and no more than four of any card with a particular English name
        other than basic land cards. [...] */
        /* 100.2a [...] For the purposes of deck construction, cards with
        interchangeable names have the same English name (see rule 201.3). */
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

        /* 100.2a [...] A constructed deck may contain any number of basic land
        cards and no more than four of any card with a particular English name
        other than basic land cards. [...] */
        /* 100.2a [...] For the purposes of deck construction, cards with
        interchangeable names have the same English name (see rule 201.3). */
        public string GetCompleteName()
        {
            return completeName;
        }

        /* 100.2a [...] A constructed deck may contain any number of basic land
        cards and no more than four of any card with a particular English name
        other than basic land cards. [...] */
        public bool CanHaveMoreThan4Copies()
        {
            bool imBasicLand = typeLine1.GetTypes().Contains(Type.LAND) &&
                typeLine1.GetSupertypes().Contains(Supertype.BASIC);

            return imBasicLand;
        }
    }
}