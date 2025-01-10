//Jackson Hill - Final Project
//CSCI 2270 - Medha Sharma - Recitation 206
//April 30, 2023

//g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db
//./movie-db IMDB-Movie-Data.csv 1000 1000

#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

/**
 * MovieHashTable - Default Constructor that initializes a new hash table with the default size.
 * The hash table is an array of MovieNode pointers.
 * The number of collisions is initialized to zero.
 * @param None
 * @return None
*/
// Constructor for MovieHashTable with default size
MovieHashTable::MovieHashTable() 
{
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode*[table_size]();
    n_collisions = 0;
}

/**
 * MovieHashTable - Constructor that initializes a new hash table with a given size.
 * The hash table is an array of MovieNode pointers.
 * The number of collisions is initialized to zero.
 * @param s - integer that represents the size of the hash table
 * @return None
*/
// Constructor for MovieHashTable with given size
MovieHashTable::MovieHashTable(int s) 
{
    table_size = s;
    table = new MovieNode*[table_size]();
    n_collisions = 0;
}

/**
 * ~MovieHashTable - Destructor that deletes all nodes in the hash table.
 * The memory allocated for the hash table is also released.
 * @param None
 * @return None
*/
// Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() 
{
    for(int i = 0; i < table_size; i++)
    {
        if(table[i] != nullptr)
        {
            MovieNode* curr = table[i];
            while(curr != nullptr)
            {
                MovieNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }
    delete[] table;
}

/**
 * hash - Hash function that calculates the index in the hash table for a given movie title.
 * The hash function is designed to minimize collisions for the given IMDB-Movie database
 * to ensure efficient insertion and retrieval of movie nodes.
 * @param title - string that represents the title of the movie
 * @return integer that represents the index in the hash table for the given movie title
*/
// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
int MovieHashTable::hash(string title) 
{
    string hash_key = "jahi7479";
    unsigned long hash = 0;

    // Compute the hash value for the "jahi7479" string
    for (char c : hash_key)
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Compute the hash value for the movie title
    for (char c : title)
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % table_size;
}

/**
 * insert - Inserts a movie node into the hash table with the specified title.
 * If the bucket at the calculated index is empty, the node is inserted directly.
 * Otherwise, the node is appended to the end of the linked list at the corresponding bucket.
 * The number of collisions is incremented accordingly.
 * @param title - string that represents the title of the movie
 * @param movie - pointer to the MovieNode to be inserted
 * @return None
*/
// Inserts a movie node into the hash table with the specified title
void MovieHashTable::insert(string title, MovieNode* movie) 
{
    int index = hash(title);
    if(table[index] == nullptr)
    {
        table[index] = movie;
    }
    else
    {
        MovieNode* curr = table[index];
        while(curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = movie;
        n_collisions++;
    }
}

/**
 * search - Searches for a movie node in the hash table with the specified title.
 * If a movie node with the specified title is found, a pointer to the node is returned.
 * Otherwise, nullptr is returned.
 * @param title - string that represents the title of the movie to be searched
 * @return pointer to the MovieNode with the specified title or nullptr if not found
*/
// Searches for a node in the hash table with the specified title
MovieNode* MovieHashTable::search(string title) 
{
    int index = hash(title);
    MovieNode* curr = table[index];
    while(curr != nullptr)
    {
        if(curr->title == title)
        {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

/**
 * getCollisions - Returns the number of collisions that have occurred during insertion into the hash table.
 * @param None
 * @return integer that represents the number of collisions during insertion into the hash table
*/
// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() 
{
    return n_collisions;
}

/**
 * setCollisions - Increments the number of collisions that have occurred during insertion into the hash table.
 * @param None
 * @return None
*/
// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() 
{
    n_collisions++;
}