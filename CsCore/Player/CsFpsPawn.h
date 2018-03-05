#pragma once
#include "Player/CsPlayerPawn.h"
#include "CsFpsPawn.generated.h"

UCLASS(config=Game)
class CSCORE_API ACsFpsPawn : public ACsPlayerPawn
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, Category = "Pawn")
	class USceneComponent* Eye;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class UCsSkeletalMeshComponent* Mesh1P;

// Camera
#pragma region
public:

	float EyeHeight;

	virtual FVector GetPawnViewLocation() const override;

	virtual FVector GetFeetLocation() const;

#pragma endregion Camera

// Weapons
#pragma region
public:

	virtual void ApplyData_Weapon() override;

#pragma endregion Weapons
};

