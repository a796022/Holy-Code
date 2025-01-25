using Gtk;

namespace wizard
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
        
        // Important GUI components
        private TreeView treeView = new TreeView();

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
            Box box_aux = AddMenuBar(window);
            AddPaned(box_aux);
        }

        private void AddPaned(Box vbox)
        {
            // Create the Gtk.Paned (vertical split)
            Paned paned = new Paned(Orientation.Horizontal);

            // Add the widgets to the Paned
            AddTreeNode(paned);
            paned.Pack2(new Label("Right side"), PANED_RESIZABLE, PANED_SHRINK);

            // Add the paned to the box
            bool expand = true; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill = true; /* If true, the child will be allocated the
                full height of the box. */
            uint padding = 0; /* Extra space in pixels around the widget. */
            vbox.PackStart(paned, expand, fill, padding);
        }

        private void AddTreeNode(Paned paned)
        {
            // Create a TreeView for the left panel
            TreeStore treeStore = new TreeStore(typeof(string));
            treeView = new TreeView(treeStore);

            // Add a column to the TreeView
            TreeViewColumn column = new TreeViewColumn { Title = "Nodes" };
            CellRendererText cellRenderer = new CellRendererText();
            column.PackStart(cellRenderer, true);
            column.AddAttribute(cellRenderer, "text", 0);
            treeView.AppendColumn(column);

            // Populate the TreeStore with sample data
            TreeIter root = treeStore.AppendValues("Root Node");
            treeStore.AppendValues(root, "Child Node 1");
            treeStore.AppendValues(root, "Child Node 2");

            // Add the TreeView to a ScrolledWindow
            ScrolledWindow scrolledWindow = new ScrolledWindow();
            scrolledWindow.Add(treeView);

            // Add the ScrolledWindow to the left panel of the Paned
            paned.Pack1(scrolledWindow, true, false);
        }

        private Box AddMenuBar(Window window)
        {
            // Create the vertical box
            int box_spacing = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box vbox = new Box(Orientation.Vertical, box_spacing);

            // Create the menu bar
            MenuBar menubar = new MenuBar();

            // Create the menus
            var fileMenu = new Menu();
            var fileMenuItem = new MenuItem("File");
            fileMenuItem.Submenu = fileMenu;

            // Create the file menu options
            var openMenuItem = new MenuItem("Open");
            fileMenu.Append(openMenuItem);

            // Connect the "Open" menu item to the event handler
            openMenuItem.Activated += OnOpenMenuItemActivated;

            // Add the file menu to the menu bar
            menubar.Append(fileMenuItem);

            // Add the menubar to the box
            bool expand = false; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill = false; /* If true, the child will be allocated the
                full height of the box. */
            uint padding = 0; /* Extra space in pixels around the widget. */
            vbox.PackStart(menubar, expand, fill, padding);

            // Add the box to the window
            window.Add(vbox);

            return vbox;
        }

        private void OnOpenMenuItemActivated(object? sender, EventArgs e)
        {
            // Create a new file chooser dialog
            FileChooserDialog fileChooser = new FileChooserDialog(
                "Select a File", 
                null, 
                FileChooserAction.Open, 
                "Cancel", ResponseType.Cancel, 
                "Open", ResponseType.Accept);

            // Show the dialog and wait for a user response
            ResponseType response = (ResponseType)fileChooser.Run();

            if (response == ResponseType.Accept)
            {
                // Get the selected file's name and print it to the terminal
                string fileName = fileChooser.Filename;
                TreeBuilder.PopulateTree(treeView, fileName);
            }

            // Destroy the dialog to free resources
            fileChooser.Destroy();
        }
    }
}
