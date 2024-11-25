// stan


#include "AbilitySystem/MMC/MMC_MaxLife.h"
#include "AbilitySystem/SotuAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxLife::UMMC_MaxLife()
{
	FaithDef.AttributeToCapture = USotuAttributeSet::GetFaithAttribute();
	FaithDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	FaithDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(FaithDef);
}

float UMMC_MaxLife::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Faith = 0.f;
	GetCapturedAttributeMagnitude(FaithDef, Spec, EvaluateParameters, Faith);
	Faith = FMath::Max<float>(Faith, 0.0f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + 4.f * Faith + 5.f * PlayerLevel;
}
