#include "Player/SotuPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "SotuGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/SotuInputComponent.h"
#include "Interaction/EnemyInterface.h"

ASotuPlayerController::ASotuPlayerController()
{
	bReplicates = true;
}

void ASotuPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ASotuPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void ASotuPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	// if (!InputTag.MatchesTagExact(FSotuGameplayTags::Get().InputTag_LMB))
	// {
	// 	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	// 	return;
	// }

	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
}

void ASotuPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	// if (!InputTag.MatchesTagExact(FSotuGameplayTags::Get().InputTag_LMB))
	// {
	// 	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	// }
	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
}

USotuAbilitySystemComponent* ASotuPlayerController::GetASC()
{
	if (SotuAbilitySystemComponent == nullptr)
	{
		SotuAbilitySystemComponent = Cast<USotuAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return SotuAbilitySystemComponent;
}

void ASotuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(SotuContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(SotuContext, 0);
	}
}

void ASotuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USotuInputComponent* SotuInputComponent = CastChecked<USotuInputComponent>(InputComponent);
	SotuInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASotuPlayerController::Move);
	SotuInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASotuPlayerController::Look);
	SotuInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ASotuPlayerController::ShiftPressed);
	SotuInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ASotuPlayerController::ShiftReleased);
	SotuInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ASotuPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, GetControlRotation().Yaw,0.f);
	
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		return;
	}

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASotuPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn)
	{
		return;
	}
	
	if (LookAxisVector.X != 0.f)
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		ControlledPawn->AddControllerPitchInput(-LookAxisVector.Y);
	}
}

