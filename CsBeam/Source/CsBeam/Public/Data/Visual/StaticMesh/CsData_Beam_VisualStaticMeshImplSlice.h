// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Macro/CsMacro_Namespace.h"
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_StaticMesh.h"
// Log
#include "Utility/CsBeamLog.h"
// Data
#include "Data/Visual/StaticMesh/CsData_Beam_VisualStaticMesh.h"

#include "CsData_Beam_VisualStaticMeshImplSlice.generated.h"

// NCsBeam::NData::NVisual::NStaticMesh::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsBeam, NData, NVisual, NStaticMesh, FImplSlice)

/**
* Represents a "slice" of data, StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_Beam_VisualStaticMeshImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data|Visual|Static Mesh")
	FCsStaticMesh Mesh;

	FCsData_Beam_VisualStaticMeshImplSlice() :
		Mesh()
	{
	}

#define SliceType NCsBeam::NData::NVisual::NStaticMesh::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

struct FCsInterfaceMap;
struct FCsBeamStaticMesh;

namespace NCsBeam
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
			#define StaticMeshVisualDataType NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh

				/**
				* Represents a "slice" of data, StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* If members are set via points to an "owning" data, then
				* "Emulates" StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSBEAM_API FImplSlice final : public StaticMeshVisualDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh)

					CS_DECLARE_MEMBER_WITH_PROXY(StaticMesh, UStaticMesh*)

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(StaticMesh, nullptr)
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

				// StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(StaticMesh, UStaticMesh)

				#pragma endregion StaticMeshVisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsBeam::NData::NVisual::NStaticMesh::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
				};

			#undef StaticMeshVisualDataType
			}
		}
	}
}