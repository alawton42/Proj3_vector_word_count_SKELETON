
#include "../includes/fileio.h"

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){
	myfile.open(myFileName.c_str(), mode);
	return myfile.is_open();
}

void closeFile(std::fstream& myfile){
	if (myfile.is_open()){
		myfile.close();
	}
}

int writetoFile(std::vector<constants::entry>  &entries, const std::string &outputfilename){
	std::fstream outputFile;
	bool opened = openFile(outputFile, outputfilename, std::ios_base::out);
	if (!opened){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	if (entries.size() == 0){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	for (unsigned int i = 0; i < entries.size(); i++){
		outputFile << entries[i].word << " " << entries[i].number_occurences << std::endl;
	}
	closeFile(outputFile);
	return constants::SUCCESS;
}
