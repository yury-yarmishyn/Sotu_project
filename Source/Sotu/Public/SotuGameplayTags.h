// stan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * SotuGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FSotuGameplayTags
{
public:
 static const FSotuGameplayTags& Get() { return GameplayTags; };
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Primary_Power;
 FGameplayTag Attributes_Primary_Faith;
 FGameplayTag Attributes_Primary_Tempo;
 FGameplayTag Attributes_Primary_Fortune;
 
 FGameplayTag Attributes_Secondary_PhysicalDamage;
 FGameplayTag Attributes_Secondary_HeartDamage;
 FGameplayTag Attributes_Secondary_CriticalHitDamage;
 FGameplayTag Attributes_Secondary_AttackSpeed;
 FGameplayTag Attributes_Secondary_HeartCastSpeed;
 FGameplayTag Attributes_Secondary_LifeRecoverySpeed;
 FGameplayTag Attributes_Secondary_CriticalHitChance;
 FGameplayTag Attributes_Secondary_DamageCancellationChance;
 FGameplayTag Attributes_Secondary_MaxParanoia;
 FGameplayTag Attributes_Secondary_MaxLife;

 FGameplayTag Attributes_Vital_Paranoia;
 FGameplayTag Attributes_Vital_Life;

 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;

private:
 static FSotuGameplayTags GameplayTags;
};