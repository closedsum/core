// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsManager_Widget.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"
#include "Managers/Widget/CsPooledWidget.h"

namespace ECsManagerWidgetCachedString
{
	namespace Str
	{
		const FString OnTick = TEXT("UCsManager_Widget::OnTick");
		const FString DeAllocate = TEXT("UCsManager_Widget::DeAllocate");
		const FString DeAllocateAll = TEXT("UCsManager_Widget::DeAllocateAll");
		const FString Show = TEXT("UCsManager_Widget::Show");
	}
}

UCsManager_Widget::UCsManager_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

///*static*/ UCsManager_Widget* UCsManager_Widget::Get(UWorld* InWorld)
//{
//	return InWorld->GetGameState<ACsGameState>()->Manager_Projectile;
//}

void UCsManager_Widget::Clear()
{
	Pool.Reset();
	ActiveWidgets.Reset();
}

void UCsManager_Widget::Shutdown()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->ConditionalBeginDestroy();
	}
	Clear();
}

void UCsManager_Widget::BeginDestroy()
{
	Shutdown();
	Super::BeginDestroy();
}

void UCsManager_Widget::CreatePool(UClass* InClass, const TCsSimpleWidgetType &Type, const int32 &Size)
{
	PoolSizes.Add(Type, Size);
	PoolIndices.Add(Type, 0);

	TArray<UCsPooledWidget*> WidgetPool;

	for (int32 I = 0; I < Size; ++I)
	{
		UCsPooledWidget* Widget = CreateWidget<UCsPooledWidget>(CurrentWorld, InClass);

		Widget->Init(I);
		Widget->DeAllocate();
		Pool.Add(Widget);
		WidgetPool.Add(Widget);
	}
	Pools.Add(Type, WidgetPool);
}

void UCsManager_Widget::AddToActivePool(UObject* InObject, const TCsSimpleWidgetType& Type)
{
	checkf(InObject, TEXT("UCsManager_Widget::AddToActivePool: InObject is NULL."));

	UCsPooledWidget* Widget = Cast<UCsPooledWidget>(InObject);

	checkf(Widget, TEXT("UCsManager_Widget::AddToActivePool: InObject (%s) is NOT type UCsPooledWidget."), *InObject->GetClass()->GetName());

	Widget->Cache.IsAllocated = true;

	if (TArray<UCsPooledWidget*>* WidgetsPtr = ActiveWidgets.Find(Type))
	{
		WidgetsPtr->Add(Widget);
	}
	else
	{
		TArray<UCsPooledWidget*> Widgets;
		Widgets.Add(Widget);
		ActiveWidgets.Add(Type, Widgets);
	}
	//Widget->Cache.OnDeAllocate_Event.AddUObject(this, &UCsManager_Widget::OnDeAllocate);
}

void UCsManager_Widget::OnNativeTick(const FGeometry& MyGeometry, const float &DeltaSeconds)
{
	const int32 PoolCount = ActiveWidgets.Num();

	for (int32 I = PoolCount - 1; I >= 0; --I)
	{
		const TCsSimpleWidgetType Type		 = (TCsSimpleWidgetType)I;
		TArray<UCsPooledWidget*>* WidgetsPtr = ActiveWidgets.Find(Type);

		const int32 WidgetCount = WidgetsPtr->Num();
		int32 EarliestIndex		= WidgetCount;

		for (int32 J = WidgetCount - 1; J >= 0; --J)
		{
			UCsPooledWidget* Widget = (*WidgetsPtr)[J];

			// Check if SimpleWidget was DeAllocated NOT in a normal way

			if (!Widget->Cache.IsAllocated)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Widget::OnTick: PooledWidget: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Widget->GetName()), Widget->Cache.Index);

				LogTransaction(ECsManagerWidgetCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Widget);

				WidgetsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
				continue;
			}

			if (!Widget->Cache.UseLifeTime)
			{
				Widget->OnNativeTick(MyGeometry, DeltaSeconds);
				continue;
			}

			if (CurrentWorld->GetTimeSeconds() - Widget->Cache.Time > Widget->Cache.LifeTime)
			{
				LogTransaction(ECsManagerWidgetCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Widget);

				Widget->DeAllocate();
				WidgetsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
			}
			else
			{
				Widget->OnNativeTick(MyGeometry, DeltaSeconds);
			}
		}

		// Update ActiveIndex
		if (EarliestIndex != WidgetCount)
		{
			const uint16 Max = WidgetsPtr->Num();

			for (uint16 J = EarliestIndex; J < Max; J++)
			{
				UCsPooledWidget* Widget = (*WidgetsPtr)[J];
				Widget->Cache.SetActiveIndex(J);
			}
		}
	}
}

