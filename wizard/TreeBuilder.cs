using Gtk;

namespace wizard
{
    public class TreeBuilder
    {
        public static void PopulateTree(TreeView treeView, string fileName)
        {
            // Validate file existence
            if (!File.Exists(fileName))
            {
                Console.WriteLine($"File not found: {fileName}");
                return;
            }

            // Initialize TreeStore
            TreeStore treeStore = new TreeStore(typeof(string));
            treeView.Model = treeStore;

            // Read file lines and build the tree
            string[] lines = File.ReadAllLines(fileName);
            List<TreeIter?> parentNodes = new List<TreeIter?>(); // Dynamic depth handling

            foreach (string line in lines)
            {
                if (string.IsNullOrWhiteSpace(line))
                    continue;

                // Determine node depth based on leading spaces (4 spaces per level)
                int depth = line.TakeWhile(char.IsWhiteSpace).Count() / 4;

                if (depth < 0)
                {
                    Console.WriteLine($"Invalid indentation level: {line}");
                    continue;
                }

                string nodeText = line.Trim();

                // Adjust parentNodes list size to match depth
                while (parentNodes.Count <= depth)
                {
                    parentNodes.Add(null);
                }

                if (depth == 0)
                {
                    // Root level node
                    parentNodes[0] = treeStore.AppendValues(nodeText);
                }
                else
                {
                    // Child node of the previous depth
                    if (parentNodes[depth - 1] != null)
                    {
                        parentNodes[depth] = treeStore.AppendValues(parentNodes[depth - 1]!.Value, nodeText);
                    }
                }

                // Clear deeper levels to avoid incorrect nesting
                if (parentNodes.Count > depth + 1)
                {
                    parentNodes.RemoveRange(depth + 1, parentNodes.Count - depth - 1);
                }
            }
        }
    }
}