# Id3Scan : C++ Documentation

### Initialisation
Importer la libraire :
` #include "mp3.hpp" `

Créer une nouvelle variable  : 
`
        MP3(){}
        //exemple
        MP3 file;
        MP3(const char* link)
        //exemple
        MP3 file2("music.mp3");
`

Charger un fichier mp3 : 
`
  bool read(const char* path)
  //exemple
  file.read('music.mp3');
`
### Affichage
Afficher les tags ID3v1 :
`void displayID3v1Tags()`

Afficher les tags ID3v2 :
`void displayID3v2Tags()`

### Guetters
Avoir tous les tags ID3v2 :
`map<string, vector<string>> getAllData())`
Avoir le titre :
`string getTitle()`
Avoir le sous titre :
`string getSubTitle()`
Avoir l'album :
`string getAlbum()`
Avoir l'artiste :
`string getArtist()`
Avoir les artistes :
`vector<string> getArtists()`
Avoir le group :
`string getBand()`
Avoir le compositeur :
`string getComposeur()`
Avoir la langue :
`string getLanguage()`
Avoir la date d'enregistrement :
`string getDate()`
Avoir l'année :
`string getYear()`
Avoir le genre :
`string getGenre()`
Avoir les genres :
`vector<string> getGenres()`
> dans ces fichiers, le genre est à l'origine juste un nombre. Ce dernier fait référence à un genre de musique grâce à une liste liant les deux.
Avoir le numéro du genre :
`int getGenreNumber()`
Avoir les numéros des genres :
`vector<int> getGenreNumbers()`
Avoir les commentaires :
`vector<string> getComments()`




