// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SotuCharacter.h"

#include "AbilitySystemComponent.h"
#include "EditorDirectories.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SotuPlayerController.h"
#include "Player/SotuPlayerState.h"
#include "UI/HUD/SotuHUD.h"

ASotuCharacter::ASotuCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ASotuCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
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
