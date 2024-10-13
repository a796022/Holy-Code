
using System;
using System.IO;
using System.Net.Http;
using System.Text.Json;
using System.Threading.Tasks;

namespace ScryfallWrapper
{
    public class ScryfallWrapper
    {
        const string SCRYFALL_API = "https://api.scryfall.com/";
        const string OUTPUT_FILE = "files/out/cards.json";

        public ScryfallWrapper() {}

        public async Task GetAllCardsJson()
        {
            using var client = new HttpClient();
            client.BaseAddress = new Uri(SCRYFALL_API);

            // Add required headers
            client.DefaultRequestHeaders.Add("User-Agent", "ScryfallWrapper");
            client.DefaultRequestHeaders.Add("Accept", "application/json");

            // Request the bulk data of all cards
            var response = await client.GetAsync("bulk-data");

            if (response.IsSuccessStatusCode)
            {
                // Get the response content as a string
                var content = await response.Content.ReadAsStringAsync();
                Console.WriteLine("Bulk data downloaded successfully.");

                // Get the URI for the all_cards bulk data
                var bulkData = JsonDocument.Parse(content);
                var allCardsUri = "";

                foreach (var item in bulkData.RootElement.GetProperty("data").EnumerateArray())
                {
                    if (item.GetProperty("type").GetString() == "all_cards")
                    {
                        allCardsUri = item.GetProperty("download_uri").GetString();
                        break;
                    }
                }

                // Download the all_cards data using the download_uri
                if (!string.IsNullOrEmpty(allCardsUri))
                {
                    using var streamResponse = await client.GetAsync(allCardsUri, HttpCompletionOption.ResponseHeadersRead);
                    streamResponse.EnsureSuccessStatusCode(); // Ensure we got a successful response

                    // Save the stream to a file directly
                    using var fileStream = new FileStream(OUTPUT_FILE, FileMode.Create, FileAccess.Write, FileShare.None);
                    await streamResponse.Content.CopyToAsync(fileStream);
                    Console.WriteLine("All cards exported to all_cards.json.");
                }
                else
                {
                    Console.WriteLine("Error: all_cards download URI not found.");
                }
            }
            else
            {
                // Handle the error if the request was unsuccessful
                Console.WriteLine("Error downloading data: " + response.StatusCode);

                var errorContent = await response.Content.ReadAsStringAsync();
                Console.WriteLine("Error details: " + errorContent);
            }
        }

        // Function to format JSON string
        private static string FormatJson(string json)
        {
            using var document = JsonDocument.Parse(json);
            return JsonSerializer.Serialize(document, new JsonSerializerOptions { WriteIndented = true });
        }
    }
}