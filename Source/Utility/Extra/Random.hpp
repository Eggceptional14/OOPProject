#ifndef SPACE_INVADER_RANDOM_HPP
#define SPACE_INVADER_RANDOM_HPP

#include <random>
#include <ctime>

using namespace std;

/*
 * Utility class using for generating floating point random number or integer random number
 */

template <typename Engine = mt19937> //Random engine
class Random {
    template <typename T>
    using UniformDist = uniform_real_distribution<T>; //Distribution of floating point
    using UniformIntDist = uniform_int_distribution<int>; //Distribution of integer

public:
    static Random nRand;

    Random( int seed = time( NULL ) ): n_rng( seed ) {}

    template <typename T>
    T getNumberinRange( T low, T high ) { //get number in range of low to high ( Not specific data type )
        return getNumberinRange<UniformDist<T>> ( low, high );
    }

    template <typename Dist, typename T>
    T getNumberinRange( T low, T high ) { //get number in range of low to high ( with Distribution )
        Dist dist( low, high );
        return dist( n_rng );
    }

    int getIntinRange( int low, int high ) { //get random integer in range
        return getNumberinRange<UniformIntDist> ( low, high );
    }

    float getFloatinRange( float low, float high ) { //get random float in range
        return getNumberinRange<UniformDist<float>> ( low, high );
    }

private:
    Engine n_rng;
};

#endif
