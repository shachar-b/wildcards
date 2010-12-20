//File name: Player.h
#ifndef ___PLAYER___H____
	#define ___PLAYER___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "UI.h"
	using namespace UIs;
	#include <time.h>
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

	protected:
		Card * m_card;
		


	public:
		static const bool KEEP=true;
		static const bool THROW=false;  
		Player(const char * playerName,bool iscomputer=true,int numOfJokers=2);
		~Player(){delete m_name;}//release assigned space
		virtual bool makeDecision();
		virtual void printPlayerDetails(int x,int y,bool showCard=true) const;
		//setter and getters
		Card * getCard(){return m_card;}
		void setCard(Card * newCard){m_card=newCard;}
		const char * getName()const{return m_name;}
		bool isHumanPlayer()const{return m_isHuman;}
		bool getDecision(){return m_decision;}
		int getScore() const {return m_score;}
		void addToScore(int num){m_score+=num;}//assuming num>0
		friend ostream& operator<<(ostream&out , const Player  * p);		
	};
	//function declaration
#endif