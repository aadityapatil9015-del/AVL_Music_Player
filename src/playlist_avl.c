#include "playlist_avl.h"
void initialise_Playlist(Playlist_AVL* root)
{
    root->Playlist_Root=NULL;
}

void initialise_History(History_AVL* root)
{
    root->History_Root=NULL;
    root->current_time=0;
}

Songs_Node_AVL *create_song(int s_id, char t_arr[], char a_arr[])
{
    Songs_Node_AVL *new_node = (Songs_Node_AVL *)malloc(sizeof(Songs_Node_AVL));
    if (!new_node)
    {
        return NULL; // failure to allocate
    }
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->Song_id = s_id;
    strncpy(new_node->Title, t_arr, MAX_LENGTH_NAME - 1);
    new_node->Title[MAX_LENGTH_NAME - 1] = '\0'; // Ensure null-termination
    strncpy(new_node->Artist, a_arr, MAX_LENGTH_NAME - 1);
    new_node->Artist[MAX_LENGTH_NAME - 1] = '\0'; // Ensure null-termination
    new_node->height = 0; // Initial height for a new node
    return new_node;
}

History_Node_AVL* create_history_node(Songs_Node_AVL* song,int current_time)
{
    History_Node_AVL* new_node=malloc(sizeof(History_Node_AVL));
    if(!new_node)
    {
        return NULL;//failure to allocate
    }
    new_node->Song_id=song->Song_id;
    new_node->left_child=NULL;
    new_node->right_child=NULL;
    strncpy(new_node->Artist,song->Artist,MAX_LENGTH_NAME-1);
    new_node->Artist[MAX_LENGTH_NAME-1]='\0';
    strncpy(new_node->Title,song->Title,MAX_LENGTH_NAME-1);
    new_node->Title[MAX_LENGTH_NAME-1]='\0';
    new_node->time_stamp=current_time;
    new_node->height_history=0; // Initial height for a new node
    return new_node;
}

int max(int a, int b)
{
    return (a>b)? a:b;
}

int get_height_history(History_Node_AVL* node)
{
    if(node==NULL)
    {
        return -1;
    }
    else
    {
        return node->height_history;
    }
}

int get_height_songs(Songs_Node_AVL* node)
{
    if(node==NULL)
    {
        return -1;
    }
    else
    {
        return node->height;
    }
}

int read_int(int *x)
{
    int res=scanf("%d", x);
    int c;
    while((c=getchar())!='\n' && c!=EOF);

    return (res==1);
}

