// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_SkeletalMesh.h"
// Data
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"

#include "CsData_Skin_VisualSkeletalMeshImplSlice.generated.h"
#pragma once

// NCsSkin::NData::NVisual::NSkeletalMesh::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NSkeletalMesh, FImplSlice)

class USkeletalMeshComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::IMaterial).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_Skin_VisualSkeletalMeshImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// SkeletalMeshVisualDataType(NCsSkin::NData::NVisual::NSkeletalMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsSkeletalMesh Mesh;

	FCsData_Skin_VisualSkeletalMeshImplSlice() :
		Mesh()
	{
	}

#define SliceType NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &FCsLog::Warning) const;

#undef SliceType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, USkeletalMeshComponent* Component) const;
	bool SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class USkeletalMesh;
class USkeletalMeshComponent;
class ICsDeconstructInterfaceSliceMap;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMesh
			{
			#define SkeletalMeshVisualDataType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh

				/**
				* Represents a "slice" of data, SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh).
				* 
				* If members are set via pointers to an "owning" data, then
				* "Emulates" SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSCORE_API FImplSlice final : public SkeletalMeshVisualDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)

					USkeletalMesh* SkeletalMesh;
					USkeletalMesh** SkeletalMesh_Emu;

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						SkeletalMesh(nullptr),
						SkeletalMesh_Emu(nullptr)
					{
						SkeletalMesh_Emu = &SkeletalMesh;
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

				// SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::IStaticMesh)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(SkeletalMesh, USkeletalMesh)

				#pragma endregion SkeletalMeshVisualDataType (NCsSkin::NData::NVisual::NSkeletalMesh::IStaticMesh)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

					void SetChecked(const FString& Context, USkeletalMeshComponent* Component) const;
					bool SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};

			#undef SkeletalMeshVisualDataType
			}
		}
	}
}