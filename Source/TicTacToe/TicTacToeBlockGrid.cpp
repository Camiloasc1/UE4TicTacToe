// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlockGrid.h"
#include "TicTacToeBlock.h"
#include "Engine/World.h"
#include "TicTacToeBlock.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATicTacToeBlockGrid::ATicTacToeBlockGrid()
{
	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ATicTacToeBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex % Size) * BlockSpacing; // Modulo gives remainder
		const float BoardOffset = -(0.5f * (Size - 1) * BlockSpacing);

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset + BoardOffset, YOffset + BoardOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ATicTacToeBlock* NewBlock = GetWorld()->SpawnActor<ATicTacToeBlock>(BlockLocation, FRotator(0, 0, 0));
		
		if (NewBlock != nullptr)
		{
			// Tell the block about its owner
			NewBlock->OwningGrid = this;
			// Add to the board
			Board.Add(NewBlock);
		}
	}
}

ATicTacToeBlock* ATicTacToeBlockGrid::GetBlockAt(int32 I, int32 J)
{
	return Board[I * Size + J];
}

ETicTacToeState ATicTacToeBlockGrid::GetWinner()
{
	for (int32 i = 0; i < Size; ++i)
	{
		int32 Rows_O = 0;
		int32 Rows_X = 0;

		int32 Cols_O = 0;
		int32 Cols_X = 0;
		for (int32 j = 0; j < Size; ++j)
		{
			if (GetBlockAt(i, j)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_O)
			{
				Rows_O++;
			}
			else if (GetBlockAt(i, j)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_X)
			{
				Rows_X++;
			}

			if (GetBlockAt(j, i)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_O)
			{
				Cols_O++;
			}
			else if (GetBlockAt(j, i)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_X)
			{
				Cols_X++;
			}
		}

		if (Cols_O == Size || Rows_O == Size)
		{
			return ETicTacToeState::PLAYER_O;
		}
		if (Cols_X == Size || Rows_X == Size)
		{
			return ETicTacToeState::PLAYER_X;
		}
	}

	int32 Diag1_O = 0;
	int32 Diag1_X = 0;

	int32 Diag2_O = 0;
	int32 Diag2_X = 0;

	for (int32 i = 0; i < Size; ++i)
	{
		if (GetBlockAt(i, i)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_O)
		{
			Diag1_O++;
		}
		else if (GetBlockAt(i, i)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_X)
		{
			Diag1_X++;
		}

		if (GetBlockAt(i, Size - i - 1)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_O)
		{
			Diag2_O++;
		}
		else if (GetBlockAt(i, Size - i - 1)->GetBlockOwner() == ETicTacToeBlockOwner::PLAYER_X)
		{
			Diag2_X++;
		}
	}

	if (Diag1_O == Size || Diag2_O == Size)
	{
		return ETicTacToeState::PLAYER_O;
	}
	if (Diag1_X == Size || Diag2_X == Size)
	{
		return ETicTacToeState::PLAYER_X;
	}

	int32 Empty = 0;
	for (int32 i = 0; i < Size; i++)
	{
		for (int32 j = 0; j < Size; j++)
		{
			if (GetBlockAt(i, i)->GetBlockOwner() == ETicTacToeBlockOwner::EMPTY)
			{
				Empty++;
			}
		}
	}
	if (Empty == 0)
	{
		return ETicTacToeState::TIE;
	}

	return ETicTacToeState::NOT_FINISHED;
}

#undef LOCTEXT_NAMESPACE