int32 UCsManager_Widget::GetActivePoolSize(const TCsSimpleWidgetType& Type)
{
	TArray<UCsPooledWidget*>* WidgetsPtr = ActiveWidgets.Find(Type);

	if (!WidgetsPtr)
		return CS_EMPTY;
	return WidgetsPtr->Num();
}

bool UCsManager_Widget::IsExhausted(const TCsSimpleWidgetType &Type)
{
	TArray<UCsPooledWidget*>* PoolPtr = Pools.Find(Type);

	if (!PoolPtr)
		return true;

	return GetActivePoolSize(Type) >= PoolPtr->Num();
}

void UCsManager_Widget::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	if (CsCVarLogManagerWidgetTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UCsPooledWidget* Widget = Cast<UCsPooledWidget>(InObject);

		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString WidgetName	   = Widget->GetName();
		const float CurrentTime		   = Widget->GetWorld()->GetTimeSeconds();
		const UObject* WidgetOwner	   = Widget->Cache.GetOwner();
		const FString OwnerName		   = WidgetOwner ? WidgetOwner->GetName() : ECsCachedString::Str::None;
		const UObject* Parent		   = Widget->Cache.GetParent();
		const FString ParentName	   = Parent ? Parent->GetName() : ECsCachedString::Str::None;

		if (WidgetOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s SimpleWidget: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *WidgetName, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (WidgetOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s SimpleWidget: %s at %f for %s."), *FunctionName, *TransactionAsString, *WidgetName, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s SimpleWidget: %s at %f attached to %s."), *TransactionAsString, *FunctionName, *WidgetName, CurrentTime, *ParentName);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s SimpleWidget: %s at %f."), *FunctionName, *TransactionAsString, *WidgetName, CurrentTime);
		}
	}
}

UCsPooledWidget* UCsManager_Widget::Allocate(const TCsSimpleWidgetType &Type)
{
	TArray<UCsPooledWidget*>* WidgetPool = Pools.Find(Type);
	const uint16 Size					 = *(PoolSizes.Find(Type));

	if (Size == CS_EMPTY)
	{
		checkf(0, TEXT("UCsManager_Widget::Allocate: Pool: %s is exhausted"), *(ECsSimpleWidgetType::ToString(Type)));
		return nullptr;
	}

	for (uint16 I = 0; I < Size; ++I)
	{
		uint16* PoolIndexPtr	= (PoolIndices.Find(Type));
		*PoolIndexPtr			= (*PoolIndexPtr + I) % Size;
		UCsPooledWidget* Widget = (*WidgetPool)[*PoolIndexPtr];

		if (!Widget->Cache.IsAllocated)
		{
			Widget->Cache.IsAllocated = true;
			return Widget;
		}
	}
	checkf(0, TEXT("UCsManager_Widget::Allocate: Pool: %s is exhausted"), *(ECsSimpleWidgetType::ToString(Type)));
	return nullptr;
}

