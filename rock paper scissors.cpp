#include <iostream>
#include <string>
#include <random> // for getRandom();
#include <windows.h> // for sleep

using std::cout; using std::cin; using std::string; using std::getline; using std::ws;

// written by chapel1337
// made on 10/13/2022
// started making this at school, finished at home
// there's not much to say about this, just a basic rock paper scissors game
// i think i've perfected the returnTo() function, maybe i'll add an argument argument (:skull:) in the future

string colorsList[]{ "black", "blue", "green", "aqua", "red", "purple", "yellow", "white", "gray", "light blue", "light green", "light aqua", "light red", "light purple", "light yellow", "bright white" };

// ------- \\

void returnTo(string returnFunction);
void askReplay(string comingFrom, string chosen);

void clear()
{
    // cout << "\x1B[2J\x1B[H";
    std::system("cls");
}

void sleep(auto time)
{
    Sleep(1000 * time);
}

void title(string title)
{
    std::system(("title " + title).c_str());
}

int getRandom(int min, int max)
{
    std::mt19937 mt{ std::random_device{}() };

    std::uniform_int_distribution random{ min, max };
    return random(mt);
}

void invalidInput(string message, string returnFunction)
{
    clear();
    title("rock paper scissors - invalid input");

    cout << message << '\n';

    sleep(2);
    returnTo(returnFunction);
}

// ------- \\

void changeColor(string& textColor, string& backgroundColor)
{
    std::system(("color " + textColor + backgroundColor).c_str());

    clear();

    cout << "changed text color to " << textColor << " and background color to " << backgroundColor;

    sleep(2);
    returnTo("settings");
}

void listColors()
{
    for (int i{ 0 }; i <= 8; i++)
    {
        cout << colorsList[i] << ": " << i << '\n';
    }

    char character = 'a';
    for (int i{ 0 }; i <= 7; i++)
    {
        cout << colorsList[i + 8] << ": " << character << '\n';

        character++;
    }
    cout << '\n';
}

void changeColorMenu()
{
    clear();
    title("rock paper scissors - change color");

    listColors();

    string response{};
    string textColor{};
    string backgroundColor{};

    cout << "text color?\n";
    cin >> textColor;

    clear();
    listColors();

    cout << "background color?\n";
    cin >> backgroundColor;

    clear();

    cout << "are you sure you want to change the color?\n";
    getline(cin >> ws, response);

    if (response == "yes" || response == "y")
    {
        changeColor(textColor, backgroundColor);
    }
    else if (response == "no" || response == "n")
    {
        returnTo("settings");
    }
    else
    {
        invalidInput("input yes or no", "changeColorMenu");
    }
}

// ------- \\

void resetSettings()
{
    clear();

    std::system("color 07");

    clear();

    cout << "successfully reset the settings\n";

    sleep(2);
    returnTo("settings");
}

void settings()
{
    clear();
    title("rock paper scissors - settings");

    char response{};

    cout << "1. change color\n";
    cout << "2. reset settings\n";
    cout << "3. back\n\n";

    cout << "> ";
    cin >> response;

    switch (response)
    {
    case '1':
        changeColorMenu();
        break;

    case '2':
        resetSettings();
        break;

    case '3':
        returnTo("menu");
        break;

    default:
        invalidInput("invalid input: please specify 1, 2, or 3", "menu");
        break;
    }
}

// ------- \\

void youWin(string chosen)
{
    clear();
    title("rock paper scissors - you win!");

    cout << "computer chose " << chosen << "\n\n";
    cout << "you win!\n";

    askReplay("youWin", chosen);
}

void youTie(string chosen)
{
    clear();
    title("rock paper scissors - tie!");

    cout << "computer chose " << chosen << "\n\n";
    cout << "tie!\n";

    askReplay("youTie", chosen);
}

void youLose(string chosen)
{
    clear();
    title("rock paper scissors - you lose!");

    cout << "computer chose " << chosen << "\n\n";
    cout << "you lose!\n";

    askReplay("youLose", chosen);
}

