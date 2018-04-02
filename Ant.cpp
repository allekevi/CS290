#include "Ant.hpp"
#include <stdlib.h>

Ant::Ant()
{
	
}

Ant::Ant(int row, int col) {
	setCritType('O');
	setRowPosition(row);
	setColPosition(col);
	setCritAge(0);
    setJustMoved(false);
    
}

Ant::~Ant()
{
}

void Ant::critMove(Critter*** boardPtr, int rowEdge, int colEdge) {
	int direction = rand() % 4 + 1;
	switch (direction) {
	case 1: if (this->getRowPosition() !=0 && boardPtr[this->getRowPosition()-1][this->getColPosition()] == NULL) {		//up
		boardPtr[this->getRowPosition() - 1][this->getColPosition()] = this;			//move ant in the array
		boardPtr[this->getRowPosition()][this->getColPosition()] = NULL;				//set old position to null
		this->setRowPosition(this->getRowPosition() - 1);								//change position in ant object
	}
			break;
	case 2: if (this->getColPosition() != colEdge && boardPtr[this->getRowPosition()][this->getColPosition()+1] == NULL) {		//right
		boardPtr[this->getRowPosition()][this->getColPosition() + 1] = this;
		boardPtr[this->getRowPosition()][this->getColPosition()] = NULL;
		this->setColPosition(this->getColPosition() + 1);
	}
			break;
	case 3: if (this->getRowPosition() != rowEdge && boardPtr[this->getRowPosition()+1][this->getColPosition()] == NULL) {		//down
		boardPtr[this->getRowPosition() + 1][this->getColPosition()] = this;
		boardPtr[this->getRowPosition()][this->getColPosition()] = NULL;
		this->setRowPosition(this->getRowPosition() + 1);
	}
			break;
	case 4: if (this->getColPosition() != 0 && boardPtr[this->getRowPosition()][this->getColPosition()-1] == NULL) {		//left
		boardPtr[this->getRowPosition()][this->getColPosition() - 1] = this;
		boardPtr[this->getRowPosition()][this->getColPosition()] = NULL;
		this->setColPosition(this->getColPosition() - 1);
	}
		
	}
	this->setCritAge(getCritAge() + 1);
}

void Ant::critBreed(Critter*** boardPtr, int rowEdge, int colEdge) {
	if (this->getCritAge() >= 3) {	

		bool antBreed = true;				//Bool to check loop conditions
		int randArr[] = { 0, 0, 0, 0 };		//Array to track if all available directions have been checked for breeding
		while (antBreed) {
			int direction = rand() % 4 + 1;
			switch (direction) {	
			case 1: if (this->getRowPosition() != 0 && boardPtr[this->getRowPosition() - 1][this->getColPosition()] == NULL) {		//up
				boardPtr[this->getRowPosition() - 1][this->getColPosition()] = new Ant((this->getRowPosition() - 1), this->getColPosition());
				antBreed = false;
			}
					randArr[0] = 1;
					break;
			case 2: if (this->getColPosition() != colEdge && boardPtr[this->getRowPosition()][this->getColPosition() + 1] == NULL) {		//right
				boardPtr[this->getRowPosition()][this->getColPosition() + 1] = new Ant(this->getRowPosition(), (this->getColPosition() + 1));
				antBreed = false;
			}
					randArr[1] = 1;
					break;
			case 3: if (this->getRowPosition() != rowEdge && boardPtr[this->getRowPosition() + 1][this->getColPosition()] == NULL) {		//down
				boardPtr[this->getRowPosition() + 1][this->getColPosition()] = new Ant((this->getRowPosition() + 1), this->getColPosition());
				antBreed = false;
			}
					randArr[2] = 1;
					break;
			case 4: if (this->getColPosition() !=0 && boardPtr[this->getRowPosition()][this->getColPosition() - 1] == NULL) {		//left
				boardPtr[this->getRowPosition()][(this->getColPosition() - 1)] = new Ant(this->getRowPosition(), (this->getColPosition() - 1));
				antBreed = false;
			}
					randArr[3] = 1;
				
			}
			int count = 0;
			while (count < 4) {				//loop to check if direction has been looped through
				if (randArr[count] == 0) {
					antBreed = true;
					count++;
				}
				else {
					antBreed = false;
					count++;
					break;
				}
			}
		}
		this->setCritAge(0);
	}
}