void UCsManager_Widget::DeAllocate(const TCsSimpleWidgetType &Type, const int32 &Index)
{
	TArray<UCsPooledWidget*>* Widgets = ActiveWidgets.Find(Type);

	if (!Widgets)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Widget::DeAllocate: SimpleWidget of Type: %s at PoolIndex: %d is already deallocated."), *(ECsSimpleWidgetType::ToString(Type)), Index);
		return;
	}

	const uint8 Count = Widgets->Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		UCsPooledWidget* Widget = (*Widgets)[I];

		// Update ActiveIndex
		if (I > CS_FIRST)
		{
			Widget->Cache.DecrementActiveIndex();
		}

		if (Widget->Cache.Index == Index)
		{
			LogTransaction(ECsManagerWidgetCachedString::Str::DeAllocate, ECsPoolTransaction::Deallocate, Widget);

			Widget->DeAllocate();
			Widgets->RemoveAt(I);

			/*
#if WITH_EDITOR
			OnDeAllocateEX_ScriptEvent.Broadcast(Index, I, Actor->Cache.Type);
#endif // #if WITH_EDITOR
			OnDeAllocateEX_Internal_Event.Broadcast(Index, I, (TCsInteractiveType)Actor->Cache.Type);
			*/
			return;
		}
	}

	// Correct on Cache "Miss"
	for (int32 I = 1; I < Count; ++I)
	{
		UCsPooledWidget* Widget = (*Widgets)[I];
		// Reset ActiveIndex
		Widget->Cache.SetActiveIndex(I);
	}
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Widget::DeAllocate: PooledWidget of Type: %s at PoolIndex: %d is already deallocated."), *(ECsSimpleWidgetType::ToString(Type)), Index);
}

void UCsManager_Widget::DeAllocateAll()
{
	for (uint8 I = 0; I < ECS_SIMPLE_WIDGET_TYPE_MAX; ++I)
	{
		const TCsSimpleWidgetType Type = (TCsSimpleWidgetType)I;

		TArray<UCsPooledWidget*>* Widgets = ActiveWidgets.Find(Type);

		if (!Widgets)
			continue;

		const int32 WidgetCount = Widgets->Num();

		for (int32 J = WidgetCount - 1; J >= 0; --J)
		{
			LogTransaction(ECsManagerWidgetCachedString::Str::DeAllocateAll, ECsPoolTransaction::Deallocate, (*Widgets)[J]);

			(*Widgets)[J]->DeAllocate();
			Widgets->RemoveAt(J);
		}
	}
}

void UCsManager_Widget::AddPoolToCanvas(UCanvasPanel* InCanvas, const TCsSimpleWidgetType &Type)
{
	TArray<UCsPooledWidget*>* WidgetsPtr = Pools.Find(Type);

	if (!WidgetsPtr)
		return;

	const uint16 Count = WidgetsPtr->Num();

	for (uint16 I = 0; I < Count; ++I)
	{
		InCanvas->AddChildToCanvas((*WidgetsPtr)[I]);
		(*WidgetsPtr)[I]->OnAddToCanvas();
	}
}

// Payload
#pragma region

FCsPooledWidgetPayload* UCsManager_Widget::AllocatePayload()
{
	for (uint8 I = 0; I < CS_POOLED_WIDGET_PAYLOAD_SIZE; ++I)
	{
		const uint8 Index				= (PayloadIndex + I) % CS_POOLED_WIDGET_PAYLOAD_SIZE;
		FCsPooledWidgetPayload* Payload = &(Payloads[Index]);
		
		if (!Payload->IsAllocated)
		{
			Payload->IsAllocated = true;
			return Payload;
		}
	}
	checkf(0, TEXT("UCsManager_Widget::AllocatePayload: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Payload

// Show
#pragma region

UCsPooledWidget* UCsManager_Widget::Show(const TCsSimpleWidgetType &Type, FCsPooledWidgetPayload* Payload, UObject* InOwner, UObject* InParent)
{
	UCsPooledWidget* Widget = Allocate(Type);

	Widget->Allocate(GetActivePoolSize(Type), Payload, CurrentWorld->GetTimeSeconds(), CurrentWorld->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(CurrentWorld), InOwner, InParent);

	LogTransaction(ECsManagerWidgetCachedString::Str::Show, ECsPoolTransaction::Allocate, Widget);

	AddToActivePool(Widget, Type);
	Payload->Reset();
	return Widget;
}

#pragma endregion Show