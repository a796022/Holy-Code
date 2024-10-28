namespace MTG
{
    public class Set
    {
        private string code;
        private string name;

        public Set(string code, string name)
        {
            this.code = code;
            this.name = name;
        }

        public string GetId()
        {
            return code;
        }

        public string GetName()
        {
            return name;
        }
    }
}