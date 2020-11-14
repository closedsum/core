// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Library_Anim2D.h"

namespace NCsAnim
{
	namespace N2D
	{
		namespace NPlay
		{
			namespace NParams
			{
				bool FParams::IsValidChecked(const FString& ContextName) const
				{
					// Check Context is Valid.
					checkf(Context, TEXT("%s: Context for UCsCoroutineScheduler and UCsManager_Time is NULL."), *ContextName);
					// Check UpdateGroup is Valid.
					checkf(EMCsUpdateGroup::Get().IsValidEnumChecked(ContextName, UpdateGroup), TEXT("%s: UpdateGroup: %s is NOT Valid."), *ContextName, UpdateGroup.ToChar());
					// Check Owner is Valid.
					checkf(Owner, TEXT("%s: Owner is NULL."));
					// Check MID is Valid.
					checkf(MID.IsValid() && MID.Get(), TEXT("%s: MID is NULL."));
					// Check Anim is Valid.
					check(Anim.IsValidChecked(ContextName));
					return true;
				}
			}
		}
	}
}