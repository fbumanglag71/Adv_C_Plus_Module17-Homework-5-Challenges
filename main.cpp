#include <cstdio> //for c-style file handling
#include <fstream> //for file input/output
#include <map> //for map container
#include <set> //for set container
#include <iostream> //for console input/output
#include <cstring> //for c-style string handling
#include <cctype> //for character operations
#include <vector> //for dynamic array
#include <cmath> //for mathematical functions

#include "input.h"

using namespace std; //standard namespace for c++

//function prototypes
int menuOption();
void Challenge3();
void Challenge4();
void Challenge6(); 
void Challenge6();
void Challenge7();
void Challenge8();


//main function starts program execution
//displays menu and handles user selection
//each case calls a specific challenge function
int main()
{
    do
    {
        switch (menuOption())
        {
        case 0: exit(1); break;
        case 3: Challenge3(); break;    //done inclass
        case 4: Challenge4(); break;
        case 6: Challenge6(); break;
        case 7: Challenge7(); break;
        case 8: Challenge8(); break;    // 20 points Extra credit
        default: cout << "\t\tERROR - Invalid option. Please re-enter."; break;
        }
        cout << "\n";
        system("pause"); //pause after each selection

    } while (true); //loop to keep menu active

    return EXIT_SUCCESS; //successful program termination
}

int menuOption()
{
    //clear screen for fresh menu display
    system("cls");

    cout << "\n\tChapter 17";
    cout << "\n\t" << string(60, char(205));
    cout << "\n\t3. Capital Quiz";
    cout << "\n\t4. File Encryption and Decryption ";
    cout << "\n\t6. Word Frequency";
    cout << "\n\t7. Word Index";
    cout << "\n\t8. Prime Number Generation";
    cout << "\n\t" << string(60, char(196));
    cout << "\n\t0. Exit";
    cout << "\n\t" << string(60, char(205));

    return inputInteger("\n\tOption: ", 0, 8); //get menu optoin from user

}

void Challenge3()
{
    srand(static_cast<unsigned int>(time(0))); //seed random number generator

    ifstream infile("STATES.TXT");

    if (infile.fail())
    {
        cout << "\n\tERROR: File, STATES.TXT, cannot be found.\n";
        return;
    }

    string state, capital;

    map<string, string> StateAndCapital; //map for state-capital pairs

    while (getline(infile, state))
    {
        getline(infile, capital);

        StateAndCapital.insert(pair<string, string>(state, capital)); //insert state-capital pair
    }

    int corrects = 0;
    int incorrects = 0;

    do
    {
        auto it = StateAndCapital.begin(); //iterator for random access

        advance(it, rand() % 51); //move iterator random positions

        string answer = inputString("\n\tWhat is the capital of " + it->first + "? ", true); //get user input

        if (it->second == answer) //check if answer correct
        {
            corrects++; //increment correct count
        }
        else
        {
            incorrects++; //increment incorrect count
        }

        if (toupper(inputChar("\n\tContinue (Y-yes or N-no)?", "YN")) == 'N')
            break; //exit if user chooses 'N'

    } while (true);
    infile.close(); //close input file

    cout << "\n\t# corrects: " << corrects;
    cout << "\n\t# incorrects: " << incorrects << "\n\n";
}



void Challenge4()
{
    //define the encryption and decryption map
    map<char, char> codes = {
        {'A', '%'}, {'a', '9'}, {'B', '@'}, {'b', '#'},
        {'C', '$'}, {'c', '8'}, {'D', '^'}, {'d', '&'},
        {'E', '*'}, {'e', '7'}, {'F', '('}, {'f', '1'},
        {'G', '-'}, {'g', '3'}, {'H', '+'}, {'h', '0'},
        {'I', '='}, {'i', '4'}, {'J', '/'}, {'j', '!'},
        {'K', '?'}, {'k', '5'}, {'L', '['}, {'l', ']'},
        {'M', '{'}, {'m', '}'}, {'N', '>'}, {'n', '<'},
        {'O', '2'}, {'o', '6'}, {'P', '|'}, {'p', '\\'},
        {'Q', ':'}, {'q', ';'}, {'R', '.'}, {'r', ','},
        {'S', '`'}, {'s', '~'}, {'T', 'z'}, {'t', 'x'},
        {'U', 'y'}, {'u', 'w'}, {'V', 'v'}, {'v', 'u'},
        {'W', 's'}, {'w', 't'}, {'X', 'r'}, {'x', 'q'},
        {'Y', 'p'}, {'y', 'o'}, {'Z', 'n'}, {'z', 'm'}
    };

    //reverse map for decryption
    map<char, char> reverseCodes;
    for (auto pair : codes)
        reverseCodes[pair.second] = pair.first;

    //file names
    string inputFile = "plain.txt";
    string encryptedFile = "encrypted.txt";
    string decryptedFile = "decrypted.txt";

    //delete existing files if they exist
    remove(inputFile.c_str());
    remove(encryptedFile.c_str());
    remove(decryptedFile.c_str());

    //create a new plain_text.txt file for demonstration
    ofstream tempOut(inputFile);
    if (tempOut) {
        tempOut << "Sample text for encryption.\n";
        tempOut.close();
        cout << "\n\tCreated a new '" << inputFile << "' file for demonstration.\n";
    }

    //display the contents of plain_text.txt before encryption
    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "\n\tERROR: Cannot open input file '" << inputFile << "' for reading.\n";
        return;
    }
    cout << "\tPlain.txt file contents: ";
    char ch;
    while (inFile.get(ch)) {
        cout << ch; //display each character of the plain text
    }
    inFile.close();
    cout << endl << endl;

    //encrypt the contents of plain_text.txt and write to encrypted_text.txt
    inFile.open(inputFile);
    ofstream outFile(encryptedFile);
    if (!outFile) {
        cout << "\n\tERROR: Cannot open output file '" << encryptedFile << "' for writing.\n";
        inFile.close();
        return;
    }

    while (inFile.get(ch)) {
        if (codes.find(ch) != codes.end())
            outFile << codes[ch]; //encrypt and write to output
        else
            outFile << ch; //write unmodified if character has no encryption
    }
    inFile.close();
    outFile.close();
    cout << "\tEncryption complete. Encrypted file saved as '" << encryptedFile << "'.\n";

    //display the contents of encrypted_text.txt
    inFile.open(encryptedFile);
    if (!inFile) {
        cout << "\n\tERROR: Cannot open encrypted file '" << encryptedFile << "' for reading.\n";
        return;
    }
    cout << "\tEncrypted.txt file contents: ";
    while (inFile.get(ch)) {
        cout << ch; //display each character of the encrypted text
    }
    inFile.close();
    cout << endl;
}



