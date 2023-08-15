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

#if WITH_EDITOR
// Material
#include "Material/Parameter/Collection/CsGetManagerMPCProxy.h"
#include "Material/Parameter/Collection/CsManager_MPC_Proxy.h"
// Engine
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

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

			FMaterialParameterCollectionInstanceResource* FLibrary::GetDefaultResourceChecked(const FString& Context, UMaterialParameterCollection* Collection)
			{
				CS_IS_PENDING_KILL_CHECKED(Collection)

				// A bit of a hack to get access to Collection->DefaultResource, which is protected.
			 
				// Get pointer to start of first Member VectorParameters
				TArray<FCollectionVectorParameter>& VectorParameters = Collection->VectorParameters;

				TArray<FCollectionVectorParameter>* Property = ((TArray<FCollectionVectorParameter>*)(&VectorParameters));
				char* Base									 = (char*)Property;

				// Offset by TArray<FCollectionVectorParameter>	- VectorParameters
				size_t Offset = sizeof(TArray<FCollectionVectorParameter>);
				// Offset by FThreadSafeBool					- ReleasedByRT
				//Offset += sizeof(FThreadSafeBool);
				Offset += 8; // Hack: seems the offset is different

				FMaterialParameterCollectionInstanceResource* Resource = *((FMaterialParameterCollectionInstanceResource**)(Base + Offset));

				CS_IS_PTR_NULL_CHECKED(Resource)
				return Resource;
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

			FUniformBufferLayoutRHIRef* FLibrary::GetUniformBufferLayoutPtrChecked(const FString& Context, FMaterialParameterCollectionInstanceResource* Resource)
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

				return (FUniformBufferLayoutRHIRef*)(Base + Offset);
			}

		#if WITH_EDITOR

			bool FLibrary::Editor_SetSafeScalarParameter(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Collection)
				CS_IS_NAME_NONE(ParamName)

				bool UpdatedParameter = false;

				const int32 Count = Collection->ScalarParameters.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					FCollectionScalarParameter& Parameter = Collection->ScalarParameters[I];

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

				Collection->PreEditChange(nullptr);
				Collection->PostEditChange();
				Collection->MarkPackageDirty();

				// Recreate all uniform buffers based off of this collection
				for (TObjectIterator<UWorld> It; It; ++It)
				{
					UWorld* CurrentWorld = *It;
					CurrentWorld->UpdateParameterCollectionInstances(true, false);
				}

				ICsGetManagerMPCProxy* GetManagerMPCProxy = CS_INTERFACE_CAST(GEngine, UEngine, ICsGetManagerMPCProxy);

				if (GetManagerMPCProxy)
				{
					typedef NCsMaterial::NParameter::NCollection::NProxy::FManager MPCProxyManagerType;
					typedef NCsMaterial::NParameter::NCollection::FProxy ProxyType;

					MPCProxyManagerType* Manager_MPC_Proxy = GetManagerMPCProxy->GetManagerMPCProxy();

					ProxyType& Proxy = Manager_MPC_Proxy->AllocateResourceRef();

					Proxy.Init(Collection);
					Proxy.GameThread_UpdateState(false);
					return true;
				}
				return false;
			}

			bool FLibrary::Editor_SetSafeScalarParameter_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const float& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Collection)
				CS_IS_NAME_NONE(ParamName)

				bool UpdatedParameter = false;

				const int32 Count = Collection->ScalarParameters.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					FCollectionScalarParameter& Parameter = Collection->ScalarParameters[I];

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
							check(0);
							/*
							for (int32 FunctionIndex = 0; FunctionIndex < CurrentMaterial->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
							{
								if (CurrentMaterial->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
								{
									bRecompile = true;
									break;
								}
							}
							*/
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

				Collection->PreEditChange(nullptr);
				Collection->PostEditChange();
				Collection->MarkPackageDirty();

				// Recreate all uniform buffers based off of this collection
				for (TObjectIterator<UWorld> It; It; ++It)
				{
					UWorld* CurrentWorld = *It;
					CurrentWorld->UpdateParameterCollectionInstances(true, false);
				}

				ICsGetManagerMPCProxy* GetManagerMPCProxy = CS_INTERFACE_CAST(GEngine, UEngine, ICsGetManagerMPCProxy);

				if (GetManagerMPCProxy)
				{
					typedef NCsMaterial::NParameter::NCollection::NProxy::FManager MPCProxyManagerType;
					typedef NCsMaterial::NParameter::NCollection::FProxy ProxyType;

					MPCProxyManagerType* Manager_MPC_Proxy = GetManagerMPCProxy->GetManagerMPCProxy();

					ProxyType& Proxy = Manager_MPC_Proxy->AllocateResourceRef();

					Proxy.Init(Collection);
					Proxy.GameThread_UpdateState(false);
					return true;
				}
				return false;
			}

			bool FLibrary::Editor_SetSafeVectorParameter(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Collection)
				CS_IS_NAME_NONE(ParamName)

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

				Collection->PreEditChange(nullptr);
				Collection->PostEditChange();
				Collection->MarkPackageDirty();

				// Recreate all uniform buffers based off of this collection
				for (TObjectIterator<UWorld> It; It; ++It)
				{
					UWorld* CurrentWorld = *It;
					CurrentWorld->UpdateParameterCollectionInstances(true, false);
				}

				ICsGetManagerMPCProxy* GetManagerMPCProxy = CS_INTERFACE_CAST(GEngine, UEngine, ICsGetManagerMPCProxy);

				if (GetManagerMPCProxy)
				{
					typedef NCsMaterial::NParameter::NCollection::NProxy::FManager MPCProxyManagerType;
					typedef NCsMaterial::NParameter::NCollection::FProxy ProxyType;

					MPCProxyManagerType* Manager_MPC_Proxy = GetManagerMPCProxy->GetManagerMPCProxy();

					ProxyType& Proxy = Manager_MPC_Proxy->AllocateResourceRef();

					Proxy.Init(Collection);
					Proxy.GameThread_UpdateState(false);
					return true;
				}
				return false;
			}

			bool FLibrary::Editor_SetSafeVectorParameter_UpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Collection)
				CS_IS_NAME_NONE(ParamName)

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
							check(0);
							/*
							for (int32 FunctionIndex = 0; FunctionIndex < CurrentMaterial->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
							{
								if (CurrentMaterial->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
								{
									bRecompile = true;
									break;
								}
							}
							*/
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

				Collection->PreEditChange(nullptr);
				Collection->PostEditChange();
				Collection->MarkPackageDirty();

				// Recreate all uniform buffers based off of this collection
				for (TObjectIterator<UWorld> It; It; ++It)
				{
					UWorld* CurrentWorld = *It;
					CurrentWorld->UpdateParameterCollectionInstances(true, false);
				}

				ICsGetManagerMPCProxy* GetManagerMPCProxy = CS_INTERFACE_CAST(GEngine, UEngine, ICsGetManagerMPCProxy);

				if (GetManagerMPCProxy)
				{
					typedef NCsMaterial::NParameter::NCollection::NProxy::FManager MPCProxyManagerType;
					typedef NCsMaterial::NParameter::NCollection::FProxy ProxyType;

					MPCProxyManagerType* Manager_MPC_Proxy = GetManagerMPCProxy->GetManagerMPCProxy();

					ProxyType& Proxy = Manager_MPC_Proxy->AllocateResourceRef();

					Proxy.Init(Collection);
					Proxy.GameThread_UpdateState(false);
					return true;
				}
				return false;
			}

			bool FLibrary::Editor_SafeUpdateMaterial(const FString& Context, UMaterialParameterCollection* Collection, UMaterial* Material, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Collection)
				CS_IS_PTR_NULL(Material)

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
						check(0);
						/*
						for (int32 FunctionIndex = 0; FunctionIndex < Material->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
						{
							if (Material->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
							{
								bRecompile = true;
							}
						}
						*/
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
				return true;
			}

			bool FLibrary::Editor_SafeUpdateMaterials(const FString& Context, UMaterialParameterCollection* Collection, TArray<UMaterial*>& Materials, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Collection)
				CS_IS_TARRAY_ANY_NULL(Materials, UMaterial)

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
							check(0);
							/*
							for (int32 FunctionIndex = 0; FunctionIndex < Material->GetCachedExpressionData().ParameterCollectionInfos.Num() && !bRecompile; FunctionIndex++)
							{
								if (Material->GetCachedExpressionData().ParameterCollectionInfos[FunctionIndex].ParameterCollection == Collection)
								{
									bRecompile = true;
								}
							}
							*/
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
				return true;
			}

		#endif // #if WITH_EDITOR
		}
	}
}