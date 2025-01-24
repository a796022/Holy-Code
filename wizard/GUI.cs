using Gtk;

namespace GUI
{
    public class GUI
    {
        // Default main window properties
        private const string MAIN_WINDOW_DEFAULT_TITLE = "New Tree - Wizard";
        private const int MAIN_WINDOW_DEFAULT_WIDTH = 1200;
        private const int MAIN_WINDOW_DEFAULT_HEIGHT = 700;
        private const int MAIN_WINDOW_DEFAULT_MIN_WIDTH = 400;
        private const int MAIN_WINDOW_DEFAULT_MIN_HEIGHT = 300;

        // Default paned properties
        private const bool PANED_RESIZABLE = true;
        private const bool PANED_SHRINK = false; /* This parameter controls
            whether the widget can be reduced beyond its minimum size when
            moving the separator. */

        public GUI()
        {
            NewWindow();
        }

        private void NewWindow()
        {
            // Create the main window
            Window window = new Window(MAIN_WINDOW_DEFAULT_TITLE);
            window.SetDefaultSize(MAIN_WINDOW_DEFAULT_WIDTH,
                                  MAIN_WINDOW_DEFAULT_HEIGHT);
            window.SetSizeRequest(MAIN_WINDOW_DEFAULT_MIN_WIDTH,
                                  MAIN_WINDOW_DEFAULT_MIN_HEIGHT);
            
            // Sets the behavior of the window in case of different events
            window.DeleteEvent += (sender, e) => Application.Quit();

            // Set the window components
            SetWindowComponents(window);

            // Show the window
            window.ShowAll();
        }

        private void SetWindowComponents(Window window)
        {
            // Create the Gtk.Paned (vertical split)
            Paned paned = new Paned(Orientation.Horizontal);

            // Create widgets for each side of the Paned (labels)
            Label leftLabel = new Label("Left side");
            Label rightLabel = new Label("Right side");

            // Add the widgets to the Paned
            paned.Pack1(leftLabel, PANED_RESIZABLE, PANED_SHRINK);
            paned.Pack2(rightLabel, PANED_RESIZABLE, PANED_SHRINK);

            // Add the Paned to the window
            window.Add(paned);
        }
    }
}
