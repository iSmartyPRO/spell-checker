#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

class SpellChecker {
private:
    std::unordered_set<std::string> dictionary;

    // Calculate Levenshtein distance between two strings
    int levenshteinDistance(const std::string& s1, const std::string& s2) {
        int m = s1.length();
        int n = s2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
        return dp[m][n];
    }

    // Find suggestions for a misspelled word
    std::vector<std::string> findSuggestions(const std::string& word) {
        std::vector<std::string> suggestions;
        for (const auto& dictWord : dictionary) {
            if (levenshteinDistance(word, dictWord) == 1) {
                suggestions.push_back(dictWord);
            }
        }
        return suggestions;
    }

public:
    // Load dictionary from file
    bool loadDictionary(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open dictionary file: " << filename << std::endl;
            return false;
        }

        std::string word;
        while (file >> word) {
            dictionary.insert(word);
        }
        return true;
    }

    // Process input file and write results to output file
    bool processFile(const std::string& inputFile, const std::string& outputFile) {
        std::ifstream inFile(inputFile);
        std::ofstream outFile(outputFile);

        if (!inFile.is_open() || !outFile.is_open()) {
            std::cerr << "Error: Could not open input or output file" << std::endl;
            return false;
        }

        std::string word;
        while (inFile >> word) {
            if (dictionary.find(word) != dictionary.end()) {
                outFile << word << " ";
            } else {
                auto suggestions = findSuggestions(word);
                outFile << word << " (suggestions: ";
                for (size_t i = 0; i < suggestions.size(); ++i) {
                    outFile << suggestions[i];
                    if (i < suggestions.size() - 1) outFile << ", ";
                }
                outFile << ") ";
            }
        }

        return true;
    }
};

int main() {
    SpellChecker checker;
    
    // Load dictionary
    if (!checker.loadDictionary("dictionary.txt")) {
        return 1;
    }

    // Process input file
    if (!checker.processFile("file.in", "file.out")) {
        return 1;
    }

    return 0;
} 