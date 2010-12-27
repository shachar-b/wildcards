//File name: Player.h
#ifndef ___PLAYER___H____
	#define ___PLAYER___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "UI.h"
	using namespace UIs;
	#include "hand.h"
	#include <time.h>
	#include <string>
	//defines
	
	//consts
	//classes
	class Player
	{
	private:
		bool m_isHuman;
		char * m_name;
		bool m_decision;
		int m_score;

	private:
		Hand * m_hand;


	public:
		static const bool KEEP=true;
		static const bool THROW=false;  
		Player(const char * playerName,bool iscomputer=true,int numOfJokers=0);
		~Player(){delete m_name;delete m_hand;}//release assigned space
		bool makeDecision(int cardNumber);
		void printPlayerDetails(int x,int y,bool showCard=true) const;
		//setter and getters
		const Card* getCard(int cardNumber){return m_hand->getCard(cardNumber);}
		void setCard(Card * newCard, int cardNumber){m_hand->setCard(newCard,cardNumber);}
		void setComunityCard(const Card * Card ,int place){m_hand->setComunityCard(Card,place);}
		const char * getName()const{return m_name;}
		bool isHumanPlayer()const{return m_isHuman;}
		bool getDecision(){return m_decision;}
		int getScore() const {return m_score;}
		Hand* getHand() const {return m_hand;}
		void addToScore(int num){m_score+=num;}//assuming num>0
		friend ostream& operator<<(ostream&out , const Player  * p);
	};
	//function declaration
#endif