// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_UI.h"
#include "CsSimpleWidget.generated.h"

USTRUCT(BlueprintType)
struct FCsSimpleWidgetCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<class UCsSimpleWidget> Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FIntPoint Offset;

	FCsSimpleWidgetCache()
	{
		Reset();
	}

	~FCsSimpleWidgetCache() {}

	void Set(const uint16 &InIndex, class UCsSimpleWidget* InWidget)
	{
		SetIndex(InIndex);
		Widget = InWidget;
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSimpleWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
	{
		SetActiveIndex(InActiveIndex);

		IsAllocated = true;

		Owner = InOwner;
		Parent = InParent;

		SetLifeTime(Payload->LifeTime);

		Time = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);

		if (InObject && OnDeAllocate)
		{
			DelegateInvoker = (UObject*)InObject;
#if WITH_EDITOR
			OnDeAllocate_ScriptEvent.AddUObject(InObject, OnDeAllocate);
#endif // #if WITH_EDITOR
			OnDeAllocate_Event.AddUObject(InObject, OnDeAllocate);
		}
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSimpleWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsSimpleWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, InOwner, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, FCsSimpleWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
	{
		SetActiveIndex(InActiveIndex);

		IsAllocated = true;

		Owner = InOwner;
		Parent = InParent;

		SetLifeTime(Payload->LifeTime);

		Time = InTime;
		RealTime = InRealTime;
		SetFrame(InFrame);
	}

	void Init(const uint16& InActiveIndex, FCsSimpleWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner)
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, InOwner, nullptr);
	}

	void Init(const uint16& InActiveIndex, FCsSimpleWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		Reset_Internal();

		DisplayName = ECsCachedString::Str::Empty;
		Offset = FIntPoint::ZeroValue;
	}

	UCsSimpleWidget* GetWidget() { return Widget.IsValid() ? Widget.Get() : nullptr; }
};

UCLASS()
class CSCORE_API UCsSimpleWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void OnTick(const float &InDeltaTime);
	virtual void Init(const int32 &Index);

	virtual void Allocate(const uint16& ActiveIndex, FCsSimpleWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	virtual void DeAllocate();

	UPROPERTY()
	bool HasNativeContructed;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	FCsSimpleWidgetCache Cache;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	ESlateVisibility DefaultVisibility;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

	virtual void OnAddToCanvas();

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Show();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Hide();

	FVector2D ParentCanvasSize;

	FCsPrimitiveType<FVector2D> Position;
	FCsPrimitiveType<FVector2D> Size;

	virtual void SetPosition(const FVector2D &InPosition);
	virtual void SetSize(const FVector2D &InSize);
};