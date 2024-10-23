using System;
using System.IO;
using Newtonsoft.Json.Linq;

namespace mtgJsonToCs
{
    class mtgJsonToCs
    {
        const string INPUT_FILE = "files/in/cards.json";
        const string OUTPUT_FILE = "files/out/Cards.cs";

        public mtgJsonToCs() {}

        public void convertFullJson()
        {
            const string LINE_INDENT = "            ";

            using (StreamReader sr = new StreamReader(INPUT_FILE))
            {
                using (StreamWriter sw = new StreamWriter(OUTPUT_FILE))
                {
                    // Write the header of the file
                    sw.WriteLine("namespace MTG");
                    sw.WriteLine("{");
                    sw.WriteLine("    public static class CardsDictionary");
                    sw.WriteLine("    {");
                    sw.WriteLine("        public static readonly Dictionary<string, Card> cards = new Dictionary<string, Card>()");
                    sw.WriteLine("        {");

                    string? line;
                    int maxLines = -1; // -1 means no limit
                    bool writeComma = false;
                    HashSet<string> cardNames = new HashSet<string>();
                    while ((line = sr.ReadLine()) != null)
                    {
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

                        /* At least until 2024, there are only 8 cards in Magic
                        that have never been printed in English, and furthermore
                        they are not legal in any format. Therefore, for
                        simplicity's sake, I will only consider cards printed in
                        English. */
                        if (lang != "en")
                        {
                            continue;
                        }

                        // If the type line contains "Token" or "Card", skip the card
                        if (typeLine.Contains("Token") || typeLine.Contains("Card"))
                        {
                            continue;
                        }

                        // If the card already is in the HashSet, skip it
                        if (!cardNames.Add(completeName))
                        {
                            continue;
                        }

                        // If it is not the first line, add the "," at the end of the line
                        if (writeComma)
                        {
                            sw.WriteLine(",");
                        }
                        else
                        {
                            writeComma = true;
                        }

                        // Parse the fields when necessary
                        completeName = completeName.Replace("\"", "\\\"");

                        // Write the card to the file
                        sw.Write($"{LINE_INDENT}{{ \"{completeName}\", new Card(completeName: \"{completeName}\", typeLine: \"{typeLine}\") }}");

                        // Check the maximum number of lines
                        if (--maxLines == 0)
                        {
                            break;
                        }
                    }

                    // Write the footer of the file
                    sw.WriteLine();
                    sw.WriteLine("        };");
                    sw.WriteLine("    }");
                    sw.WriteLine("}");
                }
            }
        }
    }
}