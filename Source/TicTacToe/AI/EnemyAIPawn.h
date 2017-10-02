// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <TicTacToeBlockGrid.h>
#include <TicTacToeBlock.h>
#include "EnemyAIPawn.generated.h"

USTRUCT()
struct FMove
{
	GENERATED_BODY()

	UPROPERTY()
	ETicTacToeState Winner;
	UPROPERTY()
	int32 X;
	UPROPERTY()
	int32 Y;
	UPROPERTY()
	int32 Deep;

	FMove()
		: Winner(ETicTacToeState::NOT_FINISHED),
		X(0),
		Y(0),
		Deep(0)
	{
	}

	FMove(ETicTacToeState Winner, int32 X, int32 Y, int32 Deep)
		: Winner(Winner),
		  X(X),
		  Y(Y),
		  Deep(Deep)
	{
	}
};

UCLASS()
class TICTACTOE_API AEnemyAIPawn : public APawn
{
	GENERATED_BODY()

public:
	AEnemyAIPawn();

public:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnTurnSwap();

public:
	FMove Play(TArray<ETicTacToeBlockOwner>& Board, ETicTacToeBlockOwner player);

	ETicTacToeState GetWinner(TArray<ETicTacToeBlockOwner>& Board);

	ETicTacToeBlockOwner GetBlockAt(TArray<ETicTacToeBlockOwner>& Board, int32 i, int32 j) const;

	void SetBlockAt(TArray<ETicTacToeBlockOwner>& Board, int32 i, int32 j, ETicTacToeBlockOwner Block) const;

protected:
	UPROPERTY(Transient)
	class ATicTacToeGameState* GameState;

	UPROPERTY(Transient)
	class ATicTacToeBlockGrid* GameBoard;

	UPROPERTY(Transient)
	int32 Size;
};
