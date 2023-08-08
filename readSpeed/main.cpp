/*--what to do--
- tell user to read text from a random selection from a txt file
- get the time the user needed to read it and print it
- get the average time out of it
- print a last sentence and print the time needed and the estimated time
*/

#include <iostream>
#include <fstream>//file
#include <string>
#include <vector>
#include <random>
#include <conio.h>//wait for btton pressed
#include <chrono>//time


std::vector<std::string> sentesces;
std::ifstream file;
std::vector<int> allSentenceslength;
std::vector<float> allSentencesTime;
int sentencesNum = 5;
float averageSentenceslength; float averageSentencesTime;
float lettersTime;
float estimatedTime;


void startInstructions() {
	char input;
	std::cout << "Wellcome!\n";
	std::cout << "In this program we will see how long it takes you, to read simple sentences.\n";
	std::cout << "when your finished reading the given sentence, press any key to see the result.\n";
	std::cout << "after 5 sentences, we will see if the program knows how long it takes you to read a sentence.\n";
	std::cout << "press any key when your ready to start:\n";
	_getch();
	std::cout << "\n";

}

void app() {
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	
	//starts a random number from 0 to the number ofsentences
	std::uniform_int_distribution<> dis(0, sentesces.size() - 1);
	int randomIndex = dis(gen);

	float sentenceLength = sentesces[randomIndex].size();
	auto randomSentence = sentesces[randomIndex];
	//starts timer
	auto startTime = std::chrono::high_resolution_clock::now();
	//prints a random sentence
	std::cout << randomSentence << std::endl;
	_getch();

	//ends timer
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> neededTime = endTime - startTime;

	//adding the time needed and the length of the sentence to the var
	allSentenceslength.push_back(sentenceLength);
	allSentencesTime.push_back(neededTime.count());

	std::cout << "Time: "<< neededTime.count() <<" press any key to continue..\n";
	_getch();
}

void timeGuess() {
	//from app()
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());

	//starts a random number from 0 to the number ofsentences
	std::uniform_int_distribution<> dis(0, sentesces.size() - 1);
	int randomIndex = dis(gen);

	float sentenceLength = sentesces[randomIndex].size();
	auto randomSentence = sentesces[randomIndex];
	//starts timer
	auto startTime = std::chrono::high_resolution_clock::now();
	//prints a random sentence
	std::cout << randomSentence << std::endl;
	_getch();

	//ends timer
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> neededTime = endTime - startTime;

	//gives out the estimated amount of time needed to read
	estimatedTime = sentenceLength / lettersTime;
	std::cout << "estimated time: " << estimatedTime << "\ntime needed: " << neededTime.count();
	std::cout << "\n";
	std::cout << "\npress any key to close the program";

}

float lettersPerTime() {
	
	//length
	for (int i = 0; i < sentencesNum; i++) {
		averageSentenceslength += allSentenceslength[i];
	}
	averageSentenceslength = averageSentenceslength / sentencesNum;

	//time
	for (int i = 0; i < sentencesNum; i++) {
		averageSentencesTime += allSentencesTime[i];
	}
	averageSentencesTime = averageSentencesTime / sentencesNum;


	lettersTime = averageSentenceslength / averageSentencesTime;
	std::cout << lettersTime << "Letters/Seconds\n";

	return lettersTime;
}

int main() {
	file.open("Sentences.txt"); //open the file
	
	if (file.is_open()) {
		std::string line;
		startInstructions();
		//reading the lines and copying them
		while(getline(file, line))
		{
			sentesces.push_back(line);
		}
		file.close();

		for (int i = 0; i <= sentencesNum; i++) {

			app();
			std::cout << "\n";
		}
		lettersPerTime();

		std::cout << "Now the final sentense. (when ready, press any key)\n" << std::endl;
		_getch();
		timeGuess();


	}
	else std::cerr << "ERROR: File 'Sentences.txt' not found! \n";_getch();
	
	return 0;
}
