constexpr unsigned MAXSONGS = 64;
constexpr unsigned MAXSTRLENNAME = 101;
//constexpr unsigned MAXSTRLENNAME = 101;

enum class Genre {
	ROCK, 
	POP, 
	THRASH, 
	METAL, 
	K_POP, 
	CHALGA
};

struct Song {
	double rating = 0;
	unsigned views = 0;
	char title[MAXSTRLENNAME] = "";
	char singer[MAXSTRLENNAME] = "";
	Genre genre = (Genre)-1;
	
	
	//char genre[] = "";
};

struct Playlist {
	Song songs[MAXSONGS] = {};
	size_t size = 0;
};

void readSong(Song& song);

//bool isFullOfCapacity(const Song& song);

void addSongInPLaylist(Playlist& playlist, const Song& song);

const Song* getSong(const Playlist& playlist, bool (*predHasSong)(const Song& song));

void sortSongsByViews(Playlist& playlist, bool (*isLess)(const Song& first, const Song& second));

void printSongNames(const Playlist& playlist);