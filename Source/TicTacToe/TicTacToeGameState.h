// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TicTacToeGameState.generated.h"

UENUM(BlueprintType)
enum class ETicTacToeTurn : uint8
{
	PLAYER_O,
	PLAYER_X
};

UCLASS()
class TICTACTOE_API ATicTacToeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATicTacToeGameState();

public:
	UFUNCTION(Blueprintcallable)
	ETicTacToeTurn GetCurrentTurn() const
	{
		return CurrentTurn;
	}

private:
	ETicTacToeTurn CurrentTurn;
};
