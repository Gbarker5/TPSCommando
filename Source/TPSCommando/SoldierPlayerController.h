// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SoldierPlayerController.generated.h"

/**
 * 
 */
class ASoldier;
class ATPSCommandoGameModeBase;
UCLASS()
class TPSCOMMANDO_API ASoldierPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	void MoveForwards(float AxisAmount);
	void Strafe(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);
	void doCrouch();
	void Jump();
	void Fire();

	FString MapName; //Stores Name of current level

	ASoldier* MySoldier;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Skeleton;

private:
	UFUNCTION(BlueprintPure)
		int GetHP();
	UFUNCTION(BlueprintPure)
		int GetEnemies();
	UFUNCTION(BlueprintPure)
		int GetTime();
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseClass;
	UPROPERTY()
		UUserWidget* SoldierUI;
	UPROPERTY(EditAnywhere)
		float timeLeft = 300.0f; //Time for player to complete the game in
	UPROPERTY(EditAnywhere)
		int playerHP;
	UPROPERTY(EditAnywhere)
		int enemyCount;
	UPROPERTY()
		ATPSCommandoGameModeBase* GameModeRef;
};
