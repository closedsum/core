// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsLibrary_Data_Skin_Visual.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsDeconstructInterfaceSliceMap.h"
// Data
#include "Skin/Data/Visual/CsData_Skin_VisualInterfaceMap.h"
#include "Skin/Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterial.h"
#include "Skin/Data/Visual/Scale/CsData_Skin_VisualUniformScale.h"
#include "Skin/Data/Visual/Scale/CsData_Skin_VisualScale_UniformRange.h"
#include "Skin/Data/Visual/StaticMesh/Attachment/CsData_Skin_VisualStaticMesh_Attachment.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

				// MaterialSkinType
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin);

				if (MaterialSkin)
				{
					check(MaterialLibrary::IsValidChecked(Context, MaterialSkin->GetMaterials()));
				}
				// StaticMeshSkin

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				if (StaticMeshSkin)
				{
					checkf(StaticMeshSkin->GetStaticMesh(), TEXT("%s: Skin->GetStaticMesh() is NULL for Skin implementing interface: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));
				}
				// SkeletalMeshSkin
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

					checkf(Materials.Num() == Mesh->StaticMaterials.Num(), TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->StaticMaterials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->StaticMaterials.Num());
				}

				// NOTE: For now this seems reasonable to check
				if (MaterialSkin &&
					SkeletalMeshSkin)
				{
					USkeletalMesh* Mesh							 = SkeletalMeshSkin->GetSkeletalMesh();
					const TArray<UMaterialInterface*>& Materials = MaterialSkin->GetMaterials();

					checkf(Materials.Num() == Mesh->Materials.Num(), TEXT("%s: Skin->GetMaterials().Num() != Skin->GetSkeletalMesh()->Materials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->Materials.Num());
				}

				// UniformScale
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinDataType;

				if (const UniformScaleSkinDataType* UniformScaleSkinData = GetSafeInterfaceChecked<UniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScaleSkinData->GetUniformScale(), 0.0f)
				}
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const SkinType* Skin, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Skin)

				// MaterialSkinType
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin);

				if (MaterialSkin)
				{
					if (MaterialLibrary::IsValid(Context, MaterialSkin->GetMaterials(), Log))
						return false;
				}
				// StaticMeshSkin

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
				// SkeletalMeshSkin
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

					if (Materials.Num() != Mesh->StaticMaterials.Num())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetMaterials().Num() != Skin->GetStaticMesh()->StaticMaterials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->StaticMaterials.Num()));
						return false;
					}
				}

				// NOTE: For now this seems reasonable to check
				if (MaterialSkin &&
					SkeletalMeshSkin)
				{
					USkeletalMesh* Mesh							 = SkeletalMeshSkin->GetSkeletalMesh();
					const TArray<UMaterialInterface*>& Materials = MaterialSkin->GetMaterials();

					if (Materials.Num() != Mesh->Materials.Num())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetMaterials().Num() != Skin->GetSkeletalMesh()->Materials.Num() (%d != %d)."), *Context, Materials.Num(), Mesh->Materials.Num()));
						return false;
					}
				}

				// UniformScale
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinDataType;

				if (const UniformScaleSkinDataType* UniformScaleSkinData = GetSafeInterfaceChecked<UniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN(UniformScaleSkinData->GetUniformScale(), 0.0f)
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

			void FLibrary::SetStaticMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetStaticMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				const MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMIDs(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
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
			#undef StaticMeshSkinType

			void FLibrary::SetSafeStaticMesh(const FString& Context, const SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString())));
				}
			}

			// Attachment
		#pragma region

			void FLibrary::SetAttachmentsChecked(const FString& Context, const UObject* WorldContext, const SkinType* Skin, USceneComponent* Component, TArray<FCsStaticMeshActorPooled*>& OutAttachments)
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

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				const MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(MaterialSkinType::Name.ToString())));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(SkeletalMeshSkinType::Name.ToString())));
				}
			}

			void FLibrary::SetSkeletalMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetSkeletalMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				const MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMIDs(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (const MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(MaterialSkinType::Name.ToString())));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(SkeletalMeshSkinType::Name.ToString())));
				}
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
			#undef SkeletalMeshSkinType

			void FLibrary::SetSafeSkeletalMesh(const FString& Context, const SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(SkeletalMeshSkinType::Name.ToString())));
				}
			}

		#pragma endregion Skeletal Mesh

		// Mesh
		#pragma region

			void FLibrary::SetMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				// StaticMesh
				if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
				{
					SetStaticMeshAndMIDsChecked(Context, Skin, StaticMeshComponent, MIDs);
				}
				// SkeletalMesh
				else
				if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
				{
					SetSkeletalMeshAndMIDsChecked(Context, Skin, SkeletalMeshComponent, MIDs);
				}
				else
				{
					checkf(0, TEXT("%s: Component: %s with Class: %s is NOT supported."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));
				}
			}

			#define ResultType NCsSkin::NData::NVisual::FLibrary::FSetMeshAndMIDs::EResult
			ResultType FLibrary::SetMeshAndMIDsChecked(const FString& Context, const SkinType* Skin, UStaticMeshComponent* StaticMeshComponent, USkeletalMeshComponent* SkeletalMeshComponent, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (const StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, StaticMeshComponent);
					SetMaterialsChecked(Context, Skin, StaticMeshComponent, MIDs);
					return ResultType::StaticMeshComponent;
				}

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (const SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, SkeletalMeshComponent);
					SetMaterialsChecked(Context, Skin, SkeletalMeshComponent, MIDs);
					return ResultType::SkeletalMeshComponent;
				}
				checkf(0, TEXT("%s: Skin: %s does NOT implement the interfaces: %s or %s."), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString()), *(SkeletalMeshSkinType::Name.ToString()));
				return ResultType::None;
			}
			#undef ResultType

		#pragma endregion Mesh

		// Material
		#pragma region

			#define MaterialSkinDataType NCsSkin::NData::NVisual::NMaterial::IMaterial
			MaterialSkinDataType* FLibrary::SetMaterialsChecked(const FString& Context, const SkinType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				const MaterialSkinDataType* MaterialSkin = GetInterfaceChecked<MaterialSkinDataType>(Context, Skin);

				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());

				return const_cast<MaterialSkinDataType*>(MaterialSkin);
			}
			#undef MaterialSkinDataType

		#pragma endregion Material

		// Scale
		#pragma region

			void FLibrary::SetUniformScaleRelativeChecked(const FString& Context, const SkinType* Skin, USceneComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				const UniformScaleSkinType* UniformScaleSkin = GetInterfaceChecked<UniformScaleSkinType>(Context, Skin);

				CS_IS_PTR_NULL_CHECKED(Component)

				const float& UniformScale = UniformScaleSkin->GetUniformScale();

				CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

				Component->SetRelativeScale3D(UniformScale * FVector::OneVector);
			}

			bool FLibrary::SetSafeUniformScaleRelative(const FString& Context, const SkinType* Skin, USceneComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NScale::NUniform::IUniform UniformScaleSkinType;

				if (const UniformScaleSkinType* UniformScaleSkin = GetSafeInterfaceChecked<UniformScaleSkinType>(Context, Skin))
				{
					CS_IS_PTR_NULL(Component);

					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Component->SetRelativeScale3D(UniformScale * FVector::OneVector);
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

					Component->SetRelativeScale3D(UniformScale * FVector::OneVector);
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
						Component->SetRelativeScale3D(Min * FVector::OneVector);
					else
						Component->SetRelativeScale3D(FMath::Lerp(Min, Max, FMath::RandRange(0.0f, 1.0f)) * FVector::OneVector);
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