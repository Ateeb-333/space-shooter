#include<conio.h>                     // for get character function
#include <iostream>                   //for input output
#include<cstdlib>                     //for functions
#include<cmath>                       //for mathematical functions
#include<time.h>        //for rand and srand function
#include<cstring>                //charcter arrays and strings
#include <windows.h>  //for colors
#include<stdlib.h>    //for colors
//#include <mmsystem.h>  //for audio
using namespace std;


const int rows = 20;
const int columns = 50;
char arr[rows][columns];
int randomiser;
int health = 10;
int stage = 1;
int stage2 = 2;
const char spaceship = '&';
const char borders = '*';
int scoring = 35;
char key;
static int speed = 0;
int check = 0;



void healthdec(int rows, int columns)    //health decrement function

{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (arr[rows][columns] == '$')
				if (arr[rows][columns] == '!')
					health = health - 10;

		}
	}
	cout << "\nscore =" << scoring;
	cout << "\t\t\t\thealth = " << health << endl;
}


void scoreincrease(int rows, int columns)  //score increase and enemy removal
{

	char ship = '$';
	static int speed_fire = 0;
	if (speed_fire >= 2)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (arr[rows][columns] == '#')
					if (arr[rows][columns] == '!')
					{
						arr[rows][columns] = ' ';
					}
				if (arr[i][j] == '&' && arr[i + 1][j] == '#')
				{
					arr[i][j] = ' ';
					scoring = scoring + 2;
				}



			}
		}
	}

}

void sides(int _row, int _col)          //borders of gameboard "*"
{



	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i == 0 || i == rows - 1)
			{
				arr[i][j] = borders;
			}
			else if (j == 0 || j == columns - 1)
			{
				system("color 06");
				arr[i][j] = '*';
			}
			else
			{
				arr[i][j] = ' ';
			}


		}
	}
	arr[_row][_col] = spaceship;
}


void screen()     //display board and health etc.
{
	system("cls");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
	if (scoring > 30)
	{
		swap(stage, stage2);
	}
	healthdec(rows, columns);
	scoreincrease(rows, columns);
	if (scoring < 30)
	{
		cout << "\n\t\t\tSTAGE : 1" << endl;
	}
	else if (scoring > 30)
	{
		cout << "\nSTAGE : 2" << endl;
	}
}
void movementofspaceship(char input)     //movement of spaceship and its fires
{

	if (input == 'w' || input == 'W')  //up
	{

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				int temp = i - 1;
				if (arr[i][j] == spaceship)
				{
					swap(arr[temp][j], arr[i][j]);
					break;
				}
			}
		}
	}
	else if (input == 'A' || input == 'a')      //left
	{

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (arr[i][j] == spaceship)
				{
					swap(arr[i][j - 1], arr[i][j]);

				}



			}
		}
	}
	else if (input == 'S' || input == 's')   //down
	{

		for (int i = rows; i >= 0; i--)
		{
			for (int j = 0; j < columns; j++)
			{
				if (arr[i][j] == spaceship)
				{

					arr[i + 1][j] = '&';
					arr[i][j] = ' ';

					break;

				}
			}
		}
	}
	else if (input == 'D' || input == 'd')    //right
	{

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (arr[i][j] == spaceship)
				{
					swap(arr[i][j + 1], arr[i][j]);
					break;
				}
			}
		}

	}
	if (input == ' ')   //space for ship fires
	{

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (arr[i][j] == spaceship)
				{
					arr[i - 1][j] = '|';
					break;
				}
			}
		}


	}

}


bool locationofenemy()   //check for enemy
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 49; j++)
		{
			if (arr[i][j] == '#')
			{
				return true;
			}
		}
	}      return false;
}
void enemysmovement()   //movement of enemy
{

	static int speed = 0;
	speed++;
	if (!locationofenemy())
	{
		int pos = rand() % 48 + 1;
		arr[1][pos] = '#';

	}
	if (speed == 2)
	{
		speed = 0;
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 48; j >= 0; j--)
			{
				int temp = i + 1;
				if (arr[i][j] == '#')
					if (i == 18)
					{
						arr[i][j] = ' ';
					}

				if (arr[i][j] == '#')
				{
					arr[i][j] = ' ';

					arr[temp][j] = '#';
				}

			}
		}
	}
}




void fireofenemy()    //firing of enemy
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (arr[i][j] == '#')
			{
				arr[i + 1][j] = '!';
				break;
			}
		}
	}
}

void enemysfiremovement() //movement of enemy fires and border intruption solving

{

	{

		speed++;

		if (speed == 2)
		{
			speed = 0;
			for (int i = 19; i >= 0; i--)
			{
				for (int j = 48; j >= 0; j--)
				{
					if (arr[i][j] == '!')
						if (j == 48 || i == 18)
						{
							arr[i][j] = ' ';
						}

					if (arr[i + 1][j] == '&')
						if (arr[i][j] == '!')
						{
							arr[i][j] = ' ';
							health--;

						}

					if (arr[i][j] == '!')
					{
						arr[i][j] = ' ';
						arr[i + 1][j] = '!';
					}
					if (arr[i - 1][j] == '#' && arr[i][j] == '!')
					{
						arr[i - 1][j] = ' ';

					}
					if (arr[i][j] == '|')
						if (arr[i + 1][j] == '#')
						{
							scoring++;
						}
				}
			}
		}
	}



}

