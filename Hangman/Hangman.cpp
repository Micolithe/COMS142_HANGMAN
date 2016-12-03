// Hangman
//System.out.println("Team");
//Adam Dennis, Sean Reiche, Alexander Kronish, Ryan Bills

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib");



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
vector<char> usedLetters, dashes;
string word;
int missed = 0;
int main()
{
	int seed = time(0); //Seed random number gen
	int mainScreenChoice;
	bool mainScreen = true;


	srand(seed);
	setScreenSize();

	while (mainScreen)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangmanMainscreen.txt");
		mainScreenChoice = 0;
		cin >> mainScreenChoice;
		while (mainScreenChoice <= 0 || mainScreenChoice > 3)
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
			highScoreScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\highscores.txt");
		}
		else if (mainScreenChoice == 1)
		{
			//mainScreen = false;
			chooseDifficultyScreen();

		}
	}
    return 0;
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
	ifstream infile;
	infile.open(path);
	system("CLS");
	int choice;

	while (infile.good())
	{
		string temp;
		getline(infile, temp);
		temp += '\n';
		cout << temp;
	}
	cin >> choice;

	while(choice < 1 || choice > 2)
	{
		cout << "Not a valid input\n";
		cin >> choice;
	}
	if (choice == 1)
	{
		main();
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


void mainScreen()
{
	int choice;
	cin >> choice;
	while (choice <= 0 || choice > 3)
	{
		cout << "Not a valid choice. Select Again.\n";
		cin >> choice;
	}
	if (choice == 3)
	{
		exit(EXIT_SUCCESS);
	}
	else if (choice == 2)
	{
		highScoreScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\highscores.txt");
	}
}

void chooseDifficultyScreen()
{
	ifstream infile;
	infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\difficultyScreen.txt");
	system("CLS");
	int choice;
	PlaySound(TEXT("spacejam.wav"),NULL,SND_FILENAME |SND_ASYNC);

	while (infile.good())
	{
		string temp;
		getline(infile, temp);
		temp += '\n';
		cout << temp;
	}
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
		infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\easyDifficultyWords.txt");
		while (infile)
		{
			string temp;
			getline(infile, temp);
			words.push_back(temp);
		}
	}
	else if (difficultyLevel == 2)
	{
		infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\mediumDifficultyWords.txt");
		while (infile)
		{
			string temp;
			getline(infile, temp);
			words.push_back(temp);
		}
	}
	else if (difficultyLevel == 3)
	{
		infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hardDifficultyWords.txt");
		while (infile)
		{
			string temp;
			getline(infile, temp);
			words.push_back(temp);
		}
	}

	printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangmanStart.txt", true);
	word = getWord(difficultyLevel);
	printDashes();
	guess();

}

string getWord(int difficultyLevel)
{
	ifstream infile; \
		int i = (rand() % (words.size() + 1 - 0));
	cout << i << endl;
	if (difficultyLevel == 1)
	{
		infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\easyDifficultyWords.txt");
	}
	else if (difficultyLevel == 2)
	{
		infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\mediumDifficultyWords.txt");
	}
	else if (difficultyLevel == 3)
	{
		infile.open("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hardDifficultyWords.txt");
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
	for (int count = 0; count < dashes.size(); count++)
	{
		cout << dashes[count];
		if(dashes[count] == '_')
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
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\gameOver.txt", true);

		int num;
		cout<<"0 To Return to Main Menu\n 1 To Exit";
			char c;
			cin  >> c;           // read next character without extracting it
			if (c == 1)
				exit(EXIT_SUCCESS);
			else if(c == 0)
				return;
	}

}

void updateGraphic(int numIncorrect)
{
	system("CLS");
	if (numIncorrect == 0)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangmanStart.txt", true);
	}
	else if (numIncorrect == 1)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangman1Wrong.txt", true);
	}
	else if(numIncorrect == 2)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangman2Wrong.txt", true);
	}
	else if(numIncorrect == 3)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangman3Wrong.txt", true);
	}
	else if(numIncorrect == 4)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangman4Wrong.txt", true);
	}
	else if(numIncorrect == 5)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangman5Wrong.txt", true);
	}
	else if (numIncorrect == 6)
	{
		printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\hangman6Wrong.txt", true);
	}
	else
	{
		cout << "An error has occured";
	}

}

void gameWin()
{
	printScreen("C:\\Users\\Alex\\git\\COMS142_HANGMAN\\Hangman\\winScreen.txt", true);
	int num;
	cout<<"Press Enter to Continue...";
		char c;
		c = cin.peek();           // read next character without extracting it
		if (c == '\n')
			return;
		cin >> num;
		return;
}