void Challenge6()
{
    ifstream infile("KENNEDY.TXT");

    if (infile.fail())
    {
        cout << "\n\tERROR: File, KENNEDY.TXT, cannot be found.\n";
        return;
    }

    map<string, int> wordFrequency; //map of key(word) and count

    string word;

    while (infile >> word)
    {
        if (wordFrequency.find(word) == wordFrequency.end())
            wordFrequency.insert(pair<string, int>(word, 0)); //insert word with count 0
        wordFrequency[word]++; //increment word count
    }

    infile.close();

    for (auto it = wordFrequency.begin(); it != wordFrequency.end(); it++)
        cout << "\n\t" << it->first << " : " << it->second;
}

void Challenge7()
{
    const char* inputFile = "Kennedy.txt"; //input file name
    const char* indexFile = "index.txt"; //output file for index
    map<string, set<int>> wordIndex; //map for word and line numbers

    //open the input file
    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "\n\tERROR: Cannot open input file '" << inputFile << "' for reading.\n";
        return;
    }

    char line[256]; //buffer for each line
    int lineNumber = 0;

    //read file line by line
    while (inFile.getline(line, sizeof(line))) {
        lineNumber++; //increment line number

        char* context = nullptr; //context for strtok_s
        char* token = strtok_s(line, " ", &context);
        while (token != nullptr) {
            //convert to lowercase, remove punctuation
            char word[256];
            int index = 0;
            for (int i = 0; i < strlen(token); i++) {
                if (isalnum(token[i])) {
                    word[index++] = tolower(token[i]);
                }
            }
            word[index] = '\0';

            //insert line number for word
            wordIndex[word].insert(lineNumber);

            //get next token
            token = strtok_s(nullptr, " ", &context);
        }
    }
    inFile.close();

    //open the output index file
    ofstream outFile(indexFile);
    if (!outFile) {
        cout << "\n\tERROR: Cannot open index file '" << indexFile << "' for writing.\n";
        return;
    }

    //write word index to file
    outFile << "Word Index\n";
    outFile << "==========\n";
    for (const auto& entry : wordIndex) {
        outFile << entry.first << ": ";
        for (const int lineNum : entry.second) {
            outFile << lineNum << " ";
        }
        outFile << "\n";
    }
    outFile.close();

    cout << "\n\tWord index created successfully in '" << indexFile << "'.\n";

    //open and display contents of index.txt
    ifstream displayFile(indexFile);
    if (!displayFile) {
        cout << "\n\tERROR: Cannot open index file '" << indexFile << "' for reading.\n";
        return;
    }

    cout << "\n\tContents of 'index.txt':\n";
    cout << "\t========================\n";
    string displayLine;
    while (getline(displayFile, displayLine)) {
        cout << "\t" << displayLine << endl;
    }
    displayFile.close();
}


//helper function to check if a number is prime -- challenge8
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i <= sqrt(num); i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

//function object to display prime numbers -- challenge 8
class PrimeChecker {
public:
    void operator()(int number) const {
        if (isPrime(number)) {
            cout << number << " ";
        }
    }
};

void Challenge8() {
    int limit;

    //prompt the user to enter a valid integer greater than 1
    cout << "\tEnter an integer greater than 1: ";
    while (!(cin >> limit) || limit <= 1) {
        cout << "Error: Please enter a valid integer greater than 1.\n";
        cout << "\tEnter an integer greater than 1: ";
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    //populate a vector with numbers from 2 up to the limit
    vector<int> numbers(limit - 1);
    for (int i = 2; i <= limit; ++i) {
        numbers[i - 2] = i;
    }

    //display prime numbers
    cout << "\tPrime numbers up to " << limit << ": ";
    for_each(numbers.begin(), numbers.end(), PrimeChecker());
    cout << endl;
}