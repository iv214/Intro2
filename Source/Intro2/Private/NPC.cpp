// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameCharacterUI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("NPCAbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("BaseAttributeSet");

	NPC_UIC = CreateDefaultSubobject<UWidgetComponent>("NPCWidgetComponent");
	NPC_UIC->SetupAttachment(RootComponent);
	NPC_UIC->SetWidgetSpace(EWidgetSpace::Screen);
	NPC_UIC->SetRelativeLocation(FVector(0, 0, 120));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetHelper{TEXT("/Game/UI/BP_GameCharacterUI")};
	if (WidgetHelper.Succeeded())
	{
		NPC_UIC->SetWidgetClass(WidgetHelper.Class);
	}
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named BP_NPC (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	SetHealth(75.0);
	/*
	//Add Input Mapping Context
	if (AAIController* NPCController = Cast<AAIController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	*/
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float health = GetHealth();
	float maxHealth = GetMaxHealth();
	// UE_LOG(LogTemp, Warning, TEXT("Health is %f/%f.\n"), health, maxHealth);

	if (auto const widget = Cast<UGameCharacterUI>(NPC_UIC->GetUserWidgetObject()))
	{
		widget->SetHealthPercent(health/maxHealth);
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("SetHealthPercent Error."));
	}
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANPC::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANPC::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}*/
}


void ANPC::Move(FVector2D MovementVector)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

UAbilitySystemComponent* ANPC::GetAbilitySystemComponent() const
{
	return ANPC::AbilitySystemComponent;
}

float ANPC::GetMaxHealth() const
{
	if (AbilitySystemComponent) {
		return AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
	}
	return -1.0f;
}
void ANPC::SetMaxHealth(float Value)
{
	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetMaxHealthAttribute(), Value);
	}
}
float ANPC::GetHealth() const
{
	if (AbilitySystemComponent) {
		return AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute());
	}
	return -1.0f;
}
void ANPC::SetHealth(float Value)
{
	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetHealthAttribute(), Value);
	}
}
void ANPC::ChangeHealth(float Value)
{
	SetHealth(GetHealth() + Value);
}
void ANPC::ChangeMaxHealth(float Value)
{
	SetMaxHealth(GetMaxHealth() + Value);
}
UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return Tree;
}