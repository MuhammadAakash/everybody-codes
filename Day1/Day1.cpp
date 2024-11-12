#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int getPotionCount(char monster)
{
    unordered_map<char, int> potionCount = {
        {'A', 0},
        {'x', 0},
        {'B', 1},
        {'C', 3},
        {'D', 5},
    };

    return potionCount[monster];
}

int main()
{
    // Part 1

    // ifstream inputFile("part1.txt");

    // // Check if the file was opened successfully
    // if (!inputFile)
    // {
    //     cerr << "Error opening file." << std::endl;
    //     return 1;
    // }

    // string content;
    // int count = 0;

    // getline(inputFile, content, '\0');

    // for (char c : content)
    // {
    //     if (c == 'B')
    //     {
    //         count++;
    //     }
    //     else if (c == 'C')
    //     {
    //         count += 3;
    //     }
    // }

    // cout << "Total count is: " << count << endl;

    // inputFile.close();

    // Part2

    // ifstream inputFile("Day1Part2.txt");

    // if (!inputFile)
    // {
    //     cerr << "Error opening file";
    //     return 1;
    // }

    // string content;

    // getline(inputFile, content, '\0');
    // inputFile.close();

    // int totalCount = 0;
    // ;

    // for (size_t i = 0; i < content.length(); i += 2)
    // {
    //     int pairPotionCount = 0;

    //     if (i + 1 < content.length())
    //     {
    //         pairPotionCount += getPotionCount(content[i]) + (content[i] != 'x' && content[i + 1] != 'x' ? 1 : 0);

    //         pairPotionCount += getPotionCount(content[i + 1]) + (content[i] != 'x' && content[i + 1] != 'x' ? 1 : 0);
    //     }
    //     else
    //     {
    //         pairPotionCount += getPotionCount(content[i]);
    //     }
    //     totalCount += pairPotionCount;
    // }
    // cout << "Total count is: " << totalCount << endl;

    // Part 3

    // Part 3

    ifstream inputFile("Day1Part3.txt");

    // Error handling for file opening
    if (!inputFile)
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Read the entire content of the file
    string content;
    getline(inputFile, content, '\0');
    inputFile.close();

    int totalCount = 0;

    // Loop through the string in chunks of 3 characters
    for (size_t i = 0; i < content.length(); i += 3)
    {
        int groupPotionCount = 0;
        int n_enemies = 0; // To track number of real enemies (non-'x')

        // Process the current group (up to 3 monsters)
        for (size_t j = 0; j < 3 && i + j < content.length(); ++j)
        {
            char c = content[i + j];
            groupPotionCount += getPotionCount(c); // Add potion cost of the current monster

            if (c != 'x')
            {
                n_enemies++; // Count how many real enemies are in the group
            }
        }

        // Add extra potions based on the number of enemies in the group
        if (n_enemies == 2)
        {
            groupPotionCount += 2; // 2 extra potions for pairs
        }
        else if (n_enemies == 3)
        {
            groupPotionCount += 6; // 6 extra potions for triples
        }

        // Print the group potion count for debugging
        cout << "Group " << content.substr(i, 3) << " potion count: " << groupPotionCount << endl;

        // Add the group's potion count to the total
        totalCount += groupPotionCount;
    }
    cout << "Total count is: " << totalCount << endl;

    return 0;
}