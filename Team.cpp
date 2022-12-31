#include "Team.h"

Team::Team(int teamId,int points) :
m_teamPlayersId(),m_teamPlayersGoals(),m_teamId(teamId),m_teamPoints(points),m_teamGoals(0),
m_teamCards(0),m_numOfTeamPlayers(0),m_numOfTeamGoalKeeper(0), 
m_moreGamesPlayed(0),m_isInLegalTeams(false),m_topTeamScorer(nullptr),m_hisLegalTeam(nullptr)
{}

Team::~Team()
{
    m_teamPlayersId.DeleteNodeInfoIsPoiter2();
    m_teamPlayersGoals.DeleteNodeKeyIsPointer();
    m_topTeamScorer = nullptr;
    m_hisLegalTeam = nullptr;
}

int Team::getNumOfAllTeamPlayers() const
{
    return m_numOfTeamPlayers;
}

bool Team::isAlegalTeam() const
{
    return ( m_numOfTeamGoalKeeper>=1 && (m_numOfTeamPlayers-1)>=10);
}

BST<int,Player*>& Team::getTeamPlayersId()
{
    return m_teamPlayersId;
}

BST<Player*,int>& Team::getTeamPlayersGoals()
 {
    return m_teamPlayersGoals;
 }

 int Team::getMoreGames() const
 {
    return m_moreGamesPlayed;
 }

 int& Team::getMoreGamesToChange()
 {
    return m_moreGamesPlayed;
 }


 int Team::getTeamId() const
 {
    return m_teamId;
 }

 int Team::getTeamPoints() const
 {
    return m_teamPoints;
 }

 void Team::addPlayerData(Player* player)
 {
    m_teamGoals+=player->getGoals();
    m_teamCards+=player->getCards();
    if(player->getGoalKeeper())
    {
        m_numOfTeamGoalKeeper++;
    }
    m_numOfTeamPlayers++;
    if(m_topTeamScorer != nullptr && *(player) > *(m_topTeamScorer))
    {
        m_topTeamScorer = player;
    }
    if(m_topTeamScorer == nullptr)
    {
        m_topTeamScorer = player;
    }
 }
 
bool Team::isInLegalTeams() const
{
    return m_isInLegalTeams;
}

bool& Team::gitIsInLegalTeams()
{
    return m_isInLegalTeams;
}
 
int Team::pointsGoalsCards() const
{
    return m_teamPoints+m_teamGoals-m_teamCards;
}

void Team::removePlayerData(Player* player)
{
    m_teamGoals-=player->getGoals();
    m_teamCards-=player->getCards();
    if(player->getGoalKeeper())
    {
        m_numOfTeamGoalKeeper--;
    }
    m_numOfTeamPlayers--;
    m_topTeamScorer = (m_teamPlayersGoals.FindBiggestNodeFF())->key;
  
}

void Team::updatePoints(int points)
{
    m_teamPoints += points;
    m_moreGamesPlayed ++;
}

int Team::getTeamGoals() const
{
    return m_teamGoals;
}

int Team::getTeamCards() const
{
    return m_teamCards;
}

int Team::getnumOfTeamGoalKeeper() const
{
    return m_numOfTeamGoalKeeper;
}

void Team::updateAfterUnite(int numAllPlayers, int points,int goals, int cards, int numallGoalKeeper,
                       bool islegal, Player* topScorrer)  
{
    m_numOfTeamPlayers += numAllPlayers;
    m_teamPoints += points;
    m_teamGoals += goals;
    m_teamCards += cards;
    m_numOfTeamGoalKeeper += numallGoalKeeper;
    m_isInLegalTeams = islegal;
    m_topTeamScorer = topScorrer;
 }

 void Team::zero()
 {
    m_numOfTeamPlayers = 0;
 }