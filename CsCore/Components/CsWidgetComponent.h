#pragma once

#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Types/CsTypes_UI.h"
#include "CsWidgetComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsWidgetComponent : public UWidgetComponent
{
	GENERATED_UCLASS_BODY()

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION()
	class UUserWidget* GetWidget();

	template<typename T>
	T* GetWidget()
	{
		return Cast<T>(GetWidget());
	}

// Camera
#pragma region

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool bOnCalcCamera;

	void OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowLocalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DistanceProjectedOutFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtLocalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FCsRotatorFlag CameraLockAxes;

	void OnTick_Handle_LocalCamera(const FVector &ViewLocation, const FRotator &ViewRotation);

#pragma endregion Camera

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetInfo(const FVector2D &Size, const FTransform &Transform, const bool &InFollowLocalCamera, const bool &InLookAtLocalCamera);

	void SetInfo(const FCsWidgetComponentInfo &Info);
	void SetInfo(const FCsWidgetActorInfo &Info);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Show();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Hide();
};