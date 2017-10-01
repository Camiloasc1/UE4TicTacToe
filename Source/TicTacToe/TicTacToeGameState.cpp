// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacToeGameState.h"


ATicTacToeGameState::ATicTacToeGameState()
{
	CurrentTurn = FMath::RandBool() ? ETicTacToeTurn::PLAYER_O : ETicTacToeTurn::PLAYER_X;
}

void ATicTacToeGameState::SwapTurn()
{
	CurrentTurn = (CurrentTurn == ETicTacToeTurn::PLAYER_O) ? ETicTacToeTurn::PLAYER_X : ETicTacToeTurn::PLAYER_O;
	OnTurnSwap.Broadcast();
}
