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

//general variables
std::ifstream file;
std::vector<std::string> sentesces;
std::vector<float> allSentenceslength, allSentencesTime;
float averageSentenceslength, averageSentencesTime;
float lettersTime, estimatedTime;
int sentencesNum = 5 - 1; //without -1 it would be ex:6 instead of 5

//explications of the program and how to use it
void startInstructions() {
	std::cout << "Wellcome!\n";
	std::cout << "In this program we will see how long it takes you, to read simple sentences.\n";
	std::cout << "when your finished reading the given sentence, press any key to see the result.\n";
	std::cout << "after 5 sentences, we will see if the program knows how long it takes you to read a sentence.\n";
	std::cout << "please enter the accuracy you need (5-10 recomended, higher = more sentences): ";
	std::cout << "press any key when your ready to start:\n"; _getch();
	std::cout << "\n";

}

//random sentences
void app() {
	//random number variables
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	
	//starts a random number from 0 to the number ofsentences
	std::uniform_int_distribution<> dis(0, sentesces.size() - 1);
	int randomIndex = dis(gen);

	//length of sentence and creates a random sentence
	float sentenceLength = sentesces[randomIndex].size();
	auto randomSentence = sentesces[randomIndex];

	//starts timer and prints a random sentence
	auto startTime = std::chrono::high_resolution_clock::now();
	std::cout << randomSentence << std::endl; _getch();

	//ends timer and calculates the time needed to read
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> neededTime = endTime - startTime;

	//adding th length and the time needed to the variable
	allSentenceslength.push_back(sentenceLength);
	allSentencesTime.push_back(neededTime.count());

	//print the needed time
	std::cout << "Time: "<< neededTime.count() <<" press any key to continue..\n"; _getch();

}

//last question, and calculates an aproximate time the user needs to read the sentence
void timeGuess() {
	//from app()
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<> dis(0, sentesces.size() - 1);
	int randomIndex = dis(gen);
	float sentenceLength = sentesces[randomIndex].size();
	auto randomSentence = sentesces[randomIndex];
	auto startTime = std::chrono::high_resolution_clock::now();

	std::cout << randomSentence << std::endl; _getch();
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> neededTime = endTime - startTime;

	//prints the estimated time needed to read
	estimatedTime = sentenceLength / lettersTime;
	std::cout << "estimated time: " << estimatedTime << "\ntime needed: " << neededTime.count();
	std::cout << "\n";
	std::cout << "\npress any key to close the program";

}

float lettersPerTime() {
	// calculates the average length of the sentence
	for (int i = 0; i < sentencesNum; i++) {
		averageSentenceslength += allSentenceslength[i];

	}
	averageSentenceslength = averageSentenceslength / sentencesNum;

	//calculates the average time needed to read
	for (int i = 0; i < sentencesNum; i++) {
		averageSentencesTime += allSentencesTime[i];

	}
	averageSentencesTime = averageSentencesTime / sentencesNum;

	//gives the average amount of letters the user can read in a second
	lettersTime = averageSentenceslength / averageSentencesTime;
	std::cout << lettersTime << "Letters/Seconds\n";

	return lettersTime;
}

int main() {
	//open the file
	file.open("Sentences.txt"); 
	
	//runs only if the file is open
	if (file.is_open()) {
		std::string line;
		startInstructions();

		//reads the lines, copyes them and closes the file
		while(getline(file, line))
		{
			sentesces.push_back(line);

		}
		file.close();

		//prints the sentences
		for (int i = 0; i <= sentencesNum; i++) {

			app();
			std::cout << "\n";

		}
		// prints the average letters per time and the last question
		lettersPerTime();
		std::cout << "Now the final sentense. (when ready, press any key)\n" << std::endl; _getch();
		timeGuess();

	}
	//if the file could not bee opened, an error message will appear
	else std::cerr << "ERROR: File 'Sentences.txt' not found! \n";_getch();
	
	return 0;
}
