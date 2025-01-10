//Jackson Hill - Final Project
//CSCI 2270 - Medha Sharma - Recitation 206
//April 30, 2023

//g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db
//./movie-db IMDB-Movie-Data.csv 1000 1000

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();

/**
 * This function is the main function of the program. It checks the number of arguments, 
 * creates a MovieHashTable and a DirectorSkipList, reads a CSV file and initializes these data structures with the data from the CSV file. 
 * It then displays a menu and prompts the user to choose an option from the menu. 
 * The options include searching for a movie by title, searching for a director by name, displaying a movie summary by title, displaying all movies by a director, and quitting the program. 
 * The user is prompted for input according to the chosen option, and the program outputs the appropriate response. 
 * The function returns 0 upon successful completion.
 * @param argc The number of command-line arguments passed to the program
 * @param argv The command-line arguments passed to the program
 * @return int
*/
// Main function
int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        cerr << "Invalid number of arguments." << endl;
        cerr << "Usage: " << argv[0] << " <csv file> <hash table size> <skip list size>" << endl;
        return 1;
    }

    string csv_file = argv[1];
    int hash_table_size = stoi(argv[2]);
    int skip_list_size = stoi(argv[3]);

    MovieHashTable movieTable(hash_table_size);
    DirectorSkipList directorList(skip_list_size, skip_list_size);

    readMovieCSV(csv_file, movieTable, directorList);
    cout << "Number of collisions: " << movieTable.getCollisions() << endl;


    int option;
    do {
        display_menu();
        cin >> option;

        string title, director;
        MovieNode *movie;
        DirectorSLNode *directorNode;

        switch (option) 
        {
            case 1:
                cout << "Enter the movie title: ";
                cin.ignore();
                getline(cin, title);
                movie = movieTable.search(title);
                if (movie) cout << "The director of " << title << " is " << movie->director << endl;
                else cout << "Movie not found" << endl;
                break;

            case 2:
                cout << "Enter the director's name: ";
                cin.ignore();
                getline(cin, director);
                directorNode = directorList.search(director);
                if (directorNode)
                {
                    cout << director << " directed " << directorNode->movies.size() << " movies" << endl;
                }
                else 
                {
                    cout << "Director not found" << endl;
                }
                break;

            case 3:
                cout << "Enter the movie title: ";
                cin.ignore();
                getline(cin, title);
                movie = movieTable.search(title);
                if (movie) 
                {
                    cout << "Summary: " << title << " is a " << movie->year << " (" << movie->genre << ") film featuring " << movie->actors << endl << "Plot: " << movie->description << endl;
                } 
                else 
                {
                    cout << "Movie not found" << endl;
                }
                break;

            case 4:
                cout << "Enter the director's name: ";
                cin.ignore();
                getline(cin, director);
                directorNode = directorList.search(director);
                if (directorNode) 
                {
                    int i = 0;
                    cout << director << " directed the following movies: "<< endl;
                    for (auto movie : directorNode->movies) 
                    {
                        cout << "    " << i << ": " << movie->title << endl;
                        i++;
                    }
                } 
                else 
                {
                    cout << "Director not found" << endl;
                }
                break;

            case 5:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
        cout << endl;
    } while (option != 5);

    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

/**
 * readMovieCSV - Reads a CSV file and populates the movieTable and directorList with MovieNode objects
 * @param filename - the name of the CSV file to read
 * @param movieTable - a reference to a MovieHashTable object to store the MovieNode objects by title
 * @param directorList - a reference to a DirectorSkipList object to store the MovieNode objects by director
*/
// Function to read a CSV file into a vector of MovieNode objects
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) 
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header line

    while (getline(file, line)) 
    {
        MovieNode *movie = parseMovieLine(line);
        if (movie) 
        {
            movieTable.insert(movie->title, movie);
            directorList.insert(movie->director, movie);
        }
    }

    file.close();
}

/**
 * display_menu - Displays the menu options to the user
*/
// Function to display the menu options
void display_menu() 
{
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
    cout << endl;
    cout << "Enter an Option: ";
}
