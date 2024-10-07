using System;

using GUI;

namespace MTG
{
    public class MTG
    {
        private GUI.GUI gui;
        private User user;
        private Friends friends;

        public MTG()
        {
            gui = new GUI.GUI();
            user = new User();
            friends = new Friends();
        }

        public void MainMenuLoop()
        {
            gui.SayWelcome(user.GetName());

            while (true)
            {
                const string OPEN_FRIENDS_MENU_OPTION = "Open friends menu";
                const string QUIT_OPTION = "Quit";

                string[] options = {
                    OPEN_FRIENDS_MENU_OPTION,
                    QUIT_OPTION
                };

                string answer = gui.MakeQuestion("main menu", "Select an option", false, options);

                switch (answer)
                {
                    case OPEN_FRIENDS_MENU_OPTION:
                        FriendsMenuLoop();
                        break;
                    case QUIT_OPTION:
                    default:
                        return;
                }
            }
        }

        private void FriendsMenuLoop()
        {
            while (true)
            {
                const string ADD_FRIEND_OPTION = "Add friend";
                const string REMOVE_FRIEND_OPTION = "Remove friend";
                const string VIEW_FRIENDS_OPTION = "View friends";
                const string SHOW_MY_IP_OPTION = "Show my IP";
                const string BACK_OPTION = "Back";

                string[] options = {
                    ADD_FRIEND_OPTION,
                    REMOVE_FRIEND_OPTION,
                    VIEW_FRIENDS_OPTION,
                    SHOW_MY_IP_OPTION,
                    BACK_OPTION
                };

                string answer = gui.MakeQuestion("main menu > friends menu", "Select an option", false, options);

                switch (answer)
                {
                    case ADD_FRIEND_OPTION:
                        friends.AddFriend();
                        break;
                    case REMOVE_FRIEND_OPTION:
                        friends.RemoveFriend();
                        break;
                    case VIEW_FRIENDS_OPTION:
                        friends.ViewFriends();
                        break;
                    case SHOW_MY_IP_OPTION:
                        friends.ShowMyIP();
                        break;
                    case BACK_OPTION:
                    default:
                        return;
                }
            }
        }
    }
}