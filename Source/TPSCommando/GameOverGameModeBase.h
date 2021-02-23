// Fill out your copyright notice in the Description page of Project Settings.

//
//
//Largely empty class to allow the player to mess around during the end screens
//
//


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameOverGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSCOMMANDO_API AGameOverGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameOverGameModeBase();
protected:
	virtual void BeginPlay() override;
	
};
