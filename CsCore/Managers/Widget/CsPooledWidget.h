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

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsPooledWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)())
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
	void Init(const uint16& InActiveIndex, FCsPooledWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr, InObject, OnDeAllocate);
	}

	template<typename T>
	void Init(const uint16& InActiveIndex, FCsPooledWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)())
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, InOwner, nullptr, InObject, OnDeAllocate);
	}

	void Init(const uint16& InActiveIndex, FCsPooledWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner, UObject* InParent)
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

	void Init(const uint16& InActiveIndex, FCsPooledWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame, UObject* InOwner)
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, InOwner, nullptr);
	}

	void Init(const uint16& InActiveIndex, FCsPooledWidgetPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		Reset_Internal();

		DisplayName = ECsCachedString::Str::Empty;
		Offset = FIntPoint::ZeroValue;
	}

	UCsPooledWidget* GetWidget() { return Widget.IsValid() ? Widget.Get() : nullptr; }
};

UCLASS()
class CSCORE_API UCsPooledWidget : public UCsSimpleWidget
{
	GENERATED_UCLASS_BODY()

	virtual void Init() override;
	virtual void Init(const int32 &Index) override;
 
	virtual void Allocate(const uint16& ActiveIndex, FCsPooledWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent);
	virtual void DeAllocate();

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	FCsPooledWidgetCache Cache;

	virtual void OnAddToCanvas();

	FVector2D ParentCanvasSize;

	virtual void SetPosition(const FVector2D &InPosition) override;
};