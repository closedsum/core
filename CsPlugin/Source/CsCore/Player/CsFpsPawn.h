#pragma once
#include "Player/CsPlayerPawn.h"
#include "CsFpsPawn.generated.h"

// Enums
#pragma region

#pragma endregion Enums

UCLASS(config=Game)
class CSCORE_API ACsFpsPawn : public ACsPlayerPawn
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, Category = "Pawn")
	class USceneComponent* Eye;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UCsSkeletalMeshComponent* Mesh1P;

// View
#pragma region
public:

	virtual TEnumAsByte<ECsViewType::Type> GetCurrentViewType() override;

#pragma endregion View

// Camera
#pragma region
public:

	float EyeHeight;

	virtual FVector GetPawnViewLocation() const override;

	virtual FVector GetFeetLocation() const;

#pragma endregion Camera

// Mesh
#pragma region
public:

	virtual USkeletalMeshComponent* GetCurrentMesh();

#pragma endregion Mesh

// Weapons
#pragma region
public:

	virtual void ApplyData_Weapon() override;

#pragma endregion Weapons
};

