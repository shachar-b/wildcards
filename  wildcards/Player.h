//File name: Player.h
#ifndef ___PLAYER___H____
	#define ___PLAYER___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "UI.h"
	#include "PlayerStatistics.h"
	using namespace UIs;
	#include <time.h>
	#include <stdarg.h>
	#include "PlayerStatistics.h"
	//defines
	
	//consts
	//classes
	class Player
	{
	private:
		bool m_isHuman;
		char * m_name;
		bool m_decision;
		GameTypes m_playerType;

	protected:
		Card * m_card;
		PlayerStatistics * m_statistics;
		


	public:
		static const bool KEEP=true;
		static const bool THROW=false;  
		Player(const char * playerName,bool iscomputer=true,int numOfJokers=2,GameTypes type=NORMAL);
		~Player(){delete m_name; delete m_statistics;}//release assigned space ()
		virtual bool makeDecision();
		virtual void printPlayerDetails(int x,int y,bool showCard=true) const;
		//setter and getters
		Card * getCard(){return m_card;}
		void setCard(Card * newCard){m_card=newCard; m_statistics->updateStatistics(newCard);}
		const char * getName()const{return m_name;}
		bool isHumanPlayer()const{return m_isHuman;}
		bool getDecision(){return m_decision;}
		GameTypes getPlayerType()const{return m_playerType;}
		void Player::updateUserAboutRound( int numOfThrows,int numberOfplayers,... );
		friend ostream& operator<<(ostream&out , const Player  * p);
		
	};
	//function declaration
#endif