// stan

#include "AbilitySystem/SotuAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "SotuGameplayTags.h"
#include "GameFramework/Character.h"

USotuAttributeSet::USotuAttributeSet()
{
	const FSotuGameplayTags& GameplayTags = FSotuGameplayTags::Get();

	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Power, GetPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Faith, GetFaithAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Tempo, GetTempoAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Fortune, GetFortuneAttribute);

	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_PhysicalDamage, GetPhysicalDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HeartDamage, GetHeartDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_AttackSpeed, GetAttackSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HeartCastSpeed, GetHeartCastSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_LifeRecoverySpeed, GetLifeRecoverySpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_DamageCancellationChance, GetDamageCancellationChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxParanoia, GetParanoiaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxLife, GetMaxLifeAttribute);
}

void USotuAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, Paranoia, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, Life, COND_None, REPNOTIFY_Always);

	// Primary Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, Power, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, Faith, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, Tempo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, Fortune, COND_None, REPNOTIFY_Always);

	// Secondary Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, HeartDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, HeartCastSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, LifeRecoverySpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, DamageCancellationChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, MaxParanoia, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USotuAttributeSet, MaxLife, COND_None, REPNOTIFY_Always);
}

void USotuAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetParanoiaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxParanoia());
	}
	if (Attribute == GetLifeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxLife());
	}
}

void USotuAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void USotuAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetParanoiaAttribute())
	{
		SetParanoia(FMath::Clamp(GetParanoia(), 0.f, GetMaxParanoia()));
	}
	if (Data.EvaluatedData.Attribute == GetLifeAttribute())
	{
		SetLife(FMath::Clamp(GetLife(), 0.f, GetMaxLife()));
	}
}

void USotuAttributeSet::OnRep_Paranoia(const FGameplayAttributeData& OldParanoia) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, Paranoia, OldParanoia);
}

void USotuAttributeSet::OnRep_Life(const FGameplayAttributeData& OldLife) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, Life, OldLife);
}

void USotuAttributeSet::OnRep_Power(const FGameplayAttributeData& OldPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, Power, OldPower);
}

void USotuAttributeSet::OnRep_Faith(const FGameplayAttributeData& OldFaith) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, Faith, OldFaith);
}

void USotuAttributeSet::OnRep_Tempo(const FGameplayAttributeData& OldTempo) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, Tempo, OldTempo);
}

void USotuAttributeSet::OnRep_Fortune(const FGameplayAttributeData& OldFortune) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, Fortune, OldFortune);
}

void USotuAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, PhysicalDamage, OldPhysicalDamage);
}

void USotuAttributeSet::OnRep_HeartDamage(const FGameplayAttributeData& OldHeartDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, HeartDamage, OldHeartDamage);
}

void USotuAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, AttackSpeed, OldAttackSpeed);
}

void USotuAttributeSet::OnRep_HeartCastSpeed(const FGameplayAttributeData& OldHeartCastSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, HeartCastSpeed, OldHeartCastSpeed);
}

void USotuAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void USotuAttributeSet::OnRep_LifeRecoverySpeed(const FGameplayAttributeData& OldLifeRecoverySpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, LifeRecoverySpeed, OldLifeRecoverySpeed);
}

void USotuAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void USotuAttributeSet::OnRep_DamageCancellationChance(const FGameplayAttributeData& OldDamageCancellationChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, DamageCancellationChance, OldDamageCancellationChance);
}

void USotuAttributeSet::OnRep_MaxParanoia(const FGameplayAttributeData& OldMaxParanoia) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, MaxParanoia, OldMaxParanoia);
}

void USotuAttributeSet::OnRep_MaxLife(const FGameplayAttributeData& OldMaxLife) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USotuAttributeSet, MaxLife, OldMaxLife);
}