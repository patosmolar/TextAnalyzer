// cvikoPT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Tema: STL algoritmy a lambda vyrazy

// TODO: Doprogramujte vyznacene metody v triede 'TextAnalyzer'

// Trieda 'TextAnalyzer' sluzi na analyzu textu, ktory je reprezentovany
// ako vektor slov (atribut 'words').
class TextAnalyzer {
private:
	vector<string> words; // text, ktory sa bude analyzovat je vyjadreny ako vektor slov
public:

	// TODO 1:
	// Default konstruktor, ktory nacita jednotlive slova zo vstupneho textu 'input_text' do vektora 'words'.
	// Biele znaky a interpunkcia musia byt ignorovane.
	//
	// Priklad:
	// input_text: "Prajem Vam pekny den."
	// words: "Prajem", "Vam", "pekny", "den"
	//
	TextAnalyzer(string input_text = "") {

		stringstream stream(input_text);

		string word;
		while (stream >> word) {
			for (int i = 0; i < word.length(); i++) {
				if (!isalpha(word[i])) {
					word.erase(i, 1);
					i--;
				}
			}
			this->words.push_back(word);
		}

	}

	// TODO 2:
	// Metoda, ktora do vektora 'words' nacita slova z textoveho suboru s nazvom 'filename'.
	// Metoda vrati true/false, podla toho, ci citanie prebehlo uspesne/neuspesne.
	//
	bool loadTextFromFile(string filename) {
		words.clear();

		fstream stream(filename);

		if (!stream.is_open())
			return false;

		string word;
		while (stream >> word) {
			for (int i = 0; i < word.length(); i++) {
				if (!isalpha(word[i])) {
					word.erase(i, 1);
					i--;
				}
			}
			this->words.push_back(word);
		}

		return true;
	}

	// TODO 3: precvicenie algoritmu 'all_of' 
	// Metoda, ktora zisti, ci su vsetky slova vo vektore 'words' dlhsie nez dlzka 'n'.
	//
	// Napoveda: pri pisani lambda vyrazu vyuzite jeho "zachytavaciu klauzulu" na 
	// zachytenie premennej 'n'.
	bool areLongerThan(int n) {
		return all_of(words.begin(), words.end(), [n](string w)
		{
			return w.length() > n;
		});
	}

	// TODO 4: precvicenie algoritmu 'count_if'
	// Metoda, ktora vypocita kolko palindromov sa nachadza vo vektore 'words'.
	// Pozn. palindrom je taky retazec, ktory sa cita rovnako spredu aj odzadu, napr. "level".
	int countPalindromes() {

		return count_if(words.begin(), words.end(), [](string word)
		{
			string rw = word;

			reverse(rw.begin(), rw.end());
		
			if (rw == word)
				return true;

			return false;
		});

		return -999;
	}

	// TODO 5: precvicenie algoritmu 'find_if'
	// Metoda, ktora najde prvy vyskyt slova zacinajuceho na znak 'start' a sucasne konciaceho na znak 'end'.
	// Najdene slovo funkcia vrati. Ak take slovo neexistuje, funkcia vrati prazdny retazec.
	string firstOccurence(char start, char end) {

		vector<string>::iterator it = find_if(words.begin(), words.end(), [start, end](string word) {
			if (word[0] == start && word[word.length() - 1] == end) {
				return true;
			}
			return false;
		});
		return it == words.end() ? "" : *it;
	}

	// TODO 6: precvicenie algoritmu 'transform'
	// Metoda, ktora transformuje vo vektore 'words' kazde slovo tak, ze sa na jeho koniec prida retazec 
	// v tvare "[x]", kde 'x' predstavuje pocet jeho znakov.
	void appendWordLength() {
		transform(words.begin(), words.end(), words.begin(), [](string word) {
		
			return word + to_string(word.length());
		});
	}

	// TODO 7: precvicenie algoritmu 'for_each'
	// Metoda, ktora najde vsetky slova vo vektore 'words', ktore obsahuju pismeno 'p'.
	// Vsetky vyhovujuce slova funkcia zapise do vstupneho vektora 'result'. 
	//
	// Napoveda: pri pisani lambda vyrazu vyuzite jeho "zachytavaciu klauzulu", v ktorej
	// budete "zachytavat" parameter 'result', aby ste ho mohli vo vnutri lambda vyrazu modifikovat
	void findWordsContaining(char p, vector<string>& result) {
		for_each(words.begin(), words.end(), [ &result, p](string word) {
			if (word.find(p) != string::npos) {
				result.push_back(word);
			}
		});
	}

	// TODO 8: precvicenie algoritmu 'remove_if'
	// Metoda, ktora odstrani z vektora 'words' tie slova, ktore sa nachadzaju vo vstupnom vektore slov 'wordlist'.
	// Funkcia vrati pocet odstranenych slov z vektora 'words'.
	int removeWords(const vector<string>& wordlist) {
		int counter = 0;
		remove_if(words.begin(), words.end(), [&wordlist,&counter](string word) {
			if (find(wordlist.begin(), wordlist.end(), word) != wordlist.end()) {
				counter++;
				return true;
			}
			return false;
		});
		return -1;
	}

	// getter
	vector<string> getWords() const { return this->words; }
};

int main() {

	TextAnalyzer t("oko, neviem, kajak, abcd efk ijk");
	cout <<t.firstOccurence('n', 'm');
	cout << t.countPalindromes();
	cout << endl;
	t.appendWordLength();


	for (string &s : t.getWords())
	{
		cout << s << " ";
	}


	return 0;
}