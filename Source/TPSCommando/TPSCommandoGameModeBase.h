
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSCommandoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSCOMMANDO_API ATPSCommandoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	
	
public:
	ATPSCommandoGameModeBase();
	virtual void Tick(float DeltaTime) override;
	FTimerHandle EndGameTimer;
	UPROPERTY(EditAnywhere)
		float GameLength = 300.0f;
	UPROPERTY(EditAnywhere)
	int enemyCount = 5;
	UFUNCTION()
		void SubtractEnemy();
	UFUNCTION()
		void TimerOver();

protected:
	virtual void BeginPlay() override;


};
