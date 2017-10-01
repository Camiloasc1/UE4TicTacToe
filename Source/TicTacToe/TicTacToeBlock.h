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

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void Highlight(bool bOn);

public:
	FORCEINLINE ETicTacToeBlockOwner GetBlockOwner() const
	{
		return BlockOwner;
	}

	void SetBlockOwner(const ETicTacToeBlockOwner BlockOwner);

protected:
	ETicTacToeBlockOwner BlockOwner;
};
