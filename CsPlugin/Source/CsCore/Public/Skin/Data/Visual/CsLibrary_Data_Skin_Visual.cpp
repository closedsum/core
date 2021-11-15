// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

			FString FLibrary::PrintObjectAndClass(SkinType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("Object: %s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			FString FLibrary::PrintNameAndClass(SkinType* Skin)
			{
				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
			FString FLibrary::PrintNameAndClass(StaticMeshSkinType* Skin)
			{
			#undef StaticMeshSkinType

				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
			FString FLibrary::PrintNameAndClass(SkeletalMeshSkinType* Skin)
			{
			#undef SkeletalMeshSkinType

				if (UObject* O = Skin->_getUObject())
					return FString::Printf(TEXT("%s with Class: %s"), *(O->GetName()), *(O->GetClass()->GetName()));
				return FString::Printf(TEXT("INVALID (Non-UObject)"));
			}

			bool FLibrary::IsValidChecked(const FString& Context, SkinType* Skin)
			{
				CS_IS_PTR_NULL_CHECKED(Skin)

				// MaterialSkinType
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin);

				if (MaterialSkin)
				{
					check(MaterialLibrary::IsValidChecked(Context, MaterialSkin->GetMaterials()));
				}
				// StaticMeshSkin

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				if (StaticMeshSkin)
				{
					checkf(StaticMeshSkin->GetStaticMesh(), TEXT("%s: Skin->GetStaticMesh() is NULL for Skin implementing interface: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));
				}
				// SkeletalMeshSkin
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

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
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, SkinType* Skin, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_PTR_NULL(Skin)

				// MaterialSkinType
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin);

				if (MaterialSkin)
				{
					if (MaterialLibrary::IsValid(Context, MaterialSkin->GetMaterials(), Log))
						return false;
				}
				// StaticMeshSkin

				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin);

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

				SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

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

			bool FLibrary::ImplementsStaticMeshSkinType(const FString& Context, SkinType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetStaticMeshAndMaterialsChecked(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				SetStaticMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
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

			void FLibrary::SetStaticMeshAndMIDsChecked(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetStaticMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
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

			void FLibrary::SetStaticMeshChecked(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				SetStaticMeshChecked(Context, StaticMeshSkin, Component);
			}

			#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
			void FLibrary::SetStaticMeshChecked(const FString& Context, StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component)
			{
				CS_IS_PTR_NULL_CHECKED(StaticMeshSkin)

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(StaticMeshSkin), *(StaticMeshSkinType::Name.ToString()));

				CS_IS_PTR_NULL_CHECKED(Component)

				Component->SetStaticMesh(Mesh);
			}
			#undef StaticMeshSkinType

			void FLibrary::SetSafeStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, Component);
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Skin: %s does NOT implement the interface: %s"), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString())));
				}
			}

		#pragma endregion Static Mesh

		// Skeletal Mesh
		#pragma region

			bool FLibrary::ImplementsSkeletalMeshSkinType(const FString& Context, SkinType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetSkeletalMeshAndMaterialsChecked(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{	
				SetSkeletalMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
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

			void FLibrary::SetSkeletalMeshAndMIDsChecked(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetSkeletalMeshChecked(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMIDs(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
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

			void FLibrary::SetSkeletalMeshChecked(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				SkeletalMeshSkinType* SkeletalMeshSkin = GetInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				SetSkeletalMeshChecked(Context, SkeletalMeshSkin, Component);
			}

			#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
			void FLibrary::SetSkeletalMeshChecked(const FString& Context, SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component)
			{
				CS_IS_PTR_NULL_CHECKED(SkeletalMeshSkin)

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin: %s of type: %s."), *Context, *PrintNameAndClass(SkeletalMeshSkin), *(SkeletalMeshSkinType::Name.ToString()));

				CS_IS_PTR_NULL_CHECKED(Component)

				Component->SetSkeletalMesh(Mesh);
			}
			#undef SkeletalMeshSkinType

			void FLibrary::SetSafeSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
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

			void FLibrary::SetMeshAndMIDsChecked(const FString& Context, SkinType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
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

			void FLibrary::SetMeshAndMIDsChecked(const FString& Context, SkinType* Skin, UStaticMeshComponent* StaticMeshComponent, USkeletalMeshComponent* SkeletalMeshComponent, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMeshChecked(Context, StaticMeshSkin, StaticMeshComponent);
					return;
				}

				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMeshChecked(Context, SkeletalMeshSkin, SkeletalMeshComponent);
					return;
				}
				checkf(0, TEXT("%s: Skin: %s does NOT implement the interfaces: %s or %s."), *Context, *PrintNameAndClass(Skin), *(StaticMeshSkinType::Name.ToString()), *(SkeletalMeshSkinType::Name.ToString()));
			}

		#pragma endregion Mesh

		#undef SkinType
		}
	}
}