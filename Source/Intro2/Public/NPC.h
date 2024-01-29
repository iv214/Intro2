// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "BaseAttributeSet.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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

	UPROPERTY()
	UBaseAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

public:
	ANPC();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
		virtual float GetHealth() const;
	
	UFUNCTION(BlueprintCallable)
		virtual void ChangeHealth(float Value);

protected:
	void Move(FVector2D MovementVector);

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};