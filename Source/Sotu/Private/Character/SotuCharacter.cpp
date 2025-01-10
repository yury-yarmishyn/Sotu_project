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
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 50.f);
	CameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = true;

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