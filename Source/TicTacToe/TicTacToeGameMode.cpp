// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TicTacToeGameMode.h"
#include "TicTacToePlayerController.h"
#include "TicTacToePawn.h"
#include "TicTacToeGameState.h"

ATicTacToeGameMode::ATicTacToeGameMode()
{
	// Defaults
	DefaultPawnClass = ATicTacToePawn::StaticClass();
	PlayerControllerClass = ATicTacToePlayerController::StaticClass();
	GameStateClass = ATicTacToeGameState::StaticClass();
}
