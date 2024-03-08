// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/StaticMesh/Attachment/CsData_Skin_VisualStaticMesh_AttachmentImplSlice.h"

// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
#include "Containers/CsDeconstructInterfaceSliceMap.h"

#define SliceType NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice

void FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::CopyToSlice(SliceType* Slice)
{
	const int32 Count = Attachments.Num();

	typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

	TArray<AttachmentType>* AttachmentsPtr = Slice->GetStaticMeshAttachmentsPtr();

	AttachmentsPtr->Reset(Count);

	for (FCsStaticMeshAttachment& Attachment : Attachments)
	{
		AttachmentType& A = AttachmentsPtr->AddDefaulted_GetRef();

		Attachment.CopyToAttachment(&A);
	}
}

void FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	const int32 Count = Attachments.Num();

	typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

	TArray<AttachmentType>* AttachmentsPtr = Slice->GetStaticMeshAttachmentsPtr();

	AttachmentsPtr->Reset(Count);

	for (const FCsStaticMeshAttachment& Attachment : Attachments)
	{
		AttachmentType& A = AttachmentsPtr->AddDefaulted_GetRef();

		Attachment.CopyToAttachmentAsValue(&A);
	}
}

SliceType* FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

	typedef NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment InterfaceType;

	if (InterfaceMap->Implements(InterfaceType::Name))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
		return nullptr;
	}

	CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

	SliceType* Slice = new SliceType();

	// Add slice as type SkinType
	InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
	// Set the InterfaceMap of Data to the "root" InterfaceMap
	Slice->SetInterfaceMap(InterfaceMap);

	DeconstructInterfaceSliceMap->AddSlice(SliceType::Name, Slice);
	DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(SliceType::Name, &SliceType::Deconstruct);

	CopyToSliceAsValue(Slice);

	return Slice;
}

#undef SliceType

bool FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::IsValidChecked(const FString& Context) const
{
	for (const FCsStaticMeshAttachment& Attachment : Attachments)
	{
		CS_IS_VALID_CHECKED(Attachment);
	}
	return true;
}

bool FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	for (const FCsStaticMeshAttachment& Attachment : Attachments)
	{
		CS_IS_VALID(Attachment)
	}
	return true;
}

void FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const
{
	check(IsValidChecked(Context));

	for (const FCsStaticMeshAttachment& Attachment : Attachments)
	{
		Attachment.AttachChecked(Context, Parent, Child);
	}
}

bool FCsData_Skin_VisualStaticMesh_AttachmentImplSlice::AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	for (const FCsStaticMeshAttachment& Attachment : Attachments)
	{
		if (!Attachment.AttachSafe(Context, Parent, Child, Log))
			return false;
	}
	return true;
}

