// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsLibraryCamera
{
	namespace NCached
	{
		namespace Str
		{
			extern CSCORE_API const FString GetLocationChecked;
			extern CSCORE_API const FString GetRotationChecked;
			extern CSCORE_API const FString GetDirectionChecked;
		}
	}
}

/**
* Library of function related to Camera
*/
class CSCORE_API FCsLibrary_Camera
{
// Location
#pragma region
public:

	/**
	* Get the current camera location from Object.
	*
	* @param Object	Object to get camera related information from.
	* return		Current camera location.
	*/
	static FVector GetLocation(UObject* Object);

	/**
	* Get the current camera location from Object with 
	* rules (see ECsLocationRules).
	*
	* @param Object	Object to get camera related information from.
	* @param Rules	Mask of bits to determine which location axis to take.
	*				Omitted axes will default to 0.0f.
	* return		Current camera location.
`	*/
	static FVector GetLocation(UObject* Object, const int32& Rules);

	/**
	* Get the current camera location from Object with checks.
	*
	* @param Context	The calling context.
	* @param Object		Object to get camera related information from.
	* return			Current camera location
	*/
	static FVector GetLocationChecked(const FString& Context, UObject* Object);

	/**
	* Get the current camera location from Object with checks.
	*
	* @param Object	Object to get camera related information from.
	* return		Current camera location
	*/
	static FVector GetLocationChecked(UObject* Object);

#pragma endregion Location

// Rotation
#pragma region
public:

	/**
	* Get the current camera rotation from Object.
	*
	* @param Object	Object to get camera related information from.
	* return		Current camera rotation.
	*/
	static FRotator GetRotation(UObject* Object);

	/**
	* Get the current camera rotation from Object with
	* rules (see ECsRotationRules).
	*
	* @param Object	Object to get camera related information from.
	* @param Rules	Mask of bits to determine which rotation axis to take.
	*				Omitted axes will default to 0.0f.
	* return		Current camera rotation.
	*/
	static FRotator GetRotation(UObject* Object, const int32& Rules);

	/**
	*/
	static FRotator GetRotationChecked(const FString& Context, UObject* Object);

	/**
	*/
	static FRotator GetRotationChecked(UObject* Object);

	/**
*/
	static FRotator GetRotationChecked(const FString& Context, UObject* Object, const int32& Rules);

	/**
	*/
	static FRotator GetRotationChecked(UObject* Object, const int32& Rules);


#pragma endregion Rotation

// Direction
#pragma region
public:

	/**
	* Get the current camera direction from Object.
	*
	* @param Object	Object to get camera related information from.
	* return		Current camera direction.	
	*/
	FORCEINLINE static FVector GetDirection(UObject* Object)
	{
		return GetRotation(Object).Vector();
	}

	/**
	* Get the current camera direction from Object with
	* rules (see ECsRotationRules).
	*
	* @param Object	Object to get camera related information from.
	* @param Rules	Mask of bits to determine which location axis to take.
	*				Omitted axes will default to 0.0f.
	* @param		Current camera direction.
	*/
	FORCEINLINE static FVector GetDirection(UObject* Object, const int32& Rules)
	{
		return GetRotation(Object, Rules).Vector();
	}

	/**
	*/
	FORCEINLINE static FVector GetDirectionChecked(const FString& Context, UObject* Object)
	{
		return GetRotationChecked(Context, Object).Vector();
	}

	/**
	*/
	FORCEINLINE static FVector GetDirectionChecked(UObject* Object)
	{
		using namespace NCsLibraryCamera::NCached;

		const FString& Context = Str::GetDirectionChecked;

		return GetRotationChecked(Context, Object).Vector();
	}

	/**
	*/
	FORCEINLINE static FVector GetDirectionChecked(const FString& Context, UObject* Object, const int32& Rules)
	{
		return GetRotationChecked(Context, Object, Rules).Vector();
	}

	/**
	*/
	FORCEINLINE static FVector GetDirectionChecked(UObject* Object, const int32& Rules)
	{
		using namespace NCsLibraryCamera::NCached;

		const FString& Context = Str::GetDirectionChecked;

		return GetRotationChecked(Context, Object, Rules).Vector();
	}

#pragma endregion Direction
};