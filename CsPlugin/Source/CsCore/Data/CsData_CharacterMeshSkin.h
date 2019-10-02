#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_View.h"
#include "CsData_CharacterMeshSkin.generated.h"

/* Current Order of Categories

01. Skin

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_CharacterMeshSkin : public ACsData
{
	GENERATED_UCLASS_BODY()

	// Skin
#pragma region

	virtual void SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void SetMesh(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow = false);

	UFUNCTION(BlueprintCallable, Category = "Character Mesh Skin")
	virtual void SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);

	virtual void SetMesh(USkeletalMeshComponent* InMesh);
	virtual void SetMesh(class ASkeletalMeshActor* InActor);
	virtual void SetMesh(UObject* InObject);

#pragma endregion Skin
};