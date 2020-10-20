// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Material.h"
#include "CsCore.h"

// Mesh
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Material
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

void FCsLibrary_Material::SetMaterials(UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
{
	checkf(Mesh, TEXT("FCsLibrary_Material::SetMaterials: Mesh is NULL."));

	const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count != MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(Mesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (!Materials[Index])
		{
			UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Materials[%d] is NULL."), Index);
		}

		Mesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::SetMaterials(UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	checkf(Mesh, TEXT("FCsLibrary_Material::SetMaterials: Mesh is NULL."));

	const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count != MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(Mesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (!Materials[Index])
		{
			UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Materials[%d] is NULL."), Index);
		}

		Mesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::SetMaterialsChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
{
	checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

	const int32 Count = Mesh->GetStaticMesh()->StaticMaterials.Num();
	const int32 MaterialCount = Materials.Num();

	checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

	ClearOverrideMaterials(Mesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

		Mesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::SetMaterials(USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
{
	checkf(Mesh, TEXT("FCsLibrary_Material::SetMaterials: Mesh is NULL."));

	const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count != MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(Mesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		Mesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::SetMaterials(USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	checkf(Mesh, TEXT("FCsLibrary_Material::SetMaterials: Mesh is NULL."));

	const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count != MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(Mesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		Mesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::SetMaterialsChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
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

void FCsLibrary_Material::ClearOverrideMaterials(UStaticMeshComponent* Mesh)
{
	checkf(Mesh, TEXT("FCsLibrary_Material::ClearOverrideMaterials: Mesh is NULL."));

	int32 Count = Mesh->OverrideMaterials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->OverrideMaterials[Index]))
		{
			if (!Material->IsPendingKill())
				Material->IsPendingKill();
		}
		Mesh->OverrideMaterials[Index] = nullptr;
	}

	Mesh->OverrideMaterials.SetNum(0, true);
}

void FCsLibrary_Material::ClearOverrideMaterials(USkeletalMeshComponent* Mesh)
{
	checkf(Mesh, TEXT("FCsLibrary_Material::ClearOverrideMaterials: Mesh is NULL."));

	int32 Count = Mesh->OverrideMaterials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(Mesh->OverrideMaterials[Index]))
		{
			if (!Material->IsPendingKill())
				Material->IsPendingKill();
		}
		Mesh->OverrideMaterials[Index] = nullptr;
	}

	Mesh->OverrideMaterials.SetNum(0, true);
}

// MID
#pragma region

void FCsLibrary_Material::DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs)
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

void FCsLibrary_Material::SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
{
	ClearOverrideMaterials(Mesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
	}
}

void FCsLibrary_Material::SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
{
	ClearOverrideMaterials(Mesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void FCsLibrary_Material::SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
{
	ClearOverrideMaterials(Mesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void FCsLibrary_Material::MIDs_SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value)
{
	for (UMaterialInstanceDynamic* MID : MIDs)
	{
		check(MID);

		MID->SetScalarParameterValue(ParamName, Value);
	}
}

void FCsLibrary_Material::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value)
{
	for (UMaterialInstanceDynamic* MID : MIDs)
	{
		check(MID);

		MID->SetVectorParameterValue(ParamName, Value);
	}
}

void FCsLibrary_Material::MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value)
{
	const int32 Count = MIDs.Num();

	for (UMaterialInstanceDynamic* MID : MIDs)
	{
		check(MID);

		MID->SetVectorParameterValue(ParamName, Value);
	}
}

#pragma endregion MID