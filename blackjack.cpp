#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

class Card 
{
public:
    Card(int value, Suit suit) : value(value), suit(suit) {} 

    int getValue() const { return value; } 
    Suit getSuit() const { return suit; }

    void displayCard() const 
    {
        string suitStr;
        string valueStr;
        switch (suit) 
        {
            case Suit::HEARTS:
                suitStr = "Hearts";
                break;
            case Suit::DIAMONDS:
                suitStr = "Diamonds";
                break;
            case Suit::CLUBS:
                suitStr = "Clubs";
                break;
            case Suit::SPADES:
                suitStr = "Spades";
                break;
        }

        if (value == 11) 
        {
            valueStr = "Jack";
        } else if (value == 12) 
        {
            valueStr = "Queen";
        } else if (value == 13) 
        {
            valueStr = "King";
        } else if (value == 1) 
        {
            valueStr = "Ace";
        } else 
        {
            valueStr = to_string(value);
        }

        cout << "Card: " << valueStr << " of " << suitStr << endl;
    }

private:
    int value;
    Suit suit;
};

class Deck {
public:
    Deck() 
    {
        // Initialize the deck with 52 cards
        for (int i = 0; i < 4; ++i) // loops through suits
        {
            for (int j = 1; j <= 13; ++j) // loops through all cards in a give suit
            {
                cards.push_back(Card(j, static_cast<Suit>(i))); // adding a new card to vector
            }
        }
    }

    void shuffle() // from algorithm library
    {
        std::random_device rd; // Must use "std::" to acess algorithm library
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card dealCard() 
    {
        if (!cards.empty()) 
        {
            Card dealtCard = cards.back();
            cards.pop_back();
            return dealtCard;
        } else 
        {
            return Card(-1, Suit::HEARTS);
        }
    }

private:
    vector<Card> cards;
};

int calculateTotal(const vector<Card>& hand) 
{
    int total = 0;
    int numAces = 0;

    for (const auto& card : hand) 
    {
        int cardValue = card.getValue();

        if (cardValue == 1) 
        { // Ace
            total += 11;
            numAces++;
        } else if (cardValue > 10) 
        {
            total += 10;
        } else 
        {
            total += cardValue;
        }
    }

    while (total > 21 && numAces > 0) 
    {
        total -= 10;
        numAces--;
    }

    return total;
}

void suspensefulDots() // Suspense Function
{
    for (int i = 0; i < 3; ++i) 
    {
        cout << ".";
        cout.flush();  // Flush the output buffer to ensure immediate display
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
    cout << "\n"; 
}

int main() 
{
    cout << "=====================" << endl;
    cout << "Welcome to Blackjack!" << endl;
    cout << "=====================\n" << endl;
    cout << "Rules:\n";
    cout << "1. The goal is to get a hand value as close to 21 as possible without exceeding it.\n";
    cout << "2. Number cards are worth their face value. Face cards (Jack, Queen, King) are worth 10.\n";
    cout << "3. Aces can be worth 1 or 11, whichever is more beneficial for the hand.\n";
    cout << "4. The game starts with each player receiving two cards.\n";
    cout << "5. Players can 'hit' to draw another card or 'stay' to keep their current hand.\n";
    cout << "6. If a player's hand exceeds 21, they bust and lose the game.\n";
    cout << "7. After the player's turn, the dealer reveals their hand and hits until their total is greater than the players hand.\n";
    cout << "8. The player with a hand value closest to 21 without exceeding it wins.\n";
    cout << "9. If the dealer busts, the player wins. If both bust or have the same total, it's a draw.\n";
    cout << "10. Enjoy the game and good luck!\n\n";

    Deck deck;
    deck.shuffle();

    vector<Card> playerHand;
    vector<Card> dealerHand;

    playerHand.push_back(deck.dealCard());
    playerHand.push_back(deck.dealCard());

    cout << "Player's Hand:\n" << endl;
    for (const auto& card : playerHand) 
    {
        card.displayCard();
    }

    int playerTotal = calculateTotal(playerHand);
    cout << "\nPlayer's Total: " << playerTotal << endl;

    string choice;
    while (playerTotal < 21) 
    {
        cout << "\nDo you want to hit or stay? (Type 'hit' or 'stay'): ";
        cin >> choice;

        if (choice == "hit") 
        {
            playerHand.push_back(deck.dealCard());
            cout << "\nPlayer's Hand after hitting:\n" << endl;
            for (const auto& card : playerHand) 
            {
                card.displayCard();
            }
            playerTotal = calculateTotal(playerHand);
            cout << "\nPlayer's Total: " << playerTotal << endl;
        } else if (choice == "stay") 
        {
            break;
        }
    }

    if (playerTotal > 21) 
    {
        cout << "Player busts... Dealer wins!" << endl;
    } else 
    {
        cout << "\nPlayer stays... Player's final total: " << playerTotal << endl;

        // Dealer's turn
        dealerHand.push_back(deck.dealCard());
        dealerHand.push_back(deck.dealCard());

         cout << "\nDealing The Dealer's Hand\n";
    suspensefulDots();  // Calling the suspenseful dots animation function
    for (const auto& card : dealerHand) 
    {
        card.displayCard();
    }
        int dealerTotal = calculateTotal(dealerHand);
        cout << "\nDealer's Total: " << dealerTotal << endl;

        while (dealerTotal <= playerTotal) 
        {
            dealerHand.push_back(deck.dealCard());
            cout << "\nDealer Hits:" << endl;
            for (const auto& card : dealerHand) 
            {
                card.displayCard();
            }
            dealerTotal = calculateTotal(dealerHand);
            cout << "Dealer's Total: " << dealerTotal << endl;
        }

        if (dealerTotal > 21) 
        {
            cout << "\nDealer busts. Player wins!" << endl;
        } else if (dealerTotal >= playerTotal) 
        {
            cout << "\nDealer wins!" << endl;
        } else 
        {
            cout << "\nPlayer wins!" << endl;
        }
    }

    return 0;
}


