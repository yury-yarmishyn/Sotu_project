// stan


#include "Character/SotuCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SotuAbilitySystemComponent.h"

ASotuCharacterBase::ASotuCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ASotuCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASotuCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASotuCharacterBase::InitAbilityActorInfo()
{
	
}

void ASotuCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ASotuCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ASotuCharacterBase::AddCharacterAbilities()
{
	USotuAbilitySystemComponent* SotuASC = CastChecked<USotuAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority()) return;

	SotuASC->AddCharacterAbilities(StartupAbilities);
}
