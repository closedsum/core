// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Data/CsTypes_Data_Projectile.h"
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsPrjLog.h"
// Data
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMesh.h"

#include "CsData_Projectile_VisualStaticMeshImplSlice.generated.h"
#pragma once

// NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NData, NVisual, NStaticMesh, FImplSlice)

/**
* Represents a "slice" of data, StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_Projectile_VisualStaticMeshImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsPrjStaticMesh Mesh;

	FCsData_Projectile_VisualStaticMeshImplSlice() :
		Mesh()
	{
	}

#define SliceType NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
struct FCsPrjStaticMesh;

namespace NCsProjectile
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
			#define StaticMeshVisualDataType NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh

				/**
				* Represents a "slice" of data, StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* If members are set via points to an "owning" data, then
				* "Emulates" StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSPRJ_API FImplSlice final : public StaticMeshVisualDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)

					CS_DECLARE_MEMBER_WITH_PROXY(StaticMesh, FCsPrjStaticMesh)

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(StaticMesh)
					{
						CS_CTOR_SET_MEMBER_PROXY(StaticMesh);
					}

					~FImplSlice()
					{
					}

				public:

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				public:

					FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				// StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(StaticMesh, FCsPrjStaticMesh)

				#pragma endregion StaticMeshVisualDataType (NCsProjectile::NData::NVisual::NStaticMesh::IStaticMesh)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
				};

			#undef StaticMeshVisualDataType
			}
		}
	}
}