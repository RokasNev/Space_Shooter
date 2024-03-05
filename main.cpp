#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

int initial_position = 6;
int difficulty_level_speed;
int obsticle_amount;
int score = -12;

void print(vector<vector<char>> &grid)
{
    for(int i = 12; i >= 0; i--)
    {
        cout<<"|";
        for(int f = 0; f < 13; f++)
        {
            cout << (grid[i])[f];
        }
        cout<<"|";

        cout << endl;
    }
}

int hit(vector<vector<char>> &grid)
{
    vector<int> row_0_obsticle_positions;
    int hits = 0;

    for(int i = 0; i < grid[0].size(); i++)
    {
        if(grid[0][i] == 'O')
        {
            row_0_obsticle_positions.push_back(i);
        }
    }

    grid[0][initial_position] = 'H';

    for(int i = 0; i < row_0_obsticle_positions.size(); i++)
    {
        if(row_0_obsticle_positions[i] == initial_position)
        {
            hits++;
            grid[0][initial_position] = 'O';
        }
    }

    row_0_obsticle_positions.clear();

    return hits;
}

vector<vector<char>> space()
{
    vector<char> row = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    vector<vector<char>> grid;

    for(int i = 0; i < 13; i++)
    {
        grid.push_back(row);
    }

    return grid;
}

void movement ()
{
    if (_kbhit())
    {
        char key = _getch();

        if (key == 'a' && initial_position > 0)
        {
            initial_position--;
        }

        else if (key == 'd' && initial_position < 12)
        {
            initial_position++;
        }
    }
}

int obsticles(vector<vector<char>> &grid, int obsticle_amount)
{
    vector<int> obstacle_positions;
    vector<char> row_of_obsicles = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

    int number_of_obsticles = (rand() % obsticle_amount) + 1;

    for(int i = 0; i < number_of_obsticles; i++)
    {
        int rand_sk = (rand() % 13);
        obstacle_positions.push_back(rand_sk);
    }

    for (int i = 0; i < obstacle_positions.size() - 1; i++)
    {
        for (int j = 0; j < obstacle_positions.size() - i - 1; j++)
        {
            if (obstacle_positions[j] > obstacle_positions[j + 1])
            {
                swap(obstacle_positions[j], obstacle_positions[j + 1]);
            }
        }
    }

    for(int i = 0; i < obstacle_positions.size(); i++)
    {
        if(obstacle_positions[i] == obstacle_positions[i + 1])
        {
            obstacle_positions.erase(obstacle_positions.begin() + i);
            i = -1;
        }
    }

    for(int i = 0; i < obstacle_positions.size(); i++)
    {
        row_of_obsicles[obstacle_positions[i]] = 'O';
    }

    grid.push_back(row_of_obsicles);

    grid.erase(grid.begin());

    for(int i = 0; i < obstacle_positions.size(); i++)
    {
        row_of_obsicles[obstacle_positions[i]] = ' ';
    }

    obstacle_positions.clear();

    int hits = hit(grid);

    print(grid);

    return hits;
}

void game_over(int score)
{
    Sleep(2000);

    system("cls");

    cout << R"(
                                     ________  ________  _____ ______   _______
                                    |\   ____\|\   __  \|\   _ \  _   \|\  ___ \
                                    \ \  \___|\ \  \|\  \ \  \\\__\ \  \ \   __/|
                                     \ \  \  __\ \   __  \ \  \\|__| \  \ \  \_|/__
                                      \ \  \|\  \ \  \ \  \ \  \    \ \  \ \  \_|\ \
                                       \ \_______\ \__\ \__\ \__\    \ \__\ \_______\
                                        \|_______|\|__|\|__|\|__|     \|__|\|_______|
                                     ________  ___      ___ _______   ________
                                    |\   __  \|\  \    /  /|\  ___ \ |\   __  \
                                    \ \  \|\  \ \  \  /  / | \   __/|\ \  \|\  \
                                     \ \  \\\  \ \  \/  / / \ \  \_|/_\ \   _  _\
                                      \ \  \\\  \ \    / /   \ \  \_|\ \ \  \\  \|
                                       \ \_______\ \__/ /     \ \_______\ \__\\ _\
                                        \|_______|\|__|/       \|_______|\|__|\|__|
    )" << endl << endl;

    cout << "                                                      " << "Your score: " << score << endl << endl;
}

void menu()
{
    vector<string> difficuly = {"Easy  ","Hard  ","Insane  "};
    string easy = "Easy *";
    string hard = "Hard *";
    string insane = "Insane *";
    string temp;
    int cursor_iterator = 0;

    while(true)
    {
        cout << R"(
                                 ________  ________  ________  ________  _______
                                |\   ____\|\   __  \|\   __  \|\   ____\|\  ___ \
                                \ \  \___|\ \  \|\  \ \  \|\  \ \  \___|\ \   __/|
                                 \ \_____  \ \   ____\ \   __  \ \  \    \ \  \_|/__
                                  \|____|\  \ \  \___|\ \  \ \  \ \  \____\ \  \_|\ \
                                    ____\_\  \ \__\    \ \__\ \__\ \_______\ \_______\
                                   |\_________\|__|     \|__|\|__|\|_______|\|_______|
                                   \|_________|
                         ________  ___  ___  ________  ________  _________  _______   ________
                        |\   ____\|\  \|\  \|\   __  \|\   __  \|\___   ___\\  ___ \ |\   __  \
                        \ \  \___|\ \  \\\  \ \  \|\  \ \  \|\  \|___ \  \_\ \   __/|\ \  \|\  \
                         \ \_____  \ \   __  \ \  \\\  \ \  \\\  \   \ \  \ \ \  \_|/_\ \   _  _\
                          \|____|\  \ \  \ \  \ \  \\\  \ \  \\\  \   \ \  \ \ \  \_|\ \ \  \\  \|
                            ____\_\  \ \__\ \__\ \_______\ \_______\   \ \__\ \ \_______\ \__\\ _\
                           |\_________\|__|\|__|\|_______|\|_______|    \|__|  \|_______|\|__|\|__|
                           \|_________|
        )" << '\n';

        cout << endl << "                                          Press C to choose your difficulty" << endl << endl;

        if(_kbhit())
        {
            char cursor = _getch();

            if(cursor == 'a' && cursor_iterator > 0)
            {
                cursor_iterator--;
            }
            if(cursor == 'd' && cursor_iterator < 2)
            {
                cursor_iterator++;
            }
            if(cursor == 'c')
            {
                system("cls");
                break;
            }
        }

        temp = difficuly[cursor_iterator];

        if(cursor_iterator == 0)
        {
            difficuly[cursor_iterator] = easy;
            difficulty_level_speed = 350;
            obsticle_amount = 4;
        }
        if(cursor_iterator == 1)
        {
            difficuly[cursor_iterator] = hard;
            difficulty_level_speed = 200;
            obsticle_amount = 5;
        }
        if(cursor_iterator == 2)
        {
            difficulty_level_speed = 50;
            obsticle_amount = 7;
            difficuly[cursor_iterator] = insane;
        }

        for(int i = 0; i < difficuly.size(); i++)
        {
            cout << "                                                      " << difficuly[i] << endl;
        }

        difficuly[cursor_iterator] = temp;
        Sleep(100);
        SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), {0,0});
    }
}

int main()
{
    srand(time(0));

    menu();

    vector<vector<char>>grid = space();

    while(true)
    {
        movement();

        int hits = obsticles(grid, obsticle_amount);

        score++;

        if(hits == 1)
        {
            game_over(score);
            break;
        }

        Sleep(difficulty_level_speed);

        SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), {0,0});
    }
}
