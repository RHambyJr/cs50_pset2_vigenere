/* Robert Hamby
 * CS50 PSET2 - Vigenere
 *
 * This program takes a single command line argument for the key to encrypt text.
 * Once a key is given and the program is ran, the program will ask for a line of text to encrypt.
 * It will then print out the encrypted text.
 *
 * This program will return prematurely if:
 *  1) More than one command line argument is given
 *  2) The command line argument contains anything other than alphabetic characters
 *
 * The word "alpha-key" will pop up every now and then in the comments. Alpha-key is just
 * what the letter signifies when not in ascii form. So, a/A = 0, z/Z = 25, and everything in
 * between.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool isValid(string arg);
void encryptText(string text, string key);
char convertChar(char curr, char key);

int main(int argc, string argv[])
{
    string key = argv[1];  // Holds the command line argument
    string phrase; // Holds user entered phrase
    int index = 0; // Holds current index to check if key is valid

    // Checks to see if more than one command line argument was added
    if (argc != 2)
    {
        printf("Only one key please.\n");
        return EXIT_FAILURE;
    }

    while (key[index] != '\0')
    {
        if (!(isalpha(key[index])))
        {
            printf("Alphabetic characters only, please.\n");
            return EXIT_FAILURE;
        }

        index++;
    }

    // Get phrase
    phrase = get_string("plaintext: ");


    // Cycle through key and apply to phrase
    encryptText(phrase, key);
}

/*
 * Checks if argument string that was entered is only alphabetic characters
 * Arguments: string
 * Returns: bool whether it's valid or not
 */
bool isValid(string arg)
{
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!(isalpha(arg[i])))
            return false;
    }

    return true;
}

/*
 * Encrypts text using the Vingenere method of encryption.
 * Arguments: string for text, string for key
 * Prints out encrypted text.
 */
void encryptText(string text, string key)
{
    const int K_LEN = strlen(key);  // The length of the key string
    const int T_LEN = strlen(text) - 1; // The length of the text string, minus one (\0 char)
    int k_i = 0; // Keeps track of index for the key

    printf("ciphertext: ");

    for (int i = 0; i <= T_LEN; i++)
    {
        char curr_txt = text[i]; // Holds current character in text string
        char curr_key = key[k_i % K_LEN]; // Holds current letter in key to be used to convert
        char convert; // Will hold converted char or original char depending on if it's alpha or not

        // Checks if current character is alphabetic
        if (isalpha(curr_txt))
        {
            convert = convertChar(curr_txt, curr_key);
            k_i++; //
        }
        else
            convert = curr_txt;

        printf("%c", convert);
    }

    printf("\n");
}

/*
 * Converts the current letter by using Vigenere formula:
 *      char = (original + key shift) % 26
 * Arguments: char for current letter to be converted
 *            char for current letter to convert
 * Returns: char that is converted
 */
char convertChar(char curr, char key)
{
    const int ALPHA = 26; // Used to mod answer by, number of letters in alphabet (duh)
    const int ALPH_KEY = (int)toupper(key) - (int)'A'; // Converts ascii char to alpha-key char
    const int CURR_FLOOR = isupper(curr) ? (int)'A' : (int)'a';
    int character; // Holds converted character ascii

    // Converts the curr char to alpha-key then adds ALPH_KEY to shift the letter.
    // Mods by 26 in case answer is < 26. Converts back to ascii
    character = (((curr - CURR_FLOOR) + ALPH_KEY) % ALPHA) + CURR_FLOOR;

    return (char)character;
}