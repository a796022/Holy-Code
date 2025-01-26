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
        private TreeStore treeStore = new TreeStore(typeof(string));
        private TreeView treeView = new TreeView();
        private Entry addInputEntry = new Entry
        {
            PlaceholderText = "Node Text"
        };

        // File path of the currently opened file
        private string currentFile = string.Empty;

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

        private void AddPaned(Box box)
        {
            // Create the Gtk.Paned (vertical split)
            Paned paned = new Paned(Orientation.Horizontal);

            // Add the widgets to the Paned
            AddTreeNode(paned);
            AddExpander(paned);

            // Add the paned to the box
            bool expand = true; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill = true; /* If true, the child will be allocated the
                full height of the box. */
            uint padding = 0; /* Extra space in pixels around the widget. */
            box.PackStart(paned, expand, fill, padding);
        }

        private void AddExpander(Paned paned)
        {
            // Create the right-side content
            int box_spacing = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box rightSide = new Box(Orientation.Vertical, box_spacing);

            // Create the expander
            Expander expander = new Expander("Add Nodes");

            // Create the containers of the inputs
            int box_spacing_2 = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box expanderContent = new Box(Orientation.Vertical, box_spacing_2);

            int box_spacing_3 = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box expanderContent_2 = new Box(Orientation.Horizontal, box_spacing_3){
                MarginTop = 5
            };

            // Create a button to add the node
            Button addButton = new Button("Add Node")
            {
                MarginEnd = 15
            };

            // Connect the button to the event handler
            addButton.Clicked += OnAddButtonClicked;

            // Pack the input label, entry, and button into the expander content
            bool expand = true; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill = true; /* If true, the child will be allocated the
                full height of the box. */
            uint padding = 15; /* Extra space in pixels around the widget. */
            expanderContent_2.PackStart(addInputEntry, expand, fill, padding);

            // Pack the input label, entry, and button into the expander content
            bool expand_2 = false; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill_2 = false; /* If true, the child will be allocated the
                full height of the box. */
            uint padding_2 = 0; /* Extra space in pixels around the widget. */
            expanderContent_2.PackStart(addButton, expand_2, fill_2, padding_2);

            // Add the expander content to the expander
            expanderContent.Add(expanderContent_2);

            // Add the content to the expander
            expander.Add(expanderContent);

            // Add the expander to the right-side content
            rightSide.PackStart(expander, expand, fill, padding);

            // Add the right-side content to the Paned
            paned.Pack2(rightSide, PANED_RESIZABLE, PANED_SHRINK);
        }

        // Event handler function for the add button
        private void OnAddButtonClicked(object? sender, EventArgs args)
        {
            string nodeText = addInputEntry.Text;
            if (!string.IsNullOrEmpty(nodeText))
            {
                // Get the selected node from the TreeView
                TreeIter selectedNode;
                TreeSelection selection = treeView.Selection;

                if (selection.GetSelected(out _, out selectedNode))
                {
                    // Add as a child of the selected node
                    treeStore.AppendValues(selectedNode, nodeText);
                }

                // Clear the input after adding the node
                addInputEntry.Text = string.Empty;
            }
        }

        private void AddTreeNode(Paned paned)
        {
            // Create a TreeView for the left panel
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
            paned.Pack1(scrolledWindow, PANED_RESIZABLE, PANED_SHRINK);
        }

        private Box AddMenuBar(Window window)
        {
            // Create the vertical box
            int box_spacing = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box box = new Box(Orientation.Vertical, box_spacing);

            // Create the menu bar
            MenuBar menubar = new MenuBar();

            // Create the menus
            Menu fileMenu = new Menu();
            MenuItem fileMenuItem = new MenuItem("File");
            fileMenuItem.Submenu = fileMenu;

            // Create the file menu options
            MenuItem openMenuItem = new MenuItem("Open");
            MenuItem saveMenuItem = new MenuItem("Save");
            fileMenu.Append(openMenuItem);
            fileMenu.Append(saveMenuItem);

            // Connect the "Open" menu item to the event handler
            openMenuItem.Activated += OnOpenMenuItemActivated;
            saveMenuItem.Activated += OnSaveMenuItemActivated;

            // Add the file menu to the menu bar
            menubar.Append(fileMenuItem);

            // Add the menubar to the box
            bool expand = false; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill = false; /* If true, the child will be allocated the
                full height of the box. */
            uint padding = 0; /* Extra space in pixels around the widget. */
            box.PackStart(menubar, expand, fill, padding);

            // Add the box to the window
            window.Add(box);

            return box;
        }

        private void OnSaveMenuItemActivated(object? sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(currentFile))
            {
                TreeNodeSaver.SaveTreeToFile(treeStore, currentFile);
            }
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
                TreeBuilder.PopulateTree(treeStore, fileName);
                currentFile = fileName;
            }

            // Destroy the dialog to free resources
            fileChooser.Destroy();
        }
    }
}
