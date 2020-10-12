#include <algorithm>
#include "../includes/utilities.h"
#include "../includes/array_functions.h"

namespace KP{

	bool ascending(const constants::entry& x, const constants::entry& y){
		return x.word_uppercase < y.word_uppercase;
	}

	bool descending(const constants::entry& x, const constants::entry& y){
		return x.word_uppercase > y.word_uppercase;
	}

	bool numOrder(const constants::entry& x, const constants::entry& y){
		return x.number_occurences > y.number_occurences;
	}


	void clear(std::vector<constants::entry>  &entries){
		entries.clear();
	}

	int getSize(std::vector<constants::entry>  &entries){
		return entries.size();
	}

	std::string getWordAt(std::vector<constants::entry>  &entries, int i){
		return i <= entries.size() ? entries[i].word : entries[entries.size()-1].word;
	}

	int getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
		return i <= entries.size() ? entries[i].number_occurences : entries[entries.size()-1].number_occurences;
	}

	bool processFile(std::vector<constants::entry>  &entries,std::fstream &myfstream){
		if (!myfstream.is_open()){
			return false;
		}

		std::string line;
		while (!myfstream.eof()){
			getline(myfstream, line);
			processLine(entries, line);
		}

		return true;
	}

	void processLine(std::vector<constants::entry>  &entries,std::string &myString){
		std::string token;
		std::stringstream ss(myString);

		while (getline(ss, token, constants::CHAR_TO_SEARCH_FOR)){
			processToken(entries, token);
		}
	}

	void processToken(std::vector<constants::entry>  &entries,std::string &token){
		strip_unwanted_chars(token);
		if (token.length() == 0){
			return;
		}
		std::string upperToken = token;
		toUpper(upperToken);

		for (int i = 0; i < entries.size(); i++){
			if (entries[i].word_uppercase == upperToken){
				entries[i].number_occurences += 1;
				return;
			}
		}

		constants::entry tmp;
		tmp.word = token;
		tmp.word_uppercase = upperToken;
		tmp.number_occurences = 1;
		entries.push_back(tmp);

	}

	void sort(std::vector<constants::entry>  &entries, constants::sortOrder so){
		switch (so){
			case(constants::ASCENDING):
				sort(entries.begin(), entries.end(), ascending);
				break;
			case(constants::DESCENDING):
				sort(entries.begin(), entries.end(), descending);
				break;
			case(constants::NUMBER_OCCURRENCES):
				sort(entries.begin(), entries.end(), numOrder);
				break;
			default:
				break;
		}
	}
}
