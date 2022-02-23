// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
#include "Mesh/CsStaticMeshAttachment.h"
// Data
#include "Skin/Data/Visual/StaticMesh/Attachment/CsData_Skin_VisualStaticMesh_Attachment.h"

#include "CsData_Skin_VisualStaticMesh_AttachmentImplSlice.generated.h"

// NCsSkin::NData::NVisual::NStaticMesh::NAttachment::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsSkin, NData, NVisual, NStaticMesh, NAttachment, FImplSlice)

class USceneComponent;
class UStaticMeshComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_Skin_VisualStaticMesh_AttachmentImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// StaticMeshVisualDataType(NCsSkin::NData::NVisual::NStaticMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual|Static Mesh")
	TArray<FCsStaticMeshAttachment> Attachments;

	FCsData_Skin_VisualStaticMesh_AttachmentImplSlice() :
		Attachments()
	{
	}

#define SliceType NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &FCsLog::Warning) const;

#undef SliceType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
	bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;
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
				#define StaticMeshAttachmentDataType NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment

					/**
					* Represents a "slice" of data, StaticMeshAttachmentDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment).
					* 
					* If members are set via pointers to an "owning" data, then
					* "Emulates" StaticMeshAttachmentDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment) by mimicking 
					* the interfaces and having pointers to the appropriate members.
					*
					* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
					* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
					*/
					struct CSCORE_API FImplSlice final : public StaticMeshAttachmentDataType
					{
					public:

						static const FName Name;

					#define AttachmentType NCsStaticMesh::NAttachment::FAttachment

					private:

						// ICsGetInterfaceMap

						/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition)
							that describe the data. */
						FCsInterfaceMap* InterfaceMap;

						// StaticMeshAttachmentDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)

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

					// StaticMeshAttachmentDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)
					#pragma region
					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(StaticMeshAttachments, TArray<AttachmentType>)

					#pragma endregion StaticMeshAttachmentDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)

					public:

						static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice*>(Ptr);
						}

						static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

						void AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const;
						bool AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) = &FCsLog::Warning) const;

					#undef AttachmentType
					};

				#undef StaticMeshAttachmentDataType
				}
			}
		}
	}
}