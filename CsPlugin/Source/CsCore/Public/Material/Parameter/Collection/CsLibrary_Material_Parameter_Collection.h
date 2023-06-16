// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UMaterialParameterCollection;
class UMaterialParameterCollectionInstance;
class FMaterialParameterCollectionInstanceResource;

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

				static FRHIUniformBufferLayout* GetUniformBufferLayoutPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource);
			};
		}
	}
}