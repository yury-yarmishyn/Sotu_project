// stan


#include "AbilitySystem/SotuAbilitySystemLibrary.h"
#include "UI/HUD/SotuHUD.h"
#include "UI/WidgetController/SotuWidgetController.h"

UOverlayWidgetController* USotuAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetController<UOverlayWidgetController>(WorldContextObject, 
		[](ASotuHUD* SotuHUD, const FWidgetControllerParams& Params) {
			return SotuHUD->GetOverlayWidgetController(Params);
		});
}

UAttributeMenuWidgetController* USotuAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	return GetWidgetController<UAttributeMenuWidgetController>(WorldContextObject, 
		[](ASotuHUD* SotuHUD, const FWidgetControllerParams& Params) {
			return SotuHUD->GetAttributeMenuWidgetController(Params);
		});
}
