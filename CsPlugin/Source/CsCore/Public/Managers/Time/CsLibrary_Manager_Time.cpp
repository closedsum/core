// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsLibrary_Manager_Time.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

namespace NCsTime
{
	namespace NManager
	{
		void FLibrary::UpdateTimeAndCoroutineScheduler(UObject* ContextRoot, const FECsUpdateGroup& Group, const float& DeltaTime)
		{
			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			Manager_Time->Update(Group, DeltaTime);

			const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// Update CoroutineScheduler
			UCsCoroutineScheduler::Get(ContextRoot)->Update(Group, ScaledDeltaTime);
		}
	}
}