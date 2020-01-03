// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsManager_Widget.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"

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

const FString& FCsManager_Widget::EnumTypeToString(const ECsSimpleWidgetType& e)
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

UCsPooledWidget* UICsManager_Widget::ConstructObject(const ECsSimpleWidgetType& Type)
{
	return  CreateWidget<UCsPooledWidget>(GetCurrentWorld(), ClassMap.Find(Type) ? ClassMap[Type] : UCsPooledWidget::StaticClass());
}

void UICsManager_Widget::CreatePool(const ECsSimpleWidgetType& Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void UICsManager_Widget::AddToPool(const ECsSimpleWidgetType& Type, UCsPooledWidget* Object)
{
	Internal->AddToPool(Type, Object);
}


void UICsManager_Widget::AddToActivePool(const ECsSimpleWidgetType& Type, UCsPooledWidget* Object)
{
	Internal->AddToActivePool(Type, Object);
}

void UICsManager_Widget::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

void UICsManager_Widget::GetAllActiveObjects(TArray<UCsPooledWidget*> &OutObjects)
{
	Internal->GetAllActiveObjects(OutObjects);
}

const TArray<class UCsPooledWidget*>* UICsManager_Widget::GetObjects(const ECsSimpleWidgetType& Type)
{
	return Internal->GetObjects(Type);
}

int32 UICsManager_Widget::GetActivePoolSize(const ECsSimpleWidgetType& Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool UICsManager_Widget::IsExhausted(const ECsSimpleWidgetType& Type)
{
	return Internal->IsExhausted(Type);
}

bool UICsManager_Widget::DeAllocate(const ECsSimpleWidgetType& Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

void UICsManager_Widget::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsWidgetPayload* UICsManager_Widget::AllocatePayload()
{
	return Internal->AllocatePayload();
}

UCsPooledWidget* UICsManager_Widget::Display(const ECsSimpleWidgetType& Type, FCsWidgetPayload& Payload)
{
	return Internal->Spawn(Type, &Payload);
}

UCsPooledWidget* UICsManager_Widget::Display(const ECsSimpleWidgetType& Type, FCsWidgetPayload* Payload)
{
	return Internal->Spawn(Type, Payload);
}