void enemyremoval() //removing enemy
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (arr[i][j] == '#')
				if (arr[i][j] == '|')
				{
					scoring++;
					arr[i][j] = ' ';


				}
			if (arr[i + 1][j] == '#' && arr[i][j] == '|')
			{
				arr[i][j] = ' ';
				scoring = scoring + 2;
			}

		}
	}
}

void shipfiremove() //ships fire removing and solving border intruption
{
	static int speed_fire = 0;
	speed_fire++;
	if (speed_fire >= 2)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (arr[i][j] == '|')
					if (i == 1)
					{
						arr[i][j] = ' ';

					}

				if (arr[i][j] == '|')
					if (i != 0)
					{
						arr[i][j] = ' ';
						arr[i - 1][j] = '|';
					}

			}
		}

	}
}
void enemymovementtwo()   //stage 2 enemys 
{
	static int speed = 2;
	speed++;
	if (!locationofenemy())
	{

		for (int i = 2; i < 4; i++)
		{
			srand(time(0));

			for (int j = 1; j < 9; j++)
			{
				srand(time(0));
				int position = rand() % 48 + 1;
				arr[position][i] = '#';
				arr[position + 1][i] = '#';
				arr[position + 2][i] = '#';
				arr[position + 3][i] = '#';
				arr[i][position] = '#';
				arr[i][position + 1] = '#';
				arr[i][position + 2] = '#';
				arr[i][position + 3] = '#';

			}
		}

	}
	if (speed == 2)
	{
		speed = 0;
		for (int i = 2; i <= 4; i++)
		{
			for (int j = 48; j >= 0; j--)
			{
				if (arr[i][j] == '#' && j == 48)
				{
					arr[i][j] = ' ';
				}
				if (arr[i][j] == '#')
				{
					arr[i][j] = ' ';
					arr[i][j + 1] = '#';
				}
			}
		}
	}
}
void gifts()                //stage 2 gifts
{
	static	 int gs = 0; //giftspeed
	gs++;


	int position2 = rand() % 48 + 1;
	int position1 = rand() % 18 + 1;
	arr[position1][position2] = '+';



	static int speed = 0; //static is used so the value don,t decrease
	speed++;


	if (speed == 3)
	{
		speed = 0;
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 48; j >= 0; j--)
			{
				if (arr[i][j] == '+' && i == 18) //border intruption and overlaping gifts solved
				{
					arr[i][j] = ' ';
				}

				if (arr[i + 1][j] == '&' && arr[i][j] == '+')               //score increase on gifts     
				{
					arr[i][j] = ' ';
					scoring = scoring + 2;
				}

				if (arr[i][j] == '+')                                      //moving next index
				{
					arr[i][j] = ' ';
					arr[i + 1][j] = '+';


				}
			}
		}
	}
}



int main()  //main body all functions called inside
{

	//PlaySound(TEXT("lifelike-126735.mp3"), NULL, SND_FILENAME | SND_ASYNC);  //background sound
	system("color f0");
	cout << "\t       **space shooter game**" << endl;
	cout << "\n\n\t\tpress 1 for instructions" << endl;  //main menu
	cout << "\t\tpress 2 to play game" << endl;

	cin >> check;
	if (check == 1)
	{

		cout << "- use w a s d to control space ship" << endl;    //instructions
		cout << "- game will be over when health is zero" << endl;
	}
	cin >> check;
	if (check == 2)
	{
		system("color f0");

		srand(time(0));
		int temp = 0;

		sides(15, 20);

		int em = 0;
		while (health >= 0) //check for health 
		{
			while (1)
			{

				if (scoring < 30)  //stage 1
				{
					em++;
					if (em == 7)
					{
						enemysmovement();
						em = 0;
					}
					fireofenemy();

					enemysfiremovement();
					screen();
					if (_kbhit())    //checks for a recent keystroke
					{
						int move = 0;
						move = _getch();
						movementofspaceship(move);
					}
					enemyremoval();
					shipfiremove();
					system("cls");
					if (health <= 0)   //game over when health is zero
					{
						system("color 40");
						cout << "\n\n\t\t  GAME OVER!!!" << endl;
						cout << "\n\n\t\t  YOU LOST !!!" << endl;
						cout << "\n\n\t\ttotal score is : " << scoring << endl;
						system("pause");

					}

				}
				if (scoring > 30)  //stage 2
				{


					em++;
					if (em == 7)
					{
						enemymovementtwo();
						em = 0;
					} //gifts();
					fireofenemy();
					gifts();

					enemysfiremovement();
					screen();
					if (_kbhit())
					{
						int move = 0;
						move = _getch();
						movementofspaceship(move);
					}
					enemyremoval();
					shipfiremove();
					system("cls");
					if (health <= 0)
					{

						system("color 40");

						cout << "\n\n\t\t  GAME OVER" << endl;
						cout << "\n\n\t\t  YOU LOST !!!" << endl;
						cout << "\n\n\t\ttotal score is : " << scoring << endl;
						system("pause");

					}
					if (scoring >= 45)    //game win
					{
						system("color 47");
						system("cls");

						cout << "\n\n\t\tYOU WON THE GAME!!!!" << endl;
						cout << "\n\n\t\tYOU WON THE GAME!!!!" << endl;
						cout << "\n\n\t\tcongratulations!!!!" << endl;
						cout << "\n\n\t\tyour total score is : " << scoring << endl;

						system("pause");
					}
				}
			}
		}
	}

}


