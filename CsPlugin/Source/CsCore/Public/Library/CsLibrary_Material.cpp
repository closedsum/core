// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Material.h"
#include "CsCore.h"

// Mesh
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Material
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

void FCsLibrary_Material::SetMaterials(UStaticMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	const int32 Count		  = InMesh->GetStaticMesh()->StaticMaterials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count > MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *InMesh->GetStaticMesh()->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(InMesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		InMesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::SetMaterials(USkeletalMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials)
{
	const int32 Count		  = InMesh->SkeletalMesh->Materials.Num();
	const int32 MaterialCount = Materials.Num();

	if (Count > MaterialCount)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsLibrary_Material::SetMaterials: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *InMesh->SkeletalMesh->GetName(), Count, MaterialCount);
		return;
	}

	ClearOverrideMaterials(InMesh);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		InMesh->SetMaterial(Index, Materials[Index]);
	}
}

void FCsLibrary_Material::ClearOverrideMaterials(UStaticMeshComponent* InMesh)
{
	int32 Count = InMesh->OverrideMaterials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(InMesh->OverrideMaterials[Index]))
		{
			if (!Material->IsPendingKill())
				Material->IsPendingKill();
		}
		InMesh->OverrideMaterials[Index] = nullptr;
	}

	InMesh->OverrideMaterials.SetNum(0, true);
}

void FCsLibrary_Material::ClearOverrideMaterials(USkeletalMeshComponent* InMesh)
{
	int32 Count = InMesh->OverrideMaterials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		if (UMaterialInstanceDynamic* Material = Cast<UMaterialInstanceDynamic>(InMesh->OverrideMaterials[Index]))
		{
			if (!Material->IsPendingKill())
				Material->IsPendingKill();
		}
		InMesh->OverrideMaterials[Index] = nullptr;
	}

	InMesh->OverrideMaterials.SetNum(0, true);
}

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

void FCsLibrary_Material::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
	}
}

void FCsLibrary_Material::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
	}
}

void FCsLibrary_Material::SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
{
	ClearOverrideMaterials(InMesh);
	DestroyMIDs(MIDs);

	const int32 Count = Materials.Num();

	for (int32 Index = 0; Index < Count; ++Index)
	{
		MIDs.Add(InMesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
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