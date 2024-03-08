// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsManager_Material.generated.h"

class UMaterialInstanceDynamic;
class FMaterialInstanceResource;
struct FMaterialParameterInfo;
struct FScalarParameterValue;
struct FVectorParameterValue;

// NCsMaterial::NParameter::NSet::FBatch
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NSet, FBatch)
// NCsMaterial::NParameter::NSet::FPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NParameter, NSet, FPayload)

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NSet
		{
			struct CSCORE_API FScalars
			{
				friend struct FBatch;

			private:

				FBatch* Outer;

			public:

				TMap<FName, int32> IndexByNameMap;

				TMap<FName, FScalarParameterValue*> ValueByNameMap;

				TArray<FScalarParameterValue*> Values;

				TSet<int32> DirtySet;

				TArray<int32> Dirties;

				FScalars() :
					Outer(nullptr),
					IndexByNameMap(),
					ValueByNameMap(),
					Values(),
					DirtySet(),
					Dirties()
				{
				}

				void Init(const TArray<FName>& InNames);

				FORCEINLINE bool IsDirty() const { return DirtySet.Num() > 0; }
				FORCEINLINE void ClearDirty()
				{
					DirtySet.Reset();
					Dirties.Reset(Dirties.Max());
				}

				void Set(const FName& Name, const float& Value, const bool& ForceDirty = false);

				FORCEINLINE void Prepare()
				{
					for (int32& Index : DirtySet)
					{
						Dirties.Add(Index);
					}
				}
			};

			struct CSCORE_API FVectors
			{
				friend struct FBatch;

			private:

				FBatch* Outer;

			public:

				TMap<FName, int32> IndexByNameMap;

				TMap<FName, FVectorParameterValue*> ValueByNameMap;

				TArray<FVectorParameterValue*> Values;

				TSet<int32> DirtySet;

				TArray<int32> Dirties;

				FVectors() :
					Outer(nullptr),
					IndexByNameMap(),
					ValueByNameMap(),
					Values(),
					DirtySet(),
					Dirties()
				{
				}

				void Init(const TArray<FName>& InNames);

				FORCEINLINE bool IsDirty() const { return DirtySet.Num() > 0; }
				FORCEINLINE void ClearDirty()
				{
					DirtySet.Reset(),
					Dirties.Reset(Dirties.Max());
				}

				void Set(const FName& Name, const FLinearColor& Value, const bool& ForceDirty = false);

				FORCEINLINE void Prepare()
				{
					for (int32& Index : DirtySet)
					{
						Dirties.Add(Index);
					}
				}
			};

			struct CSCORE_API FBatch
			{
				friend struct FPayload;

			private:

				FPayload* Outer;

			public:

				int32 ID;

				bool bProcessing;

				UMaterialInstanceDynamic* MID;

				FMaterialInstanceResource* Resource;

				FScalars Scalars;

				FVectors Vectors;

				FBatch() :
					Outer(nullptr),
					ID(INDEX_NONE),
					bProcessing(false),
					MID(nullptr),
					Resource(nullptr),
					Scalars(),
					Vectors()
				{
					Scalars.Outer = this;
					Vectors.Outer = this;
				}

				FORCEINLINE FPayload* GetOuter() { return Outer; }

				FORCEINLINE bool IsProcessing() const { return bProcessing; }
				FORCEINLINE bool IsFree() const { return !IsProcessing(); }

				void Init(UMaterialInstanceDynamic* InMID);

				FORCEINLINE bool IsDirty() const { return Scalars.IsDirty() & Vectors.IsDirty(); }
				void MarkDirty();
				FORCEINLINE void ClearyDirty()
				{
					Scalars.ClearDirty();
					Vectors.ClearDirty();
				}

			private:

				FORCEINLINE void Prepare()
				{
					check(IsFree());

					Scalars.Prepare();
					Vectors.Prepare();

					bProcessing = true;
				}

			public:

				void GameThread_Update();

				static void RenderThread_Update(FBatch* Batch);
			};

			struct CSCORE_API FPayload
			{
			public:

				bool bProcessing;

				TArray<FBatch> Batches;

				TSet<int32> DirtySet;

				TArray<int32> Dirties;

				FPayload() :
					bProcessing(false),
					Batches(),
					DirtySet(),
					Dirties()
				{
				}
				
				FORCEINLINE bool IsProcessing() const { return bProcessing; }
				FORCEINLINE bool IsFree() const { return !IsProcessing(); }

				void SetSize(const int32& InSize)
				{
					Batches.Reset(InSize);
					Dirties.Reset(InSize);

					for (int32 I = 0; I < InSize; ++I)
					{
						FBatch& Batch = Batches.AddDefaulted_GetRef();
						Batch.Outer   = this;
						Batch.ID	  = I;
					}
				}

				FORCEINLINE bool IsDirty() const { return DirtySet.Num() > 0; }
				FORCEINLINE void ClearDirty()
				{
					for (int32& Index : DirtySet)
					{
						Batches[Index].ClearyDirty();
					}
					DirtySet.Reset();
				}

			private:

				FORCEINLINE void Prepare()
				{
					check(IsFree());

					for (int32& Index : DirtySet)
					{
						Dirties.Add(Index);

						Batches[Index].Prepare();
					}
					bProcessing = true;
				}

			public:

				void GameThread_Update();

				static void RenderThread_Update(FPayload* Payload);
			};
		}
	}
}

class ICsGetManagerMaterial;

UCLASS(transient)
class CSCORE_API UCsManager_Material : public UObject
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual bool IsReadyForFinishDestroy() override;

#pragma endregion UObject Interface

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Material* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Material* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Material* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Material* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Material> ManagerMaterialClass, UObject* InOuter = nullptr);
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerMaterial* Get_GetManagerMaterial(const UObject* InRoot);
	static ICsGetManagerMaterial* GetSafe_GetManagerMaterial(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Material* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Payload
#pragma region
private:

#define SetBatchParametersPayloadType NCsMaterial::NParameter::NSet::FPayload

	SetBatchParametersPayloadType SetBatchParametersPayload;

public:

	SetBatchParametersPayloadType* AllocateSetBatchParametersPayload()
	{
		return &SetBatchParametersPayload;
	}

#undef SetBatchParametersPayloadType


#pragma endregion Payload
};