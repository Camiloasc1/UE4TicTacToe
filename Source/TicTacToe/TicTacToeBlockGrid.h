// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TicTacToeBlockGrid.generated.h"

UENUM()
enum class ETicTacToeState : uint8
{
	NOT_FINISHED,
	TIE,
	PLAYER_O,
	PLAYER_X
};

/** Class used to spawn blocks and manage score */
UCLASS()
class ATicTacToeBlockGrid : public AActor
{
	GENERATED_BODY()

public:
	ATicTacToeBlockGrid();

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	TArray<class ATicTacToeBlock*> Board;

public:
	void BeginPlay() override;

public:
	UFUNCTION()
	ATicTacToeBlock* GetBlockAt(int32 I, int32 J);

	UFUNCTION()
	ETicTacToeState GetWinner();
};
