// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fire.h"
#include "AIController.h"
#include "Soldier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Prevent crash if referenced Enemy is missing
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//Get the Ai Pawn amd cast to Soldier class
	ASoldier* AIActor = Cast<ASoldier>(OwnerComp.GetAIOwner()->GetPawn());

	//Get Player pawn location to pass along to "Fire"
	ASoldier* PlayerActor = Cast<ASoldier>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	//Shoot player, supply exact player location for consistency
	AIActor->Fire(PlayerActor->GetTargetLocation());

	return EBTNodeResult::Succeeded;
}