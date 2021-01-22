// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Material.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Mesh
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Material
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

namespace NCsMaterial
{
	void FLibrary::SetMaterialChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
	{
		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		checkf(Material, TEXT("%s: Material is NULL."), *Context);

		checkf(Index > INDEX_NONE, TEXT("%s: Index: %d is NOT >= 0."), *Context, Index);

		checkf(Index < Component->GetNumMaterials(), TEXT("%s: Index: %d is NOT Valid for Component: %s with %d Material Slots."), *Context, Index, *(Component->GetName()), Component->GetNumMaterials());

		Component->SetMaterial(Index, Material);
	}

	bool FLibrary::IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Materials.Num() > CS_EMPTY, TEXT("%s: Materials.Num() is NOT > 0."), *Context);

		const int32 Count = Materials.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			checkf(Materials[I], TEXT("%s: Materials[%d] is NULL."), *Context, I);
		}
		return true;
	}

	void FLibrary::SetMaterials(UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::SetMaterials: Mesh is NULL."));

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverrideMaterials(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Materials[%d] is NULL."), Index);
			}

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetMaterials(UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::SetMaterials: Mesh is NULL."));

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverrideMaterials(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Materials[%d] is NULL."), Index);
			}

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetMaterialsChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

		ClearOverrideMaterials(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetMaterials(USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::SetMaterials: Mesh is NULL."));

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverrideMaterials(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetMaterials(USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::SetMaterials: Mesh is NULL."));

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverrideMaterials(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetMaterialsChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);

		ClearOverrideMaterials(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::ClearOverrideMaterials(UStaticMeshComponent* Mesh)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::ClearOverrideMaterials: Mesh is NULL."));

		int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
		}
		Mesh->EmptyOverrideMaterials();
	}

	void FLibrary::ClearOverrideMaterials(USkeletalMeshComponent* Mesh)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::ClearOverrideMaterials: Mesh is NULL."));

		int32 Count = Mesh->GetNumOverrideMaterials();

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(Index)))
			{
				if (!Material->IsPendingKill())
					Material->IsPendingKill();
			}
		}
		Mesh->EmptyOverrideMaterials();
	}

	// MID
	#pragma region

	void FLibrary::SetMIDs(UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
	{
		ClearOverrideMaterials(Mesh);
		DestroyMIDs(MIDs);

		const int32 Count = Materials.Num();

		MIDs.Reset(Count);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
		}
	}

	void FLibrary::SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
	{
		ClearOverrideMaterials(Mesh);
		DestroyMIDs(MIDs);

		const int32 Count = Materials.Num();

		MIDs.Reset(Count);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
		}
	}

	void FLibrary::SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		ClearOverrideMaterials(Mesh);
		DestroyMIDs(MIDs);

		const int32 Count = Materials.Num();

		MIDs.Reset(Count);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
		}
	}

	void FLibrary::SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
	{
		ClearOverrideMaterials(Mesh);
		DestroyMIDs(MIDs);

		const int32 Count = Materials.Num();
	
		MIDs.Reset(Count);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
		}
	}

	void FLibrary::SetMIDsChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
	{
		ClearOverrideMaterials(Mesh);
		DestroyMIDs(MIDs);

		const int32 Count = Materials.Num();

		MIDs.Reset(Count);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
		}
	}

	void FLibrary::SetMIDsChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
	{
		ClearOverrideMaterials(Mesh);
		DestroyMIDs(MIDs);

		const int32 Count = Materials.Num();

		MIDs.Reset(Count);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
		}
	}

	void FLibrary::DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs)
	{
		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			if (MID &&
				!MID->IsPendingKill())
			{
				MID->MarkPendingKill();
			}
		}
		MIDs.SetNum(0, true);
	}

	void FLibrary::MIDs_SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value)
	{
		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			check(MID);

			MID->SetScalarParameterValue(ParamName, Value);
		}
	}

	void FLibrary::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value)
	{
		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			check(MID);

			MID->SetVectorParameterValue(ParamName, Value);
		}
	}

	void FLibrary::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value)
	{
		const int32 Count = MIDs.Num();

		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			check(MID);

			MID->SetVectorParameterValue(ParamName, Value);
		}
	}

	#pragma endregion MID
}