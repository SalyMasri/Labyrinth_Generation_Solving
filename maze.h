//Saly Almasri
// 21/08/2022
//betyg C

#pragma once
#include <vector>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <map>
#include <list>
#include <random>
#include <sstream>


enum Object
{
	WALL,
	PATH,
	SOLVE,
    END,
    START
};

struct Node
{
	bool visited;
	Object object;
	int x, y;
};
class Maze
{
public:
	Maze(const int x, const int y);
    void print(std::ofstream& file);
    void generate();
    void solve();

private: 
	std::vector<std::vector<Node>> matrix;
	int width;
	int height;
    std::stack<Node> stack;
    bool isValidNeighbour(Node node, Node prevNode);
    bool outOfBounds(int x, int y);
    Node * findPath( int x,  int y);
    std::vector<int> dir={-1,1,0};
    std::pair<double, double> givetworand();




};