#ifndef SPACE_INVADER_SCORE_HPP
#define SPACE_INVADER_SCORE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

/*
 * Handle all tasks refer to writing and loading score from a file
 */

class Score {

    const string PATH = "/Users/pitchakorn/Desktop/Project/Space Invader/Resource/data/";

public:
    Score( const string& fname, const string& ext );

    int getHighScore(); //Get highest score
    int getCurrentScore(); //Get current score

    void addScore( int newScore ); //write score to file
    void loadFromFile();//read scores from a file

private:
    string scorePath; //file directory

    vector<int> scores; //vector storing a score
};

#endif
