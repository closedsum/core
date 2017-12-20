// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsManager_Widget.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Managers/Widget/CsSimpleWidget.h"

namespace ECsManagerWidgetCachedString
{
	namespace Str
	{
		const FString OnTick = TEXT("UCsManager_Widget::OnTick");
		const FString DeAllocate = TEXT("UCsManager_Widget::DeAllocate");
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

	for (int32 I = 0; I < Count; I++)
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

void UCsManager_Widget::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const TCsSimpleWidgetType &Type, const int32 &Size)
{
	PoolSizes.Add(Type, Size);
	PoolIndices.Add(Type, 0);

	TArray<UCsSimpleWidget*> WidgetPool;

	for (int32 I = 0; I < Size; I++)
	{
		UCsSimpleWidget* Widget = NewObject<UCsSimpleWidget>(ObjectClass);

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

	UCsSimpleWidget* Widget = Cast<UCsSimpleWidget>(InObject);

	checkf(Widget, TEXT("UCsManager_Widget::AddToActivePool: InObject (%s) is NOT type UCsSimpleWidget."), *InObject->GetClass()->GetName());

	Widget->Cache.IsAllocated = true;

	if (TArray<UCsSimpleWidget*>* WidgetsPtr = ActiveWidgets.Find(Type))
	{
		WidgetsPtr->Add(Widget);
	}
	else
	{
		TArray<UCsSimpleWidget*> Widgets;
		Widgets.Add(Widget);
		ActiveWidgets.Add(Type, Widgets);
	}
	//Widget->Cache.OnDeAllocate_Event.AddUObject(this, &UCsManager_Widget::OnDeAllocate);
}

void UCsManager_Widget::OnTick(const float &DeltaSeconds)
{
	const int32 PoolCount = ActiveWidgets.Num();

	for (int32 I = PoolCount - 1; I >= 0; I--)
	{
		const TCsSimpleWidgetType Type		 = (TCsSimpleWidgetType)I;
		TArray<UCsSimpleWidget*>* WidgetsPtr = ActiveWidgets.Find(Type);

		const int32 WidgetCount = WidgetsPtr->Num();
		int32 EarliestIndex		= WidgetCount;

		for (int32 J = WidgetCount - 1; J >= 0; J--)
		{
			UCsSimpleWidget* Widget = (*WidgetsPtr)[J];

			// Check if SimpleWidget was DeAllocated NOT in a normal way

			if (!Widget->Cache.IsAllocated)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsManager_Widget::OnTick: SimpleWidget: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Widget->GetName()), Widget->Cache.Index);

				LogTransaction(ECsManagerWidgetCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Widget);

				WidgetsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
				continue;
			}

			if (!Widget->Cache.UseLifeTime)
				continue;

			if (GetWorld()->GetTimeSeconds() - Widget->Cache.Time > Widget->Cache.LifeTime)
			{
				LogTransaction(ECsManagerWidgetCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Widget);

				Widget->DeAllocate();
				WidgetsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
			}
		}

		// Update ActiveIndex
		if (EarliestIndex != WidgetCount)
		{
			const uint16 Max = WidgetsPtr->Num();

			for (uint16 J = EarliestIndex; J < Max; J++)
			{
				UCsSimpleWidget* Widget = (*WidgetsPtr)[J];
				Widget->Cache.SetActiveIndex(J);
			}
		}
	}
}

int32 UCsManager_Widget::GetActivePoolSize(const TCsSimpleWidgetType& Type)
{
	TArray<UCsSimpleWidget*>* WidgetsPtr = ActiveWidgets.Find(Type);

	if (!WidgetsPtr)
		return CS_EMPTY;
	return WidgetsPtr->Num();
}

bool UCsManager_Widget::IsExhausted(const TCsSimpleWidgetType &Type)
{
	TArray<UCsSimpleWidget*>* PoolPtr = Pools.Find(Type);

	if (!PoolPtr)
		return true;

	return GetActivePoolSize(Type) >= PoolPtr->Num();
}

