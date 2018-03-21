#pragma once

#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Types/CsTypes_UI.h"
#include "CsWidgetComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsWidgetComponent : public UWidgetComponent
{
	GENERATED_UCLASS_BODY()

	// virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

	UFUNCTION()
	class UCsUserWidget* GetWidget();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetInfo(const FCsWidgetActorInfo &Info);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Show();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Hide();
};