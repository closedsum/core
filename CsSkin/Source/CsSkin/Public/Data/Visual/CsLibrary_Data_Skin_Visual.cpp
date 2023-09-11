// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsLibrary_Data_Skin_Visual.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsDeconstructInterfaceSliceMap.h"
// Data
#include "Data/Visual/CsData_Skin_VisualInterfaceMap.h"
#include "Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"
#include "Data/Visual/StaticMesh/Attachment/CsData_Skin_VisualStaticMesh_Attachment.h"
#include "Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"
#include "Data/Visual/Material/CsData_Skin_VisualMaterial.h"
#include "Data/Visual/Material/Parameter/CsData_Skin_VisualMaterial_WithParameters.h"
#include "Data/Visual/Scale/CsData_Skin_VisualScale_Uniform.h"
#include "Data/Visual/Scale/CsData_Skin_VisualScale_UniformRange.h"
// Static Mesh
#include "Managers/StaticMesh/CsStaticMeshActorPooled.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Engine
#include "GameFramework/Actor.h"

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
		#define SkinType NCsSkin::NData::NVisual::IVisual

			FString FLibrary::PrintObjectAndClass(const SkinType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("Object: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintNameAndClass(const SkinType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintSkinAndClass(const SkinType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("Skin: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
			FString FLibrary::PrintNameAndClass(const StaticMeshSkinType* Skin)
			{
			#undef StaticMeshSkinType

				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
			FString FLibrary::PrintNameAndClass(const SkeletalMeshSkinType* Skin)
			{
			#undef SkeletalMeshSkinType

				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			bool FLibrary::IsValidChecked(const FString& Context, const SkinType* Skin)
			{
				CS_IS_PTR_NULL_CHECKED(Skin)

				// Material
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin);

				if (MaterialSkin)
				{
					check(MaterialLibrary::IsValidChecked(Context, MaterialSkin->GetMaterials()));
				}
				// MaterialWithParameters
				typedef NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters MaterialWithParamsSkinType;

				const MaterialWithParamsSkinType* MaterialWithParamsSkin = GetSafeInterfaceChecked<MaterialWithParamsSkinType>(Context, Skin);

				if (MaterialWithParamsSkin)
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					for (const MaterialType& Material : Materials)
					{
						check(Material.IsValidChecked(Context));
					}
				}
				// StaticMesh

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				if (StaticMeshSkin)
				{
					checkf(StaticMeshSkin->GetStaticMesh(), TEXT("%s: Skin->GetStaticMesh() is NULL for Skin implementing interface: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));
				}
				// SkeletalMesh
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				if (SkeletalMeshSkin)
				{
					checkf(SkeletalMeshSkin->GetSkeletalMesh(), TEXT("%s: Skin->GetSkeletalMesh() is NULL for Skin implementing interface: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));
				}

				// NOTE: For now this seems reasonable to check
				if (MaterialSkin &&
					StaticMeshSkin)
				{
					UStaticMesh* Mesh							 = StaticMeshSkin->GetStaticMesh();
					const TArray<UMaterialInterface*>& Materials = MaterialSkin->GetMaterials();

					checkf(Materials.Num() == Mesh->GetStaticMaterials().Num(), TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->StaticMaterials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetStaticMaterials().Num());
				}
				// NOTE: For now this seems reasonable to check
				if (MaterialWithParamsSkin &&
					StaticMeshSkin)
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					UStaticMesh* Mesh					  = StaticMeshSkin->GetStaticMesh();
					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					checkf(Materials.Num() == Mesh->GetStaticMaterials().Num(), TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->StaticMaterials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetStaticMaterials().Num());
				}
				// NOTE: For now this seems reasonable to check
				if (MaterialSkin &&
					SkeletalMeshSkin)
				{
					USkeletalMesh* Mesh							 = SkeletalMeshSkin->GetSkeletalMesh();
					const TArray<UMaterialInterface*>& Materials = MaterialSkin->GetMaterials();

					checkf(Materials.Num() == Mesh->GetMaterials().Num(), TEXT("%s: Skin->GetMaterials().Num() != Skin->GetSkeletalMesh()->Materials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetMaterials().Num());
				}
				// NOTE: For now this seems reasonable to check
				if (MaterialWithParamsSkin &&
					SkeletalMeshSkin)
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					USkeletalMesh* Mesh					  = SkeletalMeshSkin->GetSkeletalMesh();
					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					checkf(Materials.Num() == Mesh->GetMaterials().Num(), TEXT("%s: Skin->GetMaterials().Num() != Skin->GetSkeletalMesh()->Materials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetMaterials().Num());
				}

				// UniformScale
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinDataType;

				if (const UniformScaleSkinDataType* UniformScaleSkinData = GetSafeInterfaceChecked<UniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScaleSkinData->GetUniformScale(), 0.0f)
				}

				// UniformRangeScale
				typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange UniformRangeScaleSkinDataType;

				if (const UniformRangeScaleSkinDataType* UniformRangeScaleSkinData = GetSafeInterfaceChecked<UniformRangeScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformRangeScaleSkinData->GetMinUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformRangeScaleSkinData->GetMaxUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(UniformRangeScaleSkinData->GetMaxUniformScale(), UniformRangeScaleSkinData->GetMinUniformScale())
				}

				// TODO: Attachments
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const SkinType* Skin, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Skin)

				// Material
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin);

				if (MaterialSkin)
				{
					if (!MaterialLibrary::IsValid(Context, MaterialSkin->GetMaterials(), Log))
						return false;
				}
				// MaterialWithParameters
				typedef NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters MaterialWithParamsSkinType;

				const MaterialWithParamsSkinType* MaterialWithParamsSkin = GetSafeInterfaceChecked<MaterialWithParamsSkinType>(Context, Skin);

				if (MaterialWithParamsSkin)
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					for (const MaterialType& Material : Materials)
					{
						if (!Material.IsValid(Context, Log))
							return false;
					}
				}
				// StaticMesh
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				if (StaticMeshSkin)
				{
					if (!StaticMeshSkin->GetStaticMesh())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetStaticMesh() is NULL for Skin implementing interface: %s."), *Context, *(StaticMeshSkinType::Name.ToString())));
						return false;
					}
				}
				// SkeletalMesh
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				if (SkeletalMeshSkin)
				{
					if (!SkeletalMeshSkin->GetSkeletalMesh())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetSkeletalMesh() is NULL for Skin implementing interface: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString())));
						return false;
					}
				}

				// NOTE: For now this seems reasonable to check
				if (MaterialSkin &&
					StaticMeshSkin)
				{
					UStaticMesh* Mesh							 = StaticMeshSkin->GetStaticMesh();
					const TArray<UMaterialInterface*>& Materials = MaterialSkin->GetMaterials();

					if (Materials.Num() != Mesh->GetStaticMaterials().Num())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->GetStaticMaterials().Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetStaticMaterials().Num()));
						return false;
					}
				}
				// NOTE: For now this seems reasonable to check
				if (MaterialWithParamsSkin &&
					StaticMeshSkin)
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					UStaticMesh* Mesh					  = StaticMeshSkin->GetStaticMesh();
					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					if (Materials.Num() != Mesh->GetStaticMaterials().Num())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->GetStaticMaterials().Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetStaticMaterials().Num()));
						return false;
					}
				}
				// NOTE: For now this seems reasonable to check
				if (MaterialSkin &&
					SkeletalMeshSkin)
				{
					USkeletalMesh* Mesh							 = SkeletalMeshSkin->GetSkeletalMesh();
					const TArray<UMaterialInterface*>& Materials = MaterialSkin->GetMaterials();

					if (Materials.Num() != Mesh->GetMaterials().Num())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetMaterials().Num() != Skin->GetSkeletalMesh()->GetMaterials().Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetMaterials().Num()));
						return false;
					}
				}
				// NOTE: For now this seems reasonable to check
				if (MaterialWithParamsSkin &&
					SkeletalMeshSkin)
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					USkeletalMesh* Mesh					  = SkeletalMeshSkin->GetSkeletalMesh();
					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					if (Materials.Num() != Mesh->GetMaterials().Num())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->GetMaterials().Num() (%d != %d)."), *Context, Materials.Num(), Mesh->GetMaterials().Num()));
						return false;
					}
				}

				// UniformScale
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinDataType;

				if (const UniformScaleSkinDataType* UniformScaleSkinData = GetSafeInterfaceChecked<UniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN(UniformScaleSkinData->GetUniformScale(), 0.0f)
				}

				// UniformRangeScale
				typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange UniformRangeScaleSkinDataType;

				if (const UniformRangeScaleSkinDataType* UniformRangeScaleSkinData = GetSafeInterfaceChecked<UniformRangeScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN(UniformRangeScaleSkinData->GetMinUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN(UniformRangeScaleSkinData->GetMaxUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(UniformRangeScaleSkinData->GetMaxUniformScale(), UniformRangeScaleSkinData->GetMinUniformScale())
				}
				return true;
			}

			ICsDeconstructInterfaceSliceMap* FLibrary::GetSafeDeconstructInterfaceSliceMap(const FString& Context, SkinType* Skin, void(*Log)(const FString&) /*=FCLog::Warning*/)
			{
				CS_IS_PTR_NULL_RET_NULL(Skin)

				FCsInterfaceMap* InterfaceMap = Skin->GetInterfaceMap();
				const FName& RootName		  = InterfaceMap->GetRootName();

				typedef NCsSkin::NData::NVisual::FInterfaceMap DataInterfaceMapType;

				if (RootName == DataInterfaceMapType::Name)
				{
					return InterfaceMap->GetRoot<DataInterfaceMapType>();
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin is NOT a composition of unique slices."), *Context));
				return nullptr;
			}

		// Static Mesh
		#pragma region

			bool FLibrary::ImplementsStaticMeshSkinType(const FString& Context, const SkinType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetStaticMeshAndMaterialsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component)
			{
				SetStaticMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				const MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMaterials(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s."), *Context, *PrintNameAndClass(Skin), *(MaterialSkinType::Name.ToString())));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString())));
				}
			}

			void FLibrary::SetStaticMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				SetStaticMeshChecked(Context, Skin, Component);
				SetMaterialsChecked(Context, Skin, Component, OutMIDs);
			}

			bool FLibrary::SetSafeStaticMeshAndMIDs(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				if (!SetSafeStaticMesh(Context, Skin, Component, Log))
					return false;

				typedef NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult ResultType;

				ResultType Result = SetSafeMaterials(Context, Skin, Component, OutMIDs, Log);
				return Result.bSuccess;
			}

			void FLibrary::SetStaticMeshChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				const StaticMeshSkinType* StaticMeshSkin = GetInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				SetStaticMeshChecked(Context, StaticMeshSkin, Component);
			}

			#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh

			void FLibrary::SetStaticMeshChecked(const FString& Context, const StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component)
			{
				CS_IS_PTR_NULL_CHECKED(StaticMeshSkin)

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(StaticMeshSkin), *(StaticMeshSkinType::Name.ToString()));

				CS_IS_PTR_NULL_CHECKED(Component)

				Component->SetStaticMesh(Mesh);
			}

			bool FLibrary::SetSafeStaticMesh(const FString& Context, const StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(StaticMeshSkin)

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				if (!Mesh)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get StaticMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(StaticMeshSkin), *(StaticMeshSkinType::Name.ToString())));
					return false;
				}

				CS_IS_PTR_NULL(Component)

				Component->SetStaticMesh(Mesh);
				return true;
			}

			#undef StaticMeshSkinType

			bool FLibrary::SetSafeStaticMesh(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					return SetSafeStaticMesh(Context, StaticMeshSkin, Component, Log);
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString())));
				return false;
			}

		// Attachment
		#pragma region

			int32 FLibrary::GetNumAttachmentsChecked(const FString& Context, const UObject* WorldContext, const SkinType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment AttachmentSkinType;
				typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

				const AttachmentSkinType* AttachmentSkin  = GetInterfaceChecked<AttachmentSkinType>(Context, Skin);
				const TArray<AttachmentType>& Attachments = AttachmentSkin->GetStaticMeshAttachments();

				return Attachments.Num();
			}

			void FLibrary::SetupAttachmentsChecked(const FString& Context, const UObject* WorldContext, const SkinType* Skin, USceneComponent* Component, TArray<FCsStaticMeshActorPooled*>& OutAttachments)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment AttachmentSkinType;
				typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

				const AttachmentSkinType* AttachmentSkin  = GetInterfaceChecked<AttachmentSkinType>(Context, Skin);
				const TArray<AttachmentType>& Attachments = AttachmentSkin->GetStaticMeshAttachments();

				OutAttachments.Reset(FMath::Max(OutAttachments.Max(), Attachments.Num()));

				for (const AttachmentType& Attachment : Attachments)
				{
					OutAttachments.Add(Attachment.AttachChecked(Context, WorldContext, Component));
				}
			}

			void FLibrary::AttachOnlyTransformChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component, const int32& Index, const FCsStaticMeshActorPooled* Attachment)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment AttachmentSkinType;
				typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

				const AttachmentSkinType* AttachmentSkin  = GetInterfaceChecked<AttachmentSkinType>(Context, Skin);
				const TArray<AttachmentType>& Attachments = AttachmentSkin->GetStaticMeshAttachments();

				CS_IS_INT_GREATER_THAN_CHECKED(Index, INDEX_NONE)

				checkf(Attachments.Num() > Index, TEXT("%s: Index for Attachment does NOT exist."), *Context);

				Attachments[Index].AttachOnlyTransformChecked(Context, Component, Attachment->GetMeshComponent());
			}

		#pragma endregion Attachment

		#pragma endregion Static Mesh

		// Skeletal Mesh
		#pragma region

			bool FLibrary::ImplementsSkeletalMeshSkinType(const FString& Context, const SkinType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetSkeletalMeshAndMaterialsChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component)
			{	
				SetSkeletalMeshChecked(Context, Skin, Component);

				typedef NCsMaterial::FLibrary MaterialLibrary;

				// Material
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

				if (const MaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinDataType>(Context, Skin))
				{
					MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					return;
				}
				// MaterialWithParameters
				typedef NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters MaterialWithParamsSkinDataType;

				if (const MaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<MaterialWithParamsSkinDataType>(Context, Skin))
				{
					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					const int32 Count = Materials.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const MaterialType& Material = Materials[I];

						Material.SetChecked(Context, Component, I);
					}
					return;
				}
				checkf(0, TEXT("%s: %s does NOT implement any material interface."), *Context, *PrintSkinAndClass(Skin));
			}

			bool FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);

					typedef NCsMaterial::FLibrary MaterialLibrary;

					// Material
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

					if (const MaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinDataType>(Context, Skin))
					{
						return MaterialLibrary::SetSafe(Context, Component, MaterialSkin->GetMaterials());
					}
					// MaterialWithParameters
					typedef NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters MaterialWithParamsSkinDataType;

					if (const MaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<MaterialWithParamsSkinDataType>(Context, Skin))
					{
						typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

						const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

						const int32 Count = Materials.Num();

						for (int32 I = 0; I < Count; ++I)
						{
							const MaterialType& Material = Materials[I];

							if (!Material.SetSafe(Context, Component, I))
								return false;
						}
						return true;
					}
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement any material interface."), *Context, *PrintSkinAndClass(Skin)));
					return false;
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(SkeletalMeshSkinType::Name.ToString())));
				return false;
			}

			void FLibrary::SetSkeletalMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				SetSkeletalMeshChecked(Context, Skin, Component);
				SetMaterialsChecked(Context, Skin, Component, OutMIDs);
			}

			bool FLibrary::SetSafeSkeletalMeshAndMIDs(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				if (!SetSafeSkeletalMesh(Context, Skin, Component, Log))
					return false;

				typedef NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult ResultType;

				ResultType Result = SetSafeMaterials(Context, Skin, Component, OutMIDs, Log);
				return Result.bSuccess;
			}

			void FLibrary::SetSkeletalMeshChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				const SkeletalMeshSkinType* SkeletalMeshSkin = GetInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);
			}

			#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh

			void FLibrary::SetSkeletalMeshChecked(const FString& Context, const SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component)
			{
				CS_IS_PTR_NULL_CHECKED(SkeletalMeshSkin)

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(SkeletalMeshSkin), *(SkeletalMeshSkinType::Name.ToString()));

				CS_IS_PTR_NULL_CHECKED(Component)

				Component->SetSkeletalMesh(Mesh);
			}

			bool FLibrary::SetSafeSkeletalMesh(const FString& Context, const SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(SkeletalMeshSkin)

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				if (!Mesh)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get SkeletalMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(SkeletalMeshSkin), *(SkeletalMeshSkinType::Name.ToString())));
					return false;
				}

				CS_IS_PTR_NULL(Component)

				Component->SetSkeletalMesh(Mesh);
				return true;
			}

			#undef SkeletalMeshSkinType

			bool FLibrary::SetSafeSkeletalMesh(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					return SetSafeSkeletalMesh(Context, SkeletalMeshSkin, Component, Log);
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(SkeletalMeshSkinType::Name.ToString())));
				return false;
			}

		#pragma endregion Skeletal Mesh

		// Mesh
		#pragma region

			void FLibrary::SetMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				// StaticMesh
				if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
				{
					SetStaticMeshAndMIDsChecked(Context, Skin, StaticMeshComponent, OutMIDs);
				}
				// SkeletalMesh
				else
				if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
				{
					SetSkeletalMeshAndMIDsChecked(Context, Skin, SkeletalMeshComponent, OutMIDs);
				}
				else
				{
					checkf(0, TEXT("%s: Component: %s with Class: %s is NOT supported."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));
				}
			}

			#define ResultType NCsSkin::NData::NVisual::FLibrary::FSetMeshAndMIDs::EResult
			ResultType FLibrary::SetMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* StaticMeshComponent, USkeletalMeshComponent* SkeletalMeshComponent, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, StaticMeshComponent);
					SetMaterialsChecked(Context, Skin, StaticMeshComponent, OutMIDs);
					return ResultType::StaticMeshComponent;
				}

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, SkeletalMeshComponent);
					SetMaterialsChecked(Context, Skin, SkeletalMeshComponent, OutMIDs);
					return ResultType::SkeletalMeshComponent;
				}
				checkf(0, TEXT("%s: Skin: %s does NOT implement the interfaces: %s or %s."), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString()), *(SkeletalMeshSkinType::Name.ToString()));
				return ResultType::None;
			}
			#undef ResultType

		#pragma endregion Mesh

		// Material
		#pragma region

			#define ResultType NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult

			ResultType FLibrary::SetMaterialsChecked(const FString& Context, const SkinType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				ResultType Result;

				// Material
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

				if (const MaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinDataType>(Context, Skin))
				{
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					MIDLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials(), OutMIDs);

					Result.bSuccess			= true;
					Result.Type				= FSetMaterials::ESkin::Material;
					Result.MaterialSkinData = const_cast<MaterialSkinDataType*>(MaterialSkin);
					return Result;
				}
				// MaterialWithParameters
				typedef NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters MaterialWithParamsSkinDataType;

				if (const MaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<MaterialWithParamsSkinDataType>(Context, Skin))
				{
					// Clear existing MIDs from OutMIDs
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					MIDLibrary::Destroy(OutMIDs);

					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					const int32 Count = Materials.Num();

					OutMIDs.Reset(FMath::Max(OutMIDs.Max(), Count));

					for (int32 I = 0; I < Count; ++I)
					{
						const MaterialType& Material   = Materials[I];
						UMaterialInstanceDynamic*& MID = OutMIDs.AddDefaulted_GetRef();

						Material.SetChecked(Context, Component, I, MID);
					}

					Result.bSuccess					  = true;
					Result.Type						  = FSetMaterials::ESkin::MaterialWithParameters;
					Result.MaterialWithParamsSkinData = const_cast<MaterialWithParamsSkinDataType*>(MaterialWithParamsSkin);
					return Result;
				}
				checkf(0, TEXT("%s: %s does NOT implement any material interface."), *Context, *PrintSkinAndClass(Skin));
				return Result;
			}

			ResultType FLibrary::SetSafeMaterials(const FString& Context, const SkinType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				ResultType Result;

				// Material
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

				if (const MaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinDataType>(Context, Skin))
				{
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (!MIDLibrary::SetSafe(Context, Component, MaterialSkin->GetMaterials(), OutMIDs, Log))
						return Result;

					Result.bSuccess			= true;
					Result.Type				= FSetMaterials::ESkin::Material;
					Result.MaterialSkinData = const_cast<MaterialSkinDataType*>(MaterialSkin);
					return Result;
				}
				// MaterialWithParameters
				typedef NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters MaterialWithParamsSkinDataType;

				if (const MaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<MaterialWithParamsSkinDataType>(Context, Skin))
				{
					// Clear existing MIDs from OutMIDs
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					MIDLibrary::Destroy(OutMIDs);

					typedef NCsMaterial::NInterface::FWithRangeParameters MaterialType;

					const TArray<MaterialType>& Materials = MaterialWithParamsSkin->GetMaterials();

					const int32 Count = Materials.Num();

					OutMIDs.Reset(FMath::Max(OutMIDs.Max(), Count));

					for (int32 I = 0; I < Count; ++I)
					{
						const MaterialType& Material   = Materials[I];
						UMaterialInstanceDynamic*& MID = OutMIDs.AddDefaulted_GetRef();

						if (!Material.SetSafe(Context, Component, I, MID, Log))
							return Result;
					}

					Result.bSuccess					  = true;
					Result.Type						  = FSetMaterials::ESkin::MaterialWithParameters;
					Result.MaterialWithParamsSkinData = const_cast<MaterialWithParamsSkinDataType*>(MaterialWithParamsSkin);
					return Result;
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement any material interface."), *Context, *PrintSkinAndClass(Skin)));
				return Result;
			}

			#undef ResultType

		#pragma endregion Material

		// Scale
		#pragma region

			void FLibrary::SetUniformScaleChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				const UniformScaleSkinType* UniformScaleSkin = GetInterfaceChecked<UniformScaleSkinType>(Context, Skin);

				CS_IS_PTR_NULL_CHECKED(Component)

				const float& UniformScale = UniformScaleSkin->GetUniformScale();

				CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

				Component->SetWorldScale3D(UniformScale * FVector3d::OneVector);
			}

			void FLibrary::SetUniformScaleRelativeChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				const UniformScaleSkinType* UniformScaleSkin = GetInterfaceChecked<UniformScaleSkinType>(Context, Skin);

				CS_IS_PTR_NULL_CHECKED(Component)

				const float& UniformScale = UniformScaleSkin->GetUniformScale();

				CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

				Component->SetRelativeScale3D(UniformScale * FVector3d::OneVector);
			}

			bool FLibrary::SetSafeUniformScaleRelative(const FString& Context, const SkinType* Skin, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				if (const UniformScaleSkinType* UniformScaleSkin = GetSafeInterfaceChecked<UniformScaleSkinType>(Context, Skin))
				{
					CS_IS_PTR_NULL(Component);

					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Component->SetRelativeScale3D(UniformScale * FVector3d::OneVector);
					return true;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s."), *Context, *PrintNameAndClass(Skin), *(UniformScaleSkinType::Name.ToString())));
					return false;
				}
			}

			bool FLibrary::SetSafeScaleRelative(const FString& Context, const SkinType* Skin, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				// Uniform
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				if (const UniformScaleSkinType* UniformScaleSkin = GetSafeInterfaceChecked<UniformScaleSkinType>(Context, Skin))
				{
					CS_IS_PTR_NULL(Component);

					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Component->SetRelativeScale3D(UniformScale * FVector3d::OneVector);
					return true;
				}
				// UniformRange
				typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange UniformRangeScaleSkinType;

				if (const UniformRangeScaleSkinType* UniformRangeScaleSkin = GetSafeInterfaceChecked<UniformRangeScaleSkinType>(Context, Skin))
				{
					CS_IS_PTR_NULL(Component);

					const float& Min = UniformRangeScaleSkin->GetMinUniformScale();
					const float& Max = UniformRangeScaleSkin->GetMaxUniformScale();

					CS_IS_FLOAT_GREATER_THAN(Min, 0.0f)
					CS_IS_FLOAT_GREATER_THAN(Max, 0.0f)

					if (Min == Max)
						Component->SetRelativeScale3D(Min * FVector3d::OneVector);
					else
						Component->SetRelativeScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
					return true;
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface related to scale."), *Context, *PrintNameAndClass(Skin)));
				return false;
			}

			void FLibrary::SetScaleChecked(const FString& Context, const SkinType* Skin, AActor* Actor)
			{
				CS_IS_PTR_NULL_CHECKED(Skin)
				CS_IS_PTR_NULL_CHECKED(Actor)

				// Uniform
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				if (const UniformScaleSkinType* UniformScaleSkin = GetSafeInterfaceChecked<UniformScaleSkinType>(Context, Skin))
				{
					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

					Actor->SetActorScale3D(UniformScale * FVector3d::OneVector);
					return;
				}
				// UniformRange
				typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange UniformRangeScaleSkinType;

				if (const UniformRangeScaleSkinType* UniformRangeScaleSkin = GetSafeInterfaceChecked<UniformRangeScaleSkinType>(Context, Skin))
				{
					const float& Min = UniformRangeScaleSkin->GetMinUniformScale();
					const float& Max = UniformRangeScaleSkin->GetMaxUniformScale();

					CS_IS_FLOAT_GREATER_THAN_CHECKED(Min, 0.0f)
					CS_IS_FLOAT_GREATER_THAN_CHECKED(Max, 0.0f)

					if (Min == Max)
						Actor->SetActorScale3D(Min * FVector3d::OneVector);
					else
						Actor->SetActorScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
					return;
				}
				checkf(0, TEXT("%s: Skin: %s does NOT implement the interface related to scale."), *Context, *PrintNameAndClass(Skin));
			}

			bool FLibrary::SetSafeScale(const FString& Context, const SkinType* Skin, AActor* Actor, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Skin)
				CS_IS_PTR_NULL(Actor)

				// Uniform
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				if (const UniformScaleSkinType* UniformScaleSkin = GetSafeInterfaceChecked<UniformScaleSkinType>(Context, Skin))
				{
					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Actor->SetActorScale3D(UniformScale * FVector3d::OneVector);
					return true;
				}
				// UniformRange
				typedef NCsSkin::NData::NVisual::NScale::NUniform::NRange::IRange UniformRangeScaleSkinType;

				if (const UniformRangeScaleSkinType* UniformRangeScaleSkin = GetSafeInterfaceChecked<UniformRangeScaleSkinType>(Context, Skin))
				{
					const float& Min = UniformRangeScaleSkin->GetMinUniformScale();
					const float& Max = UniformRangeScaleSkin->GetMaxUniformScale();

					CS_IS_FLOAT_GREATER_THAN(Min, 0.0f)
					CS_IS_FLOAT_GREATER_THAN(Max, 0.0f)

					if (Min == Max)
						Actor->SetActorScale3D(Min * FVector3d::OneVector);
					else
						Actor->SetActorScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector3d::OneVector);
					return true;
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface related to scale."), *Context, *PrintNameAndClass(Skin)));
				return false;
			}

		#pragma endregion Scale

		#undef SkinType
		}
	}
}