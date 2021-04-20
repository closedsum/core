// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Library_Anim2D.h"

// Library
#include "Library/CsLibrary_Valid.h"

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
					bool FParams::IsValidChecked(const FString& Context) const
					{
					#if WITH_EDITOR
						// Check Context is Valid.
						checkf(ContextRoot, TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context);
					#endif // #if WITH_EDITOR
						// Check UpdateGroup is Valid.
						check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, UpdateGroup));
						// Check Owner is Valid.
						CS_IS_PTR_NULL_CHECKED(Owner)
						// Check MID is Valid.
						checkf(MID.IsValid() && MID.Get(), TEXT("%s: MID is NULL."));
						// Check Anim is Valid.
						check(Anim.IsValidChecked(Context));
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
					bool FParams::IsValidChecked(const FString& Context) const
					{
					#if WITH_EDITOR
						// Check Context is Valid.
						checkf(ContextRoot, TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context);
					#endif // #if WITH_EDITOR
						// Check UpdateGroup is Valid.
						check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, UpdateGroup));
						// Check Owner is Valid.
						CS_IS_PTR_NULL_CHECKED(Owner)
						// Check Component is Valid.
						checkf(Component.IsValid() && Component.Get(), TEXT("%s: Component is NULL."));
						// Check Anim is Valid.
						check(Anim.IsValidChecked(Context));
						return true;
					}
				}
			}
		}
	}
}