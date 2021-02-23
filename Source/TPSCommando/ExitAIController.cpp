// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitAIController.h"
#include "Kismet/GameplayStatics.h"

void AExitAIController::BeginPlay()
{
	//Workaround because SetFocus refuses to work with customcontroller and the character
	Super::BeginPlay();

	/*Get an invisible actor attached to player and focus on it,
	exit sign is mostly 2D but always faces the player so that they can always see it. Admit it's cool*/
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("PLAYER")), exitPawns);
	PlayerPawn = exitPawns[0];
	SetFocus(PlayerPawn);
}
