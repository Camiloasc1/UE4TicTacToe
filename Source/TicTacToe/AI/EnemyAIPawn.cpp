// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIPawn.h"
#include <TicTacToeGameState.h>
#include "Engine/World.h"
#include "TimerManager.h"
#include <Kismet/GameplayStatics.h>


AEnemyAIPawn::AEnemyAIPawn()
{
}

void AEnemyAIPawn::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATicTacToeBlockGrid::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		GameBoard = Cast<ATicTacToeBlockGrid>(FoundActors[0]);
		if (IsValid(GameBoard))
		{
			Size = GameBoard->Size;
		}
	}

	GameState = GetWorld()->GetGameState<ATicTacToeGameState>();
	if (IsValid(GameState))
	{
		GameState->OnTurnSwap.AddDynamic(this, &AEnemyAIPawn::OnTurnSwap);
		FTimerHandle SetupDelayTimer;
		GetWorld()->GetTimerManager().SetTimer(SetupDelayTimer, this, &AEnemyAIPawn::OnTurnSwap, 1.0f, false);
	}
}

void AEnemyAIPawn::OnTurnSwap()
{
	if (IsValid(GameState))
	{
		if (GameState->GetCurrentTurn() == ETicTacToeTurn::PLAYER_X)
		{
			if (!IsValid(GameBoard))
			{
				return;
			}

			TArray<ETicTacToeBlockOwner> Board;
			const int32 SizeSquared = Size * Size;
			for (int32 i = 0; i < SizeSquared; ++i)
			{
				Board.Add(GameBoard->GetArrayBlockAt(i)->GetBlockOwner());
				UE_LOG(LogTemp, Warning, TEXT("%u"), (uint8)GameBoard->GetArrayBlockAt(i)->GetBlockOwner())
			}

			FMove BestMove = GetBestMove(Board, ETicTacToeBlockOwner::PLAYER_X);
			UE_LOG(LogTemp,Warning,TEXT("%i : %i"), BestMove.X, BestMove.Y)
			GameBoard->GetBlockAt(BestMove.X, BestMove.Y)->SetBlockOwner(ETicTacToeBlockOwner::PLAYER_X);
		}
	}
}

FMove AEnemyAIPawn::GetBestMove(TArray<ETicTacToeBlockOwner>& Board, ETicTacToeBlockOwner Player)
{
	FMove WinMove;
	FMove TieMove;
	FMove LoseMove;

	ETicTacToeState Winner = GetWinner(Board);
	if (Winner != ETicTacToeState::NOT_FINISHED)
	{
		return FMove(Winner, -1, -1, 0);
	}

	for (int32 i = 0; i < Size; ++i)
	{
		for (int32 j = 0; j < Size; ++j)
		{
			if (GetBlockAt(Board, i, j) == ETicTacToeBlockOwner::EMPTY)
			{
				SetBlockAt(Board, i, j, Player);
				FMove Move = GetBestMove(Board, (Player == ETicTacToeBlockOwner::PLAYER_O) ? ETicTacToeBlockOwner::PLAYER_X : ETicTacToeBlockOwner::PLAYER_O);
				SetBlockAt(Board, i, j, ETicTacToeBlockOwner::EMPTY);

				if (Move.Winner == ETicTacToeState::PLAYER_X && Player == ETicTacToeBlockOwner::PLAYER_X ||
					Move.Winner == ETicTacToeState::PLAYER_O && Player == ETicTacToeBlockOwner::PLAYER_O)
				{
					WinMove = Move;
					WinMove.X = i;
					WinMove.Y = j;
					WinMove.Deep++;
				}
				else if (Move.Winner == ETicTacToeState::TIE)
				{
					TieMove = Move;
					TieMove.X = i;
					TieMove.Y = j;
					TieMove.Deep++;
				}
				else
				{
					LoseMove = Move;
					LoseMove.X = i;
					LoseMove.Y = j;
					LoseMove.Deep++;
				}
			}
		}
	}

	if (WinMove.IsValid())
	{
		return WinMove;
	}
	if (TieMove.IsValid())
	{
		return TieMove;
	}
	return LoseMove;
}

ETicTacToeState AEnemyAIPawn::GetWinner(TArray<ETicTacToeBlockOwner>& Board)
{
	for (int32 i = 0; i < Size; ++i)
	{
		int32 Rows_O = 0;
		int32 Rows_X = 0;

		int32 Cols_O = 0;
		int32 Cols_X = 0;
		for (int32 j = 0; j < Size; ++j)
		{
			if (GetBlockAt(Board, i, j) == ETicTacToeBlockOwner::PLAYER_O)
			{
				Rows_O++;
			}
			else if (GetBlockAt(Board, i, j) == ETicTacToeBlockOwner::PLAYER_X)
			{
				Rows_X++;
			}

			if (GetBlockAt(Board, j, i) == ETicTacToeBlockOwner::PLAYER_O)
			{
				Cols_O++;
			}
			else if (GetBlockAt(Board, j, i) == ETicTacToeBlockOwner::PLAYER_X)
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
		if (GetBlockAt(Board, i, i) == ETicTacToeBlockOwner::PLAYER_O)
		{
			Diag1_O++;
		}
		else if (GetBlockAt(Board, i, i) == ETicTacToeBlockOwner::PLAYER_X)
		{
			Diag1_X++;
		}

		if (GetBlockAt(Board, i, Size - i - 1) == ETicTacToeBlockOwner::PLAYER_O)
		{
			Diag2_O++;
		}
		else if (GetBlockAt(Board, i, Size - i - 1) == ETicTacToeBlockOwner::PLAYER_X)
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
			if (GetBlockAt(Board, i, j) == ETicTacToeBlockOwner::EMPTY)
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

ETicTacToeBlockOwner AEnemyAIPawn::GetBlockAt(TArray<ETicTacToeBlockOwner>& Board, int32 i, int32 j) const
{
	return Board[i * Size + j];
}

void AEnemyAIPawn::SetBlockAt(TArray<ETicTacToeBlockOwner>& Board, int32 i, int32 j, ETicTacToeBlockOwner Block) const
{
	Board[i * Size + j] = Block;
}
