#pragma once
#include "Animation/CsAnimInstance.h"
#include "Types/CsTypes_Character.h"
#include "CsAnimInstance_Character.generated.h"

UCLASS()
class CSCORE_API UCsAnimInstance_Character : public UCsAnimInstance
{
	GENERATED_UCLASS_BODY()
	
// Event Graph
#pragma region

	virtual void NativeInitializeAnimation() override;

	// Setup
#pragma region
public:

	virtual void SetupInGameSimulation() override;

	// Weapon

	TWeakObjectPtr<class ACsWeapon> Weapon;

	class ACsWeapon* GetWeapon();

	template<typename T>
	T* GetWeapon()
	{
		return Cast<T>(GetWeapon());
	}

	TSubclassOf<class ACsWeapon> WeaponClass;

	void Spawn_Weapon();
	virtual void ApplyData_Weapon();

#pragma endregion Setup

	//virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// Data
#pragma region
public:

	// Character

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_CharacterPtr Data_Character;

	class ACsData_Character* GetData();

	template<typename T>
	T* GetData()
	{
		return Cast<T>(GetData());
	}

	void OnTick_Handle_Data_Character();

	// CharacterMeshSkin

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_CharacterMeshSkinPtr Data_CharacterMeshSkin;

	class ACsData_CharacterMeshSkin* GetData_CharacterMeshSkin();

	template<typename T>
	T* GetData_CharacterMeshSkin()
	{
		return Cast<T>(GetData_CharacterMeshSkin());
	}

	void OnTick_Handle_Data_CharacterMeshSkin();

	// CharacterMaterialSkin

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_CharacterMaterialSkinPtr Data_CharacterMaterialSkin;

	class ACsData_CharacterMaterialSkin* GetData_CharacterMaterialSkin();

	template<typename T>
	T* GetData_CharacterMaterialSkin()
	{
		return Cast<T>(GetData_CharacterMaterialSkin());
	}

	void OnTick_Handle_Data_CharacterMaterialSkin();

	// Weapon

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponPtr Data_Weapon;

	class ACsData_Weapon* GetData_Weapon();

	template<typename T>
	T* GetData_Weapon()
	{
		return Cast<T>(GetData_Weapon());
	}

	void OnTick_Handle_Data_Weapon();

	// WeaponMaterialSkin

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponMaterialSkinPtr Data_WeaponMaterialSkin;

	class ACsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin();

	template<typename T>
	T* GetData_WeaponMaterialSkin()
	{
		return Cast<T>(GetData_WeaponMaterialSkin());
	}

	void OnTick_Handle_Data_WeaponMaterialSkin();

#pragma endregion Data

	// Anims
#pragma region
public:

	virtual void LoadAnims();

	virtual class UAnimMontage* GetAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index = 0) const;
	virtual class UAnimSequence* GetAnimSequence(const TCsCharacterAnim &AnimType) const;
	virtual class UBlendSpace* GetBlendSpace(const TCsCharacterBlendSpace &BlendType) const;

	virtual void StopAnimation(const TCsCharacterAnim &AnimType, const int32 &Index = 0, const float BlendOutTime = 0.0f);

#pragma endregion Anims

#pragma endregion Event Graph
};