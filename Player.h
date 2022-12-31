#ifndef PLAYER_H_
#define PLAYER_H_
class Team;
#include "Team.h"
#include "wet2util.h"

class Player
{
  private:
    int m_playerId;
    int m_gamesPlayed;
    int m_cards;
    bool m_goalKeeper;
    int m_ability;
    permutation_t m_spirit;    //include
  public:
    int m_helperGamesPlayed;
    permutation_t m_helperPartialSpirt;
    Player* m_father;
    Team* m_myTeam;

   public:
    Player(int playerId, const permutation_t& spirit, int gamesPlayed, int ability, int cards, bool goalkeeper);
    ~Player();
    int getCards() const;
    bool getGoalKeeper() const;
    int getPlayerId() const;
    int getGamesPlayed() const;
    int& getGamesPlayedch();

     

};





#endif // PLAYER_H_