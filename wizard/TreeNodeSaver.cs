using Gtk;

namespace wizard
{
    public class TreeNodeSaver
    {
        public static void SaveTreeToFile(TreeStore treeStore, string filePath)
        {
            using (StreamWriter writer = new StreamWriter(filePath))
            {
                // Initialize the iterator in the first node
                if (treeStore.GetIterFirst(out TreeIter iter))
                {
                    SaveNode(treeStore, iter, writer, 0);
                }
            }
        }

        private static void SaveNode(TreeStore treeStore, TreeIter iter, StreamWriter writer, int indentationLevel)
        {
            // Extract the node text
            string? nodeText = treeStore.GetValue(iter, 0)?.ToString();
            if (!string.IsNullOrEmpty(nodeText))
            {
                // Write the text with the appropriate indentation
                writer.WriteLine(new string(' ', indentationLevel * 4) + nodeText);
            }

            // If the node has children, process them recursively
            if (treeStore.IterChildren(out TreeIter childIter, iter))
            {
                do
                {
                    SaveNode(treeStore, childIter, writer, indentationLevel + 1);
                }
                while (treeStore.IterNext(ref childIter));
            }
        }
    }
}