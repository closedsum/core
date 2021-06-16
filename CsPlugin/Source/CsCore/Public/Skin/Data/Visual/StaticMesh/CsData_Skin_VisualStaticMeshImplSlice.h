// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_StaticMesh.h"
// Data
#include "Skin/Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"

#include "CsData_Skin_VisualStaticMeshImplSlice.generated.h"
#pragma once

// NCsSkin::NData::NVisual::NStaticMesh::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMesh, FImplSlice)

class UStaticMeshComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IMaterial).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_Skin_VisualStaticMeshImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// StaticMeshVisualDataType(NCsSkin::NData::NVisual::NStaticMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsStaticMesh Mesh;

	FCsData_Skin_VisualStaticMeshImplSlice() :
		Mesh()
	{
	}

#define SliceType NCsSkin::NData::NVisual::NStaticMesh::FImplSlice
	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;
#undef SliceType

	bool SafeAddSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
	bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class UStaticMesh;
class UStaticMeshComponent;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
			#define StaticMeshVisualDataType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh

				/**
				* Represents a "slice" of data, StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* If members are set via pointers to an "owning" data, then
				* "Emulates" StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSCORE_API FImplSlice final : public StaticMeshVisualDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

					UStaticMesh* StaticMesh;
					UStaticMesh** StaticMesh_Emu;

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						StaticMesh(nullptr),
						StaticMesh_Emu(nullptr)
					{
						StaticMesh_Emu = &StaticMesh;
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

				// StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(StaticMesh, UStaticMesh)

				#pragma endregion StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSkin::NData::NVisual::NStaticMesh::FImplSlice*>(Ptr);
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

					void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
					bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};

			#undef StaticMeshVisualDataType
			}
		}
	}
}