#ifndef PLAYLISTAVL_H
#define PLAYLISTAVL_H

// ----------- STANDARD LIBRARIES -----------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ----------- MACROS -----------//
#define MAX_LENGTH_NAME 100

// ----------- STRUCTURES -----------//

// Song AVL Node //
typedef struct Songs_Node_AVL
{
    int Song_id;
    char Title[MAX_LENGTH_NAME];
    char Artist[MAX_LENGTH_NAME];

    int height;
    struct Songs_Node_AVL* left_child;
    struct Songs_Node_AVL* right_child;

} Songs_Node_AVL;

// History AVL Node//
typedef struct History_Node_AVL
{
    int Song_id;
    char Title[MAX_LENGTH_NAME];
    char Artist[MAX_LENGTH_NAME];

    int time_stamp;
    int height_history;

    struct History_Node_AVL* left_child;
    struct History_Node_AVL* right_child;

} History_Node_AVL;

// Playlist //
typedef struct
{
    Songs_Node_AVL* Playlist_Root;
} Playlist_AVL;

// History //
typedef struct
{
    History_Node_AVL* History_Root;
    int current_time;
} History_AVL;

// ----------- INITIALIZATION -----------//
void initialise_Playlist(Playlist_AVL* root);
void initialise_History(History_AVL* root);

// ----------- NODE CREATION -----------//
Songs_Node_AVL* create_song(int s_id, char t_arr[], char a_arr[]);
History_Node_AVL* create_history_node(Songs_Node_AVL* song, int current_time);

// ----------- UTILITIES -----------//
int max(int a, int b);
int get_height_songs(Songs_Node_AVL* node);
int get_height_history(History_Node_AVL* node);
int get_balance_factor_songs(Songs_Node_AVL* node);
int get_balance_factor_history(History_Node_AVL* node);

int read_int(int *x);
int read_choice(int *x, int min, int max);

int check_ignore(char a[], char b[]);
int contains_ignore(char str[], char pattern[]);

// ----------- ROTATIONS (SONGS AVL) -----------//
Songs_Node_AVL* rotate_right_songs(Songs_Node_AVL* rotate_node);
Songs_Node_AVL* rotate_left_songs(Songs_Node_AVL* rotate_node);
Songs_Node_AVL* rotate_left_right_songs(Songs_Node_AVL* rotate_node);
Songs_Node_AVL* rotate_right_left_songs(Songs_Node_AVL* rotate_node);

// ----------- ROTATIONS (HISTORY AVL) -----------//
History_Node_AVL* rotate_right_history(History_Node_AVL* rotate_node);
History_Node_AVL* rotate_left_history(History_Node_AVL* rotate_node);
History_Node_AVL* rotate_left_right_history(History_Node_AVL* rotate_node);
History_Node_AVL* rotate_right_left_history(History_Node_AVL* rotate_node);

// ----------- INSERTION -----------//
Songs_Node_AVL* insert_songs(Songs_Node_AVL* root, int s_id, char t_arr[], char a_arr[]);
History_Node_AVL* insert_history(History_Node_AVL* root, Songs_Node_AVL* song, int current_time);

void add_songs(Playlist_AVL* playlist, int s_id, char t_arr[], char a_arr[]);
void add_to_history(History_AVL* history, Songs_Node_AVL* song_to_insert);

// ----------- COUNT & POPULATE -----------//
int count_nodes(Songs_Node_AVL* root);
void populate_playlist(Songs_Node_AVL* root, Songs_Node_AVL* Nodes_arr[], int *index);

// ----------- DISPLAY -----------//
void display_inorder(Songs_Node_AVL* root);
void display_playlist_id(Playlist_AVL* playlist);
void display_BY_input(Playlist_AVL* playlist, int choice_sort);

// ----------- SEARCH -----------//
Songs_Node_AVL* search_id(Songs_Node_AVL* node, int id);
void search_artist(Songs_Node_AVL* root, char search_arr[], int add_history, History_AVL* rh, int* song_found);
void search_title(Songs_Node_AVL* root, char search_arr[], int add_history, History_AVL* rh, int* song_found);
void search_BY_input(Playlist_AVL* playlist, int search_choice, char search_query[]);

// ----------- PLAY FUNCTIONS -----------//
void print_play_song_all(Songs_Node_AVL *root, History_AVL *rh);
void play_wrapper(Playlist_AVL *playlist, History_AVL *history, int play_choice);

// ----------- SHUFFLE -----------//
void play_one_song_random(Playlist_AVL *playlist, History_AVL *history, int Total_songs);
void shuffle_playlist(Playlist_AVL *playlist, History_AVL *history, int Total_songs);
void shuffle_wrapper(Playlist_AVL *playlist, History_AVL *history, int shuffle_choice);

// ----------- DELETE SONG -----------//
Songs_Node_AVL* find_successor(Songs_Node_AVL* node);
Songs_Node_AVL* delete_song(Songs_Node_AVL* root, int delete_key);
void delete_song_wrapper(Playlist_AVL* playlist, int delete_id);

// ----------- HISTORY DISPLAY -----------//
void display_history_new_first(History_Node_AVL* root);
void display_history_old_first(History_Node_AVL* root);
void display_history_wrapper(History_AVL* history, int display_choice);

// ----------- SET OPERATIONS -----------//
void union_helper(Songs_Node_AVL** A_nodes, Songs_Node_AVL** B_nodes, int count_A, int count_B, Songs_Node_AVL** result_nodes, int* result_index);
void intersection_helper(Songs_Node_AVL** A_nodes, Songs_Node_AVL** B_nodes, int count_A, int count_B, Songs_Node_AVL** result_nodes, int* result_index);
void difference_helper(Songs_Node_AVL** A_nodes, Songs_Node_AVL** B_nodes, int count_A, int count_B, Songs_Node_AVL** result_nodes, int* result_index);
void sym_difference_helper(Songs_Node_AVL** A_nodes, Songs_Node_AVL** B_nodes, int count_A, int count_B, Songs_Node_AVL** result_nodes, int* result_index);

void display_set_operations(Songs_Node_AVL** result_nodes, int result_count);
void set_operations(Playlist_AVL* A_playlist, Playlist_AVL* B_playlist, int set_choice);

// ----------- RANGE QUERY -----------//
void print_range(Songs_Node_AVL* root, int high, int low);
void range_query_wrapper(Playlist_AVL* playlist, int low, int high);

// ----------- CLEANUP -----------//
void delete_playlist(Songs_Node_AVL* root);
void delete_history(History_Node_AVL* root);

#endif