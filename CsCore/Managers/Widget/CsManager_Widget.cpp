// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsManager_Widget.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// Internal
#pragma region

FCsManager_Widget::~FCsManager_Widget() {}

void FCsManager_Widget::DeconstructObject(UCsPooledWidget* o)
{
	if (o && !o->IsPendingKill())
		o->ConditionalBeginDestroy();
}

FString FCsManager_Widget::GetObjectName(UCsPooledWidget* o)
{
	return o->GetName();
}

const FString& FCsManager_Widget::EnumTypeToString(const TCsSimpleWidgetType &e)
{
	return EMCsSimpleWidgetType::Get().ToString(e);
}

const FString& FCsManager_Widget::EnumTypeToString(const int32 &index)
{
	return EMCsSimpleWidgetType::Get().ToString(index);
}

void FCsManager_Widget::Log(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

#pragma endregion // Internal

UICsManager_Widget::UICsManager_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Internal = new FCsManager_Widget();
	Internal->Init(TEXT("UICsManager_Widget"), TEXT("UCsPooledWidget"), nullptr, &CsCVarLogManagerWidgetTransactions);
	Internal->ConstructObject_Call.Unbind();
	Internal->ConstructObject_Call.BindUObject(this, &UICsManager_Widget::ConstructObject);
}

///*static*/ UICsManager_Widget* UICsManager_Widget::Get(UWorld* InWorld)
//{
//	return InWorld->GetGameState<ACsGameState>()->Manager_Projectile;
//}


void UICsManager_Widget::Clear()
{
	Internal->Clear();
}

void UICsManager_Widget::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void UICsManager_Widget::BeginDestroy()
{
	Shutdown();

	Super::BeginDestroy();
}

UWorld* UICsManager_Widget::GetCurrentWorld()
{
	return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
}

UCsPooledWidget* UICsManager_Widget::ConstructObject(const TCsSimpleWidgetType &Type)
{
	return  CreateWidget<UCsPooledWidget>(GetCurrentWorld(), UCsPooledWidget::StaticClass());
}

void UICsManager_Widget::CreatePool(const TCsSimpleWidgetType &Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void UICsManager_Widget::CreatePool(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, const int32 &Size)
{
	Internal->CreatePool((TCsSimpleWidgetType)Type, Size);
}

void UICsManager_Widget::AddToPool(const TCsSimpleWidgetType &Type, UCsPooledWidget* Object)
{
	Internal->AddToPool(Type, Object);
}

void UICsManager_Widget::AddToPool(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, UCsPooledWidget* Object)
{
	Internal->AddToPool((TCsSimpleWidgetType)Type, Object);
}

void UICsManager_Widget::AddToActivePool(const TCsSimpleWidgetType &Type, UCsPooledWidget* Object)
{
	Internal->AddToActivePool(Type, Object);
}

void UICsManager_Widget::AddToActivePool(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, UCsPooledWidget* Object)
{
	Internal->AddToActivePool((TCsSimpleWidgetType)Type, Object);
}

void UICsManager_Widget::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

void UICsManager_Widget::GetAllActiveObjects(TArray<UCsPooledWidget*> &OutObjects)
{
	Internal->GetAllActiveObjects(OutObjects);
}

const TArray<class UCsPooledWidget*>* UICsManager_Widget::GetObjects(const TCsSimpleWidgetType& Type)
{
	return Internal->GetObjects(Type);
}

int32 UICsManager_Widget::GetActivePoolSize(const TCsSimpleWidgetType &Type)
{
	return Internal->GetActivePoolSize(Type);
}

int32 UICsManager_Widget::GetActivePoolSize(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type)
{
	return Internal->GetActivePoolSize((TCsSimpleWidgetType)Type);
}

bool UICsManager_Widget::IsExhausted(const TCsSimpleWidgetType &Type)
{
	return Internal->IsExhausted(Type);
}

bool UICsManager_Widget::IsExhausted(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type)
{
	return Internal->IsExhausted((TCsSimpleWidgetType)Type);
}

bool UICsManager_Widget::DeAllocate(const TCsSimpleWidgetType &Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

bool UICsManager_Widget::DeAllocate(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, const int32 &Index)
{
	return Internal->DeAllocate((TCsSimpleWidgetType)Type, Index);
}

void UICsManager_Widget::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsWidgetPayload* UICsManager_Widget::AllocatePayload()
{
	return Internal->AllocatePayload();
}

UCsPooledWidget* UICsManager_Widget::Display(const TCsSimpleWidgetType &Type, FCsWidgetPayload &Payload)
{
	return Internal->Spawn(Type, &Payload);
}

UCsPooledWidget* UICsManager_Widget::Display(const TEnumAsByte<ECsSimpleWidgetType::Type> &Type, FCsWidgetPayload &Payload)
{
	return Internal->Spawn((TCsSimpleWidgetType)Type, &Payload);
}

UCsPooledWidget* UICsManager_Widget::Display(const TCsSimpleWidgetType &Type, FCsWidgetPayload *Payload)
{
	return Internal->Spawn(Type, Payload);
}