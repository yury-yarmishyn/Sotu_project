// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SotuAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API USotuAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static USotuAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
