// Fill out your copyright notice in the Description page of Project Settings.


#include "SotuAssetManager.h"
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
}
