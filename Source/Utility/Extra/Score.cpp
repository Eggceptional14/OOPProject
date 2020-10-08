#include "Score.hpp"

Score::Score(const string& fname, const string& ext)
: scorePath( PATH + fname + "." + ext ) {
    loadFromFile();
}

int Score::getHighScore() {
    vector<int> temp;
    copy( scores.begin(), scores.end(), back_inserter( temp ) );
    sort( temp.begin(), temp.end() );

    return temp.back();
}

int Score::getCurrentScore() {
    return scores.back();
}

void Score::loadFromFile() {
    ifstream inFile;
    inFile.open( scorePath );

    string line;
    int linescore;

    if ( inFile.is_open() ) {
        while ( getline( inFile, line ) ) {
            linescore = stoi( line );
            scores.push_back( linescore );
        }
    }

    inFile.close();
}

void Score::addScore(int newScore) {
    ofstream outFile;
    outFile.open(scorePath );

    scores.push_back( newScore );

    for ( auto& score : scores )
        outFile << score << endl;

    outFile.close();
}

