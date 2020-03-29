#pragma once
#include "Player/CsPlayerPawn.h"
#include "CsFpsPawn.generated.h"

// Enums
#pragma region

#pragma endregion Enums

class USceneComponent;
class UCsSkeletalMeshComponent;

UCLASS(config=Game)
class CSCOREDEPRECATED_API ACsFpsPawn : public ACsPlayerPawn
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, Category = "Pawn")
	USceneComponent* Eye;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	UCsSkeletalMeshComponent* Mesh1P;

// View
#pragma region
public:

	virtual ECsViewType GetCurrentViewType() override;

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

