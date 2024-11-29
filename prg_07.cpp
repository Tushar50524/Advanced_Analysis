#include <iostream>
#include <vector>
using namespace std;

// Function to compute the LPS (Longest Prefix Suffix) array
void computeLPSArray(string pattern, vector<int>& lps) {
    int length = 0;
    int i = 1;
    lps[0] = 0; // LPS for the first character is always 0

    // Build the LPS array
    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform KMP search
void KMPSearch(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();

    // Create the LPS array for the pattern
    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    // Iterate through the text to search for the pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Pattern found at index (i - j)
            cout << "Pattern found at index: " << i - j << endl;
            j = lps[j - 1];
        }

        // Mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;

    // Input text and pattern from the user
    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    // Perform KMP search
    KMPSearch(text, pattern);

    return 0;
}
