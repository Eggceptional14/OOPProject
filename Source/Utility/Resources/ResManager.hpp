#ifndef SPACE_INVADER_RESMANAGER_HPP
#define SPACE_INVADER_RESMANAGER_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

/*
 * Resource Manager class holds and manage all resources needed in the game
 */

template<typename Resource>
class ResourceManager
{
public:
    ResourceManager ( const string& folder, const string& extention )
    : rm_folder("/Users/pitchakorn/Desktop/Project/Space Invader/Resource/" + folder + "/"), rm_extention ("." + extention)
    {}

    void add( const string& name ) { //add resource to resource map
        Resource res;

        //if the resource fails to load, then it adds a default "fail" resource
        if( !res.loadFromFile( getFullFilename( name ) ) ) {
            Resource failed;
            failed.loadFromFile(rm_folder + "_fail_" + rm_extention);
            rm_resources.insert( make_pair( name, failed ) );
        }
        else {
            rm_resources.insert( make_pair( name, res ));
        }
    }

    const Resource& get( const string& name ) { //get file from map
        if (!exists( name )) { //if file not exist
            add( name );
        }

        return rm_resources.at(name); //return resource file from name input
    }

    bool exists( const string& name ) const { //check for existence of a file
        return rm_resources.find( name ) != rm_resources.end();
    }


private:
    const string rm_folder;
    const string rm_extention;

    unordered_map<string, Resource> rm_resources; //pair resource name with its file

    string getFullFilename( const string& name ) { //return full file name
        return rm_folder + name + rm_extention;
    }
};

#endif
