using System;
using System.IO;
using System.Text.Json;

namespace wizard
{
    public class SessionManager
    {
        private const string SESSION_FILE_NAME = ".wizard_session";
        private readonly string _sessionFilePath;
        private SessionData _currentSession = new();

        public SessionManager()
        {
            // Obtener el directorio home del usuario
            string homeDirectory = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
            _sessionFilePath = Path.Combine(homeDirectory, SESSION_FILE_NAME);
            LoadSession();
        }

        private void LoadSession()
        {
            try
            {
                if (File.Exists(_sessionFilePath))
                {
                    string jsonContent = File.ReadAllText(_sessionFilePath);
                    var loadedSession = JsonSerializer.Deserialize<SessionData>(jsonContent);
                    _currentSession = loadedSession ?? new SessionData();
                }
                else
                {
                    _currentSession = new SessionData();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error loading session: {ex.Message}");
                _currentSession = new SessionData();
            }
        }

        public void SaveSession()
        {
            try
            {
                string jsonContent = JsonSerializer.Serialize(_currentSession, new JsonSerializerOptions 
                { 
                    WriteIndented = true 
                });
                File.WriteAllText(_sessionFilePath, jsonContent);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error saving session: {ex.Message}");
            }
        }

        public string? LastOpenedFile
        {
            get => _currentSession.LastOpenedFile;
            set
            {
                _currentSession.LastOpenedFile = value;
                SaveSession();
            }
        }

        private class SessionData
        {
            public string? LastOpenedFile { get; set; }
        }
    }
}
