// Extra Credit Challenge Problem Written by Stephanie Yoshimoto
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Provided for students.
void read_maze(string filename, vector<vector<char> > &maze) {
    ifstream ifile(filename);
    int size = 0;
    for (int i = 0; ifile; i++) {
        string line;
        getline(ifile, line);
        if (i == 0) {
            vector<char> maze_line;
            for (char c : line) {
                maze_line.push_back(c);
            }
            size = maze_line.size();
            maze.push_back(maze_line);
        } else {
            vector<char> maze_line(size);
            for (int j = 0; j < line.size(); j++) {
                maze_line[j] = line[j];
            }
            for (int j = line.size(); j < maze_line.size(); j++) {
                maze_line[j] = ' ';
            }
            maze.push_back(maze_line);
        }
    }
    maze.pop_back();
    ifile.close();
}

bool solve(vector<vector<char> > &maze, const int rows, const int cols, int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    } else if (maze[row][col] != ' ') {
        return false;
    }
    maze[row][col] = '*';
    if (row == (rows - 2) && col == (cols - 1)) {
        return true;
    }

    if (solve(maze, rows, cols, row - 1, col) || solve(maze, rows, cols, row + 1, col) ||
        solve(maze, rows, cols, row, col - 1) || solve(maze, rows, cols, row, col + 1)) {
        return true;
    }
    maze[row][col] = ' ';
    return false;
}

bool solve(vector<vector<char> > &maze) {
    if (!maze.empty()) {
        const int rows = maze.size(), cols = maze[0].size();
        if (solve(maze, rows, cols, 1, 0)) {
            cout << "Solution found!" << endl;
            return true;
        }
    }
    cout << "No solution." << endl;
    return false;
}

// Driver code provided.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "argc must be 3" << endl; // run like ----> ./maze_solver maze.txt output.txt
        return 1;
    }
    vector<vector<char> > maze;
    read_maze(argv[1], maze);

    if (solve(maze)) {
        ofstream ofile(argv[2]);
        if (ofile) {
            for (int i = 0; i < maze.size(); i++) {
                for (int j = 0; j < maze[i].size(); j++) {
                    ofile << maze[i][j];
                }
                ofile << endl;
            }
        }
        ofile.close();
    }

    return 0;
}

