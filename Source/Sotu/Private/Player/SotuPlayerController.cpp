// stan

#include "Player/SotuPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "SotuGameplayTags.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/SotuInputComponent.h"
#include "Interaction/EnemyInterface.h"

void ASotuPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

USotuAbilitySystemComponent* ASotuPlayerController::GetAbilitySystemComponent()
{
	if(SotuAbilitySystemComponent == nullptr)
	{
		SotuAbilitySystemComponent = Cast<USotuAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));  
	}
	return SotuAbilitySystemComponent;
}

void ASotuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(SotuContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(SotuContext, 0);
	}
}

void ASotuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USotuInputComponent* SotuInputComponent = CastChecked<USotuInputComponent>(InputComponent);

	SotuInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASotuPlayerController::Move);
}

void ASotuPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// const FRotator Rotation = GetControlRotation();
	// const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//
	// const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//
	// if (APawn* ControlledPawn = GetPawn<APawn>())
	// {
	// 	ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
	// 	ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	// }
}
