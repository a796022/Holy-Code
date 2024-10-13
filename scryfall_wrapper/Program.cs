using ScryfallWrapper;

class Program
{
    static async Task Main(string[] args)
    {
        ScryfallWrapper.ScryfallWrapper scrw = new ScryfallWrapper.ScryfallWrapper();
        await scrw.GetAllCardsJson();
    }
}