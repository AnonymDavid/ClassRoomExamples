#include "Player.h"

#include <iostream>

using namespace std;

bool Player::hasWon() const
{
	int i = 0;
	while (i < 4 && pieces[i].getRegion() == Piece::HOUSE)
		++i;
	return i == 4;
}

int Player::decide(int rolled)
{
	cout << "You rolled " << rolled << ", choose a piece!\n";
	int chosen;
	bool valid;
	do {
		cin >> chosen;
		valid = true;
		Piece copy = pieces[chosen];
		copy.move(rolled);
		for (int i = 0; valid && i < 4; ++i)
			if (pieces[i].getRegion() == copy.getRegion() && pieces[i].getRegion() != Piece::HOUSE
				&& pieces[i].getIndex() == copy.getIndex())
				valid = false;
	} while (!valid);
	return 0;
}

void Player::Piece::move(int length) {
	switch (region)
	{
	case Player::Piece::START:
		region = BOARD;
		index = 0;
		break;
	case Player::Piece::BOARD:
		index += length;
		if (index >= board->boardSize) {
			region = GARDEN;
			index -= board->boardSize;
		}
		break;
	case Player::Piece::GARDEN:
		index += length;
		if (index >= board->gardenLength) {
			region = HOUSE;
			index -= board->gardenLength;
		}
		break;
	default:
		break;
	}
}
