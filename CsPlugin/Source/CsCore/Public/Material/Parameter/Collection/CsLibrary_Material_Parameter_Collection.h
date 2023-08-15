// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UMaterialParameterCollection;
class UMaterialParameterCollectionInstance;
class FMaterialParameterCollectionInstanceResource;
class UMaterial;

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			/**
			* Library of functions related to Material Parameter Collection
			*/
			struct CSCORE_API FLibrary final
			{
			public:

				static UMaterialParameterCollectionInstance* GetChecked(const FString& Context, const UObject* WorldContext, UMaterialParameterCollection* Collection);

				static FMaterialParameterCollectionInstanceResource* GetDefaultResourceChecked(const FString& Context, UMaterialParameterCollection* Collection);

				static TMap<FName, float>* GetScalarParameterValuesPtrChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection);

				static TMap<FName, float>& GetScalarParameterValuesChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection);

				static TMap<FName, FLinearColor>* GetVectorParameterValuesPtrChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection);

				static TMap<FName, FLinearColor>& GetVectorParameterValuesChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection);

				static FGuid* GetIdPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource);

				static FName* GetOwnerNamePtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource);

				static FUniformBufferRHIRef* GetUniformBufferPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource);

				static FUniformBufferLayoutRHIRef* GetUniformBufferLayoutPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource);

			#if WITH_EDITOR

				/**
				* Safely set the Scalar Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection).
				*  NOTE: Editor ONLY
				* 
				* @param Context		The calling context.
				* @param Collection		Material Parameter Collection.
				* @param ParamName		Name of the Scalar Parameter Value to set.
				* @param Value			The value to set.
				* @param Log			(optional)
				* return				Whether the parameter was successful set or not.
				*/
				static bool Editor_SetSafeScalarParameter(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely set the Scalar Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection) and
				* Force a recompile of any materials references the Collection.
				*  NOTE: Editor ONLY
				*
				* @param Context		The calling context.
				* @param Collection		Material Parameter Collection.
				* @param ParamName		Name of the Scalar Parameter Value to set.
				* @param Value			The value to set.
				* @param Log			(optional)
				* return				Whether the parameter was successful set or not.
				*/
				static bool Editor_SetSafeScalarParameter_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely set the Vector Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection).
				*  NOTE: Editor ONLY
				*
				* @param Context		The calling context.
				* @param Collection		Material Parameter Collection.
				* @param ParamName		Name of the Vector Parameter Value to set.
				* @param Value			The value to set.
				* @param Log			(optional)
				* return				Whether the parameter was successful set or not.
				*/
				static bool Editor_SetSafeVectorParameter(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely set the Vector Parameter Value with name: ParamName with value Value on the Collection (Material Parameter Collection) and
				* Force a recompile of any materials references the Collection.
				*  NOTE: Editor ONLY
				*
				* @param Context		The calling context.
				* @param Collection		Material Parameter Collection.
				* @param ParamName		Name of the Vector Parameter Value to set.
				* @param Value			The value to set.
				* @param Log			(optional)
				* return				Whether the parameter was successful set or not.
				*/
				static bool Editor_SetSafeVectorParameter_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* NOTE: Editor ONLY
				*/
				static bool Editor_SafeUpdateMaterial(const FString& Context, UMaterialParameterCollection* Collection, UMaterial* Material, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* NOTE: Editor ONLY
				*/
				static bool Editor_SafeUpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, TArray<UMaterial*>& Materials, void(*Log)(const FString&) = &FCsLog::Warning);

			#endif // #if WITH_EDITOR
			};
		}
	}
}