void UCsManager_Widget::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	//if (CsCVarLogManagerProjectileTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		/*
		ACsProjectile* Projectile = Cast<ACsProjectile>(InObject);

		const FString TransactionAsString = Transaction == ECsPoolTransaction::Allocate ? TEXT("Allocating") : TEXT("DeAllocating");

		const FString ProjectileName   = Projectile->GetName();
		const FString DataName		   = Projectile->Cache.GetData()->ShortCode.ToString();
		const float CurrentTime		   = GetWorld()->GetTimeSeconds();
		const UObject* ProjectileOwner = Projectile->Cache.GetOwner();
		const FString OwnerName		   = ProjectileOwner ? ProjectileOwner->GetName() : TEXT("None");
		const UObject* Parent		   = Projectile->Cache.GetParent();
		const FString ParentName	   = Parent ? Parent->GetName() : TEXT("None");
		const FString LocationAsString = Projectile->GetActorLocation().ToString();
		const FString DirectionAsString = Projectile->GetActorRotation().Vector().GetSafeNormal().ToString();

		if (ProjectileOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f for %s attached to %s at %s moving at %s."), *FunctionName, *TransactionAsString, *ProjectileName, *DataName, CurrentTime, *OwnerName, *ParentName, *LocationAsString, *DirectionAsString);
		}
		else
		if (ProjectileOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f for %s at %s moving at %s."), *FunctionName, *TransactionAsString, *ProjectileName, *DataName, CurrentTime, *OwnerName, *LocationAsString, *DirectionAsString);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f attached to %s at %s moving at %s."), *TransactionAsString, *FunctionName, *ProjectileName, *DataName, CurrentTime, *ParentName, *LocationAsString, *DirectionAsString);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Projectile: %s with Data: %s at %f at %s moving at %s."), *FunctionName, *TransactionAsString, *ProjectileName, *DataName, CurrentTime, *LocationAsString, *DirectionAsString);
		}
		*/
	}
}

UCsSimpleWidget* UCsManager_Widget::Allocate(const TCsSimpleWidgetType &Type)
{
	TArray<UCsSimpleWidget*>* WidgetPool = Pools.Find(Type);
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
		UCsSimpleWidget* Widget = (*WidgetPool)[*PoolIndexPtr];

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
	TArray<UCsSimpleWidget*>* Widgets = ActiveWidgets.Find(Type);

	if (!Widgets)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Widget::DeAllocate: InteractiveActor of Type: %s at PoolIndex: %d is already deallocated."), *(ECsSimpleWidgetType::ToString(Type)), Index);
		return;
	}

	const uint8 Count = Widgets->Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		UCsSimpleWidget* Widget = (*Widgets)[I];

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
	for (int32 I = 1; I < Count; I++)
	{
		UCsSimpleWidget* Widget = (*Widgets)[I];
		// Reset ActiveIndex
		Widget->Cache.SetActiveIndex(I);
	}
	UE_LOG(LogCs, Warning, TEXT("UCsManager_Widget::DeAllocate: SimpleWidget of Type: %s at PoolIndex: %d is already deallocated."), *(ECsSimpleWidgetType::ToString(Type)), Index);
}

// Show
#pragma region

UCsSimpleWidget* UCsManager_Widget::Show(const TCsSimpleWidgetType &Type, FCsSimpleWidgetPayload* Payload, UObject* InOwner, UObject* InParent)
{
	UCsSimpleWidget* Widget = Allocate(Type);

	Widget->Allocate(GetActivePoolSize(Type), Payload, CurrentWorld->GetTimeSeconds(), CurrentWorld->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(CurrentWorld), InOwner, InParent);

	LogTransaction(ECsManagerWidgetCachedString::Str::Show, ECsPoolTransaction::Allocate, Widget);

	AddToActivePool(Widget, Type);
	return Widget;
}

#pragma endregion Show