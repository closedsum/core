// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/Simple/CsSimpleWidget.h"
#include "Types/CsTypes_UI.h"
#include "CsPooledWidget.generated.h"

USTRUCT(BlueprintType)
struct FCsPooledWidgetCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	TWeakObjectPtr<class UCsPooledWidget> Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	ECsSimpleWidgetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FIntPoint Offset;

	FCsPooledWidgetCache() :
		Type(ECsSimpleWidgetType::ECsSimpleWidgetType_MAX)
	{
		Reset();
	}

	~FCsPooledWidgetCache() {}

	void Set(const int32 &InIndex, class UCsPooledWidget* InWidget)
	{
		Index = InIndex;
		Widget = InWidget;
	}

	void Init(FCsWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
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
		FCsPooledObjectCache::Reset();

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
	virtual void Init(const int32& Index, const ECsSimpleWidgetType& InType) override;
 
	virtual void Allocate(FCsWidgetPayload* Payload);
	virtual void DeAllocate();

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	FCsPooledWidgetCache Cache;

	virtual void OnAddToCanvas();

	FVector2D ParentCanvasSize;

	virtual void SetPosition(const FVector2D &InPosition) override;
};