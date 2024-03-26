#include "../include/CommonFuncs/read_write_files_funcs.h"

void saveHighscoreToFile(int highscore, const std::string& filename) {
	std::ofstream file(filename);

	if( !file.is_open() ) {
		std::cerr << "Error opening file for writing: " << filename << "\n";
		return;
	}

	file << highscore;

	file.close();
}

int loadHighscoreFromFile(const std::string& filename) {
	int defaultHighscore = 0;

	std::ifstream file(filename);

	if( !file.is_open() ) {
		std::cerr << "File does not exist: " << filename << std::endl;
		std::ofstream newFile(filename);
		if( newFile.is_open() )
		{
			newFile << defaultHighscore;
			newFile.close();
			std::cout << "File created with default value.\n";
		}
		else {
			std::cerr << "Error creating file: " << filename << std::endl;
		}
		return defaultHighscore;
	}

	file >> defaultHighscore;

	file.close();

	return defaultHighscore;
}

