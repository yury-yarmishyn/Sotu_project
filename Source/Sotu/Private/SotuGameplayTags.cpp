// stan


#include "SotuGameplayTags.h"
#include "GameplayTagsManager.h"

FSotuGameplayTags FSotuGameplayTags::GameplayTags;

void FSotuGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	
	GameplayTags.Attributes_Primary_Power = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Power"),
		FString("Increases all physical damage statements")
		);
	
	GameplayTags.Attributes_Primary_Faith = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Faith"),
		FString("Increases all Heart statements")
		);

	GameplayTags.Attributes_Primary_Tempo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Tempo"),
		FString("Increases all speed statements")
		);
	
	GameplayTags.Attributes_Primary_Fortune = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Fortune"),
		FString("Increases all chance statements")
		);

	/*
	 * Secondary Attributes
	 */
	
	GameplayTags.Attributes_Secondary_PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.PhysicalDamage"),
		FString("Increases melee damage")
		);
	
	GameplayTags.Attributes_Secondary_HeartDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HeartDamage"),
		FString("Increases damage dealt by Hearts")
		);
	
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Increases damage dealt by critical hits")
		);
	
	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackSpeed"),
		FString("Increases melee attack speed")
		);
	
	GameplayTags.Attributes_Secondary_HeartCastSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HeartCastSpeed"),
		FString("Increases heart cast speed")
		);
	
	GameplayTags.Attributes_Secondary_LifeRecoverySpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.LifeRecoverySpeed"),
		FString("Increases Life recovery speed")
		);
	
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Increases the chance of critical hits")
		);
	
	GameplayTags.Attributes_Secondary_DamageCancellationChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.DamageCancellationChance"),
		FString("Increases the chance of canceling incoming damage")
		);
	
	GameplayTags.Attributes_Secondary_MaxParanoia = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxParanoia"),
		FString("Max amount of Paranoia")
		);
	
	GameplayTags.Attributes_Secondary_MaxLife = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxLife"),
		FString("Max amount of Life")
		);

	/*
	 * Vital Attributes
	 */

	GameplayTags.Attributes_Vital_Paranoia = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Paranoia"),
		FString("Shows how close the player is to death")
		);

	GameplayTags.Attributes_Vital_Life = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Life"),
		FString("Used to cast Hearts and move")
		);

	/*
	 * Input Tags
	 */

	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Move"),
		FString("Input Tag for Move")
		);
	
	GameplayTags.InputTag_Look = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Look"),
		FString("Input Tag for Look")
		);
	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);
	
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);
	
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);
	
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);
	
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);
	
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);
}
