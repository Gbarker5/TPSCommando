// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/InputComponent.h"
#include "TPSCommandoGameModeBase.h"
#include "Soldier.h"

void ASoldierPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(Cast<ACharacter>(GetCharacter()))
	MySoldier = Cast<ASoldier>(GetCharacter());
	GameModeRef = Cast<ATPSCommandoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MapName = GetWorld()->GetName();

	//Change UI based on Level
	if(MapName=="Main")
	SoldierUI = CreateWidget(this, CrosshairClass);
	else if (MapName == "Win")
	SoldierUI = CreateWidget(this, WinClass);
	else if (MapName == "Lose")
	SoldierUI = CreateWidget(this, LoseClass);

	if (SoldierUI != nullptr)
	{
		SoldierUI->AddToViewport();
	}

}

void ASoldierPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameModeRef != nullptr) 
	{
		//Check time remaining and update it on player UI
		float tempTime= GameModeRef->GameLength - GetWorldTimerManager().GetTimerElapsed(GameModeRef->EndGameTimer);
		if (tempTime > 0)
			timeLeft = tempTime;
		playerHP = MySoldier->Health;
		enemyCount = GameModeRef->enemyCount;
	}
}

void ASoldierPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis("Forwards", this, &ASoldierPlayerController::MoveForwards);
	InputComponent->BindAxis("Strafe", this, &ASoldierPlayerController::Strafe);
	InputComponent->BindAxis("LookUp", this, &ASoldierPlayerController::LookUp);
	InputComponent->BindAxis("Turn", this, &ASoldierPlayerController::Turn);
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASoldierPlayerController::Jump);
	InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ASoldierPlayerController::doCrouch);
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ASoldierPlayerController::Fire);
	
}

void ASoldierPlayerController::MoveForwards(float AxisAmount)
{
	if (MySoldier)
	{
		MySoldier->MoveForwards(float (AxisAmount));
	}
}

void ASoldierPlayerController::Strafe(float AxisAmount)
{
	if (MySoldier)
	{
		MySoldier->Strafe(float( AxisAmount));
	}
}

void ASoldierPlayerController::LookUp(float AxisAmount)
{
	if (MySoldier)
	{
		MySoldier->LookUp(float(AxisAmount));
	}
}

void ASoldierPlayerController::Turn(float AxisAmount)
{
	if (MySoldier)
	{
		MySoldier->Turn(float (AxisAmount));
	}
}

void ASoldierPlayerController::doCrouch()
{
	if (MySoldier)
	{
		MySoldier->doCrouch();
		//MySoldier->Crouch();		
	}
}

void ASoldierPlayerController::Jump()
{
	if (MySoldier)
	{
		if (MapName == "Main")
		MySoldier->DoJump();
		else
		UGameplayStatics::OpenLevel(GetWorld(), "Main");
	}
}

void ASoldierPlayerController::Fire()
{
	if (MySoldier)
	{
		MySoldier->Fire(FVector(0,0,0));
	}
}

int ASoldierPlayerController::GetHP()
{
	return playerHP;
}

int ASoldierPlayerController::GetEnemies()
{
	return enemyCount;
}

int ASoldierPlayerController::GetTime()
{
	return timeLeft;
}
