// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI_BTTBB_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class INTRO2_API UAI_BTTBB_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
		explicit UAI_BTTBB_Patrol(FObjectInitializer const& ObjectInitializer);
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
			float SearchRadius = 2000.f;

};
