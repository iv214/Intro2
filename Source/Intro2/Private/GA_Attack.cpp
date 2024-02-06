// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Attack.h"
// #include "AT_Task.h"


UGA_Attack::UGA_Attack() {
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag GATag_Attack = FGameplayTag::RequestGameplayTag(FName("Ability.Attack"));
	AbilityTags.AddTag(GATag_Attack);
	ActivationOwnedTags.AddTag(GATag_Attack);
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

}
void UGA_Attack::ActivateAbility(
			const FGameplayAbilitySpecHandle Handle,
			const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayAbilityActivationInfo ActivationInfo,
			const FGameplayEventData* TriggerEventData
        )
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{			
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	else
	{
		/*
		AT_Task* Task = UAT_Task::UAT_Task();

		// Task setup

		Task->ReadyForActivation();
		
		*/
	}
}