int read_choice(int *x,int min,int max)
{
    int res=read_int(x);
    if(res==1 && (*x>=min && *x<=max))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Songs_Node_AVL* rotate_right_songs(Songs_Node_AVL* rotate_node)
{
    Songs_Node_AVL* new_root=rotate_node->left_child;
    rotate_node->left_child=new_root->right_child;
    new_root->right_child=rotate_node;
    rotate_node->height=1+max(get_height_songs(rotate_node->left_child),get_height_songs(rotate_node->right_child));
    new_root->height=1+max(get_height_songs(new_root->left_child),get_height_songs(new_root->right_child));
    return new_root;
}

Songs_Node_AVL* rotate_left_songs(Songs_Node_AVL* rotate_node)
{
    Songs_Node_AVL* new_root=rotate_node->right_child;
    rotate_node->right_child=new_root->left_child;
    new_root->left_child=rotate_node;
    rotate_node->height=1+max(get_height_songs(rotate_node->left_child),get_height_songs(rotate_node->right_child));
    new_root->height=1+max(get_height_songs(new_root->left_child),get_height_songs(new_root->right_child));
    return new_root;
}

Songs_Node_AVL* rotate_left_right_songs(Songs_Node_AVL* rotate_node)
{
    rotate_node->left_child=rotate_left_songs(rotate_node->left_child);
    return rotate_right_songs(rotate_node);
}

Songs_Node_AVL* rotate_right_left_songs(Songs_Node_AVL* rotate_node)
{
    rotate_node->right_child=rotate_right_songs(rotate_node->right_child);
    return rotate_left_songs(rotate_node);
}

int get_balance_factor_songs(Songs_Node_AVL* node)
{
    if(node==NULL)
    {
        return 0;
    }
    else
    {
        return get_height_songs(node->left_child)-get_height_songs(node->right_child);
    }
}

History_Node_AVL* rotate_right_history(History_Node_AVL* rotate_node)
{
    History_Node_AVL* new_root=rotate_node->left_child;
    rotate_node->left_child=new_root->right_child;
    new_root->right_child=rotate_node;
    rotate_node->height_history=1+max(get_height_history(rotate_node->left_child),get_height_history(rotate_node->right_child));
    new_root->height_history=1+max(get_height_history(new_root->left_child),get_height_history(new_root->right_child));
    return new_root;
}

History_Node_AVL* rotate_left_history(History_Node_AVL* rotate_node)
{
    History_Node_AVL* new_root=rotate_node->right_child;
    rotate_node->right_child=new_root->left_child;
    new_root->left_child=rotate_node;
    rotate_node->height_history=1+max(get_height_history(rotate_node->left_child),get_height_history(rotate_node->right_child));
    new_root->height_history=1+max(get_height_history(new_root->left_child),get_height_history(new_root->right_child));
    return new_root;
}

History_Node_AVL* rotate_left_right_history(History_Node_AVL* rotate_node)
{
    rotate_node->left_child=rotate_left_history(rotate_node->left_child);
    return rotate_right_history(rotate_node);
}

History_Node_AVL* rotate_right_left_history(History_Node_AVL* rotate_node)
{
    rotate_node->right_child=rotate_right_history(rotate_node->right_child);
    return rotate_left_history(rotate_node);
}

int get_balance_factor_history(History_Node_AVL* node)
{
    if(node==NULL)
    {
        return 0;
    }
    else
    {
        return get_height_history(node->left_child)-get_height_history(node->right_child);
    }
}

Songs_Node_AVL* insert_songs(Songs_Node_AVL* root, int s_id,char t_arr[],char a_arr[])
{
    if(root==NULL)
    {
        return create_song(s_id,t_arr,a_arr);
    }
    else if(s_id<root->Song_id)
    {
        root->left_child=insert_songs(root->left_child,s_id,t_arr,a_arr);
    }
    else if(s_id>root->Song_id)
    {
        root->right_child=insert_songs(root->right_child,s_id,t_arr,a_arr);
    }
    else
    {
        return root;
    }
    root->height=1+max(get_height_songs(root->left_child),get_height_songs(root->right_child));
    int balance_factor=get_balance_factor_songs(root);
    if(balance_factor>1 && s_id<root->left_child->Song_id)
    {
        return rotate_right_songs(root);
    }
    if(balance_factor<-1 && s_id>root->right_child->Song_id)
    {
        return rotate_left_songs(root);
    }
    if(balance_factor>1 && s_id>root->left_child->Song_id)
    {
        return rotate_left_right_songs(root);
    }
    if(balance_factor<-1 && s_id<root->right_child->Song_id)
    {
        return rotate_right_left_songs(root);
    }
    return root;
}

History_Node_AVL* insert_history(History_Node_AVL* root, Songs_Node_AVL* song,int current_time)
{
    
    if(root==NULL)
    {
        History_Node_AVL* new_node=create_history_node(song,current_time);
        return new_node;
    }
    else if(current_time<root->time_stamp)
    {
        root->left_child=insert_history(root->left_child,song,current_time);
    }
    else
    {
        root->right_child=insert_history(root->right_child,song,current_time);
    }
    root->height_history=1+max(get_height_history(root->left_child),get_height_history(root->right_child));
    int balance_factor=get_balance_factor_history(root);
    if(balance_factor>1 && current_time<root->left_child->time_stamp)
    {
        return rotate_right_history(root);
    }
    if(balance_factor<-1 && current_time>root->right_child->time_stamp)
    {
        return rotate_left_history(root);
    }
    if(balance_factor>1 && current_time>root->left_child->time_stamp)
    {
        return rotate_left_right_history(root);     
    }
    if(balance_factor<-1 && current_time<root->right_child->time_stamp)
    {
        return rotate_right_left_history(root);
    }
    return root;
}

void add_to_history(History_AVL* history,Songs_Node_AVL* song_to_insert)
{
    history->History_Root=insert_history(history->History_Root,song_to_insert,history->current_time);
    history->current_time++;
}

void add_songs(Playlist_AVL* playlist, int s_id, char t_arr[],char a_arr[])
{
    if(search_id(playlist->Playlist_Root,s_id) != NULL)
    {
        printf("Duplicate Song ID %d , this song won't be added to the playlist.\n",s_id);
        return;
    }
    playlist->Playlist_Root=insert_songs(playlist->Playlist_Root,s_id,t_arr,a_arr);
    printf("Song added to Playlist successfully.\n");
}

int check_ignore(char a[], char b[])
{
    // function to compare strings without consdering case senstivity
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        char c1 = a[i];
        char c2 = b[i];
        if (c1 >= 'A' && c1 <= 'Z')
        {
            c1 = c1 - 'A' + 'a';
        }
        if (c2 >= 'A' && c2 <= 'Z')
        {
            c2 = c2 - 'A' + 'a';
        }
        if (c1 < c2)
        {
            return -1;
        }
        else if (c1 > c2)
        {
            return 1; // a is lexicographically greater than b
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0')
    {
        return 0; // both strings are equal
    }
    else if (a[i] == '\0' && b[i] != '\0')
    {
        return -1; // a is lexicographically smaller than b
    }
    else
    {
        return 1;
    }
}

int contains_ignore(char str[], char pattern[])
{
    int i = 0;

    while (str[i] != '\0')
    {
        int j = 0;

        while (str[i + j] != '\0' && pattern[j] != '\0')
        {
            char c1 = str[i + j];
            char c2 = pattern[j];

            if (c1 >= 'A' && c1 <= 'Z')
                c1 = c1 - 'A' + 'a';
            if (c2 >= 'A' && c2 <= 'Z')
                c2 = c2 - 'A' + 'a';

            if (c1 != c2)
                break;

            j++;
        }

        if (pattern[j] == '\0')
            return 1; // found

        i++;
    }

    return 0; // not found
}

int count_nodes(Songs_Node_AVL* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else{
        return 1+count_nodes(root->left_child)+count_nodes(root->right_child);
    }
}

void populate_playlist(Songs_Node_AVL* root, Songs_Node_AVL* Nodes_arr[],int *index)
{
    if(root!=NULL)
    {
        populate_playlist(root->left_child,Nodes_arr,index);
        Nodes_arr[*index]=root;
        (*index)++;
        populate_playlist(root->right_child,Nodes_arr,index);
    }
}

void display_inorder(Songs_Node_AVL* root)
{
    if(root!=NULL)
    {
        display_inorder(root->left_child);
        printf("-------------------------------------\n");
        printf("Song ID: %d\n",root->Song_id);
        printf("Title: %s\n",root->Title);
        printf("Artist: %s\n",root->Artist);
        printf("Height: %d\n",root->height);
        printf("Balance Factor: %d\n",get_balance_factor_songs(root));
        printf("-------------------------------------\n");
        display_inorder(root->right_child);
    }
}

void display_playlist_id(Playlist_AVL* playlist)
{
    if(playlist->Playlist_Root==NULL)
    {
        printf("Playlist is empty.\n");
        return;
    }
    printf("Here is the playlist of songs sorted by Their IDs:\n");
    display_inorder(playlist->Playlist_Root);
}

void display_BY_input(Playlist_AVL* playlist,int choice_sort)
{
    //0 for id ,1 for title, 2 for artist , 3 for artist + title
    int count=0;
    if(playlist->Playlist_Root==NULL)
    {
        printf("The playlist is empty!.\n");
        return;
    }
    //counting nodes in playlist
    count=count_nodes(playlist->Playlist_Root);
    Songs_Node_AVL* Nodes_arr[count];
    //populating the array with nodes of playlist
    int index=0;
    populate_playlist(playlist->Playlist_Root,Nodes_arr,&index);
    if(choice_sort==0)
    {
        //call inorder traversal to display songs sorted by id
        printf("Here is The playlist of songs sorted by Their IDs:\n");
        display_inorder(playlist->Playlist_Root);;
    }
    else if (choice_sort == 1)
    {
        for (int i = 1; i < count; i++)
        {
            // sorting The array using insertion sort based on artist name
            Songs_Node_AVL *key = Nodes_arr[i];
            int j = i - 1;
            while (j >= 0 && (check_ignore(Nodes_arr[j]->Title, key->Title) > 0))
            {
                Nodes_arr[j + 1] = Nodes_arr[j];
                j--;
            }
            Nodes_arr[j + 1] = key;
        }
        printf("Here is The playlist of songs sorted by Their Titles:\n");
        for (int i = 0; i < count; i++)
        {
            printf("-------------------------------------\n");
            printf("Song ID: %d\n", Nodes_arr[i]->Song_id);
            printf("Title: %s\n", Nodes_arr[i]->Title);
            printf("Artist: %s\n", Nodes_arr[i]->Artist);
            printf("Height: %d\n", Nodes_arr[i]->height);
            printf("Balance Factor: %d\n", get_balance_factor_songs(Nodes_arr[i]));
            printf("-------------------------------------\n");
        }
    }
    else if (choice_sort == 2)
    {
        for (int i = 1; i < count; i++)
        {
            // sorting The array using insertion sort based on artist name
            Songs_Node_AVL *key = Nodes_arr[i];
            int j = i - 1;
            while (j >= 0 && (check_ignore(Nodes_arr[j]->Artist, key->Artist) > 0))
            {
                Nodes_arr[j + 1] = Nodes_arr[j];
                j--;
            }
            Nodes_arr[j + 1] = key;
        }
        printf("Here is The playlist of songs sorted by Their Artists:\n");
        for (int i = 0; i < count; i++)
        {
            printf("-------------------------------------\n");
            printf("Song ID: %d\n", Nodes_arr[i]->Song_id);
            printf("Title: %s\n", Nodes_arr[i]->Title);
            printf("Artist: %s\n", Nodes_arr[i]->Artist);
            printf("Height: %d\n", Nodes_arr[i]->height);
            printf("Balance Factor: %d\n", get_balance_factor_songs(Nodes_arr[i]));
            printf("-------------------------------------\n");
        }
    }
    else if (choice_sort == 3)
    {
        for (int i = 1; i < count; i++)
        {
            Songs_Node_AVL *key = Nodes_arr[i];
            int j = i - 1;
            while (j >= 0)
            {
                int compare_artist = check_ignore(Nodes_arr[j]->Artist, key->Artist);
                if (compare_artist > 0 || (compare_artist == 0 && (check_ignore(Nodes_arr[j]->Title, key->Title) > 0)))
                {
                    Nodes_arr[j + 1] = Nodes_arr[j];
                    j--;
                }
                else
                {
                    break;
                }
            }
            Nodes_arr[j + 1] = key;
        }
        printf("Here is The playlist of songs sorted first by Their Artists,Then by Their Titles:\n");
        for (int i = 0; i < count; i++)
        {
            printf("-------------------------------------\n");
            printf("Song ID: %d\n", Nodes_arr[i]->Song_id);
            printf("Title: %s\n", Nodes_arr[i]->Title);
            printf("Artist: %s\n", Nodes_arr[i]->Artist);
            printf("Height: %d\n", Nodes_arr[i]->height);
            printf("Balance Factor: %d\n", get_balance_factor_songs(Nodes_arr[i]));
            printf("-------------------------------------\n");
        }
    }
}

Songs_Node_AVL* search_id(Songs_Node_AVL* node, int id)
{
    if(!node)
    {
        return NULL;
    }
    if(id<node->Song_id)
    {
        return search_id(node->left_child,id);
    }
    else if(id>node->Song_id)
    {
        return search_id(node->right_child,id);
    }
    else
    {
        return node;
    }
}

void search_artist(Songs_Node_AVL* root, char search_arr[],int add_history,History_AVL* rh,int* song_found)
{
    if (root == NULL)
    {
        return;
    }
    search_artist(root->left_child, search_arr, add_history, rh,song_found);
    if (contains_ignore(root->Artist, search_arr) == 1)
    {
        (*song_found)++;
        printf("-------------------------------------\n");
        printf("Song ID: %d\n", root->Song_id);
        printf("Title: %s\n", root->Title);
        printf("Artist: %s\n", root->Artist);
        printf("Height: %d\n", root->height);
        printf("Balance Factor: %d\n", get_balance_factor_songs(root));
        printf("-------------------------------------\n");
        if(add_history && rh!=NULL)
        {
            add_to_history(rh,root);
        }
    }
    search_artist(root->right_child, search_arr, add_history, rh,song_found);
}

void search_title(Songs_Node_AVL *root, char search_arr[], int add_history, History_AVL *rh, int *song_found)
{
    if (root == NULL)
    {
        return;
    }
    search_title(root->left_child, search_arr, add_history, rh, song_found);
    if (contains_ignore(root->Title, search_arr) == 1)
    {
        (*song_found)++;
        printf("-------------------------------------\n");
        printf("Song ID: %d\n", root->Song_id);
        printf("Title: %s\n", root->Title);
        printf("Artist: %s\n", root->Artist);
        printf("Height: %d\n", root->height);
        printf("Balance Factor: %d\n", get_balance_factor_songs(root));
        printf("-------------------------------------\n");
        if (add_history && rh != NULL)
        {
            add_to_history(rh, root);
        }
    }
    search_title(root->right_child, search_arr, add_history, rh, song_found);
}

void search_BY_input(Playlist_AVL *playlist, int search_choice, char search_query[])
{
    // 1 for id , 2 for artist, 3 for title
    if (playlist == NULL || playlist->Playlist_Root == NULL )
    {
        printf("PLaylist is empty.\n");
        return;
    }
    int song_found = 0;
    if (search_choice == 1)
    {
        int s_id = atoi(search_query);
        Songs_Node_AVL *search_result = NULL;
        search_result = search_id(playlist->Playlist_Root, s_id);
        if (!search_result)
        {
            printf("The song with ID %d doesn't exist in the playlist.\n", s_id);
        }
        else
        {
            printf("The song with ID %d exists in the playlist.\n", s_id);
            printf("Here the details of the song.\n");
            printf("----------------------------------------\n");
            printf("Song ID: %d\n", search_result->Song_id);
            printf("Title: %s\n", search_result->Title);
            printf("Artist: %s\n", search_result->Artist);
            printf("Height: %d\n", search_result->height);
            printf("Balance Factor: %d\n", get_balance_factor_songs(search_result));
            printf("----------------------------------------\n");
        }
    }
    else if (search_choice == 2)
    {
        printf("Here are the songs that match the search query \"%s\" in their artist:\n", search_query);
        search_artist(playlist->Playlist_Root, search_query, 0, NULL, &song_found);
    }
    else if (search_choice == 3)
    {
        printf("Here are the songs that match the search query \"%s\" in their title:\n", search_query);
        search_title(playlist->Playlist_Root, search_query, 0, NULL, &song_found);
    }
}

void print_play_song_all(Songs_Node_AVL *root, History_AVL *rh)
{
    if (root != NULL)
    {
        print_play_song_all(root->left_child, rh);
        printf("Now playing:\n");
        printf("-------------------------------------\n");
        printf("Song ID: %d\n", root->Song_id);
        printf("Title: %s\n", root->Title);
        printf("Artist: %s\n", root->Artist);
        printf("-------------------------------------\n");
        add_to_history(rh, root);
        print_play_song_all(root->right_child, rh);
    }
}

void play_wrapper(Playlist_AVL *playlist, History_AVL *history, int play_choice)
{
    // 1 play all songs in playlist , 2 play a specific song by id, 3 play songs by artist, 4 play songs by title
    if (!playlist || playlist->Playlist_Root == NULL)
    {
        printf("The playlist is empty!.\n");
        return;
    }
    if (!history)
    {
        printf("History is not initialised!.\n");
        return;
    }
    if (play_choice == 1)
    {
        int repeat_YN = 1;
        while (repeat_YN == 1)
        {
            printf("Playing the playlist...\n");
            print_play_song_all(playlist->Playlist_Root, history);
            printf("Wanna repeat again?(1.YES  2.NO)\n");
            while (1)
            {
                if (!read_int(&repeat_YN))
                {
                    printf("Please enter a valid choice.\n");
                    continue;
                }
                if (repeat_YN == 1 || repeat_YN == 2)
                {
                    break;
                }
                printf("Wanna repeat again?(1.YES  2.NO)\n");
            }
        }
    }
    else if (play_choice == 2)
    {
        int repeat_YN = 1;
        while (repeat_YN == 1)
        {
            printf("Please enter the ID of the song you want to play.\n");
            int search_ids;
            while (!read_int(&search_ids))
            {
                printf("Please enter a valid ID.\n");
            }
            Songs_Node_AVL *search_result = search_id(playlist->Playlist_Root, search_ids);
            if (!search_result)
            {
                printf("The song with ID %d doesn't exist in the playlist.\n", search_ids);
            }
            else
            {
                printf("Now playing:\n");
                printf("-------------------------------------\n");
                printf("Song ID: %d\n", search_result->Song_id);
                printf("Title: %s\n", search_result->Title);
                printf("Artist: %s\n", search_result->Artist);
                printf("-------------------------------------\n");
                add_to_history(history, search_result);
            }
            printf("Wanna play another song by ID?(1.YES  2.NO)\n");
            while (1)
            {
                if (!read_int(&repeat_YN))
                {
                    printf("Please enter a valid choice.\n");
                    continue;
                }
                if (repeat_YN == 1 || repeat_YN == 2)
                {
                    break;
                }
                printf("Wanna play another song by ID?(1.YES  2.NO)\n");
            }
        }
    }
    else if (play_choice == 3)
    {
        int repeat_YN = 1;
        while (repeat_YN == 1)
        {
            int song_found = 0;
            printf("Please enter the Artist name or a part of it to search for songs to play.\n");
            char search_artist_arr[MAX_LENGTH_NAME];
            scanf(" %99[^\n]", search_artist_arr);
            printf("Now playing songs that match the search query \"%s\" in their artist:\n", search_artist_arr);
            search_artist(playlist->Playlist_Root, search_artist_arr, 1, history, &song_found);
            if (!song_found)
            {
                printf("No songs found that match the search query \"%s\" in their artist.\n", search_artist_arr);
            }
            printf("Wanna play another song by Artist name?(1.YES  2.NO)\n");
            while (1)
            {
                if (!read_int(&repeat_YN))
                {
                    printf("Please enter a valid choice.\n");
                    continue;
                }
                if (repeat_YN == 1 || repeat_YN == 2)
                {
                    break;
                }
                printf("Wanna play another song by Artist name?(1.YES  2.NO)\n");
            }
        }
    }
    else if (play_choice == 4)
    {
        int repeat_YN = 1;
        while (repeat_YN == 1)
        {
            int song_found = 0;
            printf("Please enter the Title name or a part of it to search for songs to play.\n");
            char search_title_arr[MAX_LENGTH_NAME];
            scanf(" %99[^\n]", search_title_arr);
            printf("Now playing songs that match the search query \"%s\" in their title:\n", search_title_arr);
            search_title(playlist->Playlist_Root, search_title_arr, 1, history, &song_found);
            if (!song_found)
            {
                printf("No songs found that match the search query \"%s\" in their title.\n", search_title_arr);
            }
            printf("Wanna play another song by Title name?(1.YES  2.NO)\n");
            while (1)
            {
                if (!read_int(&repeat_YN))
                {
                    printf("Please enter a valid choice.\n");
                    continue;
                }
                if (repeat_YN == 1 || repeat_YN == 2)
                {
                    break;
                }
                printf("Wanna play another song by Title name? (1.YES  2.NO)\n");
            }
        }
    }
}

void play_one_song_random(Playlist_AVL *playlist, History_AVL *history, int Total_songs) //
{
    if (!playlist || playlist->Playlist_Root == NULL)
    {
        printf("The playlist is empty!.\n");
        return;
    }
    if (!history)
    {
        printf("History is not initialised!.\n");
        return;
    }
    Songs_Node_AVL *Nodes_arr[Total_songs];
    int index = 0;
    populate_playlist(playlist->Playlist_Root, Nodes_arr, &index);
    int random_index = rand() % Total_songs;
    Songs_Node_AVL *random_song = Nodes_arr[random_index];
    printf("Now playing a random song:\n");
    printf("-------------------------------------\n");
    printf("Song ID: %d\n", random_song->Song_id);
    printf("Title: %s\n", random_song->Title);
    printf("Artist: %s\n", random_song->Artist);
    printf("Index in playlist: %d\n", random_index + 1);
    printf("-------------------------------------\n");
    add_to_history(history, random_song);
}

void shuffle_playlist(Playlist_AVL *playlist, History_AVL *history, int Total_songs)
{
    if (!playlist || playlist->Playlist_Root == NULL)
    {
        printf("The playlist is empty!.\n");
        return;
    }
    if (!history)
    {
        printf("History is not initialised!.\n");
        return;
    }
    if(Total_songs<=1)
    {
        printf("Not enough songs in the playlist to shuffle.\n");
        return;
    }

    Songs_Node_AVL *Nodes_arr[Total_songs];
    int index = 0;
    populate_playlist(playlist->Playlist_Root, Nodes_arr, &index);
    // Shuffle the array using Fisher-Yates algorithm
    for (int i = Total_songs - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Songs_Node_AVL *temp = Nodes_arr[i];
        Nodes_arr[i] = Nodes_arr[j];
        Nodes_arr[j] = temp;
    }
    printf("Playing the shuffled playlist...\n");
    for (int i = 0; i < Total_songs; i++)
    {
        printf("Now playing(shuffle %d / %d ):\n",i+1,Total_songs);
        printf("-------------------------------------\n");
        printf("Song ID: %d\n", Nodes_arr[i]->Song_id);
        printf("Title: %s\n", Nodes_arr[i]->Title);
        printf("Artist: %s\n", Nodes_arr[i]->Artist);
        printf("-------------------------------------\n");
        add_to_history(history, Nodes_arr[i]);
    }
}

void shuffle_wrapper(Playlist_AVL *playlist, History_AVL *history, int shuffle_choice)
{
    // 1 for play one song random , 2 for shuffle entire playlist
    if (playlist == NULL || playlist->Playlist_Root == NULL)
    {
        printf("The playlist is empty!.\n");
        return;
    }
    if (!history)
    {
        printf("History is not initialised!.\n");
        return;
    }

    if (shuffle_choice == 1)
    {
        int repeat_YN = 1;
        while (repeat_YN == 1)
        {
            int total_songs = count_nodes(playlist->Playlist_Root);
            play_one_song_random(playlist, history, total_songs);
            printf("Wanna play another random song?(1.YES  2.NO)\n");
            while (1)
            {
                if (!read_int(&repeat_YN))
                {
                    printf("Please enter a valid choice.\n");
                    continue;
                }
                if (repeat_YN == 1 || repeat_YN == 2)
                {
                    break;
                }
                printf("Wanna play another random song?(1.YES  2.NO)\n");
            }
        }
    }
    else if (shuffle_choice == 2)
    {
        int repeat_YN = 1;
        while (repeat_YN == 1)
        {
            int total_songs = count_nodes(playlist->Playlist_Root);
            shuffle_playlist(playlist, history, total_songs);
            printf("Wanna shuffle and play the playlist again?(1.YES  2.NO)\n");
            while (1)
            {
                if (!read_int(&repeat_YN))
                {
                    printf("Please enter a valid choice.\n");
                    continue;
                }
                if (repeat_YN == 1 || repeat_YN == 2)
                {
                    break;
                }
                printf("Wanna shuffle and play the playlist again?(1.YES  2.NO)\n");
            }
        }
    }
}

//passing arugment will be node_to delete->right_child in case of 2 children
Songs_Node_AVL* find_successor(Songs_Node_AVL* node)
{
    Songs_Node_AVL* current_node=node;
    while(current_node && current_node->left_child!=NULL)
    {
        current_node=current_node->left_child;
    }
    return current_node;

}

Songs_Node_AVL* delete_song(Songs_Node_AVL* root,int delete_key)
{
    if(root==NULL)
    {
        return NULL;
    }

    if(delete_key>root->Song_id)
    {
        root->right_child=delete_song(root->right_child,delete_key);
    }
    else if(delete_key<root->Song_id)
    {
        root->left_child=delete_song(root->left_child,delete_key);
    }
    else
    {
        if(root->left_child==NULL || root->right_child==NULL)
        {
            Songs_Node_AVL* temp_node=root->left_child ? root->left_child: root->right_child;
            if(temp_node==NULL)
            {
                temp_node=root;
                root=NULL;
            }
            else 
            {
                *root = *temp_node;
            }
            free(temp_node);
        }

        else
        {
            Songs_Node_AVL *successor = find_successor(root->right_child);
            root->Song_id = successor->Song_id;
            strncpy(root->Title, successor->Title, MAX_LENGTH_NAME - 1);
            root->Title[MAX_LENGTH_NAME - 1] = '\0';
            strncpy(root->Artist, successor->Artist, MAX_LENGTH_NAME - 1);
            root->Artist[MAX_LENGTH_NAME - 1] = '\0';
            root->right_child = delete_song(root->right_child, successor->Song_id);
        }
        if(root==NULL)
        {
            return root;
        }
        root->height=1+max(get_height_songs(root->left_child),get_height_songs(root->right_child));
        int balance_factor=get_balance_factor_songs(root);
        if(balance_factor>1 && get_balance_factor_songs(root->left_child)>=0)
        {
            return rotate_right_songs(root);
        }
        else if (balance_factor>1 && get_balance_factor_songs(root->left_child)<0)
        {
            return rotate_left_right_songs(root);
        }
        else if (balance_factor<-1 && get_balance_factor_songs(root->right_child)<=0)
        {
            return rotate_left_songs(root);
        }
        else if (balance_factor<-1 && get_balance_factor_songs(root->right_child)>0)
        {
            return rotate_right_left_songs(root);
        }
        
    }
    return root;
}

void delete_song_wrapper(Playlist_AVL* playlist, int delete_id)
{
    if (!playlist || !playlist->Playlist_Root)
    {
        printf("The playlist is empty!\n");
        return;
    }

    Songs_Node_AVL* node = search_id(playlist->Playlist_Root, delete_id);
    if (!node)
    {
        printf("The song with ID %d doesn't exist in the playlist.\n", delete_id);
        return;
    }

    playlist->Playlist_Root = delete_song(playlist->Playlist_Root, delete_id);

    printf("Song with ID %d deleted successfully.\n", delete_id);
}

void display_history_new_first(History_Node_AVL* root)
{
    if(root!=NULL)
    {
        display_history_new_first(root->left_child);
        printf("-------------------------------------\n");
        printf("Song ID: %d\n",root->Song_id);
        printf("Title: %s\n",root->Title);
        printf("Artist: %s\n",root->Artist);
        printf("Time Stamp: %d\n",root->time_stamp);
        printf("Height: %d\n",root->height_history);
        printf("Balance Factor: %d\n",get_balance_factor_history(root));
        printf("-------------------------------------\n");
        display_history_new_first(root->right_child);
    }
}

void display_history_old_first(History_Node_AVL* root)
{
    if(root!=NULL)
    {
        display_history_old_first(root->right_child);
        printf("-------------------------------------\n");
        printf("Song ID: %d\n",root->Song_id);
        printf("Title: %s\n",root->Title);
        printf("Artist: %s\n",root->Artist);
        printf("Time Stamp: %d\n",root->time_stamp);
        printf("Height: %d\n",root->height_history);
        printf("Balance Factor: %d\n",get_balance_factor_history(root));
        printf("-------------------------------------\n");
        display_history_old_first(root->left_child);

    }
}

void display_history_wrapper(History_AVL* history,int display_choice)
{
    // 1 for new first , 2 for old first
    if(history==NULL || history->History_Root==NULL)
    {
        printf("History is empty!.\n");
        return;
    }
    if(display_choice==1)
    {
        printf("------------Played Recently------------\n");
        display_history_new_first(history->History_Root);
    }
    else if(display_choice==2)
    {
        printf("------------Oldest Played Songs------------\n");
        display_history_old_first(history->History_Root);
    }
}

void union_helper(Songs_Node_AVL** A_nodes,Songs_Node_AVL** B_nodes,int count_A,int count_B,Songs_Node_AVL** result_nodes,int* result_index)
{
   int i=0,j=0;
   while(i<count_A && j<count_B)
   {
    if(A_nodes[i]->Song_id<B_nodes[j]->Song_id)
    {
        result_nodes[*result_index]=A_nodes[i];
        (*result_index)++;
        i++;
    }
    else if(A_nodes[i]->Song_id>B_nodes[j]->Song_id)
    {
        result_nodes[*result_index]=B_nodes[j];
        (*result_index)++;
        j++;
    }
    else
    {
        result_nodes[*result_index]=A_nodes[i];
        (*result_index)++;
        i++;
        j++;
    }
   }
   while(i<count_A)
   {
    result_nodes[*result_index]=A_nodes[i];
    (*result_index)++;
    i++;
   }
   while(j<count_B)
   {
    result_nodes[*result_index]=B_nodes[j];
    (*result_index)++;
    j++;
   }
}

void intersection_helper(Songs_Node_AVL** A_nodes,Songs_Node_AVL** B_nodes,int count_A,int count_B,Songs_Node_AVL** result_nodes,int* result_index)
{
    int i=0,j=0;
    while(i<count_A && j<count_B)
    {
        if(A_nodes[i]->Song_id<B_nodes[j]->Song_id)
        {
            i++;
        }
        else if(A_nodes[i]->Song_id>B_nodes[j]->Song_id)
        {
            j++;
        }
        else
        {
            result_nodes[*result_index]=A_nodes[i];
            (*result_index)++;
            i++;
            j++;
        }
    }
}

void difference_helper(Songs_Node_AVL** A_nodes,Songs_Node_AVL** B_nodes,int count_A,int count_B,Songs_Node_AVL** result_nodes,int* result_index)
{
    int i=0,j=0;
    while(i<count_A && j<count_B)
    {
        if(A_nodes[i]->Song_id<B_nodes[j]->Song_id)
        {
            result_nodes[*result_index]=A_nodes[i];
            (*result_index)++;
            i++;
        }
        else if(A_nodes[i]->Song_id>B_nodes[j]->Song_id)
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }
    while(i<count_A)
    {
        result_nodes[*result_index]=A_nodes[i];
        (*result_index)++;
        i++;
    }
}

void sym_difference_helper(Songs_Node_AVL** A_nodes,Songs_Node_AVL** B_nodes,int count_A,int count_B,Songs_Node_AVL** result_nodes,int* result_index)
{
    int i=0,j=0;
    while(i<count_A && j<count_B)
    {
        if(A_nodes[i]->Song_id<B_nodes[j]->Song_id)
        {
            result_nodes[*result_index]=A_nodes[i];
            (*result_index)++;
            i++;
        }
        else if(A_nodes[i]->Song_id>B_nodes[j]->Song_id)
        {
            result_nodes[*result_index]=B_nodes[j];
            (*result_index)++;
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }
    while(i<count_A)
    {
        result_nodes[*result_index]=A_nodes[i];
        (*result_index)++;
        i++;
    }
    while(j<count_B)
    {
        result_nodes[*result_index]=B_nodes[j];
        (*result_index)++;
        j++;
    }
}

void display_set_operations(Songs_Node_AVL** result_nodes,int result_count)
{
    if(result_count==0)
    {
        printf("No songs found in the resulting set.\n");
        return;
    }
    for(int i=0;i<result_count;i++)
    {
        printf("-------------------------------------\n");
        printf("Song ID: %d\n",result_nodes[i]->Song_id);
        printf("Title: %s\n",result_nodes[i]->Title);
        printf("Artist: %s\n",result_nodes[i]->Artist);
        printf("Height: %d\n",result_nodes[i]->height);
        printf("Balance Factor: %d\n",get_balance_factor_songs(result_nodes[i]));
        printf("-------------------------------------\n");
    }
}

void set_operations(Playlist_AVL* A_playlist, Playlist_AVL* B_playlist,int set_choice)
{
    if (!A_playlist || !B_playlist)
    {
        printf("One or both playlists are not initialized.\n");
        return;
    }
    if (!A_playlist->Playlist_Root || !B_playlist->Playlist_Root)
    {
        printf("One or both playlists are empty.\n");
        return;
    }

    int count_A = count_nodes(A_playlist->Playlist_Root);
    int count_B = count_nodes(B_playlist->Playlist_Root);

    Songs_Node_AVL* A_nodes[count_A];
    Songs_Node_AVL* B_nodes[count_B];

    int index_A = 0, index_B = 0;
    populate_playlist(A_playlist->Playlist_Root, A_nodes, &index_A);
    populate_playlist(B_playlist->Playlist_Root, B_nodes, &index_B);
    Songs_Node_AVL* result_nodes[count_A + count_B];
    int result_index = 0;
    if (set_choice == 1)
    {
        union_helper(A_nodes, B_nodes, count_A, count_B, result_nodes, &result_index);
        printf("Total songs in the resulting set: %d\n", result_index);
        printf("Union of the two playlists:\n");
    }
    else if (set_choice == 2)
    {
        intersection_helper(A_nodes, B_nodes, count_A, count_B, result_nodes, &result_index);
        printf("Total songs in the resulting set: %d\n", result_index);
        printf("Intersection of the two playlists:\n");
    }
    else if (set_choice == 3)
    {
        difference_helper(A_nodes, B_nodes, count_A, count_B, result_nodes, &result_index);
        printf("Total songs in the resulting set: %d\n", result_index);
        printf("Difference of Playlist A from Playlist B (A - B):\n");
    }
    else if (set_choice == 4)
    {
        sym_difference_helper(A_nodes, B_nodes, count_A, count_B, result_nodes, &result_index);
        printf("Total songs in the resulting set: %d\n", result_index);
        printf("Symmetric Difference of the two playlists:\n");
    }
    
    display_set_operations(result_nodes, result_index);
}

void print_range(Songs_Node_AVL* root, int high,int low)
{
    if(root==NULL)
    {
        return;
    }   
    if(root->Song_id>low)
    {
        print_range(root->left_child,high,low);
    }
    if(root->Song_id>=low && root->Song_id<=high)
    {
        printf("-------------------------------------\n");
        printf("Song ID: %d\n",root->Song_id);
        printf("Title: %s\n",root->Title);
        printf("Artist: %s\n",root->Artist);
        printf("Height: %d\n",root->height);
        printf("Balance Factor: %d\n",get_balance_factor_songs(root));
        printf("-------------------------------------\n");
    }
    if(root->Song_id<high)
    {
        print_range(root->right_child,high,low);
    }
}

void range_query_wrapper(Playlist_AVL* playlist,int low,int high)
{
    if(playlist==NULL || playlist->Playlist_Root==NULL)
    {
        printf("The playlist is empty!.\n");
        return;
    }
    if(low>high)
    {
        printf("Invalid range. Low should be less than or equal to High.\n");
        return;
    }
    printf("Songs with IDs in the range [%d, %d]:\n", low, high);
    print_range(playlist->Playlist_Root, high, low);
}

void delete_playlist(Songs_Node_AVL* root)
{
    if(root!=NULL)
    {
        delete_playlist(root->left_child);
        delete_playlist(root->right_child);
        free(root);
    }
}

void delete_history(History_Node_AVL* root)
{
    if(root!=NULL)
    {
        delete_history(root->left_child);
        delete_history(root->right_child);
        free(root);
    }
}