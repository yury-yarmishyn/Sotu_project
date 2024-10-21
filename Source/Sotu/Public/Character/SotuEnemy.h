// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SotuCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "SotuEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API ASotuEnemy : public ASotuCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ASotuEnemy();

	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** end Enemy Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};