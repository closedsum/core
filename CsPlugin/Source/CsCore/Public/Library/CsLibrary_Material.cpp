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

	void FLibrary::SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index)
	{
		checkf(Component, TEXT("%s: Component is NULL."), *Context);

		checkf(Material, TEXT("%s: Material is NULL."), *Context);

		checkf(Index > INDEX_NONE, TEXT("%s: Index: %d is NOT >= 0."), *Context, Index);

		checkf(Index < Component->GetNumMaterials(), TEXT("%s: Index: %d is NOT Valid for Component: %s with %d Material Slots."), *Context, Index, *(Component->GetName()), Component->GetNumMaterials());

		Component->SetMaterial(Index, Material);
	}

	void FLibrary::Set(UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::Set: Mesh is NULL."));

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::Set: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::SetMaterials: Materials[%d] is NULL."), Index);
			}

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::Set(UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::Set: Mesh is NULL."));

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::Set: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			if (!Materials[Index])
			{
				UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::Set: Materials[%d] is NULL."), Index);
			}

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

		const int32 Count		  = Mesh->GetStaticMesh()->StaticMaterials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->GetStaticMesh()->GetName(), Count, MaterialCount);

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::Set(USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::Set: Mesh is NULL."));

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::Set: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::Set(USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::Set: Mesh is NULL."));

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		if (Count != MaterialCount)
		{
			UE_LOG(LogCs, Warning, TEXT("NCsMaterial::FLibrary::Set: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);
			return;
		}

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials)
	{
		checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

		const int32 Count		  = Mesh->SkeletalMesh->Materials.Num();
		const int32 MaterialCount = Materials.Num();

		checkf(Count == MaterialCount, TEXT("%s: Mismatch between Mesh (%s) material count (%d) != input material count (%d)"), *Context, *Mesh->SkeletalMesh->GetName(), Count, MaterialCount);

		ClearOverride(Mesh);

		for (int32 Index = 0; Index < Count; ++Index)
		{
			checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

			Mesh->SetMaterial(Index, Materials[Index]);
		}
	}

	void FLibrary::ClearOverride(UStaticMeshComponent* Mesh)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::ClearOverride: Mesh is NULL."));

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

	void FLibrary::ClearOverride(USkeletalMeshComponent* Mesh)
	{
		checkf(Mesh, TEXT("NCsMaterial::FLibrary::ClearOverride: Mesh is NULL."));

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

	namespace NMID
	{
		bool FLibrary::IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				checkf(MIDs[I] && !MIDs[I]->IsPendingKill(), TEXT("%s: MIDs[%d] is NULL or IsPendingKill."), *Context, I);
			}
			return true;
		}

		void FLibrary::Set(UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index].MaterialInterface));
			}
		}

		void FLibrary::Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();
	
			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				checkf(Materials[Index], TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Materials[Index]));
			}
		}

		void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

			check(IsValidChecked(Context, MIDs));

			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Mesh->SetMaterial(I, MIDs[I]);
			}
		}

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials)
		{
			typedef NCsMaterial::FLibrary MaterialLibrary;

			MaterialLibrary::ClearOverride(Mesh);
			Destroy(MIDs);

			const int32 Count = Materials.Num();

			MIDs.Reset(Count);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				UMaterialInterface* Material = Materials[Index];

				checkf(Material, TEXT("%s: Materials[%d] is NULL."), *Context, Index);

				MIDs.Add(Mesh->CreateDynamicMaterialInstance(Index, Material));
			}
		}

		void FLibrary::SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs)
		{
			checkf(Mesh, TEXT("%s: Mesh is NULL."), *Context);

			check(IsValidChecked(Context, MIDs));

			const int32 Count = MIDs.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Mesh->SetMaterial(I, MIDs[I]);
			}
		}

		void FLibrary::Destroy(TArray<UMaterialInstanceDynamic*>& MIDs)
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

		bool FLibrary::IsScalarParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			checkf(MID, TEXT("%s: MID is NULL."), *Context);

			checkf(ParamName != NAME_None, TEXT("%s: ParamName: None is NOT Valid."), *Context);

			// MaterialInstance
			if (UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent))
			{
				for (const FScalarParameterValue& Value : MI->ScalarParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				TArray<FMaterialParameterInfo> Infos;
				TArray<FGuid> Ids;

				M->GetAllScalarParameterInfo(Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}

			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()));
			return false;
		}

		bool FLibrary::IsVectorParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			checkf(MID, TEXT("%s: MID is NULL."), *Context);

			checkf(ParamName != NAME_None, TEXT("%s: ParamName: None is NOT Valid."), *Context);

			// MaterialInstance
			if (UMaterialInstance* MI = Cast<UMaterialInstance>(MID->Parent))
			{
				for (const FVectorParameterValue& Value : MI->VectorParameterValues)
				{
					if (Value.ParameterInfo.Name == ParamName)
					{
						return true;
					}
				}
			}
			// Material
			if (UMaterial* M = Cast<UMaterial>(MID->Parent))
			{
				TArray<FMaterialParameterInfo> Infos;
				TArray<FGuid> Ids;

				M->GetAllVectorParameterInfo(Infos, Ids);

				for (const FMaterialParameterInfo& Info : Infos)
				{
					if (Info.Name == ParamName)
					{
						return true;
					}
				}

			}
			checkf(0, TEXT("%s: Failed to find ParamName: %s in MID: %s."), *Context, *(ParamName.ToString()), *(MID->GetName()));
			return false;
		}

		void FLibrary::SetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value)
		{
			check(IsScalarParameterValidChecked(Context, MID, ParamName));

			MID->SetScalarParameterValue(ParamName, Value);
		}

		void FLibrary::SetScalarParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*> MIDs, const FName& ParamName, const float& Value)
		{
			checkf(MIDs.Num() > CS_EMPTY, TEXT("%s: MIDs is EMPTY."), *Context);

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetScalarParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		void FLibrary::SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value)
		{
			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				check(MID);

				MID->SetScalarParameterValue(ParamName, Value);
			}
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value)
		{
			check(IsVectorParameterValidChecked(Context, MID, ParamName));

			MID->SetVectorParameterValue(ParamName, Value);
		}

		void FLibrary::SetVectorParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value)
		{
			checkf(MIDs.Num() > CS_EMPTY, TEXT("%s: MIDs is EMPTY."), *Context);

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				SetVectorParameterValueChecked(Context, MID, ParamName, Value);
			}
		}

		void FLibrary::SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value)
		{
			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				check(MID);

				MID->SetVectorParameterValue(ParamName, Value);
			}
		}

		void FLibrary::SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value)
		{
			const int32 Count = MIDs.Num();

			for (UMaterialInstanceDynamic* MID : MIDs)
			{
				check(MID);

				MID->SetVectorParameterValue(ParamName, Value);
			}
		}

		float FLibrary::GetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName)
		{
			check(IsScalarParameterValidChecked(Context, MID, ParamName));

			return MID->K2_GetScalarParameterValue(ParamName);
		}
	}
}