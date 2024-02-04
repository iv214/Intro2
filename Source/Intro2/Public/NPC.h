// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "BaseAbilitySet.h"
#include "BaseAttributeSet.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "NPC.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UGameCharacterUI;
class UWidgetComponent;
class UGE_Damage;

UCLASS(config=Game)
class INTRO2_API ANPC : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(VisibleDefaultsOnly, Category = "Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	UBaseAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	UBaseAbilitySet* AbilitySet;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	FGameplayEffectSpec GESpec;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultEffect;

public:
	ANPC();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) //,  meta = (BindWidget, BlueprintSpawnableComponent))
	class UWidgetComponent* NPC_UIC;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable)
		virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable)
		virtual void SetMaxHealth(float Value);
	
	UFUNCTION(BlueprintCallable)
		virtual void SetHealth(float Value);
	
	UFUNCTION(BlueprintCallable)
		virtual void ChangeHealth(float Value);
	
	UFUNCTION(BlueprintCallable)
		virtual void ChangeMaxHealth(float Value);

protected:
	void Move(FVector2D MovementVector);

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* Tree;

	UFUNCTION(BlueprintCallable, Category = "Effects")
		void InitAbilities();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;
};