// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAIController.h"

AGameAIController::AGameAIController(FObjectInitializer const& ObjectInitializer)
{
    ;
}
void AGameAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (ANPC* const npc = Cast<ANPC>(InPawn))
    {
        if (UBehaviorTree* const tree = npc->GetBehaviorTree())
        {
            UBlackboardComponent* b;
            UseBlackboard(tree->BlackboardAsset, b);
            Blackboard = b;
            RunBehaviorTree(tree);
        }
    }
}