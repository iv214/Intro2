// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_Damage.h"
#include "GEMM_Custom.h"


UGE_Damage::UGE_Damage(const FObjectInitializer &ObjectInitializer)
{
    TTGEC_Damage = CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>("TTGEC_Damage");
}
void UGE_Damage::PostInitProperties()
{
    Super::PostInitProperties();
    
    FInheritedTagContainer TC_Damage;
    TC_Damage.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.Negative.Damage")));
    TTGEC_Damage->SetAndApplyTargetTagChanges(TC_Damage);
    DurationPolicy = EGameplayEffectDurationType::Instant;
    FGameplayModifierInfo DamageModifier;
    DamageModifier.Attribute = UBaseAttributeSet::GetHealthAttribute();
    DamageModifier.ModifierOp = EGameplayModOp::Additive;
    FGEMM_Custom FGEMM_Damage;
    DamageModifier.ModifierMagnitude = FGEMM_Damage;
    Modifiers.Empty();
    Modifiers.Add(DamageModifier);
}
