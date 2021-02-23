// Fill out your copyright notice in the Description page of Project Settings.

//
//
//Largely empty class to allow the player to mess around during the end screens
//
//

#include "GameOverGameModeBase.h"
#include "SoldierPlayerController.h"
#include "Kismet/GameplayStatics.h"
AGameOverGameModeBase::AGameOverGameModeBase()
{
	PlayerControllerClass = ASoldierPlayerController::StaticClass();
}
void AGameOverGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
