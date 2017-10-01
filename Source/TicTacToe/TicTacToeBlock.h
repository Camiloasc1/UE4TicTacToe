// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacToeBlock.generated.h"

UENUM(BlueprintType)
enum class ETicTacToeBlockOwner : uint8
{
	EMPTY,
	PLAYER_O,
	PLAYER_X
};

UCLASS()
class ATicTacToeBlock : public AActor
{
	GENERATED_BODY()

public:
	ATicTacToeBlock();

public:
	/** Grid that owns us */
	UPROPERTY(Transient)
	class ATicTacToeBlockGrid* OwningGrid;

	UFUNCTION(BlueprintImplementableEvent)
	void Highlight(bool bOn);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSetBlockOwner();

public:
	UFUNCTION()
	FORCEINLINE ETicTacToeBlockOwner GetBlockOwner() const
	{
		return BlockOwner;
	}

	UFUNCTION(BlueprintSetter)
	void SetBlockOwner(const ETicTacToeBlockOwner BlockOwner);

protected:
	UPROPERTY(BlueprintSetter = SetBlockOwner)
	ETicTacToeBlockOwner BlockOwner;
};