const FName NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NStaticMesh::NAttachment::FImplSlice");

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
					namespace NImplSlice
					{
						namespace NCached
						{
							namespace Name
							{
								const FName VisualStaticMeshAttachmentSlice = FName("VisualStaticMeshAttachmentSlice");

								const FName StaticMeshAttachments = FName("StaticMeshAttachments");
							}
						}
					}

					/*static*/ FImplSlice* FImplSlice::AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
					{
						using namespace NCsSkin::NData::NVisual::NStaticMesh::NAttachment::NImplSlice::NCached;

						CS_IS_PTR_NULL_RET_NULL(InterfaceMap)

						typedef NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment InterfaceType;

						if (InterfaceMap->Implements(InterfaceType::Name))
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InterfaceMap already contains a reference an interface of type: %s."), *Context, *(InterfaceType::Name.ToString())));
							return nullptr;
						}

						CS_IS_PTR_NULL_RET_NULL(DeconstructInterfaceSliceMap)

						CS_IS_PTR_NULL_RET_NULL(Object)

						// Check for properties matching interface: StaticMeshAttachmentDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)
						typedef NCsProperty::FLibrary PropertyLibrary;

						FImplSlice* Slice = nullptr;
						bool Success	  = false;

						// Try FCsData_Skin_VisualStaticMesh_AttachmentImplSlice
						typedef FCsData_Skin_VisualStaticMesh_AttachmentImplSlice StructSliceType;

						if (StructSliceType* SliceAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructSliceType>(Context, Object, Object->GetClass(), Name::VisualStaticMeshAttachmentSlice, nullptr))
						{
							Slice = new FImplSlice();

							// Add slice as type SkinType
							InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
							// Set the InterfaceMap of Data to the "root" InterfaceMap
							Slice->SetInterfaceMap(InterfaceMap);

							DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
							DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

							SliceAsStruct->CopyToSlice(Slice);
							Success = true;
						}
						// Try individual properties
						else
						{
							TArray<FCsStaticMeshAttachment>* AttachmentsPtr = PropertyLibrary::GetArrayStructPropertyValuePtr<FCsStaticMeshAttachment>(Context, Object, Object->GetClass(), Name::StaticMeshAttachments, nullptr);

							if (AttachmentsPtr)
							{
								Slice = new FImplSlice();
								
								// Add slice as type SkinType
								InterfaceMap->Add<InterfaceType>(InterfaceType::Name, static_cast<InterfaceType*>(Slice));
								// Set the InterfaceMap of Data to the "root" InterfaceMap
								Slice->SetInterfaceMap(InterfaceMap);
								
								DeconstructInterfaceSliceMap->AddSlice(FImplSlice::Name, Slice);
								DeconstructInterfaceSliceMap->AddDeconstructSliceImpl(FImplSlice::Name, &FImplSlice::Deconstruct);

								// Copy the values to Slice
								TArray<FCsStaticMeshAttachment>& AttachmentsRef = *AttachmentsPtr;

								const int32 Count = AttachmentsRef.Num();

								typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

								TArray<AttachmentType>* StaticMeshAttachmentsPtr = Slice->GetStaticMeshAttachmentsPtr();

								StaticMeshAttachmentsPtr->Reset(Count);

								for (FCsStaticMeshAttachment& Attachment : AttachmentsRef)
								{
									AttachmentType& A = StaticMeshAttachmentsPtr->AddDefaulted_GetRef();

									Attachment.CopyToAttachment(&A);
								}
								Success = true;
							}
						}

						if (!Success)
						{
							if (Log)
							{
								typedef NCsObject::FLibrary ObjectLibrary;

								Log(FString::Printf(TEXT("%s: Failed to find any properties from %s for interface: StaticMeshVisualDataType (NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment)."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
								Log(FString::Printf(TEXT("%s: - Failed to get struct property of type: FCsData_Skin_VisualStaticMesh_AttachmentImplSlice with name: VisualStaticMeshAttachmentSlice."), *Context));
								Log(FString::Printf(TEXT("%s: - OR"), *Context));
								Log(FString::Printf(TEXT("%s: - Failed to get array struct property of type: TArray<FCsStaticMeshAttachment> with name: StaticMeshAttachments."), *Context));
							}
						}
						return Slice;
					}

					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

						for (const AttachmentType& Attachment : GetStaticMeshAttachments())
						{
							CS_IS_VALID_CHECKED(Attachment);
						}
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
					{
						typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

						for (const AttachmentType& Attachment : GetStaticMeshAttachments())
						{
							CS_IS_VALID(Attachment);
						}
						return true;
					}

					void FImplSlice::AttachChecked(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child) const
					{
						check(IsValidChecked(Context));

						typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

						for (const AttachmentType& Attachment : GetStaticMeshAttachments())
						{
							Attachment.AttachChecked(Context, Parent, Child);
						}
					}

					bool FImplSlice::AttachSafe(const FString& Context, USceneComponent* Parent, UStaticMeshComponent* Child, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
					{
						if (!IsValid(Context, Log))
							return false;

						typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

						for (const AttachmentType& Attachment : GetStaticMeshAttachments())
						{
							if (!Attachment.AttachSafe(Context, Parent, Child, Log))
								return false;
						}
						return true;
					}
				}
			}
		}
	}
}