void askReplay(string comingFrom, string chosen)
{
    title("rock paper scissors - play again?");

    string response{};

    cout << '\n';
    cout << "would you like to play again?\n\n";

    cout << "> ";
    getline(cin >> ws, response);

    if (response == "yes" || response == "y")
    {
        returnTo("start");
    }
    else if (response == "no" || response == "n")
    {
        returnTo("menu");
    }
    else
    {
        clear();

        cout << "invalid input: please specify yes or no\n";

        sleep(2);

        // invalidInput does not support arguments with returnFunction
        if (comingFrom == "youWin")
        {
            youWin(chosen);
        }
        else if (comingFrom == "youTie")
        {
            youTie(chosen);
        }
        else if (comingFrom == "youLose")
        {
            youLose(chosen);
        }
    }
}

// ------- \\

void rock()
{
    // 1 = rock, 2 = paper, 3 = scissors
    int random{ getRandom(1, 3) };

    switch (random)
    {
    case 1:
        youTie("rock");
        break;

    case 2:
        youLose("paper");
        break;

    case 3:
        youWin("scissors");
        break;
    }
}

void paper()
{
    int random{ getRandom(1, 3) };

    switch (random)
    {
    case 1:
        youWin("rock");
        break;

    case 2:
        youTie("paper");
        break;

    case 3:
        youLose("scissors");
        break;
    }
}

void scissors()
{
    int random{ getRandom(1, 3) };

    switch (random)
    {
    case 1:
        youLose("rock");
        break;

    case 2:
        youWin("paper");
        break;

    case 3:
        youTie("scissors");
        break;
    }
}

// ------- \\

void startHandler(string& input)
{
    clear();

    for (int i{ 0 }; i <= 3; ++i)
    {
        // there's probably a better way to do this
        switch (i)
        {
        case 1:
            cout << '.';
            break;

        case 2:
            cout << "..";
            break;

        case 3:
            cout << "...";
            break;
        }
        cout << '\n';

        sleep(0.5);
        clear();
    }

    if (input == "1" || input == "rock" || input == "r")
    {
        rock();
    }
    else if (input == "2" || input == "paper" || input == "p")
    {
        paper();
    }

    else if (input == "3" || input == "scissors" || input == "s")
    {
        scissors();
    }

    else
    {
        invalidInput("invalid input: please specify rock, paper, or scissors", "start");
    }
}

void start()
{
    clear();
    title("rock paper scissors");

    string input{};

    cout << "input rock, paper, or scissors: \n";
    getline(cin >> ws, input);

    startHandler(input);
}

// ------- \\

void quit()
{
    clear();

    for (int i{ 3 }; i >= 1; --i)
    {
        cout << "okay, exiting in " << i << '\n';

        sleep(1);
        clear();
    }

    sleep(0.25);
    exit(1);
}

// ------- \\

void menu()
{
    clear();
    title("rock paper scissors - menu");

    char response{};

    cout << "rock paper scissors\n\n";

    cout << "1. start\n";
    cout << "2. settings\n";
    cout << "3. quit \n\n";

    cout << "> ";
    cin >> response;

    switch (response)
    {
    case '1':
        start();
        break;

    case '2':
        settings();
        break;

    case '3':
        quit();
        break;

    default:
        invalidInput("invalid input: please specify 1, 2, or 3", "menu");
        break;
    }
}

// ------- \\

void returnTo(string returnFunction)
{
    if (returnFunction == "menu")
    {
        menu();
    }
    else if (returnFunction == "start")
    {
        start();
    }

    else if (returnFunction == "settings")
    {
        settings();
    }
    else if (returnFunction == "changeColorMenu")
    {
        changeColorMenu();
    }
}

int main()
{
    title("rock paper scissors - credits");

    cout << "rock paper scissors\n";
    cout << "written by chapel1337\n";

    sleep(2);
    menu();
}

// ------- \\