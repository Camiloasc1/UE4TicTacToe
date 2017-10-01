// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacToePawn.generated.h"

UCLASS(config=Game)
class ATicTacToePawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ATicTacToeBlock* CurrentBlockFocus;
};
