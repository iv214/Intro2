// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Attack.generated.h"

UCLASS()
class INTRO2_API UGA_Attack : public UGameplayAbility
{
	GENERATED_BODY()

	protected:
		virtual void ActivateAbility
		(
			const FGameplayAbilitySpecHandle Handle,
			const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayAbilityActivationInfo ActivationInfo,
			const FGameplayEventData* TriggerEventData
		) override;
	public:
		UGA_Attack();
	
};
