// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsLibrary_Data_Skin_Visual.h"

// Library
#include "Material/CsLibrary_Material.h"
// Data
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

			bool FLibrary::IsValidChecked(const FString& Context, SkinType* Skin)
			{
				checkf(Skin, TEXT("%s: Skin is NULL."), *Context);

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

		// Static Mesh
		#pragma region

			bool FLibrary::ImplementsStaticMeshSkinType(const FString& Context, SkinType* Skin)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
					return true;
				return false;
			}

			void FLibrary::SetStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				SetStaticMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMaterials(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMesh(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetStaticMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeStaticMeshAndMIDs(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMesh(Context, StaticMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				StaticMeshSkinType* StaticMeshSkin = GetInterfaceChecked<StaticMeshSkinType>(Context, Skin);

				SetStaticMesh(Context, StaticMeshSkin, Component);
			}

			#define StaticMeshSkinType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
			void FLibrary::SetStaticMesh(const FString& Context, StaticMeshSkinType* StaticMeshSkin, UStaticMeshComponent* Component)
			{
				checkf(StaticMeshSkin, TEXT("%s: StaticMeshSkin is NULL."), *Context);

				UStaticMesh* Mesh = StaticMeshSkin->GetStaticMesh();

				checkf(Mesh, TEXT("%s: Failed to get StaticMesh from Skin of type: %s."), *Context, *(StaticMeshSkinType::Name.ToString()));

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				Component->SetStaticMesh(Mesh);
			}
			#undef StaticMeshSkinType

			void FLibrary::SetSafeStaticMesh(const FString& Context, SkinType* Skin, UStaticMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinType;

				if (StaticMeshSkinType* StaticMeshSkin = GetSafeInterfaceChecked<StaticMeshSkinType>(Context, Skin))
				{
					SetStaticMesh(Context, StaticMeshSkin, Component);
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

			void FLibrary::SetSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{	
				SetSkeletalMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::FLibrary MaterialLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMaterials(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMesh(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::FLibrary MaterialLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MaterialLibrary::SetChecked(Context, Component, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetSkeletalMeshAndMIDs(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				SetSkeletalMesh(Context, Skin, Component);

				// Materials
				typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
				typedef NCsMaterial::NMID::FLibrary MIDLibrary;

				MaterialSkinType* MaterialSkin = GetInterfaceChecked<MaterialSkinType>(Context, Skin);

				MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
			}

			void FLibrary::SetSafeSkeletalMeshAndMIDs(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMesh(Context, SkeletalMeshSkin, Component);

					// Materials
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinType;
					typedef NCsMaterial::NMID::FLibrary MIDLibrary;

					if (MaterialSkinType* MaterialSkin = GetSafeInterfaceChecked<MaterialSkinType>(Context, Skin))
					{
						MIDLibrary::SetChecked(Context, Component, MIDs, MaterialSkin->GetMaterials());
					}
				}
			}

			void FLibrary::SetSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				SkeletalMeshSkinType* SkeletalMeshSkin = GetInterfaceChecked<SkeletalMeshSkinType>(Context, Skin);

				SetSkeletalMesh(Context, SkeletalMeshSkin, Component);
			}

			#define SkeletalMeshSkinType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
			void FLibrary::SetSkeletalMesh(const FString& Context, SkeletalMeshSkinType* SkeletalMeshSkin, USkeletalMeshComponent* Component)
			{
				checkf(SkeletalMeshSkin, TEXT("%s: SkeletalMeshSkin is nULL."));

				USkeletalMesh* Mesh = SkeletalMeshSkin->GetSkeletalMesh();

				checkf(Mesh, TEXT("%s: Failed to get SkeletalMesh from Skin of type: %s."), *Context, *(SkeletalMeshSkinType::Name.ToString()));

				checkf(Component, TEXT("%s: Component is NULL."), *Context);

				Component->SetSkeletalMesh(Mesh);
			}
			#undef SkeletalMeshSkinType

			void FLibrary::SetSafeSkeletalMesh(const FString& Context, SkinType* Skin, USkeletalMeshComponent* Component)
			{
				typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinType;

				if (SkeletalMeshSkinType* SkeletalMeshSkin = GetSafeInterfaceChecked<SkeletalMeshSkinType>(Context, Skin))
				{
					SetSkeletalMesh(Context, SkeletalMeshSkin, Component);
				}
			}

		#pragma endregion Skeletal Mesh

		// Mesh
		#pragma region

			void FLibrary::SetMeshAndMIDs(const FString& Context, SkinType* Skin, USceneComponent* Component, TArray<UMaterialInstanceDynamic*>& MIDs)
			{
				// StaticMesh
				if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
				{
					SetStaticMeshAndMIDs(Context, Skin, StaticMeshComponent, MIDs);
				}
				// SkeletalMesh
				else
				if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
				{
					SetSkeletalMeshAndMIDs(Context, Skin, SkeletalMeshComponent, MIDs);
				}
				else
				{
					checkf(0, TEXT("%s: Component: %s with Class: %s is NOT supported."), *Context, *(Component->GetName()), *(Component->GetClass()->GetName()));
				}
			}

		#pragma endregion Mesh

		#undef SkinType
		}
	}
}