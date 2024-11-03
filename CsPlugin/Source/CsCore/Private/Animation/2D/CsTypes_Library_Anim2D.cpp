// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/2D/CsTypes_Library_Anim2D.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Material
#include "Materials/MaterialInstanceDynamic.h"
// Component
#include "Components/PrimitiveComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Library_Anim2D)

// FCsAnim2DTextureFlipbook_Params
#pragma region

namespace NCsAnim2DTextureFlipbook_Params
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		Params->ContextRoot = This->ContextRoot;
		Params->UpdateGroup = This->UpdateGroup;
		Params->Owner = This->Owner;
		Params->MID = This->MID;
		This->Anim.CopyToFlipbook(Params->GetAnimPtr());
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		Params->ContextRoot = This->ContextRoot;
		Params->UpdateGroup = This->UpdateGroup;
		Params->Owner = This->Owner;
		Params->MID = This->MID;
		This->Anim.CopyToFlipbookAsValue(Params->GetAnimPtr());
	}	
}

CS_DEFINE_STATIC_LOG_WARNING(FCsAnim2DTextureFlipbook_Params, FCsLog::Warning);

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

bool FCsAnim2DTextureFlipbook_Params::IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT) const
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
					CS_DEFINE_STATIC_LOG_WARNING(FParams, FCsLog::Warning);

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

					bool FParams::IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT) const
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