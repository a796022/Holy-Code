using System;

namespace MTG
{
    public class User
    {
        private string name;

        public User()
        {
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
                return "User";
            }
        }
    }
}