// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlock.h"
#include "TicTacToeBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "TicTacToeGameState.h"

ATicTacToeBlock::ATicTacToeBlock()
{
	this->BlockOwner = ETicTacToeBlockOwner::EMPTY;
}

void ATicTacToeBlock::SetBlockOwner(const ETicTacToeBlockOwner BlockOwner)
{
	ATicTacToeGameState* GameState = GetWorld()->GetGameState<ATicTacToeGameState>();
	if (IsValid(GameState))
	{
		if (GameState->GetCurrentTurn() == ETicTacToeTurn::PLAYER_O && BlockOwner == ETicTacToeBlockOwner::PLAYER_O ||
			GameState->GetCurrentTurn() == ETicTacToeTurn::PLAYER_X && BlockOwner == ETicTacToeBlockOwner::PLAYER_X)
		{
			this->BlockOwner = BlockOwner;
			OnSetBlockOwner();
			if(IsValid(OwningGrid))
			{
				ETicTacToeState State = OwningGrid->GetWinner();
				if (State == ETicTacToeState::NOT_FINISHED)
				{
					GameState->SwapTurn();
				}
				else
				{
					GameState->EndGame(State);
				}
			}
		}
	}
}
