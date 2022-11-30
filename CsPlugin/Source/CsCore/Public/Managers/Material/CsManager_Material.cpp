// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Material/CsManager_Material.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Material
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Private/Materials/MaterialInstanceSupport.h" // TODO: NOTE: Test Batch Updating Material's Params
// Render
#include "Misc/App.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Material/CsGetManagerMaterial.h"
#endif // #if WITH_EDITOR

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NSet
		{
			namespace NScalars
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NSet::FScalars, Init);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NSet::FScalars, Set);
					}
				}
			}

			void FScalars::Init(const TArray<FName>& InNames)
			{
				using namespace NCsMaterial::NParameter::NSet::NScalars::NCached;

				const FString& Context = Str::Init;

				CS_IS_TARRAY_EMPTY_CHECKED(InNames, FName)
				CS_IS_TARRAY_ANY_NONE_CHECKED(InNames)

				const int32 Count = InNames.Num();

				Values.Reset(Count);

				for (int32 I = 0; I < Count; ++I)
				{
					Values.Add(nullptr);
					IndexByNameMap.Add(InNames[I], I);
				}

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::PopulateScalarParameterValuesChecked(Context, Outer->MID, InNames, Values);

				for (int32 I = 0; I < Count; ++I)
				{
					ValueByNameMap.Add(InNames[I], Values[I]);
				}
			}

			void FScalars::Set(const FName& Name, const float& Value, const bool& ForceDirty /*=false*/)
			{
				using namespace NCsMaterial::NParameter::NSet::NScalars::NCached;

				const FString& Context = Str::Set;

				CS_IS_NAME_NONE_CHECKED(Name)

				const int32 Index = IndexByNameMap[Name];

				checkf(Name == Values[Index]->ParameterInfo.Name, TEXT("%s: Mismatch between Name: %s and Values[%d].ParameterInfo.Name: %s."), *Context, *(Name.ToString()), Index, *(Values[Index]->ParameterInfo.Name.ToString()));

				if (ForceDirty || 
					Values[Index]->ParameterValue != Value)
				{
					Values[Index]->ParameterValue = Value;
					DirtySet.Add(Index);
					Outer->MarkDirty();
				}
			}

			namespace NVectors
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NSet::FVectors, Init);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NSet::FVectors, Set);
					}
				}
			}

			void FVectors::Init(const TArray<FName>& InNames)
			{
				using namespace NCsMaterial::NParameter::NSet::NVectors::NCached;

				const FString& Context = Str::Init;

				CS_IS_TARRAY_EMPTY_CHECKED(InNames, FName)
				CS_IS_TARRAY_ANY_NONE_CHECKED(InNames)

				const int32 Count = InNames.Num();

				Values.Reset(Count);

				for (int32 I = 0; I < Count; ++I)
				{
					Values.Add(nullptr);
					IndexByNameMap.Add(InNames[I], I);
				}

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::PopulateVectorParameterValuesChecked(Context, Outer->MID, InNames, Values);

				for (int32 I = 0; I < Count; ++I)
				{
					ValueByNameMap.Add(InNames[I], Values[I]);
				}
			}

			void FVectors::Set(const FName& Name, const FLinearColor& Value, const bool& ForceDirty /*=false*/)
			{
				using namespace NCsMaterial::NParameter::NSet::NVectors::NCached;

				const FString& Context = Str::Set;

				CS_IS_NAME_NONE_CHECKED(Name)

				const int32 Index = IndexByNameMap[Name];

				checkf(Name == Values[Index]->ParameterInfo.Name, TEXT("%s: Mismatch between Name: %s and Values[%d].ParameterInfo.Name: %s."), *Context, *(Name.ToString()), Index, *(Values[Index]->ParameterInfo.Name.ToString()));

				if (ForceDirty || 
					Values[Index]->ParameterValue != Value)
				{
					Values[Index]->ParameterValue = Value;
					DirtySet.Add(Index);
					Outer->MarkDirty();
				}
			}

			namespace NBatch
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NParameter::NSet::FBatch, Init);
					}
				}
			}

			void FBatch::Init(UMaterialInstanceDynamic* InMID)
			{
				using namespace NCsMaterial::NParameter::NSet::NBatch::NCached;

				const FString& Context = Str::Init;

				CS_IS_PTR_NULL_CHECKED(InMID)

				MID		 = InMID;
				Resource = MID->Resource;

				CS_IS_PTR_NULL_CHECKED(Resource)
			}

			void FBatch::MarkDirty()
			{
				Outer->DirtySet.Add(ID);
			}

			void FBatch::GameThread_Update()
			{
				if (IsDirty() &&
					FApp::CanEverRender())
				{
					FBatch* Batch = this;

					Batch->bProcessing = false;
					Batch->Prepare();
					Batch->bProcessing = false;

					// Scalars
					{
						TArray<FScalarParameterValue*>& Values = Scalars.Values;
						TArray<int32>& Dirties				   = Scalars.Dirties;

						int32 DirtyCount = Dirties.Num();

						for (int32 J = DirtyCount - 1; J >= 0; --J)
						{
							const int32& Index = Dirties[J];

							FMaterialInstanceResource* R				= Resource;
							const FMaterialParameterInfo& ParameterInfo = Values[Index]->ParameterInfo;
							float Value									= FScalarParameterValue::GetValue(*(Values[Index]));

							ENQUEUE_RENDER_COMMAND(CsSetBatchMaterialParameterValue)(
								[R, ParameterInfo, Value](FRHICommandListImmediate& RHICmdList)
							{
								R->RenderThread_UpdateParameter(ParameterInfo, Value);
								//R->CacheUniformExpressions(false);
							});

							Dirties.RemoveAt(J, 1, false);
						}
						Scalars.DirtySet.Reset();
					}
					// Vectors
					{
						TArray<FVectorParameterValue*>& Values = Vectors.Values;
						TArray<int32>& Dirties				   = Vectors.Dirties;

						int32 DirtyCount = Dirties.Num();

						for (int32 J = DirtyCount - 1; J >= 0; --J)
						{
							const int32& Index = Dirties[J];

							FMaterialInstanceResource* R				= Resource;
							const FMaterialParameterInfo& ParameterInfo = Values[Index]->ParameterInfo;
							FLinearColor Value						    = FVectorParameterValue::GetValue(*(Values[Index]));

							ENQUEUE_RENDER_COMMAND(CsSetBatchMaterialParameterValue)(
								[R, ParameterInfo, Value](FRHICommandListImmediate& RHICmdList)
							{
								R->RenderThread_UpdateParameter(ParameterInfo, Value);
								//R->CacheUniformExpressions(false);
							});

							Dirties.RemoveAt(J, 1, false);
						}
						Vectors.DirtySet.Reset();
					}

					FMaterialInstanceResource* R = Resource;

					ENQUEUE_RENDER_COMMAND(SetBatchParameterValues)(
						[R](FRHICommandListImmediate& RHICmdList)
					{
						R->CacheUniformExpressions(false);
					});
				}
			}

			/*static*/ void FBatch::RenderThread_Update(FBatch* Batch)
			{
				FMaterialInstanceResource* Resource = Batch->Resource;

				// Scalars
				{
					FScalars& Scalars					   = Batch->Scalars;
					TArray<FScalarParameterValue*>& Values = Scalars.Values;
					TArray<int32>& Dirties				   = Scalars.Dirties;

					int32 DirtyCount = Dirties.Num();

					for (int32 J = DirtyCount - 1; J >= 0; --J)
					{
						const int32& Index = Dirties[J];

						Resource->RenderThread_UpdateParameter(Values[Index]->ParameterInfo, Values[Index]->ParameterValue);
						Resource->CacheUniformExpressions(false);

						Dirties.RemoveAt(J, 1, false);
					}
				}
				// Vectors
				{
					FVectors& Vectors					   = Batch->Vectors;
					TArray<FVectorParameterValue*>& Values = Vectors.Values;
					TArray<int32>& Dirties				   = Vectors.Dirties;

					int32 DirtyCount = Dirties.Num();

					for (int32 J = DirtyCount - 1; J >= 0; --J)
					{
						const int32& Index = Dirties[J];

						Resource->RenderThread_UpdateParameter(Values[Index]->ParameterInfo, Values[Index]->ParameterValue);
						Resource->CacheUniformExpressions(false);

						Dirties.RemoveAt(J, 1, false);
					}
				}
				
				Batch->bProcessing = false;
			}

			void FPayload::GameThread_Update()
			{
				if (IsDirty() &&
					FApp::CanEverRender())
				{
					FPayload* Payload = this;

					Payload->bProcessing = false;
					Payload->Prepare();
					Payload->bProcessing = false;

					const int32 Count = Dirties.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						const int32 Index = Dirties[I];
						FBatch& Batch	  = Batches[Index];

						Batch.GameThread_Update();

						Dirties.RemoveAt(I, 1, false);
					}
					DirtySet.Reset();
					/*
					ENQUEUE_RENDER_COMMAND(SetBatchParameterValues)(
						[Payload](FRHICommandListImmediate& RHICmdList)
						{
							FPayload::RenderThread_Update(Payload);
						});
					*/
				}
			}

			/*static*/ void FPayload::RenderThread_Update(FPayload* Payload)
			{
				int32 BatchCount = Payload->Dirties.Num();

				for (int32 I = BatchCount - 1; I >= 0; --I)
				{
					const int32 BatchIndex = Payload->Dirties[I];
					FBatch& Batch		   = Payload->Batches[BatchIndex];

					FMaterialInstanceResource* Resource = Batch.Resource;

					// Scalars
					{
						FScalars& Scalars					   = Batch.Scalars;
						TArray<FScalarParameterValue*>& Values = Scalars.Values;
						TArray<int32>& Dirties				   = Scalars.Dirties;

						int32 DirtyCount = Dirties.Num();

						for (int32 J = DirtyCount - 1; J >= 0; --J)
						{
							const int32& Index = Dirties[J];

							Resource->RenderThread_UpdateParameter(Values[Index]->ParameterInfo, Values[Index]->ParameterValue);
							Resource->CacheUniformExpressions(false);

							Dirties.RemoveAt(J, 1, false);
						}
					}
					// Vectors
					{
						FVectors& Vectors					   = Batch.Vectors;
						TArray<FVectorParameterValue*>& Values = Vectors.Values;
						TArray<int32>& Dirties				   = Vectors.Dirties;

						int32 DirtyCount = Dirties.Num();

						for (int32 J = DirtyCount - 1; J >= 0; --J)
						{
							const int32& Index = Dirties[J];

							Resource->RenderThread_UpdateParameter(Values[Index]->ParameterInfo, Values[Index]->ParameterValue);
							Resource->CacheUniformExpressions(false);

							Dirties.RemoveAt(J, 1, false);
						}
					}
				}
				
				for (int32 I = BatchCount - 1; I >= 0; --I)
				{
					const int32 BatchIndex = Payload->Dirties[I];
					FBatch& Batch		   = Payload->Batches[BatchIndex];

					Batch.bProcessing = false;

					Payload->Dirties.RemoveAt(I, 1, false);
				}

				Payload->bProcessing = false;
			}
		}
	}
}

