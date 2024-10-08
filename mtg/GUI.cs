using System;
using System.Runtime.InteropServices;

using MTG;

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
            "║┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓║";
        private const string SMALL_FRAME_END =
            "║┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛║";
        private const string SMALL_FRAME_LINE_INIT = "║┃ ";
        private const string SMALL_FRAME_LINE_END = " ┃║";

        private const int CONSOLE_WIDTH = 80;

        public GUI() {}

        public void WriteMessage(string messager, string message)
        {
            const int CHUNK_SIZE = CONSOLE_WIDTH;
            string line = "[" + messager + "]: " + message;
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

            foreach (string chunk in lines)
            {
                Console.WriteLine(chunk);
            }
        }

        public string MakeQuestion(string questioner, string question, bool avoidEmpty, string[] options)
        {
            WriteMessage(questioner, question);
            for (int i = 0; i < options.Length; i++)
            {
                WriteOption(options[i], i + 1);
            }
            
            // Get the input and check if it's valid
            Console.Write(">> ");
            string? input = Console.ReadLine();
            string answer;

            if (options.Length > 0)
            {
                int option;
                while (!int.TryParse(input, out option) || option < 1 || option > options.Length)
                {
                    Console.Write(">> ");
                    input = Console.ReadLine();
                }

                answer = options[option - 1];
            }
            else
            {
                while (avoidEmpty && string.IsNullOrEmpty(input))
                {
                    Console.Write(">> ");
                    input = Console.ReadLine();
                }

                answer = input ?? "";
            }

            return answer;
        }

        private void WriteOption(string option, int number)
        {
            string firstPrefix = "  " + (number) + ". ";
            string prefix = new string(' ', firstPrefix.Length);
            int chunkSize = CONSOLE_WIDTH - prefix.Length;
            List<string> lines = new List<string>();

            for (int i = 0; i < option.Length; i += chunkSize)
            {
                if (i + chunkSize > option.Length)
                {
                    lines.Add(option.Substring(i));
                }
                else
                {
                    lines.Add(option.Substring(i, chunkSize));
                }
            }

            Console.WriteLine(firstPrefix + lines[0]);
            for (int i = 1; i < lines.Count; i++)
            {
                Console.WriteLine(prefix + lines[i]);
            }
        }

        public void ShowNotImplemented()
        {
            WriteBigDialog("This feature is not implemented yet.");
        }

        public void WriteBigDialog(string line)
        {
            StartBigDialog();
            WriteBigDialogLine(line);
            EndBigDialog();
        }

        public void StartBigDialog()
        {
            Console.WriteLine(BIG_FRAME_INIT);
        }

        public void EndBigDialog()
        {
            Console.WriteLine(BIG_FRAME_END);
        }

        public void WriteBigDialogLine(string line)
        {
            // Divide the line in multiple lines of characters
            const int CHUNK_SIZE = CONSOLE_WIDTH - 4;
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

        public void WriteSmallDialog(string line)
        {
            StartSmallDialog();
            WriteSmallDialogLine(line);
            EndSmallDialog();
        }

        public void StartSmallDialog()
        {
            Console.WriteLine(SMALL_FRAME_INIT);
        }

        public void EndSmallDialog()
        {
            Console.WriteLine(SMALL_FRAME_END + "\n");
        }

        public void WriteSmallDialogLine(string line)
        {
            // Divide the line in multiple lines of characters
            const int CHUNK_SIZE = CONSOLE_WIDTH - 6;
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