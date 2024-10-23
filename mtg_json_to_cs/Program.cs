using mtgJsonToCs;

class Program
{
    static void Main(string[] args)
    {
        mtgJsonToCs.mtgJsonToCs mjtc = new mtgJsonToCs.mtgJsonToCs();
        mjtc.convertFullJson();
    }
}