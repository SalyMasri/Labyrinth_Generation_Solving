//Saly Almasri
// 21/08/2022
//betyg C

#include "maze.h"
bool check(std::string v) {
  for (int i=0; i<v.length(); i++)
  if (isdigit(v[i]) == true)
      return true;
      return false;
}
int main()
{
    
	std::string choice;
	
	std::ofstream myMaze;
	myMaze.open("maze.txt");
	
	bool a = true;

while(a )
{
    do
    {
        system("cls");
        std::cout << "********************* "<< "/ Maze /" << "********************* \n";
        std::cout << "****** "<< "/ Only Enter Valid Numbers; 1 OR 2 /" << "*******\n\n";
		std::cout << "1. Create and solve a Maze" << std::endl;
		std::cout << "2. exit program" << std::endl;
        std::cin >> choice;
    }while (!check(choice) || stoi(choice)!=1&&stoi(choice)!=2  );
		switch (stoi(choice))
		{
			case 1:
			{
				std::string x, y;
				do
				{
					std::cout << "Choose your width X<11 and Y<11 for your maze: " << std::endl;
					std::cout << "X: ";
					std::cin >> x;
                    std::cout << "Y: ";
					std::cin >> y;
				} while (!check(y) || !check(x) ||stoi(x) < 11 && stoi(y) < 11);
                
				Maze maze(stoi(x), stoi(y));
				maze.generate();
				myMaze<<"Unsolved: \n";
                std::cout<<"Unsolved: \n";
				maze.print(myMaze);
				maze.solve();
				std::cout<<"\n\n\n";
				myMaze<<"Solved: \n";
                std::cout<<"Solved: \n";
				maze.print(myMaze);
				system("PAUSE");
				break;
			}
			
			case 2:
			{
				a = false;
			}
		}
	 }


		

	myMaze.close();
	return EXIT_SUCCESS;
    return 0;
}
