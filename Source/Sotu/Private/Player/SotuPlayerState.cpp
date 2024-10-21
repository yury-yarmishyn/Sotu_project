// stan

#include "Player/SotuPlayerState.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"
#include "AbilitySystem/SotuAttributeSet.h"
#include "Net/UnrealNetwork.h"

ASotuPlayerState::ASotuPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<USotuAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<USotuAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void ASotuPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASotuPlayerState, Level);
}

UAbilitySystemComponent* ASotuPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASotuPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
