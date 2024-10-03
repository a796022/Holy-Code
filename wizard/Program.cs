using Gtk;
using GUI;

class Program
{
    static void Main(string[] args)
    {
        Application.Init();
        
        // Show the main window
        GUI.GUI gui = new GUI.GUI();

        // Init the GTK main loop
        Application.Run();
    }
}
