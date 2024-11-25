// stan


#include "AbilitySystem/MMC/MMC_MaxParanoia.h"
#include "AbilitySystem/SotuAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxParanoia::UMMC_MaxParanoia()
{
	FortuneDef.AttributeToCapture = USotuAttributeSet::GetFortuneAttribute();
	FortuneDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	FortuneDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(FortuneDef);
}

float UMMC_MaxParanoia::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Fortune = 0.f;
	GetCapturedAttributeMagnitude(FortuneDef, Spec, EvaluateParameters, Fortune);
	Fortune = FMath::Max<float>(Fortune, 0.0f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + 2.5f * Fortune + 10.f * PlayerLevel;
}


