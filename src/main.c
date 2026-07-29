#include "playlist_avl.h"

int main()
{
    srand(time(NULL));
    Playlist_AVL A_playlist, B_playlist;
    History_AVL A_history, B_history;
    initialise_Playlist(&A_playlist);
    initialise_Playlist(&B_playlist);
    initialise_History(&A_history);
    initialise_History(&B_history);
    printf("====================================================\n");
    printf("              AVL MUSIC PLAYLIST MANAGER            \n");
    printf("====================================================\n");
    int universal_running = 1;
    int universal_choice;
    printf("1) Add songs .\n");
    printf("2) Search Songs .\n");
    printf("3) Display sorted Songs.\n");
    printf("4) Play Song?\n");
    printf("5) Display History of either playlist.\n");
    printf("6) Set operations on playlists.\n");
    printf("7) Delete Song from either playlist.\n");
    printf("8) Exit.\n");
    printf("9) Display options again.\n");
    printf("====================================================\n");
    while (universal_running)
    {
        printf("Your choice user: \n");
        if (!read_choice(&universal_choice, 1, 9))
        {
            printf("Invalid choice User.\n");
            printf("Enter again.\n");
            continue;
        }
        switch (universal_choice)
        {
        case 1:
        {
            printf("Understood\n");
            printf("Select the playlist you want to add songs to:\n");
            printf("1) Playlist A\n");
            printf("2) Playlist B\n");
            printf("Your choice User: ");
            int playlist_choice;
            while (!read_choice(&playlist_choice, 1, 2))
            {
                printf("Invalid choice User.\n");
                printf("Enter again.\n");
            }
            int s_id;
            char t_arr[MAX_LENGTH_NAME], a_arr[MAX_LENGTH_NAME];
            printf("Enter the Song ID ( positive integer ): ");
            while (!read_choice(&s_id, 0, 100000))
            {
                printf("Invalid Song ID. Please enter a positive integer.\n");
            }
            printf("Enter the Title of the Song: ");
            scanf(" %99[^\n]", t_arr);
            printf("Enter the Artist of the Song: ");
            scanf(" %99[^\n]", a_arr);
            if (playlist_choice == 1)
            {
                add_songs(&A_playlist, s_id, t_arr, a_arr);
            }
            else
            {
                add_songs(&B_playlist, s_id, t_arr, a_arr);
            }

            break;
        }

        case 2:
        {
            printf("Understood\n");
            printf("Select the playlist you want to search songs in:\n");
            printf("1) Playlist A\n");
            printf("2) Playlist B\n");
            printf("Your choice User: ");
            int playlist_choice;
            while (!read_choice(&playlist_choice, 1, 2))
            {
                printf("Invalid choice User.\n");
                printf("Enter again.\n");
            }
            printf("Select the parameter you want to search songs by:\n");
            printf("1) Song ID\n");
            printf("2) Title\n");
            printf("3) Artist\n");
            printf("Your choice User: ");
            int search_choice;
            while (!read_choice(&search_choice, 1, 3))
            {
                printf("Invalid choice User.\n");
                printf("Enter again.\n");
            }
            char search_query[MAX_LENGTH_NAME];
            printf("Enter the search query: ");
            scanf(" %99[^\n]", search_query);
            if (playlist_choice == 1)
            {
                search_BY_input(&A_playlist, search_choice, search_query);
            }
            else
            {
                search_BY_input(&B_playlist, search_choice, search_query);
            }
            break;
        }

        case 3:
        {
            printf("Understood\n");
            printf("Select the playlist you want to display songs of:\n");
            printf("Your choice User: \n");
            printf("1) Playlist A\n");
            printf("2) Playlist B\n");
            printf("Your choice User: ");
            int playlist_choice;
            while (!read_choice(&playlist_choice, 1, 2))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }
            printf("Select the sorting basis you want to display songs by:\n");
            printf("0) Song ID\n");
            printf("1) Title\n");
            printf("2) Artist\n");
            printf("3) Artist + Title\n");
            printf("4) Search query range for Song IDs\n");
            printf("Your choice: ");
            int display_choice;
            while (!read_choice(&display_choice, 0, 4))
            {
                printf("Invalid choice User.\n");
                printf("Enter again.\n");
            }
            if (playlist_choice == 1)
            {
                if (display_choice == 4)
                {
                    int high, low;
                    printf("Enter the positive lower bound of the Song ID range:\n");
                    while (!read_choice(&low, 0, 100000))
                    {
                        printf("Invalid input. Please enter a positive integer.\n");
                    }
                    printf("Enter the positive upper bound of the Song ID range:\n");
                    while (!read_choice(&high, 0, 100000) || high < low)
                    {
                        printf("Invalid input. Please enter a positive integer greater than or equal to the lower bound.\n");
                    }
                    printf("Displaying songs with Song IDs in the range [%d, %d]:\n", low, high);
                    print_range(A_playlist.Playlist_Root, high, low);
                }
                else
                {
                    display_BY_input(&A_playlist, display_choice);
                }
            }
            else
            {
                if (display_choice == 4)
                {
                    int high, low;
                    printf("Enter the positive lower bound of the Song ID range:\n");
                    while (!read_choice(&low, 0, 100000))
                    {
                        printf("Invalid input. Please enter a positive integer.\n");
                    }
                    printf("Enter the positive upper bound of the Song ID range:\n");
                    while (!read_choice(&high, 0, 100000) || high < low)
                    {
                        printf("Invalid input. Please enter a positive integer greater than or equal to the lower bound.\n");
                    }
                    printf("Displaying songs with Song IDs in the range [%d, %d]:\n", low, high);
                    print_range(B_playlist.Playlist_Root, high, low);
                }
                else
                {
                    display_BY_input(&B_playlist, display_choice);
                }
            }
            break;
        }

        case 4:
        {
            printf("Understood\n");
            printf("Select the playlist you want to play songs from:\n");
            printf("1) Playlist A\n");
            printf("2) Playlist B\n");
            printf("Your choice User: \n");
            int playlist_choice;
            while (!read_choice(&playlist_choice, 1, 2))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }
            printf("Select the play option:\n");
            printf("1) Play songs on different parameters.\n");
            printf("2) Play a random song.\n");
            printf("3) Shuffle and play the entire playlist.\n");
            printf("Your choice user: \n");
            int play_choice;
            while (!read_choice(&play_choice, 1, 3))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }
            if (play_choice == 1)
            {
                printf("Select the parameter you want to play songs by:\n");
                printf("1) Play entire playlist\n");
                printf("2) Song ID\n");
                printf("3) Title\n");
                printf("4) Artist\n");
                printf("Your choice User: ");
                int search_choice;
                while (!read_choice(&search_choice, 1, 4))
                {
                    printf("Invalid choice User.");
                    printf("Enter again.\n");
                }
                play_wrapper(playlist_choice == 1 ? &A_playlist : &B_playlist, playlist_choice == 1 ? &A_history : &B_history, search_choice);
            }
            else if (play_choice == 2)
            {
                shuffle_wrapper(playlist_choice == 1 ? &A_playlist : &B_playlist, playlist_choice == 1 ? &A_history : &B_history, 1);
            }
            else if (play_choice == 3)
            {
                shuffle_wrapper(playlist_choice == 1 ? &A_playlist : &B_playlist, playlist_choice == 1 ? &A_history : &B_history, 2);
            }
            break;
        }

        case 5:
        {
            printf("Understood\n");
            printf("Select the playlist history you want to display:\n");
            printf("1) Playlist A History\n");
            printf("2) Playlist B History\n");
            printf("Your choice User: \n");
            int playlist_choice;
            while (!read_choice(&playlist_choice, 1, 2))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }
            printf("Select the display order:\n");
            printf("1) Newest to Oldest\n");
            printf("2) Oldest to Newest\n");
            printf("Your choice User: \n");
            int display_choice;
            while (!read_choice(&display_choice, 1, 2))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }
            display_history_wrapper(playlist_choice == 1 ? &A_history : &B_history, display_choice);
            break;
        }

        case 6:
        {
            printf("Understood\n");
            printf("Select the set operation you want to perform on the playlists:\n");
            printf("1) Union\n");
            printf("2) Intersection\n");
            printf("3) Difference\n");
            printf("4) Symmetric Difference\n");
            printf("Your choice User: \n");
            int set_choice;
            while (!read_choice(&set_choice, 1, 4))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }
            if (set_choice == 3)
            {
                printf("Difference of which playlist from which playlist? (A - B or B - A)\n");
                printf("1) A - B\n");
                printf("2) B - A\n");
                printf("Your choice User: \n");
                int diff_choice;
                while (!read_choice(&diff_choice, 1, 2))
                {
                    printf("Invalid choice User.");
                    printf("Enter again.\n");
                }
                if (diff_choice == 2)
                {
                    set_operations(&B_playlist, &A_playlist, 3);
                }

            }
            set_operations(&A_playlist, &B_playlist, set_choice);
            break;
        }

        case 7:
        {
            printf("Select the playlist to delete song from it:\n");
            printf("1) Playlist A \n");
            printf("2) Playlist B \n");
            printf("Your choice User: \n");
            int playlist_choice;
            while (!read_choice(&playlist_choice, 1, 2))
            {
                printf("Invalid choice User.");
                printf("Enter again.\n");
            }

            int delete_id;
            printf("Enter the positive ID of the Song: ");
            while (!read_choice(&delete_id, 0, 100000))
            {
                printf("Invalid choice user.\n");
                printf("ENter again.\n");
            }
            delete_song_wrapper(playlist_choice == 1 ? &A_playlist : &B_playlist, delete_id);
            break;
        }
        case 8:
        {
            printf("Understood.\n");
            printf("Exiting the Music Player.");
            delete_playlist(A_playlist.Playlist_Root);
            delete_playlist(B_playlist.Playlist_Root);
            delete_history(A_history.History_Root);
            delete_history(B_history.History_Root);
            A_playlist.Playlist_Root=NULL;
            B_playlist.Playlist_Root=NULL;
            A_history.History_Root=NULL;
            B_history.History_Root=NULL;
            universal_running=0;
            break;
        }
        case 9:
        {
            printf("Here are the options.\n");
            printf("===========================================\n");
            printf("1) Add songs to either playlists i.e. A or B.\n");
            printf("2) Search Songs on either playlist with different parameters.\n");
            printf("3) Display songs on different sorting basis on either playlist.\n");
            printf("4) Play Song?\n");
            printf("5) Display History of either playlist.\n");
            printf("6) Set operations on playlists.\n");
            printf("7) Delete Song from either playlist.\n");
            printf("8) Exit.\n");
            printf("9) Display options again.\n");
            printf("====================================================\n");
        }
        default:
            break;
        }
    }
}