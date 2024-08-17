#ifndef MP3_HPP
#define MP3_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <string.h>

#include "ID3.hpp"

using namespace std;

class MP3{

    private:
        vector<char> data;

        bool hasID3v1;
        ID3::ID3v1 id3v1;

        bool hasID3v2;
        ID3::ID3v2 id3v2;

        map<string, vector<string>> id3v2Data;

        void processIDv2Tags(){
            id3v2Data.clear();
            unsigned int sizeHeader = id3v2.calcSize();

            int i = 0;
            while(i < sizeHeader){
                string newKey = getTag(i);

                if(!newKey.size()) //if the Tag isnt valid, leave the while loop
                    break;

                string value = getValueTag(i);

                id3v2Data[newKey].push_back(value);
                
            }
            
            cleanHeader(sizeHeader);
            cleanGenre();
        }

        string getTag(int& index){
            string newKey = "";

            for(int j = 0; j < 4; j++){
                if(!isValidChar(data[index+j])){ //if the char isnt from a Tag, return an empty string
                    return "";
                }
                newKey.push_back(data[index+j]);
            }

            index += 4; //update the cursor in the data array

            return newKey;
        }

        string getValueTag(int& index){
            unsigned int res = getSizeData(index);

            index += 7; //update the cursor in the data array, after the size value and 3 bytes

            string value = "";

            for(int j = 0; j < res-1; j++){
                value.push_back(data[index + j]);
            }

            index += res - 1; //update the cursor in the data array, after the value
            return value;
        }

        unsigned int getSizeData(int index){ //return the size of the IDv2 Tag
            char size[4];
            size[0] = data[index+0];
            size[1] = data[index+1];
            size[2] = data[index+2];
            size[3] = data[index+3];
            unsigned int res = 0;
            for(int j =0; j < 4; j++){
                res += size[3 - j] << (7 * j);
            }
            return res;
        }

        inline bool isValidChar(char c){
            return((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z'));
        }

        void cleanHeader(unsigned int sizeHeader){
            unsigned int ogSize = data.size();

            for(unsigned int i = 0; i < ogSize - sizeHeader; i++){
                data[i] = data[i + sizeHeader];
            }

            data.resize(ogSize - sizeHeader);
        }

        void cleanGenre(){ //every genre is between "()", so lets remove them to simplify his use
            if(id3v2Data.count("TCON")) {
                for(std::string& s : id3v2Data["TCON"]) {
                    if (s.size() > 1) {
                        s.erase(0, 1);
                        s.erase(s.size() - 1);
                    }
                }
            }
        }
    
    public:
        MP3(){}

        MP3(const char* link){
            read(link);
        }

        ~MP3(){
            data.clear();
            id3v2Data.clear();
        }

        bool read(const char* path){
            ifstream file(path, ios::in|ios::binary|ios::ate);

            if(!file.is_open())
                return false;
            
            ifstream::pos_type fileSize = file.tellg();
            if(fileSize < 0)
                return false;

            file.seekg(0, ios::beg);

            data = vector<char>(fileSize);
            file.read(&data[0], fileSize);

            string tagId = "ID3";
            bool hasTag = true;

            for(int i = 0; i < 3; i++){
                if(data[i] != tagId[i]){
                    hasTag = false;
                    break;
                }
            }

            if(hasTag){
                memcpy(&id3v2, &data[0], sizeof(ID3::ID3v2));
                for(int i = 0, size = sizeof(ID3::ID3v2); i < size; i++){
                    data.erase(data.begin());
                }
                processIDv2Tags();
                hasID3v2 = true;
            }

            tagId = "TAG";
            hasTag = true;

            for(int i = 0; i < 3; i++){
                if(data[data.size() - 128 + i] != tagId[i]){
                    hasTag = false;
                    break;
                }
            }

            if(hasTag){
                memcpy(&id3v1, &data[data.size() - 128], sizeof(ID3::ID3v1));
                data.resize(data.size() - sizeof(ID3::ID3v1));

                hasID3v1 = true;
            }

            data.shrink_to_fit();

            file.close();

            return true;
        };

/*
        bool write(const char* path){
            ofstream file(path, ios::out|ios::binary|ios::ate);

            if(!file.is_open())
                return false;

            if(hasID3v2){
                file.write(reinterpret_cast<char*>(&id3v2), sizeof(id3v2));

                for(auto pair : id3v2Data){
                    file.write(&pair.first[0], pair.first.size());
                    file.write(&pair.second[0], pair.second.size());
                }
            }
            
            file.write(&data[0], data.size());

            if(hasID3v1){
                file.write(reinterpret_cast<char*>(&id3v1), sizeof(id3v1));
            }

            file.close();

            return true;
        };
*/

        void displayID3v1Tags(){
            cout << "title : " << id3v1.title << endl
            << "artist : " << id3v1.artist << endl
            << "album : " << id3v1.album << endl
            << "year : " << id3v1.year << endl
            << "comment : " << id3v1.comment << endl
            << "genre : " << id3v1.genre << endl;
        }

        void displayID3v2Tags(){
            map<string, vector<string>>::iterator it;

            for (it = id3v2Data.begin(); it != id3v2Data.end(); it++){
                std::cout << it->first << " : " << endl;

                for(string value : it->second){
                    cout << value << endl;
                }

            }
        }

        map<string, vector<string>> getAllData(){
            return id3v2Data;
        }

        string getTitle(){
            return id3v2Data["TIT2"][0];
        }

        string getSubTitle(){
            return id3v2Data["TIT3"][0];
        }

        string getComposer(){
            return id3v2Data["TCOM"][0];
        }

        string getLanguage(){
            return id3v2Data["TLAN"][0];
        }

        string getAlbum(){
            return id3v2Data["TALB"][0];
        }

        string getArtist(){
            return id3v2Data["TPE1"][0];
        }

        vector<string> getArtists(){
            return id3v2Data["TPE1"];
        }

        string getBand(){
            return id3v2Data["TPE2"][0];
        }

        string getDate(){
            return id3v2Data["TDRC"][0];
        }

        string getYear(){
            return id3v2Data["TYER"][0];
        }

        string getGenre(){            
            return ID3::genres[id3v2Data["TCON"][0]];
        }

        vector<string> getGenres(){
            vector<string> bufVec;
            for(string buf : id3v2Data["TCON"]){
                bufVec.push_back(ID3::genres[buf]);
            }
            return bufVec;
        }

        int getGenreNumber(){
            return stoi(id3v2Data["TCON"][0]);
        }

        vector<int> getGenreNumbers(){
            vector<int> bufVec;
            for(string buf : id3v2Data["TCON"]){
                bufVec.push_back(stoi(buf));
            }
            return bufVec;
        }

        vector<string> getComments(){
            return id3v2Data["TXXX"];
        }
    
};

#endif
