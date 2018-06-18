// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_UI.h"
#include "CsPooledWidget.generated.h"

USTRUCT(BlueprintType)
struct FCsPooledWidgetCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class UCsPooledWidget> Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FIntPoint Offset;

	FCsPooledWidgetCache()
	{
		Reset();
	}

	~FCsPooledWidgetCache() {}

	void Set(const uint16 &InIndex, class UCsPooledWidget* InWidget)
	{
		SetIndex(InIndex);
		Widget = InWidget;
	}

	void Init(const uint16& InActiveIndex, FCsWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		SetActiveIndex(InActiveIndex);

		IsAllocated = true;

		Owner = Payload->Owner;
		Parent = Payload->Parent;

		SetLifeTime(Payload->LifeTime);

		Time = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);
	}

	virtual void Reset() override
	{
		Reset_Internal();

		DisplayName = ECsCached::Str::Empty;
		Offset = FIntPoint::ZeroValue;
	}

	FORCEINLINE UCsPooledWidget* GetWidget() { return Widget.IsValid() ? Widget.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetWidget() { return Cast<T>(GetWidget()); }
};

UCLASS()
class CSCORE_API UCsPooledWidget : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void Init(const FGeometry& MyGeometry) override;
	virtual void Init(const int32 &Index, const TCsSimpleWidgetType &InType) override;
 
	virtual void Allocate(const uint16& ActiveIndex, FCsWidgetPayload* Payload);
	virtual void DeAllocate();

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	FCsPooledWidgetCache Cache;

	virtual void OnAddToCanvas();

	FVector2D ParentCanvasSize;

	virtual void SetPosition(const FVector2D &InPosition) override;
};