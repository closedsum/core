#pragma once

#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "UI/CsTypes_UI.h"
#include "CsWidgetComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCOREDEPRECATED_API UCsWidgetComponent : public UWidgetComponent
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
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool bOnCalcCamera;

	void OnCalcCamera(const uint8& MappingId, const float& DeltaTime, const struct FMinimalViewInfo& OutResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowLocalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DistanceProjectedOutFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtLocalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FCsRotatorFlag CameraLockAxes;

	void OnTick_Handle_LocalCamera(const FVector& ViewLocation, const FRotator& ViewRotation);

#pragma endregion Camera

// Info
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetInfo(const FVector2D& Size, const FTransform& Transform, const bool& InFollowLocalCamera, const bool& InLookAtLocalCamera);

	void SetInfo(const FCsWidgetComponentInfo& Info);
	void SetInfo(const FCsWidgetActorInfo& Info);

#pragma endregion Info

// Visibility
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TEnumAsByte<ECsVisibility::Type> Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (InlineEditConditionToggle))
	bool bMinDrawDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (editcondition = "bMinDrawDistance"))
	FCsDrawDistance MyMinDrawDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool ScaleByDistance;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Show();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Hide();

	void OnTick_Handle_Scale();
	void OnTick_Handle_DrawDistance();

#pragma endregion Visiblity

// Movement
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector LocationOffset;

	void OnTick_Handle_Movement();

#pragma endregion Movement
};