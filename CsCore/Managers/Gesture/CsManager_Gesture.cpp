// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Gesture/CsManager_Gesture.h"
#include "CsCore.h"
#include "Managers/Gesture/CsGesture.h"

// static initializations
UCsManager_Gesture* UCsManager_Gesture::s_managerGestureSingleton;
bool UCsManager_Gesture::s_bManagerHasShutdown = false;

UCsManager_Gesture::UCsManager_Gesture(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

/*static*/ UCsManager_Gesture* UCsManager_Gesture::Get()
{
	if (s_bManagerHasShutdown)
		return nullptr;

	if (!s_managerGestureSingleton)
	{
		s_managerGestureSingleton = NewObject<UCsManager_Gesture>(GetTransientPackage(), UCsManager_Gesture::StaticClass(), TEXT("Manager_Gesture_Singleton"), RF_Transient | RF_Public);
		s_managerGestureSingleton->AddToRoot();
		s_managerGestureSingleton->Initialize();
	}
	return s_managerGestureSingleton;
}

/*static*/ void UCsManager_Gesture::Init()
{
	s_bManagerHasShutdown = false;
	UCsManager_Gesture::Get();
}

/*static*/ void UCsManager_Gesture::Shutdown()
{
	if (!s_managerGestureSingleton)
		return;

	s_managerGestureSingleton->CleanUp();
	s_managerGestureSingleton->RemoveFromRoot();
	s_managerGestureSingleton = nullptr;
	s_bManagerHasShutdown = true;
}

void UCsManager_Gesture::Initialize()
{
}

void UCsManager_Gesture::CleanUp()
{
	Clear();
}

void UCsManager_Gesture::Clear()
{
	const int32 Count = Gestures.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Gestures[I] && !Gestures[I]->IsPendingKill())
			Gestures[I]->ConditionalBeginDestroy();
	}
	Gestures.Reset();
}

void UCsManager_Gesture::SetCurrentWorld(UWorld* InWorld) { CurrentWorld = InWorld; }
UWorld* UCsManager_Gesture::GetCurrentWorld() { return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr; }

void UCsManager_Gesture::AddGesture(TSubclassOf<class UCsGesture> GestureClass)
{
	UCsGesture* Gesture = NewObject<UCsGesture>(this, GestureClass);
	Gesture->SetCurrentWorld(GetCurrentWorld());

	Gestures.Add(Gesture);
}

UCsGesture* UCsManager_Gesture::GetGesture(const TCsGestureType &GestureType)
{
	const int32 Count = Gestures.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Gestures[I]->Type == GestureType)
			return Gestures[I];
	}
	return nullptr;
}

UCsGesture* UCsManager_Gesture::GetGesture_Script(const uint8 &GestureType)
{
	return GetGesture((TCsGestureType)GestureType);
}

void UCsManager_Gesture::ProcessInputs(FCsInputFrame &InputFrame)
{
	const int32 Count = Gestures.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Gestures[I]->CanProcessInputs())
			Gestures[I]->ProcessInputs(InputFrame);
	}
}