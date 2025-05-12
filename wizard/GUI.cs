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

        // Keyboard shortcut manager
        private KeyboardShortcutManager shortcutManager;

        public GUI()
        {
            Window window = NewWindow();
            shortcutManager = new KeyboardShortcutManager(window, this);
        }

        private Window NewWindow()
        {
            // Create the main window
            Window window = new Window(MAIN_WINDOW_DEFAULT_TITLE);
            window.SetDefaultSize(MAIN_WINDOW_DEFAULT_WIDTH,
                                  MAIN_WINDOW_DEFAULT_HEIGHT);
            window.SetSizeRequest(MAIN_WINDOW_DEFAULT_MIN_WIDTH,
                                  MAIN_WINDOW_DEFAULT_MIN_HEIGHT);
            
            // Sets the behavior of the window in case of different events
            window.DeleteEvent += Window_DeleteEvent;

            // Set the window components
            SetWindowComponents(window);

            // Show the window
            window.ShowAll();
            
            return window;
        }

        private void Window_DeleteEvent(object sender, DeleteEventArgs args)
        {
            shortcutManager.Dispose();
            Application.Quit();
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

            // Connect to the "realize" signal to set the initial position
            paned.Realized += SetPanedInitialPosition;

            // Add the paned to the box
            bool expand = true; /* If true, the child will be allocated all
                the extra space in the box. */
            bool fill = true; /* If true, the child will be allocated the
                full height of the box. */
            uint padding = 0; /* Extra space in pixels around the widget. */
            box.PackStart(paned, expand, fill, padding);
        }

        private void SetPanedInitialPosition(object? sender, EventArgs e)
        {
            // Cast the sender to a Paned object
            Paned? paned = sender as Paned;

            // Ensure the sender is a Paned
            if (paned == null)
            {
                throw new ArgumentException("Sender must be a Gtk.Paned object.");
            }

            // Get the total width of the Paned
            int panedWidth = paned.AllocatedWidth;

            // Calculate the midpoint
            int midpoint = panedWidth / 2;

            // Set the initial position to the midpoint
            paned.Position = midpoint;

            // Lock the position unless the user drags it
            paned.PositionSet = true;
        }

        private void AddExpander(Paned paned)
        {
            // Create the right-side content
            int box_spacing = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box rightSide = new Box(Orientation.Vertical, box_spacing);

            // Create the expander
            Expander expander = new Expander("Add Nodes");

            // Set the expander properties
            expander.Expanded = true;

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

            // Populate the TreeStore with sample data (if empty)
            if (!treeStore.GetIterFirst(out _))
            {
                TreeIter root = treeStore.AppendValues("Root Node");
                treeStore.AppendValues(root, "Child Node 1");
                treeStore.AppendValues(root, "Child Node 2");

                // Expand the first node
                ExpandFirstNodeInTreeView();
            }

            // Connect the event handler to the TreeView
            treeView.RowActivated += OnRowActivated;

            // Add the TreeView to a ScrolledWindow
            ScrolledWindow scrolledWindow = [treeView];

            // Add the ScrolledWindow to the left panel of the Paned
            paned.Pack1(scrolledWindow, PANED_RESIZABLE, PANED_SHRINK);
        }

        private void OnRowActivated(object? sender, RowActivatedArgs e)
        {
            if (sender is TreeView treeView)
            {
                TreePath path = e.Path;

                if (treeView.GetRowExpanded(path))
                {
                    treeView.CollapseRow(path); // Contract
                }
                else
                {
                    treeView.ExpandRow(path, false); // Expand
                }
            }
        }

        private Box AddMenuBar(Window window)
        {
            // Create the vertical box
            int box_spacing = 0; /* Space in pixels between the widgets that
                will be added to the Box. */
            Box box = new Box(Orientation.Vertical, box_spacing);

            // Create and add AccelGroup to the window
            AccelGroup accelGroup = new AccelGroup();
            window.AddAccelGroup(accelGroup);

            // Create the menu bar
            MenuBar menubar = new MenuBar();

            // Create the menus
            Menu fileMenu = new Menu();
            MenuItem fileMenuItem = new MenuItem("File");
            fileMenuItem.Submenu = fileMenu;

            // Create the file menu options with accelerator labels
            MenuItem openMenuItem = new MenuItem("_Open");
            openMenuItem.UseUnderline = true;
            openMenuItem.AddAccelerator("activate", accelGroup, (uint)Gdk.Key.o, 
                                      Gdk.ModifierType.ControlMask, AccelFlags.Visible);

            MenuItem saveMenuItem = new MenuItem("_Save");
            saveMenuItem.UseUnderline = true;
            saveMenuItem.AddAccelerator("activate", accelGroup, (uint)Gdk.Key.s, 
                                      Gdk.ModifierType.ControlMask, AccelFlags.Visible);
            
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

        public void OnSaveMenuItemActivated(object? sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(currentFile))
            {
                TreeNodeSaver.SaveTreeToFile(treeStore, currentFile);
            }
        }

        public void OnOpenMenuItemActivated(object? sender, EventArgs e)
        {
            // Create a new file chooser dialog
            FileChooserDialog fileChooser = new FileChooserDialog(
                "Select a File", 
                null, 
                FileChooserAction.Open, 
                "Cancel", ResponseType.Cancel, 
                "Open", ResponseType.Accept);

            // Show the dialog and wait for a user response
            if (fileChooser.Run() == (int)ResponseType.Accept)
            {
                // Get the selected file name
                string fileName = fileChooser.Filename;
                currentFile = fileName;

                // Load the file into the TreeStore
                treeStore.Clear();
                TreeBuilder.PopulateTree(treeStore, fileName);

                // Expand the first node in the TreeView
                ExpandFirstNodeInTreeView();
            }

            // Destroy the dialog to free resources
            fileChooser.Destroy();
        }

        private void ExpandFirstNodeInTreeView(bool expandChildrenRecursively = false)
        {
            if (treeStore == null || treeView == null)
            {
                Console.WriteLine("Warning: TreeStore or TreeView is not initialized. Cannot expand first node.");
                return;
            }

            if (treeStore.GetIterFirst(out TreeIter firstNodeIter))
            {
                TreePath firstNodePath = treeStore.GetPath(firstNodeIter);

                if (firstNodePath != null)
                {
                    treeView.ExpandRow(firstNodePath, expandChildrenRecursively);
                }
            }
        }
    }
}
