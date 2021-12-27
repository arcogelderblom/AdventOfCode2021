#include <iostream>
#include <chrono>
#include <map>
#include <set>

#include "inputfile.hpp"
#include "stringoperations.hpp"
#include "vectoroperations.hpp"

struct Player
{
	int playerNum;
	int score = 0;
    int currentPos;
    friend bool operator<(const Player& lhs, const Player& rhs) //friend claim has to be here
    {
        return lhs.playerNum < rhs.playerNum && lhs.score < rhs.score && lhs.currentPos < rhs.currentPos;
    }
};

std::vector<Player> toVectorWithPlayers(std::vector<std::string> stringVectorPlayersStartingPositions)
{
	std::vector<Player> result;
	for (std::string stringVectorPlayerStartingPosition : stringVectorPlayersStartingPositions)
	{
		Player player;
		std::vector<std::string> splitted = StringOperations::splitString(stringVectorPlayerStartingPosition, " ");
		player.playerNum = std::stoi(splitted[1]);
        player.currentPos = std::stoi(*splitted.rbegin());
        result.push_back(player);
	}
	return result;
}

long play(std::vector<Player> players, int diceSides, int winningScore)
{
	int timesDiceRolled = 0;
	int currentDiceSide = 0;
	std::set<int> playerPlayOrder;
	for (Player player : players)
	{
		playerPlayOrder.insert(player.playerNum);
	}
	int amountOfOtherPlayers = playerPlayOrder.size() - 1;
	std::set<int>::iterator currentPlayerPlay = playerPlayOrder.begin();
	while (std::find_if(players.begin(), players.end(), [](Player p){ return p.score >= 1000; }) == players.end())
	{
		int currentThrow = 0;
		// roll dice
		for (int i = 0; i < 3; i++)
		{
			timesDiceRolled++;
			currentDiceSide++;
			currentThrow += currentDiceSide;
			if (currentDiceSide == diceSides)
			{
				currentDiceSide = 0;
			}
		}
        
		int stepsToTake = currentThrow % 10;
		
		// current position
		Player& currentPlayer = *std::find_if(players.begin(), players.end(), [&](const Player & p){ return p.playerNum == *currentPlayerPlay; });
		int newPosition = currentPlayer.currentPos;
		// move player
		for (int i = 0; i < stepsToTake; i++)
		{
			newPosition++;
            if (newPosition > 10)
            {
                newPosition -= 10;
            }
		}
		currentPlayer.score += newPosition;
        currentPlayer.currentPos = newPosition;
		
		currentPlayerPlay++;
		if (currentPlayerPlay == playerPlayOrder.end())
		{
			currentPlayerPlay = playerPlayOrder.begin();
		}
	}
	
	return (*std::find_if(players.begin(), players.end(), [](const Player & p){ return p.score < 1000; })).score * timesDiceRolled;
}


// map which holds game state and outcome
std::map< std::vector<Player>, std::pair<long long, long long> > gameStateAndOutcome;
std::pair<long long, long long> getHowManyUniversesPlayerWins(std::vector<Player>& players, int diceSides, int winningScore)
{
    if (std::find_if(players.begin(), players.end(), [&](const Player & p){ return p.playerNum == 1; })->score >= winningScore)
    {
        return std::make_pair(1, 0);
    }
    if (std::find_if(players.begin(), players.end(), [&](const Player & p){ return p.playerNum == 2; })->score >= winningScore)
    {
        return std::make_pair(0, 1);
    }
    if (gameStateAndOutcome.find(players) != gameStateAndOutcome.end())
    {
        return gameStateAndOutcome[players];
    }

    std::pair<long long, long long> outcome = std::make_pair(0, 0);
    for (int d1 = 1; d1 <= diceSides; d1++)
    {
        for (int d2 = 1; d2 <= diceSides; d2++)
        {
            for (int d3 = 1; d3 <= diceSides; d3++)
            {   
                int stepsToTake = (d1 + d2 + d3) % 10;
                Player& currentPlayer = players[0];
                int newPosition = currentPlayer.currentPos;
                // move player
                for (int i = 0; i < stepsToTake; i++)
                {
                    newPosition++;
                    if (newPosition > 10)
                    {
                        newPosition -= 10;
                    }
                }
                currentPlayer.currentPos = newPosition;
                currentPlayer.score += newPosition;

                std::reverse(players.begin(), players.end());
                std::pair<long long, long long> result = getHowManyUniversesPlayerWins(players, diceSides, winningScore);
                outcome.first += result.first;
                outcome.second += result.second;
            }
        }
    }
    gameStateAndOutcome[players] = outcome;
    return outcome;
}

int main(void)
{
    std::vector<std::string> testInput = StringOperations::splitString("Player 1 starting position: 4\nPlayer 2 starting position: 8", "\n");
    std::vector<Player> testVectorWithPlayers = toVectorWithPlayers(testInput);
    assert(play(toVectorWithPlayers(testInput), 100, 1000) == 739785);
    
    InputFile inputFile("InputFiles/day21.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::vector<Player> vectorWithPlayers = toVectorWithPlayers(input);
    std::cout << "Day 21, puzzle 1: " << std::flush << play(vectorWithPlayers, 100, 1000) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    std::pair<long long, long long> testResult = getHowManyUniversesPlayerWins(testVectorWithPlayers, 3, 21);
    std::cout << testResult.first << std::endl;
    std::cout << testResult.second << std::endl;
    assert((testResult.first > testResult.second ? testResult.first : testResult.second)  == 444356092776315);
    t_begin = std::chrono::high_resolution_clock::now();    
    std::pair<long long, long long> result = getHowManyUniversesPlayerWins(vectorWithPlayers, 3, 21);
    std::cout << "Day 21, puzzle 2: " << std::flush << (result.first > result.second ? result.first : result.second) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}