// Hangman
//System.out.println("Team");
//Adam Dennis, Sean Reiche, Alexander Kronish, Ryan Bills

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <mmsystem.h>
#include <map>
#include <stddef.h>
#pragma comment(lib, "winmm.lib")

using namespace std;
void printScreen(string);
void printScreen(string, bool);
void setScreenSize();
void highScoreScreen(string);
void mainScreen();
void chooseDifficultyScreen();
void startGame(int);
void printDashes(char, int, bool);
void printDashes();
void guess();
void gameWin();
void updateGraphic(int);
string getWord(int);

vector<string> words;
vector<int> hiscore;
string username[10];
vector<char> usedLetters, dashes;
string word, userName;
bool cheat = false;
map <string, int> hiscoreList;
int mainScreenChoice;
int gamesWon;


int main()
{
	int seed = time(0); //Seed random number gen
	srand(seed); 
	mainScreen();
	
}

void mainScreen()
{
	PlaySound(NULL, 0, 0);
	PlaySound(TEXT("..\\prelude.wav"), NULL, SND_ASYNC);
	bool mainScreen = true;
	system("Color F0");
	setScreenSize();
	printScreen("..\\hangmanMainscreen.txt");
	if (gamesWon > 0)
		cout << "\t\t\t\tScore: " << gamesWon;
	while (mainScreen)
	{
		cin >> mainScreenChoice;

		while(mainScreenChoice <= 0 || mainScreenChoice > 3 && mainScreenChoice != 45)
		{
			cout << "Not a valid choice. Select Again.\n";
			cin >> mainScreenChoice;
		}
		if (mainScreenChoice == 3)
		{
			exit(EXIT_SUCCESS);
		}
		else if (mainScreenChoice == 2)
		{
			system("CLS");
			highScoreScreen("..\\highscores.txt");
		}
		else if (mainScreenChoice == 1)
		{
			mainScreen = false;
			chooseDifficultyScreen();
		}
		else if (mainScreenChoice == 45)
		{
			cheat = true;
			continue;
		}
	}
	exit(EXIT_SUCCESS);
}

void printScreen(string path) //Prints from a .txt file. 
{
	ifstream infile;
	infile.open(path);

	while (infile.good()) 
	{
		string temp;
		getline(infile, temp);
		temp += '\n';
		cout << temp;
	}
}

void printScreen(string path, bool screenClear) //Clears the screen before printing from txt file
{
	ifstream infile;
	infile.open(path);

	if (screenClear)
	{
		system("CLS");
	}
	while (infile.good())
	{
		string temp;
		getline(infile, temp);
		temp += '\n';
		cout << temp;
	}
}

void highScoreScreen(string path)
{
	
	int choice;
	system("CLS");
	ifstream infile;
	infile.open("hiScoreList.txt");
	cout << "HIGH SCORES \n";
	int tempHiScore = 0;
	string temp;
	string tempUserName;
	while(!infile.eof())
	{
		getline(infile, temp);
		tempHiScore = temp.find(':');
		string tempUserName = temp.substr(0, tempHiScore);
		string userHiscore = temp.substr(tempHiScore + 1, temp.length());
		if(tempUserName.length() != 0)
		cout << tempUserName << ':' << userHiscore << endl;
	}

	cout << "1: Return to Main Menu\n2: Exit" << endl;
	cin >> choice;
	infile.close();

	if(choice < 1 || choice > 2)
	{
		cout << "Not a valid input\n";
		cin >> choice;
	}
	else if (choice == 1)
	{
		system("CLS");
		mainScreen();
	}
	else
	{
		exit(EXIT_SUCCESS);
	}

	 
}
void setScreenSize() //Sets the size of the console window
{
	HWND screen = GetConsoleWindow();
	RECT rectangle;
	GetWindowRect(screen, &rectangle);
	MoveWindow(screen, rectangle.left, rectangle.top, 900, 900, TRUE);
	
}

void chooseDifficultyScreen()
{
	ifstream infile;
	infile.open("..\\difficultyScreen.txt");
	
	system("CLS");
	int choice;

	while (infile.good())
	{
		string temp;
		getline(infile, temp);
		temp += '\n';
		cout << temp;
	}
	system("Color 5F");
	infile.close();
	cin >> choice;
	while(choice < 1 || choice > 3)
	{
		cout << "That is not a valid input\n";
		cin >> choice;
	}
	if (choice == 1)
	{
		startGame(1);
	}
	else if (choice == 2)
	{
		startGame(2);
	}
	else if (choice == 3)
	{
		startGame(3);
	}

}

