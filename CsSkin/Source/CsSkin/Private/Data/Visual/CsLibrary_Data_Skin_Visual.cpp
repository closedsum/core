// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsLibrary_Data_Skin_Visual.h"

// Types
#include "CsMacro_Misc.h"
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
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Engine
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"

using LogClassType = NCsSkin::FLog;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);
	
			using StaticMeshSkinDataType = NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh;
			using SkeletalMeshSkinDataType = NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh;
			using MaterialSkinDataType = NCsSkin::NData::NVisual::NMaterial::IMaterial;

			using SetMeshAndMIDsResultType = NCsSkin::NData::NVisual::FLibrary::FSetMeshAndMIDs::EResult;
			using SetMaterialsResultType = NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult;

			FString FLibrary::PrintObjectAndClass(const CsSkinDataType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("Object: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintNameAndClass(const CsSkinDataType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintSkinAndClass(const CsSkinDataType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("Skin: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintNameAndClass(const CsStaticMeshSkinDataType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintNameAndClass(const CsSkeletalMeshSkinDataType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			bool FLibrary::IsValidChecked(const FString& Context, const CsSkinDataType* Skin)
			{
				CS_IS_PTR_NULL_CHECKED(Skin)

				// Material
				const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin);

				if (MaterialSkin)
				{
					check(CsMaterialLibrary::IsValidChecked(Context, MaterialSkin->GetMaterials()));
				}
				// MaterialWithParameters
				const CsMaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<CsMaterialWithParamsSkinDataType>(Context, Skin);

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
				const CsStaticMeshSkinDataType* StaticMeshSkin = GetSafeInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin);

				if (StaticMeshSkin)
				{
					checkf(StaticMeshSkin->GetStaticMesh(), TEXT("%s: Skin->GetStaticMesh() is NULL for Skin implementing interface: %s."), *Context, *(CsStaticMeshSkinDataType::Name.ToString()));
				}
				// SkeletalMesh
				const CsSkeletalMeshSkinDataType* SkeletalMeshSkin = GetSafeInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin);

				if (SkeletalMeshSkin)
				{
					checkf(SkeletalMeshSkin->GetSkeletalMesh(), TEXT("%s: Skin->GetSkeletalMesh() is NULL for Skin implementing interface: %s."), *Context, *(CsSkeletalMeshSkinDataType::Name.ToString()));
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
				if (const CsUniformScaleSkinDataType* UniformScaleSkinData = GetSafeInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScaleSkinData->GetUniformScale(), 0.0f)
				}

				// UniformRangeScale
				if (const CsUniformRangeScaleSkinDataType* UniformRangeScaleSkinData = GetSafeInterfaceChecked<CsUniformRangeScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformRangeScaleSkinData->GetMinUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformRangeScaleSkinData->GetMaxUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(UniformRangeScaleSkinData->GetMaxUniformScale(), UniformRangeScaleSkinData->GetMinUniformScale())
				}

				// TODO: Attachments
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const CsSkinDataType* Skin, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL(Skin)

				// Material
				const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin);

				if (MaterialSkin)
				{
					if (!CsMaterialLibrary::IsValid(Context, MaterialSkin->GetMaterials(), Log))
						return false;
				}
				// MaterialWithParameters
				const CsMaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<CsMaterialWithParamsSkinDataType>(Context, Skin);

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
				const CsStaticMeshSkinDataType* StaticMeshSkin = GetSafeInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin);

				if (StaticMeshSkin)
				{
					if (!StaticMeshSkin->GetStaticMesh())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetStaticMesh() is NULL for Skin implementing interface: %s."), *Context, *(CsStaticMeshSkinDataType::Name.ToString())));
						return false;
					}
				}
				// SkeletalMesh
				const CsSkeletalMeshSkinDataType* SkeletalMeshSkin = GetSafeInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin);

				if (SkeletalMeshSkin)
				{
					if (!SkeletalMeshSkin->GetSkeletalMesh())
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin->GetSkeletalMesh() is NULL for Skin implementing interface: %s."), *Context, *(CsSkeletalMeshSkinDataType::Name.ToString())));
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
				if (const CsUniformScaleSkinDataType* UniformScaleSkinData = GetSafeInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN(UniformScaleSkinData->GetUniformScale(), 0.0f)
				}

				// UniformRangeScale
				if (const CsUniformRangeScaleSkinDataType* UniformRangeScaleSkinData = GetSafeInterfaceChecked<CsUniformRangeScaleSkinDataType>(Context, Skin))
				{
					CS_IS_FLOAT_GREATER_THAN(UniformRangeScaleSkinData->GetMinUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN(UniformRangeScaleSkinData->GetMaxUniformScale(), 0.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(UniformRangeScaleSkinData->GetMaxUniformScale(), UniformRangeScaleSkinData->GetMinUniformScale())
				}
				return true;
			}

			ICsDeconstructInterfaceSliceMap* FLibrary::GetSafeDeconstructInterfaceSliceMap(const FString& Context, CsSkinDataType* Skin, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

			bool FLibrary::ImplementsStaticMeshSkinType(const FString& Context, const CsSkinDataType* Skin)
			{
				if (GetSafeInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetStaticMeshAndMaterialsChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component)
			{
				SetStaticMeshChecked(Context, Skin, Component);

				// Materials
				const CsMaterialSkinDataType* MaterialSkin = GetInterfaceChecked<CsMaterialSkinDataType>(Context, Skin);

				CsMaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMaterials(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (const CsStaticMeshSkinDataType* StaticMeshSkin = GetSafeInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);

					// Materials
					if (const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin))
					{
						CsMaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s."), *Context, *PrintNameAndClass(Skin), *(CsMaterialSkinDataType::Name.ToString())));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(CsStaticMeshSkinDataType::Name.ToString())));
				}
			}

			void FLibrary::SetStaticMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				SetStaticMeshChecked(Context, Skin, Component);
				SetMaterialsChecked(Context, Skin, Component, OutMIDs);
			}

			bool FLibrary::SetSafeStaticMeshAndMIDs(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (!SetSafeStaticMesh(Context, Skin, Component, Log))
					return false;

				typedef NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult ResultType;

				ResultType Result = SetSafeMaterials(Context, Skin, Component, OutMIDs, Log);
				return Result.bSuccess;
			}

			void FLibrary::SetStaticMeshChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component)
			{
				SetStaticMeshChecked(Context, GetInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin), Component);
			}

			void FLibrary::SetStaticMeshChecked(const FString& Context, const StaticMeshSkinDataType* StaticMeshSkin, UStaticMeshComponent* Component)
			{
				CS_IS_PTR_NULL_CHECKED(StaticMeshSkin)

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(StaticMeshSkin), *(CsStaticMeshSkinDataType::Name.ToString()));

				CS_IS_PTR_NULL_CHECKED(Component)

				Component->SetStaticMesh(Mesh);
			}

			bool FLibrary::SetSafeStaticMesh(const FString& Context, const StaticMeshSkinDataType* StaticMeshSkin, UStaticMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL(StaticMeshSkin)

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				if (!Mesh)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get StaticMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(StaticMeshSkin), *(CsStaticMeshSkinDataType::Name.ToString())));
					return false;
				}

				CS_IS_PTR_NULL(Component)

				Component->SetStaticMesh(Mesh);
				return true;
			}

			bool FLibrary::SetSafeStaticMesh(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (const CsStaticMeshSkinDataType* StaticMeshSkin = GetSafeInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin))
				{
					return SetSafeStaticMesh(Context, StaticMeshSkin, Component, Log);
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(CsStaticMeshSkinDataType::Name.ToString())));
				return false;
			}

		// Attachment
		#pragma region

			int32 FLibrary::GetNumAttachmentsChecked(const FString& Context, const UObject* WorldContext, const CsSkinDataType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment AttachmentSkinType;
				typedef NCsStaticMesh::NAttachment::FAttachment AttachmentType;

				const AttachmentSkinType* AttachmentSkin  = GetInterfaceChecked<AttachmentSkinType>(Context, Skin);
				const TArray<AttachmentType>& Attachments = AttachmentSkin->GetStaticMeshAttachments();

				return Attachments.Num();
			}

		#pragma endregion Attachment

		#pragma endregion Static Mesh

		// Skeletal Mesh
		#pragma region

			bool FLibrary::ImplementsSkeletalMeshSkinType(const FString& Context, const CsSkinDataType* Skin)
			{
				if (GetSafeInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetSkeletalMeshAndMaterialsChecked(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component)
			{	
				SetSkeletalMeshChecked(Context, Skin, Component);

				// Material
				if (const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin))
				{
					CsMaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					return;
				}
				// MaterialWithParameters
				if (const CsMaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<CsMaterialWithParamsSkinDataType>(Context, Skin))
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

			bool FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (const CsSkeletalMeshSkinDataType* SkeletalMeshSkin = GetSafeInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);

					// Material
					if (const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin))
					{
						return CsMaterialLibrary::SetSafe(Context, Component, MaterialSkin->GetMaterials());
					}
					// MaterialWithParameters
					if (const CsMaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<CsMaterialWithParamsSkinDataType>(Context, Skin))
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
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(CsSkeletalMeshSkinDataType::Name.ToString())));
				return false;
			}

			void FLibrary::SetSkeletalMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				SetSkeletalMeshChecked(Context, Skin, Component);
				SetMaterialsChecked(Context, Skin, Component, OutMIDs);
			}

			bool FLibrary::SetSafeSkeletalMeshAndMIDs(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (!SetSafeSkeletalMesh(Context, Skin, Component, Log))
					return false;

				typedef NCsSkin::NData::NVisual::FLibrary::FSetMaterials::FResult ResultType;

				ResultType Result = SetSafeMaterials(Context, Skin, Component, OutMIDs, Log);
				return Result.bSuccess;
			}

			void FLibrary::SetSkeletalMeshChecked(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component)
			{
				SetSkeletalMeshChecked(Context, GetInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin), Component);
			}

			void FLibrary::SetSkeletalMeshChecked(const FString& Context, const SkeletalMeshSkinDataType* SkeletalMeshSkin, USkeletalMeshComponent* Component)
			{
				CS_IS_PTR_NULL_CHECKED(SkeletalMeshSkin)

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(SkeletalMeshSkin), *(CsSkeletalMeshSkinDataType::Name.ToString()));

				CS_IS_PTR_NULL_CHECKED(Component)

				Component->SetSkeletalMesh(Mesh);
			}

			bool FLibrary::SetSafeSkeletalMesh(const FString& Context, const SkeletalMeshSkinDataType* SkeletalMeshSkin, USkeletalMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL(SkeletalMeshSkin)

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				if (!Mesh)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get SkeletalMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(SkeletalMeshSkin), *(CsSkeletalMeshSkinDataType::Name.ToString())));
					return false;
				}

				CS_IS_PTR_NULL(Component)

				Component->SetSkeletalMesh(Mesh);
				return true;
			}

			bool FLibrary::SetSafeSkeletalMesh(const FString& Context, const CsSkinDataType* Skin, USkeletalMeshComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (const CsSkeletalMeshSkinDataType* SkeletalMeshSkin = GetSafeInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin))
				{
					return SetSafeSkeletalMesh(Context, SkeletalMeshSkin, Component, Log);
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(CsSkeletalMeshSkinDataType::Name.ToString())));
				return false;
			}

		#pragma endregion Skeletal Mesh

		// Mesh
		#pragma region

			void FLibrary::SetMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
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

			SetMeshAndMIDsResultType FLibrary::SetMeshAndMIDsChecked(const FString& Context, const CsSkinDataType* Skin, UStaticMeshComponent* StaticMeshComponent, USkeletalMeshComponent* SkeletalMeshComponent, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				if (const CsStaticMeshSkinDataType* StaticMeshSkin = GetSafeInterfaceChecked<CsStaticMeshSkinDataType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, StaticMeshComponent);
					SetMaterialsChecked(Context, Skin, StaticMeshComponent, OutMIDs);
					return SetMeshAndMIDsResultType::StaticMeshComponent;
				}

				if (const CsSkeletalMeshSkinDataType* SkeletalMeshSkin = GetSafeInterfaceChecked<CsSkeletalMeshSkinDataType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, SkeletalMeshComponent);
					SetMaterialsChecked(Context, Skin, SkeletalMeshComponent, OutMIDs);
					return SetMeshAndMIDsResultType::SkeletalMeshComponent;
				}
				checkf(0, TEXT("%s: Skin: %s does NOT implement the interfaces: %s or %s."), *Context, *PrintNameAndClass(Skin), *(CsStaticMeshSkinDataType::Name.ToString()), *(CsSkeletalMeshSkinDataType::Name.ToString()));
				return SetMeshAndMIDsResultType::None;
			}

		#pragma endregion Mesh

		// Material
		#pragma region

			SetMaterialsResultType FLibrary::SetMaterialsChecked(const FString& Context, const CsSkinDataType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs)
			{
				SetMaterialsResultType Result;

				// Material
				if (const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin))
				{
					CsMIDLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials(), OutMIDs);

					Result.bSuccess			= true;
					Result.Type				= FSetMaterials::ESkin::Material;
					Result.MaterialSkinData = const_cast<CsMaterialSkinDataType*>(MaterialSkin);
					return Result;
				}
				// MaterialWithParameters
				if (const CsMaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<CsMaterialWithParamsSkinDataType>(Context, Skin))
				{
					// Clear existing MIDs from OutMIDs
					CsMIDLibrary::Destroy(OutMIDs);

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
					Result.MaterialWithParamsSkinData = const_cast<CsMaterialWithParamsSkinDataType*>(MaterialWithParamsSkin);
					return Result;
				}
				checkf(0, TEXT("%s: %s does NOT implement any material interface."), *Context, *PrintSkinAndClass(Skin));
				return Result;
			}

			SetMaterialsResultType FLibrary::SetSafeMaterials(const FString& Context, const CsSkinDataType* Skin, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				SetMaterialsResultType Result;

				// Material
				if (const CsMaterialSkinDataType* MaterialSkin = GetSafeInterfaceChecked<CsMaterialSkinDataType>(Context, Skin))
				{
					if (!CsMIDLibrary::SetSafe(Context, Component, MaterialSkin->GetMaterials(), OutMIDs, Log))
						return Result;

					Result.bSuccess			= true;
					Result.Type				= FSetMaterials::ESkin::Material;
					Result.MaterialSkinData = const_cast<CsMaterialSkinDataType*>(MaterialSkin);
					return Result;
				}
				// MaterialWithParameters
				if (const CsMaterialWithParamsSkinDataType* MaterialWithParamsSkin = GetSafeInterfaceChecked<CsMaterialWithParamsSkinDataType>(Context, Skin))
				{
					// Clear existing MIDs from OutMIDs
					CsMIDLibrary::Destroy(OutMIDs);

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
					Result.MaterialWithParamsSkinData = const_cast<CsMaterialWithParamsSkinDataType*>(MaterialWithParamsSkin);
					return Result;
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT implement any material interface."), *Context, *PrintSkinAndClass(Skin)));
				return Result;
			}

		#pragma endregion Material

		// Scale
		#pragma region

			void FLibrary::SetUniformScaleChecked(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component)
			{
				const CsUniformScaleSkinDataType* UniformScaleSkin = GetInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin);

				CS_IS_PTR_NULL_CHECKED(Component)

				const float& UniformScale = UniformScaleSkin->GetUniformScale();

				CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

				Component->SetWorldScale3D(UniformScale * FVector3d::OneVector);
			}

			void FLibrary::SetUniformScaleRelativeChecked(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component)
			{
				const CsUniformScaleSkinDataType* UniformScaleSkin = GetInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin);

				CS_IS_PTR_NULL_CHECKED(Component)

				const float& UniformScale = UniformScaleSkin->GetUniformScale();

				CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

				Component->SetRelativeScale3D(UniformScale * FVector3d::OneVector);
			}

			bool FLibrary::SetSafeUniformScaleRelative(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (const CsUniformScaleSkinDataType* UniformScaleSkin = GetSafeInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_PTR_NULL(Component);

					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Component->SetRelativeScale3D(UniformScale * FVector3d::OneVector);
					return true;
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s."), *Context, *PrintNameAndClass(Skin), *(CsUniformScaleSkinDataType::Name.ToString())));
					return false;
				}
			}

			bool FLibrary::SetSafeScaleRelative(const FString& Context, const CsSkinDataType* Skin, USceneComponent* Component, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				// Uniform
				if (const CsUniformScaleSkinDataType* UniformScaleSkin = GetSafeInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin))
				{
					CS_IS_PTR_NULL(Component);

					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Component->SetRelativeScale3D(UniformScale * FVector3d::OneVector);
					return true;
				}
				// UniformRange
				if (const CsUniformRangeScaleSkinDataType* UniformRangeScaleSkin = GetSafeInterfaceChecked<CsUniformRangeScaleSkinDataType>(Context, Skin))
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

			void FLibrary::SetScaleChecked(const FString& Context, const CsSkinDataType* Skin, AActor* Actor)
			{
				CS_IS_PTR_NULL_CHECKED(Skin)
				CS_IS_PTR_NULL_CHECKED(Actor)

				// Uniform
				if (const CsUniformScaleSkinDataType* UniformScaleSkin = GetSafeInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin))
				{
					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN_CHECKED(UniformScale, 0.0f)

					Actor->SetActorScale3D(UniformScale * FVector3d::OneVector);
					return;
				}
				// UniformRange
				if (const CsUniformRangeScaleSkinDataType* UniformRangeScaleSkin = GetSafeInterfaceChecked<CsUniformRangeScaleSkinDataType>(Context, Skin))
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

			bool FLibrary::SetSafeScale(const FString& Context, const CsSkinDataType* Skin, AActor* Actor, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL(Skin)
				CS_IS_PTR_NULL(Actor)

				// Uniform
				if (const CsUniformScaleSkinDataType* UniformScaleSkin = GetSafeInterfaceChecked<CsUniformScaleSkinDataType>(Context, Skin))
				{
					const float& UniformScale = UniformScaleSkin->GetUniformScale();

					CS_IS_FLOAT_GREATER_THAN(UniformScale, 0.0f)

					Actor->SetActorScale3D(UniformScale * FVector3d::OneVector);
					return true;
				}
				// UniformRange
				if (const CsUniformRangeScaleSkinDataType* UniformRangeScaleSkin = GetSafeInterfaceChecked<CsUniformRangeScaleSkinDataType>(Context, Skin))
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
		}
	}
}