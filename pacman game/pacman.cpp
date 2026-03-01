#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

// Function Declarations
void printmaze();
void gotoxy(int x, int y);
void erase(int x, int y);
void printpacman(int x, int y);
char getcharatxy(short int x, short int y);
void ghost1(int g1X, int g1Y);
void ghost2(int g2X, int g2Y);
void ghost3(int g3X, int g3Y);
void erase1(int g1X, int g1Y);
void erase2(int g2X, int g2Y);
void erase3(int g3X, int g3Y);

int main()
{
    char again;
    int life = 3;
    int score = 0;

    for (int i = 1; i <= 3; i++) {
        system("color 0D");
        int pacmanX = 4;
        int pacmanY = 4;

        // Ghost locations
        int g1X = 18, g1Y = 1;
        int g2X = 55, g2Y = 1;
        int g3X = 1, g3Y = 7;

        bool gamerunning = true;
        system("cls");
        printmaze();
        ghost1(g1X, g1Y);
        ghost2(g2X, g2Y);
        ghost3(g3X, g3Y);
        printpacman(pacmanX, pacmanY);

        while (gamerunning) {
            // Ghost 3 Movement
            char nextlocation = getcharatxy(g3X + 1, g3Y);
            if (nextlocation == ' ') {
                erase3(g3X, g3Y);
                g3X += 1;
                ghost3(g3X, g3Y);
            } else if (nextlocation == '%') {
                erase3(g3X, g3Y);
                g3X = 1;
                g3Y = 7;
                ghost3(g3X, g3Y);
            } else if (nextlocation == 'P') {
                gamerunning = false;
                life--;
            }

            // Ghost 2 Movement
            nextlocation = getcharatxy(g2X, g2Y + 1);
            if (nextlocation == ' ') {
                erase2(g2X, g2Y);
                g2Y += 1;
                ghost2(g2X, g2Y);
            } else if (nextlocation == '%') {
                erase2(g2X, g2Y);
                g2X = 55;
                g2Y = 1;
                ghost2(g2X, g2Y);
            } else if (nextlocation == 'P') {
                gamerunning = false;
                life--;
            }

            // Ghost 1 Movement
            nextlocation = getcharatxy(g1X, g1Y + 1);
            if (nextlocation == ' ') {
                erase1(g1X, g1Y);
                g1Y += 1;
                ghost1(g1X, g1Y);
            } else if (nextlocation == '%') {
                erase1(g1X, g1Y);
                g1X = 18;
                g1Y = 1;
                ghost1(g1X, g1Y);
            } else if (nextlocation == 'P') {
                gamerunning = false;
                life--;
            }

            // Pacman Movement
            if (GetAsyncKeyState(VK_LEFT)) {
                char nextlocation = getcharatxy(pacmanX - 1, pacmanY);
                if (nextlocation == ' ' || nextlocation == '.') {
                    erase(pacmanX, pacmanY);
                    pacmanX -= 1;
                    printpacman(pacmanX, pacmanY);
                }
                if (nextlocation == '.') {
                    score += 1;
                }
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                char nextlocation = getcharatxy(pacmanX + 1, pacmanY);
                if (nextlocation == ' ' || nextlocation == '.') {
                    erase(pacmanX, pacmanY);
                    pacmanX += 1;
                    printpacman(pacmanX, pacmanY);
                }
                if (nextlocation == '.') {
                    score += 1;
                }
            }
            if (GetAsyncKeyState(VK_UP)) {
                char nextlocation = getcharatxy(pacmanX, pacmanY - 1);
                if (nextlocation == ' ' || nextlocation == '.') {
                    erase(pacmanX, pacmanY);
                    pacmanY -= 1;
                    printpacman(pacmanX, pacmanY);
                }
                if (nextlocation == '.') {
                    score += 1;
                }
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                char nextlocation = getcharatxy(pacmanX, pacmanY + 1);
                if (nextlocation == ' ' || nextlocation == '.') {
                    erase(pacmanX, pacmanY);
                    pacmanY += 1;
                    printpacman(pacmanX, pacmanY);
                }
                if (nextlocation == '.') {
                    score += 1;
                }
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {
                system("cls");
                exit(0);
            }

            Sleep(100);
            gotoxy(0, 14);
            cout << "SCORE = " << score << endl;
            cout << "LIFES = " << life;
        }
    }

    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t---------------------------------------------\n";
    cout << "\t\t\t\t\tTHANK YOU FOR PLAYING\n\t\t\t\tSCORE = " << score << endl;
    cout << "\t\t\t\t\tPRESS R TO RESTART THE GAME \n";
    cout << "\t\t\t\t\t---------------------------------------------";
    cin >> again;
    if (again == 'R' || again == 'r') {
        main();
    }

    return 0;
}

// Supporting Functions
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getcharatxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufsize = {1, 1};
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufsize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void printpacman(int x, int y)
{
    gotoxy(x, y);
    cout << "P";
}

void printmaze()
{
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%   .       .      .         .           .         .           .       .       .  %" << endl;
    cout << "% . |#########|       |###########|   |###########|       ####    ###    ####     %" << endl;
    cout << "%   |  spawn  |       |   AVOID   |   |  COLLECT  |       ### #  #   #    ###  .  %" << endl;
    cout << "% .        .  |       |   GHOST   |   |   DOTS    |       ###     #  #  . #####   %" << endl;
    cout << "%   |#########|       |###########|   |###########|       # # # . #  #   ####     %" << endl;
    cout << "%    .     .    .     .      .      .        .       .     ###   ######  ####     %" << endl;
    cout << "%                                                                                 %" << endl;
    cout << "% . ### . ##   ##    # # # #   ##   ##  #    .       .        .         .      .  %" << endl;
    cout << "%   #_#  #--# # .    #  #  #  #--#  # # #     -#-#-#-       -#-#-#-#-#-#-#-#-#-   %" << endl;
    cout << "% . #    #  #  ##    #  .  #  #  #  #  ##  .  -#-#-#-       -#-#-#-#-#-#-#-#-#- . %" << endl;
    cout << "%       .      .      .    .          .        .               .         .        %" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}

void erase(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void erase1(int g1X, int g1Y)
{
    gotoxy(g1X, g1Y);
    cout << " ";
}

void erase2(int g2X, int g2Y)
{
    gotoxy(g2X, g2Y);
    cout << " ";
}

void erase3(int g3X, int g3Y)
{
    gotoxy(g3X, g3Y);
    cout << " ";
}

void ghost1(int g1X, int g1Y)
{
    gotoxy(g1X, g1Y);
    cout << "G";
}

void ghost2(int g2X, int g2Y)
{
    gotoxy(g2X, g2Y);
    cout << "G";
}

void ghost3(int g3X, int g3Y)
{
    gotoxy(g3X, g3Y);
    cout << "G";
}
