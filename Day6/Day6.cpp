#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Function to read the file and return the graph in a map
unordered_map<string, vector<string>> readFile(const string &filename)
{
    ifstream inputFile(filename);
    unordered_map<string, vector<string>> C;
    string line;

    // Read each line from the file
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string start, edges_str;
        getline(ss, start, ':'); // Extract the start node
        getline(ss, edges_str);  // Extract the edges (comma-separated)

        // Split the edges into a vector
        stringstream edgeStream(edges_str);
        string edge;
        while (getline(edgeStream, edge, ','))
        {
            C[start].push_back(edge);
        }
    }

    return C;
}

// Recursive function to get all paths starting from the given root node
vector<vector<string>> getPaths(const string &root, const unordered_map<string, vector<string>> &C)
{
    vector<vector<string>> ret;

    // Base case: if root is "@", return a path containing only "@"
    if (root == "@")
    {
        ret.push_back({"@"});
        return ret;
    }

    // Check if the root exists in the map
    auto it = C.find(root);
    if (it == C.end())
    {
        // If root is not in the map, return an empty list (no paths for this node)
        return ret;
    }

    // Loop through each child node and recursively get all paths
    for (const string &child : it->second)
    {
        vector<vector<string>> childPaths = getPaths(child, C);
        for (auto &path : childPaths)
        {
            path.insert(path.begin(), root); // Prepend root to each path
            ret.push_back(path);
        }
    }

    return ret;
}

// Main function
int main()
{
    // Read the file and build the graph (C)
    unordered_map<string, vector<string>> C = readFile("A.in");

    // Get all paths starting from 'RR'
    vector<vector<string>> paths = getPaths("RR", C);

    // Map to store paths grouped by their length
    unordered_map<int, vector<vector<string>>> by_length;

    // Group paths by their length
    for (const auto &path : paths)
    {
        by_length[path.size()].push_back(path);
    }

    // Check each length group and print the unique path
    for (const auto &entry : by_length)
    {
        if (entry.second.size() == 1)
        {
            // Only one path of this length, so print it
            for (const string &node : entry.second[0])
            {
                cout << node; // Print each node in the path
            }
            cout << endl;
        }
    }

    return 0;
}
