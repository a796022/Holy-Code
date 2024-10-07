using GUI;
using System;

namespace MTG
{
    public class User
    {
        private GUI.GUI gui;
        private string name;

        public User()
        {
            gui = new GUI.GUI();
            name = LoadName();
        }

        public string GetName()
        {
            return name;
        }

        private string LoadName()
        {
            string homeDir = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
            string nameFilePath = Path.Combine(homeDir, ".local", "share", "mtg", "user_name");

            if (File.Exists(nameFilePath))
            {
                return File.ReadAllText(nameFilePath);
            }
            else
            {
                string username = gui.AskUsername();

                Directory.CreateDirectory(Path.GetDirectoryName(nameFilePath) ?? "");
                File.WriteAllText(nameFilePath, username);

                return username;
            }
        }
    }
}