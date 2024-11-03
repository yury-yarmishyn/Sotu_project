// stan


#include "AbilitySystem/SotuAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SotuPlayerState.h"
#include "UI/HUD/SotuHUD.h"

UOverlayWidgetController* USotuAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)
	{
		if (ASotuHUD* SotuHUD = Cast<ASotuHUD>(PC->GetHUD()))
		{
			ASotuPlayerState* PS = PC->GetPlayerState<ASotuPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return SotuHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
