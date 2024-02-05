// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_BTTBB_Charge.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UAI_BTTBB_Charge::UAI_BTTBB_Charge(FObjectInitializer const& ObjectInitializer)
{
    NodeName = "Follow Player";
}
EBTNodeResult::Type UAI_BTTBB_Charge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto* const Controller = Cast<AGameAIController>(OwnerComp.GetAIOwner()))
    {
        auto const PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}

