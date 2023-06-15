// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/Parameter/Collection/Script/CsScriptLibrary_MPC.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsLog.h"
// Material
#include "Materials/Material.h"
#include "Materials/MaterialParameterCollection.h"

// Cached
#pragma region

namespace NCsScriptLibraryMPC
{
	namespace NCached
	{
		namespace Str
		{
			// Scalar
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetScalarParameterValue);
			// Vector
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetVectorParameterValue);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, SetVectorParameterValue_NoMaterialUpdate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, UpdateMaterial);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_MPC, UpdateMaterials);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_MPC::UCsScriptLibrary_MPC(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Scalar
#pragma region

bool UCsScriptLibrary_MPC::SetScalarParameterValue(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetScalarParameterValue : Context;

	void (*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_PTR_NULL(Collection)

	const int32 Count = Collection->ScalarParameters.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCollectionScalarParameter& Parameter = Collection->ScalarParameters[I];

		if (Parameter.ParameterName == ParamName)
		{
			Parameter.DefaultValue = Value;
		}
	}

#if WITH_EDITOR
	Collection->PreEditChange(nullptr);
	Collection->PostEditChange();
	Collection->MarkPackageDirty();
#endif // #if WITH_EDITOR
	return true;
}

#pragma endregion Scalar

// Vector
#pragma region

bool UCsScriptLibrary_MPC::SetVectorParameterValue(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetVectorParameterValue : Context;

	void (*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_PTR_NULL(Collection)

	bool UpdatedParameter = false;

	const int32 Count = Collection->VectorParameters.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCollectionVectorParameter& Parameter = Collection->VectorParameters[I];

		if (Parameter.ParameterName == ParamName)
		{
			if (Parameter.DefaultValue != Value)
			{
				Parameter.DefaultValue = Value;
				UpdatedParameter = true;
			}
		}
	}

	if (!UpdatedParameter)
		return false;

#if WITH_EDITOR
	Collection->PreEditChange(nullptr);
	Collection->PostEditChange();
	Collection->MarkPackageDirty();

	// Create a material update context so we can safely update materials using this parameter collection.
	{
		FMaterialUpdateContext UpdateContext;

		// Go through all materials in memory and recompile them if they use this material parameter collection
		for (TObjectIterator<UMaterial> It; It; ++It)
		{
			UMaterial* CurrentMaterial = *It;

			bool bRecompile = false;

			// Preview materials often use expressions for rendering that are not in their Expressions array, 
			// And therefore their MaterialParameterCollectionInfos are not up to date.
			if (CurrentMaterial->bIsPreviewMaterial || CurrentMaterial->bIsFunctionPreviewMaterial)
			{
				bRecompile = true;
			}
			else
			{
				for (int32 FunctionIndex = 0; FunctionIndex < CurrentMaterial->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
				{
					if (CurrentMaterial->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
					{
						bRecompile = true;
						break;
					}
				}
			}

			if (bRecompile)
			{
				UpdateContext.AddMaterial(CurrentMaterial);

				// Propagate the change to this material
				CurrentMaterial->PreEditChange(nullptr);
				CurrentMaterial->PostEditChange();
				CurrentMaterial->MarkPackageDirty();
			}
		}
	}
#endif // #if WITH_EDITOR

	// Recreate all uniform buffers based off of this collection
	for (TObjectIterator<UWorld> It; It; ++It)
	{
		UWorld* CurrentWorld = *It;
		CurrentWorld->UpdateParameterCollectionInstances(true, true);
	}
	return true;
}

bool UCsScriptLibrary_MPC::SetVectorParameterValue_NoMaterialsUpdate(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetVectorParameterValue_NoMaterialUpdate : Context;

	void (*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_PTR_NULL(Collection)

	bool UpdatedParameter = false;

	const int32 Count = Collection->VectorParameters.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCollectionVectorParameter& Parameter = Collection->VectorParameters[I];

		if (Parameter.ParameterName == ParamName)
		{
			if (Parameter.DefaultValue != Value)
			{
				Parameter.DefaultValue = Value;
				UpdatedParameter = true;
			}
		}
	}

	if (!UpdatedParameter)
		return false;

#if WITH_EDITOR
	Collection->PreEditChange(nullptr);
	Collection->PostEditChange();
	Collection->MarkPackageDirty();
#endif // #if WITH_EDITOR

	// Recreate all uniform buffers based off of this collection
	for (TObjectIterator<UWorld> It; It; ++It)
	{
		UWorld* CurrentWorld = *It;
		CurrentWorld->UpdateParameterCollectionInstances(true, false);
	}
	return true;
}

#pragma endregion Vector

bool UCsScriptLibrary_MPC::UpdateMaterial(const FString& Context, UMaterialParameterCollection* Collection, UMaterial* Material)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::UpdateMaterial : Context;

	void (*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_PTR_NULL(Collection)
	CS_IS_PTR_NULL(Material)

#if WITH_EDITOR
	// Create a material update context so we can safely update materials using this parameter collection.
	{
		FMaterialUpdateContext UpdateContext;

		bool bRecompile = false;

		// Preview materials often use expressions for rendering that are not in their Expressions array, 
		// And therefore their MaterialParameterCollectionInfos are not up to date.
		if (Material->bIsPreviewMaterial || Material->bIsFunctionPreviewMaterial)
		{
			bRecompile = true;
		}
		else
		{
			for (int32 FunctionIndex = 0; FunctionIndex < Material->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
			{
				if (Material->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
				{
					bRecompile = true;
				}
			}
		}

		if (bRecompile)
		{
			UpdateContext.AddMaterial(Material);

			// Propagate the change to this material
			Material->PreEditChange(nullptr);
			Material->PostEditChange();
			Material->MarkPackageDirty();
		}
	}
#endif // #if WITH_EDITOR
	return true;
}

bool UCsScriptLibrary_MPC::UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, TArray<UMaterial*>& Materials)
{
	using namespace NCsScriptLibraryMPC::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::UpdateMaterials : Context;

	void (*Log)(const FString&) = &FCsLog::Warning;

	CS_IS_PTR_NULL(Collection)
	CS_IS_TARRAY_ANY_NULL(Materials, UMaterial)

#if WITH_EDITOR
	// Create a material update context so we can safely update materials using this parameter collection.
	{
		FMaterialUpdateContext UpdateContext;

		bool bRecompile = false;

		for (UMaterial* Material : Materials)
		{
			// Preview materials often use expressions for rendering that are not in their Expressions array, 
			// And therefore their MaterialParameterCollectionInfos are not up to date.
			if (Material->bIsPreviewMaterial || Material->bIsFunctionPreviewMaterial)
			{
				bRecompile = true;
			}
			else
			{
				for (int32 FunctionIndex = 0; FunctionIndex < Material->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
				{
					if (Material->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
					{
						bRecompile = true;
					}
				}
			}

			if (bRecompile)
			{
				UpdateContext.AddMaterial(Material);

				// Propagate the change to this material
				Material->PreEditChange(nullptr);
				Material->PostEditChange();
				Material->MarkPackageDirty();
			}
		}
	}
#endif // #if WITH_EDITOR
	return true;
}