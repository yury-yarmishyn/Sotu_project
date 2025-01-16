// stan


#include "AbilitySystem/Abilities/SotuProjectileSpell.h"

#include "Character/SotuCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/SotuPlayerController.h"
#include "Player/SotuPlayerState.h"

void USotuProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKismetSystemLibrary::PrintString(this, "ActivateAbility", true, true);
}

void USotuProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		const ASotuPlayerState* PlayerState = Cast<ASotuPlayerState>(GetOwningActorFromActorInfo());
		APawn* OwningPawn = PlayerState->GetPawn();
		if (!OwningPawn) return;

		const APlayerController* PlayerController = PlayerState->GetPlayerController();
		if (!PlayerController) return;

		FVector Direction;
		if (ProjectileTargetLocation != FVector::ZeroVector)
		{
			Direction = (ProjectileTargetLocation - SocketLocation).GetSafeNormal();
		}
		else
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

			Direction = (CameraLocation + CameraRotation.Vector() * 1000.0f - SocketLocation).GetSafeNormal();
		}
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Direction.Rotation().Quaternion());

		ASotuProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASotuProjectile>(
			ProjectileClass,
			SpawnTransform,
			OwningPawn,
			OwningPawn,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
