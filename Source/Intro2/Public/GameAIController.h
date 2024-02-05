// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "NPC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameAIController.generated.h"


UCLASS()
class INTRO2_API AGameAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AGameAIController(FObjectInitializer const& ObjectInitializer);
protected:
	virtual void OnPossess(APawn* InPawn) override;
private:
	UAISenseConfig_Sight* SightConfig;
	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetSeen(AActor* Actor, FAIStimulus const Stimulus);
public:
	UPROPERTY(EditAnywhere, Category = "AI")
    UEnvQuery* AIC_EQS;

	UFUNCTION(BlueprintCallable)
	void EQSf();

	void MoveToQueryResult(TSharedPtr<FEnvQueryResult> result);
};
