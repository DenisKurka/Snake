#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

bool GameOver;
const int width = 40;
const int height = 20;

int x, y, mouseX, mouseY, score;  //Координати и щет игрока

int tailX[100], tailY[100];
int nTail;                        //Длинна хвоста

enum MoveDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; 
MoveDirection dir;

void Setup() {          //Настройка параметров
    GameOver = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1; 
    mouseX = rand() % width;
    mouseY = rand() % height;
    score = 0;

}

void Draw() {           //прорисовка карты и змейки

    system("cls");      //Очистка консоли

    cout << "Змейка и её метаболизм" << endl;
    cout << endl;
    cout << "Управление: " << endl;
    cout << "W = вверх" << endl;
    cout << "S = в низ" << endl;
    cout << "А = в лево" << endl;
    cout << "D = в право" << endl;


    for (int i = 0; i < width + 1; i++)           //Верхняя Граница
        cout << "_";
    cout << endl;
    
   for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {               //Боковые границы
            if (j == 0 || j == width - 1)
                cout << "|";

            if (i == y && j == x)                      //Змейкка
                cout << "X";
            else if (i == mouseY && j == mouseX)       //Фрукты
                cout << "O";
            else {
                bool print = false;

                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << "x";
                    }
                }
                if(!print)
                cout << " ";
            }
        }
       cout << endl;
    }


    for (int i = 0; i < width + 1; i++)            //Нижняя граница
        cout << "-";
    cout << endl;
    
    cout << "Score: " << score <<endl;

}

void Input() {         //Слежка за нажатиями


    if (_kbhit()) {
        switch (_getch ())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            GameOver = true;
            break;
        }
    }


}

void logic() {

    int prevX = tailX[0];         //Придедущая позицыя По X 
    int prevY = tailY[0];         //Придедущая позицыя По Y
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x > width || x < 0 || y > height || y < 0)       //Режим Професионал
        GameOver = true;

    /*if (x >= width)                                       //Режим новичёк    
        x = 0;
    else if (x < 0)
        x = width - 1;*/
    

    

    
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            GameOver = true;
    }


    if (x == mouseX && y == mouseY) {
        score += 10;
        mouseX = rand() % width;
        mouseY = rand() % height;
        nTail++;
    }

}

int main(int argc, char* argv[])
{
    setlocale(0, "");

    Setup();
    while (!GameOver)
    {
        Draw();
        Input();
        logic();
    }
    return 0;
}

