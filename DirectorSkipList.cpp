//Jackson Hill - Final Project
//CSCI 2270 - Medha Sharma - Recitation 206
//April 30, 2023

//g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db
//./movie-db IMDB-Movie-Data.csv 1000 1000

#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * Constructor for DirectorSkipList with default capacity and levels
*/
// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() 
{
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head = new DirectorSLNode("", levels);
    size = 0;
}

/**
 * Constructor for DirectorSkipList with given capacity and levels
 * @param _capacity - the given capacity
 * @param _levels - the given number of levels
*/
// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _capacity, int _levels) 
{
    capacity = _capacity;
    levels = _levels;
    head = new DirectorSLNode("", levels);
    size = 0;

}

/**
 * Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
*/
// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
DirectorSkipList::~DirectorSkipList() 
{
    DirectorSLNode *current = head;
    while (current != nullptr) 
    {
        DirectorSLNode *nextNode = current->next[0];
        delete current;
        current = nextNode;
    }
}

/**
 * Generates a random level for a new node
 * @param maxLevel - the maximum level
 * @return the new level generated
*/
int randomLevel(int maxLevel) 
{
    int level = 1;
    while (rand() % 2 == 0 && level < maxLevel) 
    {
        level++;
    }
    return level;
}

/**
 * Inserts a movie node into the skip list with the specified director
 * @param director - the director of the movie node to be inserted
 * @_movie - the pointer to the movie node to be inserted
*/
// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) 
{
    if (size >= capacity) 
    {
        cout << "Skip list is full!" << endl;
        return;
    }

    vector<DirectorSLNode*> update(levels, nullptr);
    DirectorSLNode *current = head;

    for (int i = levels - 1; i >= 0; i--) 
    {
        while (current->next[i] != nullptr && current->next[i]->director < director) 
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];
    if (current != nullptr && current->director == director) 
    {
        current->addMovie(_movie);
    }
    else
    {
        int newLevel = randomLevel(levels);
        DirectorSLNode *newNode = new DirectorSLNode(director, newLevel);

        for (int i = 0; i < newLevel; i++) 
        {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }

        newNode->addMovie(_movie);
        size++;
    }
}

/**
 * Searches for a node in the skip list with the specified director
 * @param director - the director to search for
 * @return the DirectorSLNode containing the specified director, or null if not found
*/
// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) 
{
    DirectorSLNode *current = head;
    for (int i = levels - 1; i >= 0; i--) 
    {
        while (current->next[i] != nullptr && current->next[i]->director < director) 
        {
            current = current->next[i];
        }
    }

    current = current->next[0];
    if (current != nullptr && current->director == director) 
    {
        return current;
    }
    return nullptr;
}

/**
 * Pretty-prints the skip list
*/
void DirectorSkipList::prettyPrint() 
{
    for (int i = 0; i < levels; i++) 
    {
        DirectorSLNode *current = head->next[i];
        cout << "Level " << i << ": ";
        while (current != nullptr) 
        {
            cout << current->director << " -> ";
            current = current->next[i];
        }
        cout << "null" << endl;
    }
}
