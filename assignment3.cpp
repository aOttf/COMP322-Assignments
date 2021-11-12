/*
 * assignment3.cpp
 *
 *  Created on: Apr. 9, 2021
 *      Author: Jacob Wang
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

//Represents a single Card
//A Card has a rank and type
class Card {

public:
	enum rank {
		ACE = 1,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
	};
	enum type : char {
		CLUBS = 'C', DIAMONDS = 'D', HEARTS = 'H', SPADES = 'S',
	};
	Card(Card::rank, Card::type);
	int getValue();
	void displayCard();
	int RanktoVal();

private:
	Card::rank aRank;
	Card::type aType;

};

//Constructor of Card Class
Card::Card(Card::rank pRank, Card::type pType) {
	this->aRank = pRank;
	this->aType = pType;
}

//Return the numerical value of the Card
//Ace will return 1 only; Queen, King and Jack will return 10
//The rest will return what it is
int Card::getValue() {
	switch (aRank) {
	case JACK:
	case QUEEN:
	case KING:
		return 10;
	default:
		return static_cast<int>(aRank);
	}
}

//print Rank and Type of the Card
//example: Card Jack Heart will print JH ending with a white space
void Card::displayCard() {
	switch (aRank) {
	case JACK:
		cout << 'J';
		break;
	case QUEEN:
		cout << 'Q';
		break;
	case KING:
		cout << 'K';
		break;
	case TEN:
		cout << "10";
		break;
	default:
		cout << (char) ('0' + static_cast<int>(aRank));
		break;

	}
	cout << static_cast<char>(aType) << ' ';
}

//Represents a Collection of Cards
//This Class should be inherited by Deck Class and AbstractPlayer Class
//Client should not create an object of this Class directly
class Hand {
public:
	Hand();
	void add(Card *pCard);
	Card* pop_Last();
	void clear();
	int getTotal() const;
	int size();
	bool isEmpty();
	void display();
	~Hand();
protected:
	vector<Card*> *aCards;

};

Hand::Hand() {
	aCards = new vector<Card*>();
}

//pop and return the last Card of hand
Card* Hand::pop_Last() {
	Card *tmp = (*aCards)[size() - 1];
	aCards->pop_back();
	return tmp;
}

//return the number of elements of Hand
int Hand::size() {
	return aCards->size();
}

bool Hand::isEmpty() {
	return size() == 0;
}

//Return the sum of numerical values of all Cards held by Hand
//Notice that an ACE Card can represent either 1 or 11
//The choice of the value of Each ACE Card will make the sum as large as possible and not exceed 21 if possible
//Example:(ACE, ACE, ACE) will return 21 and (ACE, Jack, 4) will return 15
int Hand::getTotal() const {
	unsigned int i, sum, n_ace;
	n_ace = sum = 0;

	for (i = 0; i < aCards->size(); i++) {
		if ((*aCards)[i]->getValue() == Card::ACE)
			n_ace++;
		sum += (*aCards)[i]->getValue();
	}

	for (; n_ace > 0 && (sum + 10) <= 21; n_ace--)
		sum += 10;

	return sum;
}

//Display the info of all Cards and the sum of numerical value held by Hand
//Example:Hand with Ace Heart, 2 Spide, Jack Diamond will display AH 2S JD [13] with a newline character
void Hand::display() {
	unsigned int i;
	for (i = 0; i < aCards->size(); i++) {
		(*aCards)[i]->displayCard();

	}
	cout << '[' << getTotal() << ']' << endl;
}

void Hand::add(Card *pCard) {
	aCards->push_back(pCard);
}

//clear all the pointers to Cards
//No memory being free
void Hand::clear() {
	aCards->clear();
}

Hand::~Hand() {
	for (Card *c : *aCards) {
		delete c;
	}

	delete aCards;
}

//represents the deck of cards and the actions that can be performed on the
//cards like shuffling and dealing.
//Deck is inherited from Hand
class Deck: public Hand {
public:
	void populate();
	void shuffle();
	void deal(Hand *pHand);
};

//create a standard deck of 52 cards
void Deck::populate() {
	for (int r = 1; r < 14; r++) {
		Card::rank aRank = static_cast<Card::rank>(r);
		Card *aCard = new Card(aRank, Card::CLUBS);
		this->add(aCard);
		Card *bCard = new Card(aRank, Card::DIAMONDS);
		this->add(bCard);
		Card *cCard = new Card(aRank, Card::HEARTS);
		this->add(cCard);
		Card *dCard = new Card(aRank, Card::SPADES);
		this->add(dCard);
	}
}

void Deck::shuffle() {
	srand(time(0));
	random_shuffle(aCards->begin(), aCards->end());
}
//deal one card to a hand
void Deck::deal(Hand *pHand) {
	pHand->add((*aCards)[aCards->size() - 1]);
	aCards->pop_back();
}

//represents a generic abstract player that can be a human or the
//computer. This is an abstract class which should be inherited by HumanPlayer or ComputerPlayer
class AbstractPlayer: public Hand {
public:
	virtual bool isDrawing() const = 0;
	bool isBusted();
	virtual ~ AbstractPlayer() {
	}
	;
};

//whether the sum of values exceed 21
bool AbstractPlayer::isBusted() {
	return getTotal() > 21;
}

class HumanPlayer: public AbstractPlayer {
public:
	bool isDrawing() const;
	void announce(AbstractPlayer *pPlayer);
};

//indicates whether a player wants to draw another card
//It is decided by client after each drawing
//The client should enter y(Y):Yes or n(N):No Otherwise the input will be omitted and ask again
//If the input is more than one character, the rest will be consumed with no info shoued
bool HumanPlayer::isDrawing() const {
	char c;
	int i;
	while (getTotal() < 21) {
		cout << "Do you want to draw? (y/n)" << endl;
		cin >> c;
		while ((i = fgetc(stdin)) != EOF && i != '\n')
			;
		switch (c) {
		case 'y':
		case 'Y':
			return true;
		case 'n':
		case 'N':
			return false;
		default:
			cout << "Please enter y(yes) or n(no)" << endl;
			break;
		}
	}

	return false;
}

//print the result of game
void HumanPlayer::announce(AbstractPlayer *pPlayer) {
	if (this->isBusted()) {
		cout << "Player busts" << endl;
		cout << "Casino wins" << endl;
		return;
	}
	if (pPlayer->isBusted()) {
		cout << "Casino busts" << endl;
		cout << "Player wins" << endl;
		return;
	}

	if (this->getTotal() > pPlayer->getTotal())
		cout << "Player wins" << endl;
	else if (this->getTotal() < pPlayer->getTotal())
		cout << "Casino wins" << endl;
	else
		cout << "Push: No one wins" << endl;

}

class ComputerPlayer: public AbstractPlayer {
public:
	virtual bool isDrawing() const {
		return (getTotal() <= 16) ? true : false;
	}
	;
};

//The main class of game
//The client should only create an object of this class to start a game
class BlackJackGame {
public:
	BlackJackGame();
	void play();
	~BlackJackGame();
private:
	Deck *m_deck;
	ComputerPlayer *m_casino;
	HumanPlayer *m_human;
	void setUp();
};

BlackJackGame::BlackJackGame() {
	m_deck = new Deck();
	m_casino = new ComputerPlayer();
	m_human = new HumanPlayer();

}

//Do all the necessary setup to start a new round of game
void BlackJackGame::setUp() {
	static int time = 0;

	if ((++time) == 1) {
		m_deck->populate();
		m_deck->shuffle();
		return;
	}

	while (!m_casino->isEmpty())
		m_deck->add(m_casino->pop_Last());
	while (!m_human->isEmpty())
		m_deck->add(m_human->pop_Last());
	m_deck->shuffle();
}

//One Round of the game
void BlackJackGame::play() {
	setUp();
	m_deck->deal(m_casino);
	m_deck->deal(m_human);
	m_deck->deal(m_human);

	cout << "Casino: ";
	m_casino->display();
	cout << "Player: ";
	m_human->display();

	while (m_human->isDrawing()) {
		m_deck->deal(m_human);
		cout << "Player: ";
		m_human->display();
	}

	while (!m_human->isBusted() && m_casino->isDrawing()) {
		m_deck->deal(m_casino);
		cout << "Casino: ";
		m_casino->display();
	}

	m_human->announce(m_casino);
}

BlackJackGame::~BlackJackGame() {
	delete m_casino;
	delete m_human;
	delete m_deck;
}
//The Main program of the game
int main() {

	cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;
	BlackJackGame game;
	// The main loop of the game
	bool playAgain = true;
	char answer = 'y';
	while (playAgain) {
		game.play();
		// Check whether the player would like to play another round
		cout << "Would you like another round? (y/n): ";
		cin >> answer;
		cout << endl << endl;
		playAgain = (answer == 'y' ? true : false);
	}
	cout << "Gave over!";
	return 0;
}
