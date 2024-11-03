// stan


#include "SotuGameplayTags.h"
#include "GameplayTagsManager.h"

FSotuGameplayTags FSotuGameplayTags::GameplayTags;

void FSotuGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),
		FString("Reduces damage taken, improves Block Chance"));
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance"));
}
