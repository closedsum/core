#pragma once
#include "Animation/CsAnimInstance.h"
#include "Types/CsTypes_Character.h"
#include "CsAnimInstance_Character.generated.h"

// Enums
#pragma region

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsAnimInstance_Character : public UCsAnimInstance
{
	GENERATED_UCLASS_BODY()
	
// Event Graph
#pragma region
public:

	virtual void NativeInitializeAnimation() override;

	// Setup
#pragma region
public:

#if WITH_EDITOR

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

	virtual void Spawn_Weapon();
	virtual void ApplyData_Weapon();

#endif // #if WITH_EDITOR

#pragma endregion Setup

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

#if WITH_EDITOR
	virtual void OnTick_Handle_Weapon(const float &DeltaTimeX);
#endif // #if WITH_EDITOR

	// Data
#pragma region
public:

		// Character
#pragma region 
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_CharacterPtr Data_Character;

	class ACsData_Character* GetData();

	template<typename T>
	T* GetData()
	{
		return Cast<T>(GetData());
	}

private:
	void LoadData_Character();

public:
#if WITH_EDITOR
	void OnTick_Handle_Data_Character();
#endif // #if WITH_EDITOR

#pragma endregion Character

		// CharacterMeshSkin
#pragma region 
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_CharacterMeshSkinPtr Data_CharacterMeshSkin;

	class ACsData_CharacterMeshSkin* GetData_CharacterMeshSkin();

	template<typename T>
	T* GetData_CharacterMeshSkin()
	{
		return Cast<T>(GetData_CharacterMeshSkin());
	}

private:
	void LoadData_CharacterMeshSkin();

public:
#if WITH_EDITOR
	void OnTick_Handle_Data_CharacterMeshSkin();
#endif // #if WITH_EDITOR

#pragma endregion CharacterMeshSkin

		// CharacterMaterialSkin
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_CharacterMaterialSkinPtr Data_CharacterMaterialSkin;

	class ACsData_CharacterMaterialSkin* GetData_CharacterMaterialSkin();

	template<typename T>
	T* GetData_CharacterMaterialSkin()
	{
		return Cast<T>(GetData_CharacterMaterialSkin());
	}

private:
	void LoadData_CharacterMaterialSkin();

public:
#if WITH_EDITOR
	void OnTick_Handle_Data_CharacterMaterialSkin();
#endif // #if WITH_EDITOR

#pragma endregion CharacterMaterialSkin

		// Weapon
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponPtr Data_Weapon;

	class ACsData_Weapon* GetData_Weapon();

	template<typename T>
	T* GetData_Weapon()
	{
		return Cast<T>(GetData_Weapon());
	}

protected:
	virtual void LoadData_Weapon();

public:
#if WITH_EDITOR
	virtual void OnTick_Handle_Data_Weapon();
#endif // #if WITH_EDITOR

#pragma endregion Weapon

		// WeaponMaterialSkin
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Data")
	FCsDataAnimInstance_WeaponMaterialSkinPtr Data_WeaponMaterialSkin;

	class ACsData_WeaponMaterialSkin* GetData_WeaponMaterialSkin();

	template<typename T>
	T* GetData_WeaponMaterialSkin()
	{
		return Cast<T>(GetData_WeaponMaterialSkin());
	}

protected:
	virtual void LoadData_WeaponMaterialSkin();

public:
#if WITH_EDITOR
	virtual void OnTick_Handle_Data_WeaponMaterialSkin();
#endif // #if WITH_EDITOR

#pragma endregion WeaponMaterialSkin

#pragma endregion Data

	// Anims
#pragma region
public:

	virtual void LoadAnims();

	UFUNCTION(BlueprintCallable, Category = "AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "AnimType,Index"))
	virtual class UAnimMontage* GetAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index = 0) const;
	UFUNCTION(BlueprintCallable, Category = "AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "AnimType"))
	virtual class UAnimSequence* GetAnimSequence(const FECsCharacterAnim &AnimType) const;
	UFUNCTION(BlueprintCallable, Category = "AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "BlendType"))
	virtual class UBlendSpace1D* GetBlendSpace1D(const FECsCharacterBlendSpace &BlendType) const;
	UFUNCTION(BlueprintCallable, Category = "AnimInstance", meta = (BlueprintThreadSafe, AutoCreateRefTerm = "BlendType"))
	virtual class UBlendSpace* GetBlendSpace(const FECsCharacterBlendSpace &BlendType) const;

	virtual void StopAnimation(const FECsCharacterAnim &AnimType, const int32 &Index = 0, const float BlendOutTime = 0.0f);

#pragma endregion Anims

#pragma endregion Event Graph
};