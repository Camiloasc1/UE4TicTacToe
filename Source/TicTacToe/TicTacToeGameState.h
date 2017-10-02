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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnSwap);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnd, ETicTacToeState, FinalState);

public:
	ATicTacToeGameState();

public:
	UFUNCTION()
	ETicTacToeTurn GetCurrentTurn() const
	{
		return CurrentTurn;
	}

	UFUNCTION(BlueprintCallable)
	void SwapTurn();

	UFUNCTION(BlueprintCallable)
	void EndGame(ETicTacToeState FinalState);

public:
	UPROPERTY(BlueprintAssignable)
	FOnTurnSwap OnTurnSwap;

	UPROPERTY(BlueprintAssignable)
	FOnGameEnd OnGameEnd;

protected:
	UPROPERTY(BlueprintReadOnly)
	ETicTacToeTurn CurrentTurn;
};
