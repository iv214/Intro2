// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Attack.h"

UGA_Attack::UGA_Attack() {
    ;
}
bool UGA_Attack::CanActivateAbility(
			const FGameplayAbilitySpecHandle Handle,
			const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayTagContainer* SourceTags,
			const FGameplayTagContainer* TargetTags,
			OUT FGameplayTagContainer* OptionalRelevantTags
		) const
{
    return true;
}
void UGA_Attack::ActivateAbility(
			const FGameplayAbilitySpecHandle Handle,
			const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayAbilityActivationInfo ActivationInfo,
			const FGameplayEventData* TriggerEventData
            )
{

}