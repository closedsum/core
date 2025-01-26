// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Misc.h"
#include "Mesh/CsStaticMeshAttachment.h"
// Data
#include "Data/Visual/StaticMesh/Attachment/CsData_Skin_VisualStaticMesh_Attachment.h"
// Log
#include "Utility/CsSkinLog.h"

#include "CsData_Skin_VisualStaticMesh_AttachmentImplSlice.generated.h"

// NCsSkin::NData::NVisual::NStaticMesh::NAttachment::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsSkin, NData, NVisual, NStaticMesh, NAttachment, FImplSlice)

class USceneComponent;
class UStaticMeshComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualStaticMesh_AttachmentImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual|Static Mesh")
	TArray<FCsStaticMeshAttachment> Attachments;

	FCsData_Skin_VisualStaticMesh_AttachmentImplSlice() :
		Attachments()
	{
	}

	using SliceType = NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice;

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
	bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
};

struct FCsInterfaceMap;
class USceneComponent;
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
				namespace NAttachment
				{
					/**
					* Represents a "slice" of data, CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment).
					* 
					* If members are set via pointers to an "owning" data, then
					* "Emulates" CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment) by mimicking 
					* the interfaces and having pointers to the appropriate members.
					*
					* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
					* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
					*/
					struct CSSKIN_API FImplSlice final : public CsStaticMeshAttachmentSkinDataType
					{
					public:

						static const FName Name;

					private:

						using AttachmentType = NCsStaticMesh::NAttachment::FAttachment;

					private:

						// ICsGetInterfaceMap

						/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition)
							that describe the data. */
						FCsInterfaceMap* InterfaceMap;

						// CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)

						CS_DECLARE_MEMBER_WITH_PROXY(StaticMeshAttachments, TArray<AttachmentType>)

					public:

						FImplSlice() :
							InterfaceMap(nullptr),
							CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(StaticMeshAttachments)
						{
							CS_CTOR_SET_MEMBER_PROXY(StaticMeshAttachments);
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

					// CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)
					#pragma region
					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(StaticMeshAttachments, TArray<AttachmentType>)

					#pragma endregion CsStaticMeshAttachmentSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)

					public:

						static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice*>(Ptr);
						}

						static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &NCsSkin::FLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

						void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
						bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
					};
				}
			}
		}
	}
}