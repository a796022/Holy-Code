using Gtk;

namespace GUI
{
    public class GUI
    {
        // Default main window properties
        private const string MAIN_WINDOW_DEFAULT_TITLE = "New Tree - Wizard";
        private const int MAIN_WINDOW_DEFAULT_WIDTH = 400;
        private const int MAIN_WINDOW_DEFAULT_HEIGHT = 300;

        public GUI()
        {
            NewWindow();
        }

        public void NewWindow()
        {
            // Create the main window
            Window window = new Window(MAIN_WINDOW_DEFAULT_TITLE);
            window.SetDefaultSize(MAIN_WINDOW_DEFAULT_WIDTH,
                                  MAIN_WINDOW_DEFAULT_HEIGHT);
            
            // Sets the behavior of the window in case of different events
            window.DeleteEvent += (sender, e) => Application.Quit();

            // Show the window
            window.ShowAll();
        }
    }
}
