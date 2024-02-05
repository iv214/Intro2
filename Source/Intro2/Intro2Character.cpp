// Copyright Epic Games, Inc. All Rights Reserved.

#include "Intro2Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameCharacterUI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AIntro2Character

AIntro2Character::AIntro2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("NPCAbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("BaseAttributeSet");

	Player_UIC = CreateDefaultSubobject<UWidgetComponent>("NPCWidgetComponent");
	Player_UIC->SetupAttachment(RootComponent);
	Player_UIC->SetWidgetSpace(EWidgetSpace::Screen);
	Player_UIC->SetRelativeLocation(FVector(0, 0, 120));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetHelper{TEXT("/Game/UI/BP_GameCharacterUI")};
	if (WidgetHelper.Succeeded())
	{
		Player_UIC->SetWidgetClass(WidgetHelper.Class);
	}
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SetupStimulusSource();
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AIntro2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	SetHealth(95.0f);
}

// Called every frame
void AIntro2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float health = GetHealth();
	float maxHealth = GetMaxHealth();
	// UE_LOG(LogTemp, Warning, TEXT("Player Health is %f/%f.\n"), health, maxHealth);

	if (auto const widget = Cast<UGameCharacterUI>(Player_UIC->GetUserWidgetObject()))
	{
		widget->SetHealthPercent(health/maxHealth);
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("SetHealthPercent Error."));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AIntro2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIntro2Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIntro2Character::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AIntro2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AIntro2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

UAbilitySystemComponent* AIntro2Character::GetAbilitySystemComponent() const
{
	return AIntro2Character::AbilitySystemComponent;
}

float AIntro2Character::GetMaxHealth() const
{
	if (AbilitySystemComponent) {
		return AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
	}
	return -1.0f;
}
void AIntro2Character::SetMaxHealth(float Value)
{
	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetMaxHealthAttribute(), Value);
	}
}
float AIntro2Character::GetHealth() const
{
	if (AbilitySystemComponent) {
		return AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute());
	}
	return -1.0f;
}
void AIntro2Character::SetHealth(float Value)
{
	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetNumericAttributeBase(UBaseAttributeSet::GetHealthAttribute(), Value);
	}
}
void AIntro2Character::ChangeHealth(float Value)
{
	SetHealth(GetHealth() + Value);
}
void AIntro2Character::ChangeMaxHealth(float Value)
{
	SetMaxHealth(GetMaxHealth() + Value);
}

void AIntro2Character::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}