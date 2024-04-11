#include "MovieCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

MovieCollection::MovieCollection() {
    root = nullptr;
}

void MovieCollection::Movie_destructor(Movie* current){
    if(!current){
        return;
    }
    Movie_destructor(current->left);
    Movie_destructor(current->right);
    delete current;
    current = nullptr;
    return;
}
MovieCollection::~MovieCollection() {
    Movie_destructor(root);
}


void MovieCollection::addMovie(string movieName, string director, string genre) {
    Movie* temp = new Movie(movieName, director, genre);
    Movie* current = root;
    if(!root){
        root = temp;
        return;
    }
    while(current){
        if(current -> movieName > movieName){
            if(current -> left){
                current = current -> left;
            }else{
                current -> left = temp;
                return;
            }
        
        }
        if(current -> movieName < movieName){
            if(current -> right){
                current = current -> right;
            }else{
                current -> right = temp;
                return;
            }
        }
    }
}

void MovieCollection::showMovieCollectionHelper(Movie* current){
    if(!current){
        return;
    }
    showMovieCollectionHelper(current->left);
    cout << "MOVIE: " << current->movieName << " DIRECTOR: " << current->director << " GENRE: " << current->genre << endl;
    showMovieCollectionHelper(current->right);
}
void MovieCollection::showMovieCollection() {
    if(!root){
        cout << "Collection is empty." << endl;
        return;
    }
     showMovieCollectionHelper(root);
}


void MovieCollection::showMovie(string movieName) {
    if(!root){
        cout << "Movie not found." << endl;
        return;
    }
    Movie* current = root;
    while(current){
        if(current->movieName == movieName){
            cout << "Movie:" << endl;
        cout << "==================" << endl;
        cout << "Name :" << current->movieName << endl;
        cout << "Director :" << current->director << endl;
        cout << "Genre :" << current->genre << endl;
        return;
        }
        if(current->movieName > movieName){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    cout << "Movie not found." << endl;
    return;
}

void MovieCollection::showMoviesDirector(string director, Movie* current){
    if(!current){
        return;
    }
    showMoviesDirector(director, current->right);
    if(current->director == director){
        cout << current->movieName << " GENRE: " << current->genre << endl;
    }
    showMoviesDirector(director, current->left);
}

void MovieCollection::showMoviesByDirector(string director) {
    cout << "Movies Directed By: " << director << endl;
    showMoviesDirector(director, root);
}

void MovieCollection::printLeavesHelper(Movie* current){
    if(!current){
        return;
    }
    printLeavesHelper(current->left);
    if(!current->left && !current->right){
         cout << "MOVIE: " << current->movieName << " DIRECTOR: " << current->director << " GENRE: " << current->genre << endl;
    }
    printLeavesHelper(current->right);
}

void MovieCollection::printLeaves()
{
    printLeavesHelper(root);
}

int MovieCollection::heightHelper(Movie* current){
    if(!current){
        return 0;
    }
    int lheight = heightHelper(current->left);
    int rheight = heightHelper(current->right);
    if(lheight > rheight){
        return lheight + 1;
    }else{
        return rheight + 1;
    }
}

int MovieCollection::getHeightOfMovieCollection() {
    return heightHelper(root);
}
