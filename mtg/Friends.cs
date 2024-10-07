using System;
using System.Net;
using System.Net.Sockets;

using GUI;

namespace MTG
{
    public class Friends
    {
        private GUI.GUI gui;
        private List<Friend> friends;

        public Friends()
        {
            gui = new GUI.GUI();
            friends = new List<Friend>();

            LoadFriends();
        }

        public void AddFriend()
        {
            string newFriendName = gui.MakeQuestion("main menu > friends menu", "Type your friend's name", false, new string[] { });
            if (FriendAlreadyExistsName(newFriendName))
            {
                gui.WriteMessage("main menu > friends menu", "There's already a friend with that name.");
                return;
            }

            string newFriendIP = gui.MakeQuestion("main menu > friends menu", "Type your friend's IP", false, new string[] { });
            if (FriendAlreadyExistsIP(newFriendIP))
            {
                gui.WriteMessage("main menu > friends menu", "There's already a friend with that IP.");
                return;
            }
            if (!checkIp(newFriendIP))
            {
                gui.WriteMessage("main menu > friends menu", "Invalid IP.");
                return;
            }

            friends.Add(new Friend(newFriendName, newFriendIP));
            UpdateFriendsFile();
        }

        public void RemoveFriend()
        {
            const string TYPE_NAME_OPTION = "Type name";
            const string TYPE_IP_OPTION = "Type IP";
            const string CANCEL_OPTION = "Cancel";

            string[] options = {
                TYPE_NAME_OPTION,
                TYPE_IP_OPTION,
                CANCEL_OPTION
            };

            string answer = gui.MakeQuestion("main menu > friends menu", "Do you want to remove a friend by typing their name or IP?", false, options);

            if (answer == CANCEL_OPTION)
            {
                return;
            }

            if (answer == TYPE_NAME_OPTION)
            {
                string friendName = gui.MakeQuestion("main menu > friends menu", "Type your friend's name", false, new string[] { });
                Friend? friendToRemove = null;

                foreach (Friend friend in friends)
                {
                    if (friend.GetName() == friendName)
                    {
                        friendToRemove = friend;
                        break;
                    }
                }

                if (friendToRemove == null)
                {
                    gui.WriteMessage("main menu > friends menu", "There's no friend with that name.");
                    return;
                }

                friends.Remove(friendToRemove);
                UpdateFriendsFile();
            }
            else if (answer == TYPE_IP_OPTION)
            {
                string friendIP = gui.MakeQuestion("main menu > friends menu", "Type your friend's IP", false, new string[] { });
                Friend? friendToRemove = null;

                foreach (Friend friend in friends)
                {
                    if (friend.GetIP() == friendIP)
                    {
                        friendToRemove = friend;
                        break;
                    }
                }

                if (friendToRemove == null)
                {
                    gui.WriteMessage("main menu > friends menu", "There's no friend with that IP.");
                    return;
                }

                friends.Remove(friendToRemove);
                UpdateFriendsFile();
            }
        }

        public void ViewFriends()
        {
            gui.ShowFriends(friends);
        }

        public void ShowMyIP()
        {
            // Get the local IP
            string localIP = "Not found";
            
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    localIP = ip.ToString();
                }
            }

            gui.ShowDialog(localIP);
        }

        private bool checkIp(string ip)
        {
            string[] ipParts = ip.Split('.');
            if (ipParts.Length != 4)
            {
                return false;
            }

            foreach (string ipPart in ipParts)
            {
                if (!int.TryParse(ipPart, out int ipPartNum) || ipPartNum < 0 || ipPartNum > 255)
                {
                    return false;
                }
            }

            return true;
        }

        private void LoadFriends()
        {
            string homeDir = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
            string friendsFilePath = Path.Combine(homeDir, ".local", "share", "mtg", "friends");

            if (File.Exists(friendsFilePath))
            {
                string[] friendsNames = File.ReadAllLines(friendsFilePath);
                foreach (string friendLine in friendsNames)
                {
                    // Syntax: friend_name ip
                    // Example: John 192.178.110.77
                    // NOTE: name can contain spaces
                    string[] friendData = friendLine.Split(' ');
                    if (friendData.Length < 2) continue;

                    int lineNumWords = friendData.Length;
                    string[] friendNameWords = new string[lineNumWords - 1];
                    Array.Copy(friendData, friendNameWords, lineNumWords - 1);

                    string name = string.Join(' ', friendNameWords);
                    string friendIP = friendData[lineNumWords - 1];

                    // Add friend to the list
                    friends.Add(new Friend(name, friendIP));
                }
            }
            else
            {
                Directory.CreateDirectory(Path.GetDirectoryName(friendsFilePath) ?? "");
                File.Create(friendsFilePath);
            }
        }

        private void UpdateFriendsFile()
        {
            string homeDir = Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
            string friendsFilePath = Path.Combine(homeDir, ".local", "share", "mtg", "friends");

            // Check if the directory exist (if not, create it)
            Directory.CreateDirectory(Path.GetDirectoryName(friendsFilePath) ?? "");

            // Write the friends to the file
            List<string> friendsLines = new List<string>();
            foreach (Friend friend in friends)
            {
                friendsLines.Add($"{friend.GetName()} {friend.GetIP()}");
            }

            File.WriteAllLines(friendsFilePath, friendsLines);
        }

        private bool FriendAlreadyExistsName(string name)
        {
            foreach (Friend friend in friends)
            {
                if (friend.GetName() == name)
                {
                    return true;
                }
            }

            return false;
        }

        private bool FriendAlreadyExistsIP(string ip)
        {
            foreach (Friend friend in friends)
            {
                if (friend.GetIP() == ip)
                {
                    return true;
                }
            }

            return false;
        }
    }

    public class Friend
    {
        private string name;
        private string ip;

        public Friend(string name, string ip)
        {
            this.name = name;
            this.ip = ip;
        }

        public string GetName()
        {
            return name;
        }

        public string GetIP()
        {
            return ip;
        }
    }
}