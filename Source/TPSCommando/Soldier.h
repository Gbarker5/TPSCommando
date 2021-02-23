// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Camera/CameraComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Soldier.generated.h"

class ATPSCommandoGameModeBase;
class UCameraComponent;
class USceneCaptureComponent2D;

UCLASS()
class TPSCOMMANDO_API ASoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoldier();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTimerHandle DeathTimer;
	float deathTime = 0.25f;
	float deathTimePlayer = 2.0f;
	// Called to bind functionality to input
	void MoveForwards(float AxisAmount);
	void Strafe(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);
	void doCrouch();
	void Fire(FVector Location);
	void Die();
	void EndGame();
	void DoJump();
	bool isDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
		TArray <AActor*> WeaponActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
	 UAnimationAsset* Death;
	UPROPERTY(EditAnywhere)
		float Health = 100.0f;
	UPROPERTY(EditAnywhere)
		USoundBase* shootFX;
	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MapCamera;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* MapArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
		USkeletalMeshComponent* charMesh;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
		bool shouldCrouch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
		bool wantsToFire;
private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EVentInstigator, class AActor* DamageCauser) override;
	UPROPERTY()
		ATPSCommandoGameModeBase* GameModeRef;

};
