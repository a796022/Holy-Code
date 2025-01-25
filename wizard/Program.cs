using Gtk;
using wizard;

class Program
{
    static void Main(string[] args)
    {
        Application.Init();
        
        // Show the main window
        GUI gui = new GUI();

        // Init the GTK main loop
        Application.Run();
    }
}
