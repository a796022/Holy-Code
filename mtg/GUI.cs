using System;

namespace GUI
{
    public class GUI
    {
        private const string BIG_FRAME_INIT =
            "╔══════════════════════════════════════════════════════════════════════════════╗";
        private const string BIG_FRAME_END =
            "╚══════════════════════════════════════════════════════════════════════════════╝";
        private const string BIG_FRAME_LINE_INIT = "║ ";
        private const string BIG_FRAME_LINE_END = " ║";

        private const string SMALL_FRAME_INIT =
            "┌──────────────────────────────────────────────────────────────────────────────┐";
        private const string SMALL_FRAME_END =
            "└──────────────────────────────────────────────────────────────────────────────┘";
        private const string SMALL_FRAME_LINE_INIT = "│ ";
        private const string SMALL_FRAME_LINE_END = " │";

        public GUI() {}

        public void SayWelcome(string userName)
        {
            WriteBigDialog("Welcome to MTG Console, " + userName + "!");
        }

        private void WriteBigDialog(string line)
        {
            StartBigDialog();
            WriteBigDialogLine(line);
            EndBigDialog();
        }

        private void StartBigDialog()
        {
            Console.WriteLine(BIG_FRAME_INIT);
        }

        private void EndBigDialog()
        {
            Console.WriteLine(BIG_FRAME_END + "\n");
        }

        private void WriteBigDialogLine(string line)
        {
            // Divide the line in multiple lines of 76 characters
            const int CHUNK_SIZE = 76;
            List<string> lines = new List<string>();

            for (int i = 0; i < line.Length; i += CHUNK_SIZE)
            {
                if (i + CHUNK_SIZE > line.Length)
                {
                    lines.Add(line.Substring(i));
                }
                else
                {
                    lines.Add(line.Substring(i, CHUNK_SIZE));
                }
            }

            // Print the lines with the frame
            foreach (string chunk in lines)
            {
                Console.WriteLine(BIG_FRAME_LINE_INIT + chunk.PadRight(CHUNK_SIZE) + BIG_FRAME_LINE_END);
            }
        }

        private void WriteSmallDialog(string line)
        {
            StartSmallDialog();
            WriteSmallDialogLine(line);
            EndSmallDialog();
        }

        private void StartSmallDialog()
        {
            Console.WriteLine(SMALL_FRAME_INIT);
        }

        private void EndSmallDialog()
        {
            Console.WriteLine(SMALL_FRAME_END + "\n");
        }

        private void WriteSmallDialogLine(string line)
        {
            // Divide the line in multiple lines of 36 characters
            const int CHUNK_SIZE = 76;
            List<string> lines = new List<string>();

            for (int i = 0; i < line.Length; i += CHUNK_SIZE)
            {
                if (i + CHUNK_SIZE > line.Length)
                {
                    lines.Add(line.Substring(i));
                }
                else
                {
                    lines.Add(line.Substring(i, CHUNK_SIZE));
                }
            }

            // Print the lines with the frame
            foreach (string chunk in lines)
            {
                Console.WriteLine(SMALL_FRAME_LINE_INIT + chunk.PadRight(CHUNK_SIZE) + SMALL_FRAME_LINE_END);
            }
        }
    }
}