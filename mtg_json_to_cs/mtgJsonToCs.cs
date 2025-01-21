using System;
using System.IO;
using Newtonsoft.Json.Linq;

namespace mtgJsonToCs
{
    class mtgJsonToCs
    {
        const string INPUT_FILE = "files/in/cards.json";
        const string OUTPUT_FILE_CARDS = "files/out/Cards.cs";
        const string OUTPUT_FILE_SETS = "files/out/Sets.cs";

        public mtgJsonToCs() {}

        public void convertFullJson()
        {
            const string LINE_INDENT_CARDS = "            ";
            const string LINE_INDENT_SETS = "            ";

            int numLines = CountLines(INPUT_FILE);

            Console.WriteLine("Converting the full json file to C# classes...");

            using (StreamReader sr = new StreamReader(INPUT_FILE))
            {
                using (StreamWriter swSets = new StreamWriter(OUTPUT_FILE_SETS))
                using (StreamWriter swCards = new StreamWriter(OUTPUT_FILE_CARDS))
                {
                    // Write the header of the files
                    swCards.WriteLine("namespace MTG");
                    swCards.WriteLine("{");
                    swCards.WriteLine("    public static class CardsDictionary");
                    swCards.WriteLine("    {");
                    swCards.WriteLine("        public static readonly Dictionary<string, Card> cards = new Dictionary<string, Card>()");
                    swCards.WriteLine("        {");

                    swSets.WriteLine("namespace MTG");
                    swSets.WriteLine("{");
                    swSets.WriteLine("    public static class SetsDictionary");
                    swSets.WriteLine("    {");
                    swSets.WriteLine("        public static List<Set> sets = new List<Set>()");
                    swSets.WriteLine("        {");

                    string? line;
                    int maxLines = -1; // -1 means no limit
                    bool writeCommaCards = false;
                    bool writeCommaSets = false;
                    HashSet<string> cardNames = new HashSet<string>();
                    HashSet<string> setCodes = new HashSet<string>();
                    double progress = 0.0;
                    int lineCount = 0;
                    while ((line = sr.ReadLine()) != null)
                    {
                        // Print the progress
                        lineCount++;
                        double newProgress = (double)lineCount / numLines;
                        if (newProgress - progress >= 0.01)
                        {
                            progress = newProgress;
                            UpdateProgressBar(lineCount, numLines);
                        }

                        if (line == "[" || line == "]")
                        {
                            continue;
                        }

                        // If there is a "," at the end of the line, remove it
                        if (line.EndsWith(","))
                        {
                            line = line.Remove(line.Length - 1);
                        }
                        
                        // Parse the json
                        JObject json = JObject.Parse(line);
                        string completeName = json["name"]?.ToString() ?? "";
                        string lang = json["lang"]?.ToString() ?? "";
                        string typeLine = json["type_line"]?.ToString() ?? "";
                        string setCode = json["set"]?.ToString() ?? "";
                        string setName = json["set_name"]?.ToString() ?? "";

                        /*
                        For cards:
                        1- At least until 2024, there are only 8 cards in Magic
                        that have never been printed in English, and furthermore
                        they are not legal in any format. Therefore, for
                        simplicity's sake, I will only consider cards printed in
                        English.
                        2- If the type line contains "Token" or "Card", skip the
                        card.
                        3- If the card already is in the HashSet, skip it.
                        */
                        if (lang == "en" &&
                            !typeLine.Contains("Token") && 
                            !typeLine.Contains("Card") &&
                            cardNames.Add(completeName))
                        {
                            // If it is not the first line, add the "," at the end of the line
                            if (writeCommaCards)
                            {
                                swCards.WriteLine(",");
                            }
                            else
                            {
                                writeCommaCards = true;
                            }

                            // Parse the fields when necessary
                            completeName = completeName.Replace("\"", "\\\"");

                            // Write the card to the file
                            swCards.Write($"{LINE_INDENT_CARDS}{{ \"{completeName}\", new Card(completeName: \"{completeName}\", typeLine: \"{typeLine}\") }}");
                        }

                        /*
                        For sets:
                        1- At least until 2024, there are only 8 cards in Magic
                        that have never been printed in English, and furthermore
                        they are not legal in any format. Therefore, for
                        simplicity's sake, I will only consider cards printed in
                        English.
                        2- If the card already is in the HashSet, skip it.
                        */
                        if (lang == "en" && setCodes.Add(setCode))
                        {
                            // If it is not the first line, add the "," at the end of the line
                            if (writeCommaSets)
                            {
                                swSets.WriteLine(",");
                            }
                            else
                            {
                                writeCommaSets = true;
                            }

                            // If there are info about the card, print it
                            if (SetsInfo.setsInfo.ContainsKey(setCode))
                            {
                                List<string> setInfo = SetsInfo.setsInfo[setCode];
                                foreach (string info in setInfo)
                                {
                                    swSets.WriteLine($"{LINE_INDENT_CARDS}// {info}");
                                }
                            }

                            // Parse the fields when necessary
                            setName = setName.Replace("\"", "\\\"");

                            // Write the set to the file
                            swSets.Write($"{LINE_INDENT_SETS}new Set(\"{setCode}\", \"{setName}\")");
                        }

                        // Check the maximum number of lines
                        if (--maxLines == 0)
                        {
                            break;
                        }
                    }

                    // Write the footer of the files
                    swCards.WriteLine();
                    swCards.WriteLine("        };");
                    swCards.WriteLine("    }");
                    swCards.WriteLine("}");

                    swSets.WriteLine();
                    swSets.WriteLine("        };");
                    swSets.WriteLine("    }");
                    swSets.WriteLine("}");
                }

                UpdateProgressBar(numLines, numLines);
                Console.WriteLine(" Done!");
            }
        }

        public int CountLines(string inputFile)
        {
            int count = 0;
            using (StreamReader sr = new StreamReader(inputFile))
            {
                string? line;
                while ((line = sr.ReadLine()) != null)
                {
                    count++;
                }
            }

            return count;
        }

        public void UpdateProgressBar(int progress, int total)
        {
            Console.Write("\r["); // Return to the beginning of the line
            int barWidth = 50; // Width of the loading bar in characters
            int filledWidth = (progress * barWidth) / total; // Calculate filled portion
            Console.Write(new string('#', filledWidth)); // Draw filled part of the bar
            Console.Write(new string(' ', barWidth - filledWidth)); // Draw remaining empty part
            Console.Write($"] {progress * 100 / total}%"); // Display the percentage
        }
    }
}