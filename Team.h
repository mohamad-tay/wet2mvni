#ifndef TEAM_H_
#define TEAM_H_
class Player;
#include "Player.h"
#include "BST.h"
#include <memory>
#include <iostream>

class Team
{
    private:
    BST<int,Player*> m_teamPlayersId;
    BST<Player*,int> m_teamPlayersGoals; 
    int m_teamId;       //put int = id
    int m_teamPoints;
    int m_teamGoals;
    int m_teamCards;
    int m_numOfTeamPlayers;                   // kolel goalkeeper ?? yes
    int m_numOfTeamGoalKeeper;
    int m_moreGamesPlayed;
    bool m_isInLegalTeams;
    public:
    Player* m_topTeamScorer;                // shared_ptr                      
    typename BST<int,int>::node* m_hisLegalTeam;

    public:
    Team(int teamId,int points);
    ~Team();
    int getNumOfAllTeamPlayers() const;
    bool isAlegalTeam() const;
    BST<int,Player*>& getTeamPlayersId();
    BST<Player*,int>& getTeamPlayersGoals();
    int getMoreGames() const;
    int& getMoreGamesToChange();
    int getTeamId() const;
    int getTeamPoints() const;
    void addPlayerData(Player* player);
    bool isInLegalTeams() const;
    bool& gitIsInLegalTeams();
    int pointsGoalsCards() const;
    void removePlayerData(Player* player);
    void updatePoints(int points);
    int getTeamGoals() const;
    int getTeamCards() const;
    int getnumOfTeamGoalKeeper() const;
    void updateAfterUnite(int numAllPlayers, int points,int goals, int cards, int numallGoalKeeper,
                          bool islegal, Player* topScorrer);
    void zero();
};
//1









#endif // TEAM_H_