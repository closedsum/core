// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Library_Anim2D.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Material
#include "Materials/MaterialInstanceDynamic.h"

// FCsAnim2DTextureFlipbook_Params
#pragma region

#define ParamsType NCsAnim::N2D::NTexture::NPlay::NParams::FParams

void FCsAnim2DTextureFlipbook_Params::CopyToParams(ParamsType* Params)
{
	Params->ContextRoot = ContextRoot;
	Params->UpdateGroup = UpdateGroup;
	Params->Owner = Owner;
	Params->MID = MID;
	Anim.CopyToFlipbook(Params->GetAnimPtr());
}

void FCsAnim2DTextureFlipbook_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->ContextRoot = ContextRoot;
	Params->UpdateGroup = UpdateGroup;
	Params->Owner = Owner;
	Params->MID = MID;
	Anim.CopyToFlipbookAsValue(Params->GetAnimPtr());
}

#undef ParamsType

bool FCsAnim2DTextureFlipbook_Params::IsValidChecked(const FString& Context) const
{
#if WITH_EDITOR
	// Check Context is Valid.
	checkf(ContextRoot, TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context);
#endif // #if WITH_EDITOR
	// Check UpdateGroup is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup)
	// Check Owner is Valid.
	CS_IS_PTR_NULL_CHECKED(Owner)
	// Check Component is Valid.
	CS_IS_PTR_NULL_CHECKED(MID)
	// Check Anim is Valid.
	check(Anim.IsValidChecked(Context));
	return true;
}

bool FCsAnim2DTextureFlipbook_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
#if WITH_EDITOR
	// Check Context is Valid.
	if (!ContextRoot)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context));
		return false;
	}
#endif // #if WITH_EDITOR
	// Check UpdateGroup is Valid.
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, UpdateGroup)
	// Check Owner is Valid.
	CS_IS_PTR_NULL(Owner)
	// Check MID is Valid.
	CS_IS_PTR_NULL(MID)
	// Check Anim is Valid.
	if (!Anim.IsValid(Context, Log))
		return false;
	return true;
}

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
						CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup)
						// Check Owner is Valid.
						CS_IS_PTR_NULL_CHECKED(Owner)
						// Check MID is Valid.
						CS_IS_WEAK_OBJ_PTR_NULL_CHECKED(MID, UMaterialInstanceDynamic)
						// Check Anim is Valid.
						check(Anim.IsValidChecked(Context));
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
					{
					#if WITH_EDITOR
						// Check Context is Valid.
						if (!ContextRoot)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context));
							return false;
						}
					#endif // #if WITH_EDITOR
						// Check UpdateGroup is Valid.
						CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, UpdateGroup)
						// Check Owner is Valid.
						CS_IS_PTR_NULL(Owner)
						// Check MID is Valid.
						CS_IS_WEAK_OBJ_PTR_NULL(MID, UMaterialInstanceDynamic)
						// Check Anim is Valid.
						if (!Anim.IsValid(Context, Log))
							return false;
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DTextureFlipbook_Params

// FCsAnim2DMaterialFlipbook_Params
#pragma region

#define ParamsType NCsAnim::N2D::NMaterial::NPlay::NParams::FParams

void FCsAnim2DMaterialFlipbook_Params::CopyToParams(ParamsType* Params)
{
	Params->ContextRoot = ContextRoot;
	Params->UpdateGroup = UpdateGroup;
	Params->Owner = Owner;
	Params->Component = Component;
	Anim.CopyToFlipbook(Params->GetAnimPtr());
}

void FCsAnim2DMaterialFlipbook_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->ContextRoot = ContextRoot;
	Params->UpdateGroup = UpdateGroup;
	Params->Owner = Owner;
	Params->Component = Component;
	Anim.CopyToFlipbookAsValue(Params->GetAnimPtr());
}

#undef ParamsType

bool FCsAnim2DMaterialFlipbook_Params::IsValidChecked(const FString& Context) const
{
#if WITH_EDITOR
	// Check Context is Valid.
	checkf(ContextRoot, TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context);
#endif // #if WITH_EDITOR
	// Check UpdateGroup is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup)
	// Check Owner is Valid.
	CS_IS_PTR_NULL_CHECKED(Owner)
	// Check Component is Valid.
	CS_IS_PTR_NULL_CHECKED(Component)
	// Check Anim is Valid.
	check(Anim.IsValidChecked(Context));
	return true;
}

bool FCsAnim2DMaterialFlipbook_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
#if WITH_EDITOR
	// Check Context is Valid.
	if (!ContextRoot)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context));
		return false;
	}
#endif // #if WITH_EDITOR
	// Check UpdateGroup is Valid.
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, UpdateGroup)
	// Check Owner is Valid.
	CS_IS_PTR_NULL(Owner)
	// Check MID is Valid.
	CS_IS_PTR_NULL(Component)
	// Check Anim is Valid.
	if (!Anim.IsValid(Context, Log))
		return false;
	return true;
}

namespace NCsAnim
{
	namespace N2D
	{
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
						CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup)
						// Check Owner is Valid.
						CS_IS_PTR_NULL_CHECKED(Owner)
						// Check Component is Valid.
						CS_IS_WEAK_OBJ_PTR_NULL_CHECKED(Component, UPrimitiveComponent)
						// Check Anim is Valid.
						check(Anim.IsValidChecked(Context));
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
					{
					#if WITH_EDITOR
						// Check Context is Valid.
						if (!ContextRoot)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ContextRoot for UCsCoroutineScheduler and UCsManager_Time is NULL."), *Context));
							return false;
						}
					#endif // #if WITH_EDITOR
						// Check UpdateGroup is Valid.
						CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, UpdateGroup)
						// Check Owner is Valid.
						CS_IS_PTR_NULL(Owner)
						// Check MID is Valid.
						CS_IS_WEAK_OBJ_PTR_NULL(Component, UPrimitiveComponent)
						// Check Anim is Valid.
						if (!Anim.IsValid(Context, Log))
							return false;
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DMaterialFlipbook_Params