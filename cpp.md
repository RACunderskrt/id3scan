# Id3Scan : C++ Documentation

### Initialisation
Importer la libraire :<br>
` #include "mp3.hpp" `

Constructeur : <br>
`
        MP3(){} \n
        MP3(const char* link)
`

Charger un fichier mp3 : <br>
`
  bool read(const char* path)
  //exemple
  file.read('music.mp3');
`
### Affichage
Afficher les tags ID3v1 :<br>
`void displayID3v1Tags()`<br>

Afficher les tags ID3v2 :<br>
`void displayID3v2Tags()`<br>

### Guetters
Avoir tous les tags ID3v2 :<br>
`map<string, vector<string>> getAllData())`<br>
Avoir le titre :<br>
`string getTitle()`<br>
Avoir le sous titre :<br>
`string getSubTitle()`<br>
Avoir l'album :<br>
`string getAlbum()`<br>
Avoir l'artiste :<br>
`string getArtist()`<br>
Avoir les artistes :<br>
`vector<string> getArtists()`<br>
Avoir le group :<br>
`string getBand()`<br>
Avoir le compositeur :<br>
`string getComposeur()`<br>
Avoir la langue :<br>
`string getLanguage()`<br>
Avoir la date d'enregistrement :<br>
`string getDate()`<br>
Avoir l'année :<br>
`string getYear()`<br>
Avoir les commentaires :<br>
`vector<string> getComments()`
Avoir le genre :<br>
`string getGenre()`<br>
Avoir les genres :<br>
`vector<string> getGenres()`<br>
Avoir le numéro du genre :<br>
`int getGenreNumber()`<br>
Avoir les numéros des genres :<br>
`vector<int> getGenreNumbers()`<br>
> dans ces fichiers, le genre est à l'origine juste un nombre. Ce dernier fait référence à un genre de musique grâce à une liste liant les deux.





