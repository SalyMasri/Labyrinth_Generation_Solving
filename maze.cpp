//Saly Almasri
// 21/08/2022
//betyg C

#include "maze.h"

Maze::Maze(const int x, const int y)
{
	this->width = x;   
	this->height = y;  
	for (int column = 0; column < x; column++)  
	{
		matrix.resize(width);
		matrix[column].resize(height); 
		for (int row = 0; row < y; row++)   
		{
			matrix[column][row].x = column;
			matrix[column][row].y = row;
		}
	}
}

void Maze::print(std::ofstream& file)
{
	for (int column = 0; column < width; column++)
	{
		for (int row = 0; row < height; row++)
		{
			if (matrix[column][row].object == WALL)
			{
				std::cout << " * ";
				file << " * ";
			}
			else if (matrix[column][row].object == PATH)
			{
				std::cout << " X ";
				file << " X ";
			}
            else if (matrix[column][row].object == START)
            {
                std::cout << " S ";
				file << " S ";
            }
            else if (matrix[column][row].object == END )
			{
				std::cout << " E ";
				file << " E ";
			}
			else
			{
				std::cout << " O ";
				file << " O ";
			}
		}
		std::cout << std::endl;
		file << std::endl;
	}
    std::cout <<"\n\n";
	file << "\n\n";
}

std::pair<double, double> Maze::givetworand()
{
         
			std::random_device rd;
             std::mt19937 gen(rd());
            std::shuffle(dir.begin(), dir.end(), gen);
			return std::make_pair(dir[0], dir[1]) ;
	
            
}
    

bool Maze::outOfBounds( int x, int y)
{
    if (x < 0 || x > this->matrix.size() - 1) return true;
	if (y < 0 || y > this->matrix[x].size() - 1) return true;
	return false;
    
}

bool Maze::isValidNeighbour(Node node, Node prevNode)
 {  
    for (int e = 0; e < 200; e++)
        {    
        int i=givetworand().first, j=givetworand().second;
	    if ( i!=j && i+j!=0&&!outOfBounds(node.x+i, node.y + j)&&matrix[node.x+i][node.y + j].visited &&(node.x+i != prevNode.x) && (node.y + j != prevNode.y))return false;
        }
    return true;
}

void Maze::generate()
{
    int startX=0, startY=0;
	for (int column = 0; column < width; column++)
	{
		for (int row = 0; row < height; row++) 
		{
			matrix[column][row].visited = false; //Markera alla noder som obesökta .
			matrix[column][row].object = WALL; 
		}
	}
    
    Node currentNode=matrix[startX][startY]; //Välj en startnod och låt den vara nuvarande nod N
	matrix[startX][startY].visited = true; //Markera N som besökt .
	stack.push(currentNode); //Lägg till N till en stack S.
	
    while (!stack.empty()) // Så länge som S inte är tom :
	{
       Node currentNode = matrix[stack.top().x][stack.top().y]; //Hämta en nod från S och låt den vara N
        bool found = false;
        for (int i = 0; i <  200 && !found; i++)
        {        
            int e=givetworand().first, j=givetworand().second;
				if (e!=j && e+j!=0&&!outOfBounds(currentNode.x+e, currentNode.y+j)&&!matrix[currentNode.x+e][currentNode.y+j].visited)
				{
					Node * NeighbourPointer= &matrix[currentNode.x+e][currentNode.y+j];
					if (NeighbourPointer != nullptr) //Om N har obesökta grannar
					{
					Node Neighbour = *NeighbourPointer; // Välj slumpmässigt en obesökt granne G .
						if (isValidNeighbour(Neighbour, currentNode))
						{
							matrix[Neighbour.x][Neighbour.y].visited = true; //Markera G som bes ¨o kt .
							matrix[Neighbour.x][Neighbour.y].object = PATH;
							stack.push(Neighbour); //Lägg till G till S.
							found = true;
						}
					}
				}
            
            
        }
        if (!found)stack.pop();
		
    }
}
Node * Maze::findPath( int x,  int y)
{
     for (int i = 0; i <  200 ; i++)
        {        
            int j=givetworand().first, e=givetworand().second;
            if(e!=j && e+j!=0&&!outOfBounds(x+e, y + j)&& !matrix[x+e][y + j].visited && matrix[x+e][y + j].object != WALL){
				return &matrix[x+e][y + j]; 
				//Only unvisited and non-WALL nodes are returned
			} 
            
        }		
		return nullptr;		
}

void Maze::solve(){
        int startX=0,  startY=0,  endX=width - 1,  endY=height - 1;
        while (matrix[startX][startY].object == WALL)
	{
		startX++;
	}
        while (matrix[endX][endY].object == WALL)
	{
		endY--;
	}
for (int column = 0; column < width; column++)
	{
		for (int row = 0; row < height; row++) 
		{
			matrix[column][row].visited = false; // Markera alla noder som obesökta .

		}
	}
	matrix[startX][startY].visited = true;
	stack.push(matrix[startX][startY]); //Välj en startnod och lägg den till en stack S.
	while(!stack.empty()) //Så länge som S inte är tom :
	{
        
		Node* path = findPath(stack.top().x, stack.top().y); //Hämta en nod från S och låt den vara N.
		if (stack.top().x == endX &&stack.top().y == endY) // Om N är slutnoden:
		{
			stack.push(matrix[endX][endY]); //Lägg till N till S. Du är klar .
			break;
		}

		if (path != nullptr)
		{ // Om N har obesökta grannar :
			matrix[path->x][path->y].visited = true;
			matrix[path->x][path->y].object = SOLVE;
			stack.push(matrix[path->x][path->y]);
			
		}
		else // if Node is visited or is not a wall
		{
			
            matrix[stack.top().x][stack.top().y].object = PATH;
			stack.pop();
		}
		if (stack.empty()) //Om S är tom så finns ingen lösning .
		{
			std::cout<<"\nNo Solution!\n";
			
		}
		
	}
	matrix[startX][startY].object = START;
	matrix[endX][endY].object=END;
    }

	