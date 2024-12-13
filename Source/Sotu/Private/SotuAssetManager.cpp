// stan


#include "SotuAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "SotuGameplayTags.h"

USotuAssetManager& USotuAssetManager::Get()
{
	check(GEngine)
	
	USotuAssetManager* SotuAssetManager = Cast<USotuAssetManager>(GEngine->AssetManager);
	return *SotuAssetManager;
}

void USotuAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FSotuGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
