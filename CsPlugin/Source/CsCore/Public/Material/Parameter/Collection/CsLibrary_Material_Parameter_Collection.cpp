// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/Parameter/Collection/CsLibrary_Material_Parameter_Collection.h"

// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Material
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
// World
#include "Engine/World.h"

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			UMaterialParameterCollectionInstance* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, UMaterialParameterCollection* Collection)
			{
				typedef NCsWorld::FLibrary WorldLibrary;

				UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

				CS_IS_PENDING_KILL_CHECKED(Collection);

				UMaterialParameterCollectionInstance* Instance = World->GetParameterCollectionInstance(Collection);
				return Instance;
			}

			TMap<FName, float>* FLibrary::GetScalarParameterValuesPtrChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection)
			{
				CS_IS_PENDING_KILL_CHECKED(Collection)

				// A bit of a hack to get access to Collection->ScalarParameterValues, which is protected.
				// Access is needed to more efficiently update ScalarParameterValues
			 
				// Get pointer to start of first Member bLoggedMissingParameterWarning
				bool& bLoggedMissingParameterWarning = Collection->bLoggedMissingParameterWarning;

				bool* Property = ((bool*)(&bLoggedMissingParameterWarning));
				char* Base		= (char*)Property;

				// Offset by bool							- bLoggedMissingParameterWarning
				//size_t Offset = sizeof(bool);
				size_t Offset = 8; // Hack: seems the offset is different
				// Offset by UMaterialParameterCollection*	- Collection
				Offset += sizeof(UMaterialParameterCollection*);
				// Offset by TWeakObjectPtr<UWorld>			- World
				Offset += sizeof(TWeakObjectPtr<UWorld>);

				return (TMap<FName, float>*)(Base + Offset);
			}

			TMap<FName, float>& FLibrary::GetScalarParameterValuesChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection)
			{
				return *GetScalarParameterValuesPtrChecked(Context, Collection);
			}

			TMap<FName, FLinearColor>* FLibrary::GetVectorParameterValuesPtrChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection)
			{
				CS_IS_PENDING_KILL_CHECKED(Collection)

				// A bit of a hack to get access to Collection->VectorParameterValues, which is protected.
				// Access is needed to more efficiently update VectorParameterValues
			 
				// Get pointer to start of first Member bLoggedMissingParameterWarning
				bool& bLoggedMissingParameterWarning = Collection->bLoggedMissingParameterWarning;

				bool* Property = ((bool*)(&bLoggedMissingParameterWarning));
				char* Base		= (char*)Property;

				// Offset by bool							- bLoggedMissingParameterWarning
				//size_t Offset = sizeof(bool);
				size_t Offset = 8; // Hack: seems the offset is different
				// Offset by UMaterialParameterCollection*	- Collection
				Offset += sizeof(UMaterialParameterCollection*);
				// Offset by TWeakObjectPtr<UWorld>			- World
				Offset += sizeof(TWeakObjectPtr<UWorld>);
				// Offset by TMap<FName, float>				= ScalarParameterValues
				Offset += sizeof(TMap<FName, float>);

				return (TMap<FName, FLinearColor>*)(Base + Offset);
			}

			TMap<FName, FLinearColor>& FLibrary::GetVectorParameterValuesChecked(const FString& Context, UMaterialParameterCollectionInstance* Collection)
			{
				return *GetVectorParameterValuesPtrChecked(Context, Collection);
			}

			FGuid* FLibrary::GetIdPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource)
			{
				CS_IS_PTR_NULL_CHECKED(Resource)

				// A bit of a hack to get access to Resource->Id, which is protected.
				// Access is needed to more efficiently update the UniformBuffer

				// Get pointer to start of struct
				FGuid* Id = (FGuid*)(Resource);

				return Id;
			}

			FName* FLibrary::GetOwnerNamePtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource)
			{
				CS_IS_PTR_NULL_CHECKED(Resource)

				// A bit of a hack to get access to Resource->OwnerName, which is protected.
				// Access is needed to more efficiently update the UniformBuffer
				
				// Get pointer to start of struct
				FGuid* Id  = (FGuid*)(Resource);
				char* Base = (char*)Id;

				// Offset by Property
				size_t Offset = sizeof(FGuid);

				return (FName*)(Base + Offset);
			}

			FUniformBufferRHIRef* FLibrary::GetUniformBufferPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource)
			{
				CS_IS_PTR_NULL_CHECKED(Resource)

				// A bit of a hack to get access to Resource->UniformBuffer, which is protected.
				// Access is needed to more efficiently update the UniformBuffer
				
				// Get pointer to start of struct
				FGuid* Id  = (FGuid*)(Resource);
				char* Base = (char*)Id;

				// Offset by FGuid	- Id
				size_t Offset = sizeof(FGuid);
				// Offset by FName	- OwnerName
				//Offset += sizeof(FName);
				// Hack: sizeof doesn't seem to give the correct the offset
			#if WITH_CASE_PRESERVING_NAME
				Offset += 16; // FName size changes with editor data
			#else
				Offset += 8;
			#endif // #if WITH_CASE_PRESERVING_NAME

				return (FUniformBufferRHIRef*)(Base + Offset);
			}

			FRHIUniformBufferLayout* FLibrary::GetUniformBufferLayoutPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource)
			{
				CS_IS_PTR_NULL_CHECKED(Resource)

				// A bit of a hack to get access to Resource->UniformBufferLayout, which is protected.
				// Access is needed to more efficiently update the UniformBuffer
				
				// Get pointer to start of struct
				FGuid* Id  = (FGuid*)(Resource);
				char* Base = (char*)Id;

				// Offset by FGuid					- Id
				size_t Offset = sizeof(FGuid);
				// Offset by FName					- OwnerName
				//Offset += sizeof(FName);
				// Hack: sizeof doesn't seem to give the correct the offset
			#if WITH_CASE_PRESERVING_NAME
				Offset += 16; // FName size changes with editor data
			#else
				Offset += 8;
			#endif // #if WITH_CASE_PRESERVING_NAME
				// Offset by FUniformBufferRHIRef	- UniformBuffer
				Offset += sizeof(FUniformBufferRHIRef);

				return (FRHIUniformBufferLayout*)(Base + Offset);
			}
		}
	}
}