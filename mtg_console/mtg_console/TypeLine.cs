namespace MTG
{
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