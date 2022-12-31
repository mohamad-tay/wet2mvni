#include "Player.h"

//tekon helperpermutation 
Player::Player(int playerId, const permutation_t& spirit, int gamesPlayed,
               int ability, int cards, bool goalkeeper):
               m_playerId(playerId), m_spirit(spirit),m_gamesPlayed(gamesPlayed),
               m_ability(m_ability),m_cards(cards),m_goalKeeper(goalkeeper),
               m_helperGamesPlayed(0),m_helperPartialSpirt(),m_father(nullptr),
               m_myTeam(nullptr){}

Player::~Player()
{
    m_myTeam = nullptr;                   
    m_prev = nullptr;
    m_next = nullptr;
}

int Player::getCards() const
{
    return m_cards;
}

bool Player::getGoalKeeper() const
{
    return m_goalKeeper;
}

int Player::getPlayerId() const
{
    return m_playerId;
}

int Player::getGamesPlayed() const
{
    return m_gamesPlayed;
}

int& Player::getGamesPlayedch()
{
    return m_gamesPlayed;
}

