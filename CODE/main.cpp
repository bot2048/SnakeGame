#include<iostream>
#include"Game.h"



int main()
{
    //Init strand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Window
    Game game;

    //Game Loop

    while (game.running() && !game.getEndGame())
    {


        //update
        game.update();




        //render

        game.render();


    }


    //End of Application
    return 0;
}