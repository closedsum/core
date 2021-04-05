// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Library_Anim2D.h"

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			namespace NPlay
			{
				namespace NParams
				{
					bool FParams::IsValidChecked(const FString& ContextName) const
					{
					#if WITH_EDITOR
						// Check Context is Valid.
						checkf(ContextRoot, TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *ContextName);
					#endif // #if WITH_EDITOR
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

		namespace NMaterial
		{
			namespace NPlay
			{
				namespace NParams
				{
					bool FParams::IsValidChecked(const FString& ContextName) const
					{
					#if WITH_EDITOR
						// Check Context is Valid.
						checkf(ContextRoot, TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *ContextName);
					#endif // #if WITH_EDITOR
						// Check UpdateGroup is Valid.
						checkf(EMCsUpdateGroup::Get().IsValidEnumChecked(ContextName, UpdateGroup), TEXT("%s: UpdateGroup: %s is NOT Valid."), *ContextName, UpdateGroup.ToChar());
						// Check Owner is Valid.
						checkf(Owner, TEXT("%s: Owner is NULL."));
						// Check Component is Valid.
						checkf(Component.IsValid() && Component.Get(), TEXT("%s: Component is NULL."));
						// Check Anim is Valid.
						check(Anim.IsValidChecked(ContextName));
						return true;
					}
				}
			}
		}
	}
}