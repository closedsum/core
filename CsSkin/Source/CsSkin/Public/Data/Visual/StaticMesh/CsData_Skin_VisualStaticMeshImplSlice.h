// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "Types/CsTypes_StaticMesh.h"
// Data
#include "Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"
// Log
#include "Utility/CsSkinLog.h"

#include "CsData_Skin_VisualStaticMeshImplSlice.generated.h"

// NCsSkin::NData::NVisual::NStaticMesh::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMesh, FImplSlice)

class UStaticMeshComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IMaterial).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualStaticMeshImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual|Static Mesh")
	FCsStaticMesh Mesh;

	FCsData_Skin_VisualStaticMeshImplSlice() :
		Mesh()
	{
	}

	using SliceType = NCsSkin::NData::NVisual::NStaticMesh::FImplSlice;

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
	bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UStaticMesh;
class UStaticMeshComponent;
class ICsDeconstructInterfaceSliceMap;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				/**
				* Represents a "slice" of data, CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh).
				* 
				* If members are set via pointers to an "owning" data, then
				* "Emulates" StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSSKIN_API FImplSlice final : public CsStaticMeshSkinDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

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

				// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(StaticMesh, UStaticMesh)

				#pragma endregion CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSkin::NData::NVisual::NStaticMesh::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &NCsSkin::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

					void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
					bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
				};
			}
		}
	}
}