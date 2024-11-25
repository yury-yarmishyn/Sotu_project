// stan

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SotuAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {};

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */

//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class SOTU_API USotuAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	USotuAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	// Vital Attributes 
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Paranoia, Category = "Vital Attributes")
	FGameplayAttributeData Paranoia;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, Paranoia);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Life, Category = "Vital Attributes")
	FGameplayAttributeData Life;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, Life);
	
	// Primary Attributes 

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Power, Category = "Primary Attributes")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, Power);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Faith, Category = "Primary Attributes")
	FGameplayAttributeData Faith;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, Faith);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Tempo, Category = "Primary Attributes")
	FGameplayAttributeData Tempo;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, Tempo);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Fortune, Category = "Primary Attributes")
	FGameplayAttributeData Fortune;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, Fortune);
	
	// Secondary Attributes 

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamage, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, PhysicalDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HeartDamage, Category = "Secondary Attributes")
	FGameplayAttributeData HeartDamage;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, HeartDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, AttackSpeed);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HeartCastSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData HeartCastSpeed;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, HeartCastSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LifeRecoverySpeed, Category = "Secondary Attributes")
	FGameplayAttributeData LifeRecoverySpeed;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, LifeRecoverySpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageCancellationChance, Category = "Secondary Attributes")
	FGameplayAttributeData DamageCancellationChance;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, DamageCancellationChance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxParanoia, Category = "Secondary Attributes")
	FGameplayAttributeData MaxParanoia;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, MaxParanoia);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxLife, Category = "Secondary Attributes")
	FGameplayAttributeData MaxLife;
	ATTRIBUTE_ACCESSORS(USotuAttributeSet, MaxLife);

	// Vital Attributes func
	
	UFUNCTION()
	void OnRep_Paranoia(const FGameplayAttributeData& OldParanoia) const;

	UFUNCTION()
	void OnRep_Life(const FGameplayAttributeData& OldLife) const;
	
	// Primary Attributes func
	
	UFUNCTION()
	void OnRep_Power(const FGameplayAttributeData& OldPower) const;

	UFUNCTION()
	void OnRep_Faith(const FGameplayAttributeData& OldFaith) const;
	
	UFUNCTION()
	void OnRep_Tempo(const FGameplayAttributeData& OldTempo) const;
	
	UFUNCTION()
	void OnRep_Fortune(const FGameplayAttributeData& OldFortune) const;
	
	// Secondary Attributes func 

	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const;

	UFUNCTION()
	void OnRep_HeartDamage(const FGameplayAttributeData& OldHeartDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UFUNCTION()
	void OnRep_HeartCastSpeed(const FGameplayAttributeData& OldHeartCastSpeed) const;

	UFUNCTION()
	void OnRep_LifeRecoverySpeed(const FGameplayAttributeData& OldLifeRecoverySpeed) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_DamageCancellationChance(const FGameplayAttributeData& OldDamageCancellationChance) const;
	
	UFUNCTION()
	void OnRep_MaxParanoia(const FGameplayAttributeData& OldMaxParanoia) const;
	
	UFUNCTION()
	void OnRep_MaxLife(const FGameplayAttributeData& OldMaxLife) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};