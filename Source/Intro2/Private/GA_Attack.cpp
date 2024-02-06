// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Attack.h"

UGA_Attack::UGA_Attack() {
    ;
}
void UGA_Attack::ActivateAbility(
			const FGameplayAbilitySpecHandle Handle,
			const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayAbilityActivationInfo ActivationInfo,
			const FGameplayEventData* TriggerEventData
        )
{
	bool bReplicateEndAbility = false;
	bool bWasCancelled = false;
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{			
		bReplicateEndAbility = true;
		bWasCancelled = true;
	}
	else
	{
		
		// ...

		
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}