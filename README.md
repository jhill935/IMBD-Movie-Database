Here is the README for the IMDB Movie Database project:

---

# IMDB Movie Database

**Created by Jackson Hill**

The IMDB Movie Database project is an application designed to store and retrieve movie-related information efficiently using hash tables and skip lists. It allows users to search for movies by title, find movies by a specific director, view movie descriptions, and list all movies by a director.

## Features

### 1. **Search by Movie Title**
- Find the director of a movie by its title.
- Retrieve detailed descriptions, including plot, genre, cast, year, and more.

### 2. **Search by Director**
- Display the number of movies directed by a specific director.
- List all movies by the director with their titles.

### 3. **Efficient Data Structures**
- **Hash Table**: Used for storing and retrieving movies by title.
  - Collision resolution using chaining.
  - Optimized hash function for minimal collisions.
- **Skip List**: Used for managing directors and their associated movies.
  - Supports quick search, insert, and delete operations with \(O(\log n)\) complexity.

### 4. **CSV File Integration**
- Parse and populate the database from CSV files (`IMDB-Movie-Data.csv` and `IMDB-small.csv`).

### 5. **Menu-Driven Interface**
- Interactive console menu for seamless user interaction.
- Supports multiple operations without restarting the application.

### 6. **Memory Management**
- Ensures proper allocation and deallocation of memory.
- Implements destructors for both hash tables and skip lists to avoid memory leaks.

## Technologies Used
- **C++**: For implementing data structures and algorithms.
- **Google C++ Style Guide**: Used for maintaining clean and readable code.
- **Valgrind**: Utilized to detect memory leaks.

## Getting Started

### Prerequisites
- C++ compiler supporting C++11 standard.

### Compilation and Execution
1. Compile the project using the provided command:
   ```bash
   g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db
   ```
2. Run the application:
   ```bash
   ./movie-db <csv file> <hash table size> <skip list size>
   ```
   Example:
   ```bash
   ./movie-db IMDB-Movie-Data.csv 1000 1000
   ```

## User Guide

### Menu Options
1. **Find the Director of a Movie**  
   Enter a movie title to retrieve its director.
2. **Find the Number of Movies by a Director**  
   Enter a director's name to view the number of movies they've directed.
3. **Find the Description of a Movie**  
   Enter a movie title to view details like genre, plot, actors, and year.
4. **List Movies by a Director**  
   Enter a director's name to see all their movies.
5. **Quit**  
   Exit the application.

### CSV File Format
The application reads data from a CSV file with the following structure:
```
Rank,Title,Genre,Description,Director,Actors,Year,Runtime,Rating,Votes,Revenue,Metascore
```

## Hash Function and Collision Handling
- **Hash Function**: Combines the user's identikey ("jahi7479") with the movie title using a custom hash algorithm to minimize collisions.
- **Collision Resolution**: Utilizes chaining to handle collisions effectively.

## Skip List Implementation
- Implements multi-level linked lists for fast searching.
- Randomized level generation using coin flips.
- Supports search, insertion, and deletion.

## Additional Features
- Extensible design for integrating advanced search features (e.g., filtering by genre or year).
- Potential for future enhancements like fuzzy search, recommendation systems, or graph-based actor relationships.
