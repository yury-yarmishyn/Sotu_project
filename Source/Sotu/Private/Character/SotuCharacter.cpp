// stan


#include "Character/SotuCharacter.h"

#include "AbilitySystemComponent.h"
#include "EditorDirectories.h"
#include "EnhancedInputSubsystems.h"
#include "SotuGameplayTags.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/SotuInputComponent.h"
#include "Player/SotuPlayerController.h"
#include "Player/SotuPlayerState.h"
#include "UI/HUD/SotuHUD.h"

struct FSotuGameplayTags;

ASotuCharacter::ASotuCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(40.f, 90.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 50.f);
	CameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ASotuCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ASotuCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

int32 ASotuCharacter::GetPlayerLevel()
{
	const ASotuPlayerState* SotuPlayerState = GetPlayerState<ASotuPlayerState>();
	check(SotuPlayerState);
	return SotuPlayerState->GetPlayerLevel();
}

void ASotuCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset,TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);

	USotuInputComponent* SotuInputComponent = CastChecked<USotuInputComponent>(PlayerInputComponent);

	SotuInputComponent->BindNativeInputAction(InputConfigDataAsset, FSotuGameplayTags::Get().InputTag_Move, ETriggerEvent::Triggered,this, &ThisClass::Input_Move);
	SotuInputComponent->BindNativeInputAction(InputConfigDataAsset, FSotuGameplayTags::Get().InputTag_Look, ETriggerEvent::Triggered ,this, &ThisClass::Input_Look);
}

void ASotuCharacter::InitAbilityActorInfo()
{
	ASotuPlayerState* SotuPlayerState = GetPlayerState<ASotuPlayerState>();
	check(SotuPlayerState);
	SotuPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SotuPlayerState, this);
	Cast<USotuAbilitySystemComponent>(SotuPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = SotuPlayerState->GetAbilitySystemComponent();
	AttributeSet = SotuPlayerState->GetAttributeSet();
	
	if(ASotuPlayerController* SotuPlayerController = Cast<ASotuPlayerController>(GetController()))
	{
		if (ASotuHUD* SotuHUD = Cast<ASotuHUD>(SotuPlayerController->GetHUD()))
		{
			SotuHUD->InitOverlay(SotuPlayerController, SotuPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}

void ASotuCharacter::Input_Move(const FInputActionValue& InputActionValue)
{	
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f,Controller->GetControlRotation().Yaw,0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection,MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection,MovementVector.X);
	}
}

void ASotuCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}
