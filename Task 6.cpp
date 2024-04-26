#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void textWrap(string sentence, int lineWidth) {
    // Split the sentence into seperate words (by using the space character ' ' as a delimiter of sorts).
    string temp;
    istringstream iss(sentence);
    vector<string> words;
    while (iss >> temp) {
        words.push_back(temp);
	}
    int i = 0;
    int lineNum = 1;
    int len = 0;
    cout << "line 1: ";
    // Loop through the 'words' vector.
    while (i < words.size()) {
        // Add the current word's length to 'len'. If 'len' is greater than / exceeds the line width then it should be added
        // to the next line + increment 'lineNum' + change 'len' accordingly. Else, add the word to the current line
        // and increment len by 1 (to account for the space character).
        len += words[i].length();
        if (len > lineWidth) {
            lineNum++;
            cout << "\nline " << lineNum << ": " << words[i] << " ";
            len = words[i].length() + 1;
        }
        else {
            cout << words[i] << " ";
            len++;
        }
        // Move on to the next element.
        i++;
    }
}

int main() {
    // Declare variables to store the sentence and the line width.
    string sen;
    int LW;
    cout << "text = ";
    // Get sentence as input from user.
    getline(cin, sen);
    cout << "line width = ";
    // Get line width from user. Assume that LW > length of longest word.
    // Note: no check will be made.
    cin >> LW;
    // Call textWrap().
    textWrap(sen, LW);
    return 0;
}