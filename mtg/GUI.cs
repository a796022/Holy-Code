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

        public void SayWelcome(string userName)
        {
            WriteBigDialog("Welcome to MTG Console, " + userName + "!");
        }

        public void WriteMessage(string messager, string message)
        {
            Console.WriteLine("[" + messager + "]: " + message);
        }

        public string MakeQuestion(string questioner, string question, bool avoidEmpty, string[] options)
        {
            Console.WriteLine("[" + questioner + "]: " + question);
            for (int i = 0; i < options.Length; i++)
            {
                string questionStr = "  " + (i + 1) + ". " + options[i];
                Console.WriteLine(questionStr);
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

        public void ShowFriends(List<Friend> friends)
        {
            if (friends.Count == 0)
            {
                WriteBigDialog("You don't have any friends yet.");
                return;
            }

            StartBigDialog();

            WriteBigDialogLine("Your friends are:");
            foreach (Friend friend in friends)
            {
                WriteBigDialogLine("  - " + friend.GetName() + " (" + friend.GetIP() + ")");
            }

            EndBigDialog();
        }

        public void ShowDialog(string content)
        {
            WriteBigDialog(content);
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
            Console.WriteLine(BIG_FRAME_END);
        }

        private void WriteBigDialogLine(string line)
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