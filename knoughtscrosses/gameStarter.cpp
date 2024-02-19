#include "gameStarter.h"
#include <iostream>

void gameStarter::humanVsHuman()
{
    bool win = false;

    while (!win)
    {
        int pos = 0;
        std::cout << "what position would you like to place your counter";
        std::cin >> pos;
        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);

            win = myboard->checkallwin(pos);
            if (win)
            {
                std::cout << "noice";
                myboard->startNewGame();
            }
            else if(myboard->checkDraw())
            {
                myboard->startNewGame();
            }
            myboard->switchCounter();
            myboard->presentBoard();
        }
    }
}

void gameStarter::AISelfPlay(agent* myAgent)
{
    bool win = false; 
    myAgent->getCurrentState()->updateLegalMoves(myboard);
    myAgent->getCurrentState()->id = 1;
    int episodes = 1000;
   
    while (myAgent->getEpisodeCount() < episodes)
    {
        //std::cout << "the current episodes" + myAgent->getEpisodeCount() << std::endl;
        bool minOrMax = myboard->getCounter();
        myAgent->takeAction(minOrMax % 2);//if counter 2 false 
        int pos = myAgent->getAction();
        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);
            myAgent->afterActionUpdates();
            myAgent->getCurrentState()->updateLegalMoves(myboard); 

            win = myboard->checkallwin(pos);
            if (win)
            {
                //std::cout << "noice";
                myboard->startNewGame();
                myAgent->agentCleanUp();
            }
            else if (myboard->checkDraw())
            {
                myboard->startNewGame();
                myAgent->agentCleanUp();
            }
            else
            {
                myboard->switchCounter();
            }
            //myboard->presentBoard();
        }
    }
    std::cout << "finished" << std::endl;

}

void gameStarter::humanVSAi(agent* myAgent)
{

    bool win = false;
    myAgent->getCurrentState()->updateLegalMoves(myboard);
    myAgent->getCurrentState()->id = 1;
    int episodes = 1000;
    int pos = 0;
    while (!win)
    {
        if (myboard->getCounter() == 1)
        {
            //std::cout << "the current episodes" + myAgent->getEpisodeCount() << std::endl;
            bool minOrMax = myboard->getCounter();
            myAgent->takeAction(minOrMax % 2);//if counter 2 false 
            pos = myAgent->getAction();
        }
        else
        {

            std::cout << "what position would you like to place your counter";
            std::cin >> pos;
        }

        if (myboard->legalMove(pos))
        {
            myboard->setCounter(pos);
            myAgent->afterActionUpdates();


            win = myboard->checkallwin(pos);
            if (win)
            {
                //std::cout << "noice";
                myboard->startNewGame();

            }
            else if (myboard->checkDraw())
            {
                myboard->startNewGame();

            }
            else
            {
                myboard->switchCounter();
            }
            myboard->presentBoard();
        }
    }

}