// Cached
#pragma region

namespace NCsManagerMaterial
{
	namespace NCached
	{
		namespace Str
		{
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Material* UCsManager_Material::s_Instance;
bool UCsManager_Material::s_bShutdown = false;

UCsManager_Material::UCsManager_Material(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr)
{
}

// UObject Interface
#pragma region

bool UCsManager_Material::IsReadyForFinishDestroy()
{
	if (!Super::IsReadyForFinishDestroy())
	{
		return false;
	}
	return SetBatchParametersPayload.IsFree();
}

#pragma endregion UObject Interface

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_Material* UCsManager_Material::Get(const UObject* InRoot /*= nullptr*/)
{
	return Get_GetManagerMaterial(InRoot)->GetManager_Material();
}

/*static*/ UCsManager_Material* UCsManager_Material::GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerMaterial* GetManagerMaterial = GetSafe_GetManagerMaterial(Context, InRoot, Log))
		return GetManagerMaterial->GetManager_Material();
	return nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Material::Init(UObject* InRoot, TSubclassOf<UCsManager_Material> ManagerMaterialClass, UObject* InOuter /*= nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerMaterial* GetManagerMaterial = Get_GetManagerMaterial(InRoot);

	UCsManager_Material* Manager_Menu = GetManagerMaterial->GetManager_Material();

	if (!Manager_Menu)
	{
		Manager_Menu = NewObject<UCsManager_Material>(InOuter ? InOuter : InRoot, ManagerMaterialClass, TEXT("Manager_Material_Singleton"), RF_Transient | RF_Public);

		GetManagerMaterial->SetManager_Material(Manager_Menu);

		Manager_Menu->SetMyRoot(InRoot);
		Manager_Menu->Initialize();
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Material>(GetTransientPackage(), ManagerMaterialClass, TEXT("Manager_Material_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Material::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerMaterial* GetManagerMaterial = Get_GetManagerMaterial(InRoot);
	UCsManager_Material* Manager_Menu     = GetManagerMaterial->GetManager_Material();
	Manager_Menu->CleanUp();
	Manager_Menu->SetMyRoot(nullptr);

	GetManagerMaterial->SetManager_Material(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->SetMyRoot(nullptr);
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Material::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerMaterial(InRoot)->GetManager_Material() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerMaterial* UCsManager_Material::Get_GetManagerMaterial(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Material::Get_GetManagerMaterial: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Material::Get_GetManagerMaterial: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Material::Get_GetManagerMaterial: Manager_Singleton is NULL."));

	ICsGetManagerMaterial* GetManagerMaterial = Cast<ICsGetManagerMaterial>(Manager_Singleton);

	checkf(GetManagerMaterial, TEXT("UCsManager_Material::Get_GetManagerMaterial: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerMaterial."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerMaterial;
}

/*static*/ ICsGetManagerMaterial* UCsManager_Material::GetSafe_GetManagerMaterial(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetManagerMaterial>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Material::Initialize()
{
	bInitialized = true;
}

/*static*/ bool UCsManager_Material::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Material::CleanUp()
{
	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Material::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton