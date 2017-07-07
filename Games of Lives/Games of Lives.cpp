#include "iostream"
#include "windows.h"
#include "time.h"
#include "stdlib.h"
#include "fstream"
#include "conio.h"
#define MAXLEN 20
using namespace std;
int map[MAXLEN][MAXLEN] = {0};
int map_tmp[MAXLEN][MAXLEN] = {0};
ifstream fin("map.txt");
ofstream fout("map_out.txt");
ofstream fout_new("map_new.txt");

void print_map(); 

void gotoxy(int x,int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void set_forecolor_white()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void set_forecolor_green()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

void create_random_map()
{
	srand((unsigned)time(NULL));
	for(int i = 1; i < MAXLEN - 1; i++)
	{
		for(int j = 1; j < MAXLEN - 1; j++)
		{
			map[i][j] = rand()%2;
		}
	}
}

void read_in_map()
{
	if(fin!=NULL)
	{
		for(int i = 0; i < MAXLEN; i++)
		for(int j = 0; j < MAXLEN; j++)
		{
			fin>>map[i][j];
		}
	}
	fin.close();
}

void map_out()
{
	for(int i = 0; i < MAXLEN; i++)
	{
		for(int j = 0; j < MAXLEN; j++)
		{
			fout<<map[i][j]<<" ";
		}
		fout<<endl;	
	}
	fout.close();
}

void map_out_new()
{
	for(int i = 0; i < MAXLEN; i++)
	{
		for(int j = 0; j < MAXLEN; j++)
		{
			fout_new<<map[i][j]<<" ";
		}
		fout_new<<endl;	
	}
	fout_new.close();
}

int welcome_view()
{
	int inp = 0;
	gotoxy(85,10);
	cout<<"Welcome to the Game of Lives!"<<endl;
	gotoxy(85,12);
	cout<<"Press '1' to Readin Your Map"<<endl;
	gotoxy(85,13);
	cout<<"Press '2' to create Rand One"<<endl;
	gotoxy(85,14);
	cout<<"Press '3' to Outport a new Map"<<endl;
	gotoxy(85,16);
	cout<<"Press Any Key to Quit"<<endl;
	gotoxy(0,0);
	cin>>inp;
	while(inp == 3)
	{
		map_out_new();
		cin>>inp;
	}
	return inp;
}

void copy_array(int arr1[MAXLEN][MAXLEN],int arr2[MAXLEN][MAXLEN])
{
	for(int i = 0; i < MAXLEN; i++)
	for(int j = 0; j < MAXLEN; j++)
	{
		arr2[i][j] = arr1[i][j];
	}
}

int neighbors(int pos_i, int pos_j)
{
	int count_live = 0;
	if((map[pos_i - 1][pos_j - 1]) == 1)
	{
		count_live++;
	}
	if((map[pos_i - 1][pos_j]) == 1)
	{
		count_live++;
	}
	if((map[pos_i - 1][pos_j + 1]) == 1)
	{
		count_live++;
	}
	if((map[pos_i][pos_j - 1]) == 1)
	{
		count_live++;
	}
	if((map[pos_i][pos_j + 1]) == 1)
	{
		count_live++;
	}
	if((map[pos_i + 1][pos_j - 1]) == 1)
	{
		count_live++;
	}
	if((map[pos_i + 1][pos_j]) == 1)
	{
		count_live++;
	}
	if((map[pos_i + 1][pos_j + 1]) == 1)
	{
		count_live++;
	}
	return count_live;
}

void generate()
{
	copy_array(map,map_tmp);
	for(int i = 1; i < MAXLEN - 1; i++)
	{
		for(int j = 1; j < MAXLEN - 1; j++)
		{
			switch(neighbors(i,j))
			{
				case 3:map_tmp[i][j] = 1;break;
				case 2:break;
				case 0:
				case 1:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:map_tmp[i][j] = 0;break;
				default:break;
			}
		}
	}
	copy_array(map_tmp,map);
}

void init()
{
	SetConsoleTitle("Games of Lives");
	for(int i = 0; i < MAXLEN; i++)
	{
		map[0][i] = 2;
		map[MAXLEN - 1][i] = 2;
	}
	for(int i = 0; i < MAXLEN; i++)
	{
		map[i][0] = 2;
		map[i][MAXLEN - 1] = 2;
	}
}

void print_map()
{
	for(int i = 0; i < MAXLEN; i++)
	{
		for(int j = 0; j < MAXLEN; j++)
		{
			if(map[i][j] == 2)
			{
				set_forecolor_green();
				cout<<"¡ö";
			}
			else if(map[i][j] == 0)
			{
				set_forecolor_white();
				cout<<"¡õ"; 
			}
			else if(map[i][j] == 1)
			{
				set_forecolor_white();
				cout<<"¡ö"; 
			}
		}
		cout<<endl;
	}
	set_forecolor_white();
}

int main()
{
	int cho;
	init();
	cho = welcome_view();
	switch(cho)
	{
		case 1:read_in_map();break;
		case 2:create_random_map();
		default:create_random_map();
	}
	gotoxy(0,0);
	print_map();
	while(1)
	{
		gotoxy(0,0);
		generate();
		print_map();
		Sleep(1000);
		if(kbhit())
		{
			break;
		}
	}
	map_out();
	return 0;
 } 
