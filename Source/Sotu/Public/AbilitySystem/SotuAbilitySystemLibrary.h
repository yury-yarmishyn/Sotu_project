// stan

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SotuPlayerState.h"
#include "UI/HUD/SotuHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "SotuAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SOTU_API USotuAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "SotuAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "SotuAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	template<typename T>
	static T* GetWidgetController(const UObject* WorldContextObject,
		TFunction<T*(ASotuHUD*, const FWidgetControllerParams&)> GetControllerFunc);
};

template<typename T>
T* USotuAbilitySystemLibrary::GetWidgetController(const UObject* WorldContextObject, TFunction<T*(ASotuHUD*, const FWidgetControllerParams&)> GetControllerFunc)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ASotuHUD* SotuHUD = Cast<ASotuHUD>(PC->GetHUD()))
		{
			ASotuPlayerState* PS = PC->GetPlayerState<ASotuPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return GetControllerFunc(SotuHUD, WidgetControllerParams);
		}
	}
	return nullptr;
}