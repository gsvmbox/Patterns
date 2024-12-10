#include <iostream>
using namespace std;
/**
 * An abstract class that is common to several games in
 * which players play against the оthers, but only one is
 * playing at a given time.
 */

class GameObject
{
protected:
    int PlayersCount;

    virtual bool EndOfGame() = 0;
    virtual void InitializeGame() = 0;
    virtual void MakePlay(int player) = 0;
    virtual void PrintWinner() = 0;

public:
    /* A template method: */
    void PlayOneGame(int playersCount)
    {
        PlayersCount = playersCount;
        InitializeGame();

        int j = 0;

        while (!EndOfGame() and j <= 2) {
            MakePlay(j);
             j = (j + 1) * playersCount;
        }

        PrintWinner();
    }
};

class Сheckers : public GameObject
{
protected:
    /* Implementation of necessary concrete methods */
    void InitializeGame() override
    {
        // Initialize game
        cout << "Играем в ШАШКИ" << endl;
        cout << "Расстановка шашек" << endl;
    }

    void MakePlay(int player) override
    {
        // Process one turn of player
        cout << "Игрок "<<player/2<<" - ваш ход!" << endl;
    }

    bool EndOfGame() override
    {
        return false;
    }

    void PrintWinner() override
    {
        // Display who won
        cout << "Победила дружба" << endl;
    }
};

class Chess : public GameObject
{
protected:
    /* Implementation of necessary concrete methods */
    void InitializeGame() override
    {
        // Put the pieces on the board
        cout <<endl<< "Играем в ШАХМАТЫ" << endl;
        cout << "Расстановка фигур" << endl;
        cout << "Определение очердности хода" << endl;
    }

    void MakePlay(int player) override
    {
        // Process a turn for the player
        cout << "Игрок " << player / 2 << " - ваш ход!" << endl;
    }

    bool EndOfGame() override
    {
        // Return true if in Checkmate or Stalemate has been reached
        return false;
    }

    void PrintWinner() override
    {
        // Display the winning player
        cout << "Победитель не выявлен - ничья" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    GameObject* game = new Сheckers();
    game->PlayOneGame(2);
 
    game = new Chess();
    game->PlayOneGame(2);
    delete game;

    return 0;
}