void startGame(int difficultyLevel)
{
	ifstream infile;
	if (difficultyLevel == 1)
	{
		infile.open("..\\easyDifficultyWords.txt");
		while (infile)
		{
			string temp;
			getline(infile, temp);
			words.push_back(temp);
		}
	}
	else if (difficultyLevel == 2)
	{
		infile.open("..\\mediumDifficultyWords.txt");
		while (infile)
		{
			string temp;
			getline(infile, temp);
			words.push_back(temp);
		}
	}
	else if (difficultyLevel == 3)
	{
		infile.open("..\\hardDifficultyWords.txt");
		while (infile)
		{
			string temp;
			getline(infile, temp);
			words.push_back(temp);
		}
	}

	printScreen("..\\hangmanStart.txt", true);
	word = getWord(difficultyLevel);
	printDashes();
	guess();

}

string getWord(int difficultyLevel)
{
	ifstream infile; 
	int i = (rand() % (words.size() + 1 - 0));
	cout << i << endl;
	if (difficultyLevel == 1)
	{
		infile.open("..\\easyDifficultyWords.txt");
	}
	else if (difficultyLevel == 2)
	{
		infile.open("..\\mediumDifficultyWords.txt");
	}
	else if (difficultyLevel == 3)
	{
		infile.open("..\\hardDifficultyWords.txt");
	}

	return words[i];
}

void printDashes()
{
	for (int i = 0; i < word.size(); i++)
	{
		cout << "_";
		dashes.push_back('_');
	}
	cout << "\n";
}

void printDashes(char userLetter, int letterIndex, bool letterFound)
{
	bool winner = false;
	bool hasDashes = false;
	for (int i = 0; i < dashes.size(); i++)
	{
		cout << dashes[i];
		if(dashes[i] == '_')
		{
			hasDashes = true;
		}
	}

	if (!hasDashes)
	{
		gameWin();
	}
	cout << endl;
}

void guess()
{
	char userLetter;
	int correctLetterIndex = 0;
	int missed = 0;

	while (missed <= 6)
	{
		cout << endl << "Guess a letter\n";
		cin >> userLetter;
		for (int i = 0; i < word.size(); i++)
		{
			char wordChar = word.at(i);
			for (int count = 0; count < usedLetters.size(); count++)
			{
				while(userLetter == usedLetters[count])
				{
					cout << "You already entered that letter. Enter again.\n";
					cin >> userLetter;
				}
			}
			if (wordChar == userLetter)
			{
				dashes.at(i) = userLetter;
			}
		}
		if (word.find(userLetter) != string::npos)
		{
		}
		else
		{
			missed += 1;
		}

		usedLetters.push_back(userLetter);
		updateGraphic(missed);
		printDashes(userLetter, correctLetterIndex, true);
		
	}
	if(missed > 6)
	{
		usedLetters.clear();
		words.clear();
		dashes.clear();
		system("Color 0C");
		if(!cheat)
		{
			PlaySound(TEXT("..\\hangmanRope.wav"), NULL, SND_ASYNC);
		}
		else if(cheat)
		{
			cout << "here";
			PlaySound(TEXT("..\\garbage.wav"), NULL, SND_ASYNC);
		}
		printScreen("..\\gameOver.txt", true);
		cout << "The Word Was " <<  word << endl;
		cout << "Press Enter to Continue...";
		char c = cin.get();
		cin.ignore();
		system("CLS");
		mainScreen();
	}
}

void updateGraphic(int numIncorrect)
{
	system("CLS");
	if (numIncorrect == 0)
	{
		printScreen("..\\hangmanStart.txt", true);
	}
	else if (numIncorrect == 1)
	{
		printScreen("..\\hangman1Wrong.txt", true);
	}
	else if(numIncorrect == 2)
	{
		printScreen("..\\hangman2Wrong.txt", true);
	}
	else if(numIncorrect == 3)
	{
		printScreen("..\\hangman3Wrong.txt", true);
	}
	else if(numIncorrect == 4)
	{
		printScreen("..\\hangman4Wrong.txt", true);
	}
	else if(numIncorrect == 5)
	{
		printScreen("..\\hangman5Wrong.txt", true);
	}
	else if (numIncorrect == 6)
	{
		printScreen("..\\hangman6Wrong.txt", true);
	}
	else
	{
		cout << "An error has occured";
	}

}

void gameWin()
{
	static bool firstWin = true;
	gamesWon++;
	printScreen("C:\\Users\\Adam\\OneDrive\\FALL 2016\\C++\\winScreen.txt", true);
	cout << "Do you want to play again? Y/N";
	char replay;
	cin >> replay;
	if (firstWin)
	{
		firstWin = false;
		cout << "Enter a username: \n";
		cin >> userName;
	}
	if (toupper(replay) == 'Y')
	{
		words.clear();
		dashes.clear();
		usedLetters.clear();
		system("CLS");
		main();
	}
	else
	{
		ofstream outFile;
		outFile.open("hiScoreList.txt", ofstream::out | ofstream::app);
		outFile << userName << ":" << gamesWon << '\n';
		outFile.close();
		exit(EXIT_SUCCESS);
	}
}




