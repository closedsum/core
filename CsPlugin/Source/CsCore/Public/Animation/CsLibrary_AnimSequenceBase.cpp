// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsLibrary_AnimSequenceBase.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Blueprint
#include "Animation/AnimSequenceBase.h"

namespace NCsAnimSequenceBase
{
	namespace NNotify
	{
		float FLibrary::GetTimeChecked(const FString& Context, const UAnimSequenceBase* Anim, const FName& NotifyName)
		{
			CS_IS_PTR_NULL_CHECKED(Anim)
			CS_IS_NAME_NONE_CHECKED(NotifyName)
			CS_IS_TARRAY_EMPTY_CHECKED(Anim->Notifies, FAnimNotifyEvent)

			for (const FAnimNotifyEvent& Event : Anim->Notifies)
			{
				if (Event.NotifyName == NotifyName)
				{
					return Event.GetTime();
				}
			}
			checkf(0, TEXT("%s: Failed to find Notify with Name: %s in Anim: %s."), *Context, *(NotifyName.ToString()), *(Anim->GetName()));
			return 0.0f;
		}

		float FLibrary::GetRemainingTimeAfterChecked(const FString& Context, UAnimSequenceBase* Anim, const FName& NotifyName)
		{
			const float Time = GetTimeChecked(Context, Anim, NotifyName);

			return Anim->GetPlayLength() - Time;
		}

		void FLibrary::GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& Time, TArray<FName>& OutNames)
		{
			CS_IS_PTR_NULL_CHECKED(Anim)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)

			for (const FAnimNotifyEvent& Event : Anim->Notifies)
			{
				if (Event.GetTime() == Time)
					OutNames.Add(Event.NotifyName);
			}
		}

		void FLibrary::GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& Time, TArray<FName, TFixedAllocator<8>>& OutNames)
		{
			CS_IS_PTR_NULL_CHECKED(Anim)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Time, 0.0f)

			for (const FAnimNotifyEvent& Event : Anim->Notifies)
			{
				if (Event.GetTime() == Time)
					OutNames.Add(Event.NotifyName);
			}
		}

		void FLibrary::GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& MinTime, const float& MaxTime, TArray<FName>& OutNames)
		{
			CS_IS_PTR_NULL_CHECKED(Anim)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinTime, 0.0f)
			CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MinTime, MaxTime)

			for (const FAnimNotifyEvent& Event : Anim->Notifies)
			{
				if ((Event.GetTime() >= MinTime) &
					(Event.GetTime() <= MaxTime))
				{
					OutNames.Add(Event.NotifyName);
				}
			}
		}

		void FLibrary::GetNamesChecked(const FString& Context, UAnimSequenceBase* Anim, const float& MinTime, const float& MaxTime, TArray<FName, TFixedAllocator<8>>& OutNames)
		{
			CS_IS_PTR_NULL_CHECKED(Anim)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(MinTime, 0.0f)
			CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(MinTime, MaxTime)

			for (const FAnimNotifyEvent& Event : Anim->Notifies)
			{
				if ((Event.GetTime() >= MinTime) &
					(Event.GetTime() <= MaxTime))
				{
					OutNames.Add(Event.NotifyName);
				}
			}
		}
	}
}