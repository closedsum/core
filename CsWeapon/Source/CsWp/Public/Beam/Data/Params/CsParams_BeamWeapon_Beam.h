// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/Enum/CsEnumMap.h"
#include "Engine/EngineTypes.h"
#include "CollisionShape.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_BeamWeapon_Beam.generated.h"

// BeamWeaponLaunchLocation
#pragma region

/**
* Describes the different methods to get the Location from which a trace
* will be performed from a weapon of type: ICsBeamWeapon.
*/
UENUM(BlueprintType)
enum class ECsBeamWeaponBeamLocation : uint8
{
	/** Root object's Location (usually a SceneComponent). */
	Self							UMETA(DisplayName = "Self"),
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner							UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the 
		Weapon, use the Bone's location. */
	Bone							UMETA(DisplayName = "Bone"),
	/** If there is a SkeletalMesh that acts as the root object for the
		Weapon, use the Socket's location. */
	Socket							UMETA(DisplayName = "Socket"),
	/** SceneComponent's Location. The Component is marked as the Beam Component Transform. */
	Component						UMETA(DisplayName = "Component"),
	/** Owner's Camera's Location. */
	Camera							UMETA(DisplayName = "Camera"),
	Custom							UMETA(DisplayName = "Custom"),
	ECsBeamWeaponBeamLocation_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsBeamWeaponBeamLocation : public TCsEnumMap<ECsBeamWeaponBeamLocation>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamWeaponBeamLocation, ECsBeamWeaponBeamLocation)
};

namespace NCsBeamWeaponBeamLocation
{
	typedef ECsBeamWeaponBeamLocation Type;

	namespace Ref
	{
		extern CSWP_API const Type Self;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Socket;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsBeamWeaponBeamLocation_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				/**
				* Describes the different methods to get the Location from which a beam
				* will be preformed from a weapon of type: ICsBeamWeapon.
				*/
				enum class ELocation : uint8
				{
					/** Root object's Location (usually a SceneComponent). */
					Self,
					/** Owner's Location. If the Owner is of type: AActor, then it will
						be GetActorLocation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the 
						Weapon, use the Bone's location. */ 
					Bone,
					/** If there is a SkeletalMesh that acts as the root object for the 
						Weapon, use the Socket's location. */ 
					Socket,
					/** SceneComponent's Location. The Component is marked as the Beam Component Transform. */
					Component,
					/** Owner's Camera's Location. */
					Camera,
					Custom,
					ELocation_MAX
				};

				struct CSWP_API EMLocation : public TCsEnumMap<ELocation>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMLocation, ELocation)
				};

				namespace NLocation
				{
					typedef ELocation Type;

					namespace Ref
					{
						extern CSWP_API const Type Self;
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Bone;
						extern CSWP_API const Type Socket;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Camera;
						extern CSWP_API const Type Custom;
						extern CSWP_API const Type ELocation_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion BeamWeaponLaunchLocation

// FCsBeamWeaponBeamParamsLocationInfo
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NParams, NBeam, FLocationInfo)

/**
* Describes Location related information for performing a trace from a
* weapon of type: ICsBeamWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsBeamWeaponBeamParamsLocationInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsBeamWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamWeaponBeamLocation Type;

	/** Get the Bone from which Location information is used.
		Only valid if:
		 Type == ECsBeamWeaponBeamLocation::Bone ||
		 Type == ECsBeamWeaponBeamLocation::Socket */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BoneOrSocket;

	FCsBeamWeaponBeamParamsLocationInfo() :
		Type(ECsBeamWeaponBeamLocation::Owner),
		BoneOrSocket(NAME_None)
	{
	}

#define InfoType NCsWeapon::NBeam::NParams::NBeam::FLocationInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				/**
				* Describes Location related information for performing a beam from a 
				* weapon of type: ICsBeamWeapon.
				*/
				struct CSWP_API FLocationInfo
				{
				#define LocationType NCsWeapon::NBeam::NParams::NBeam::ELocation

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(Type, LocationType)
					CS_DECLARE_MEMBER_WITH_PROXY(BoneOrSocket, FName)

				public:

					FLocationInfo() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, LocationType::Self),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(BoneOrSocket, NAME_None)
					{
						CS_CTOR_SET_MEMBER_PROXY(Type);
						CS_CTOR_SET_MEMBER_PROXY(BoneOrSocket);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, LocationType)

					/**
					* Get the Bone from which Location information is used.
					* NOTE: LocationType (NCsWeapon::NBeam::NParams::NBeam::ELocation)
					* Only valid if:
					*  GetType() == LocationType::Bone ||
	* 				*  GetType() == LocationType::Socket
					*
					* return Bone or Socket name
					*/
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(BoneOrSocket, FName)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef LocationType
				};
			}
		}
	}
}

#pragma endregion FCsBeamWeaponBeamParamsLocationInfo

// BeamWeaponBeamDirection
#pragma region

/**
* Describes the different methods to get the Direction from which a trace
* will be performed from a weapon of type: ICsBeamWeapon.
*/
UENUM(BlueprintType)
enum class ECsBeamWeaponBeamDirection : uint8
{
	/** Root object's direction (usually a SceneComponent). */
	Self								UMETA(DisplayName = "Self"),
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner								UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Bone's rotation. */
	Bone								UMETA(DisplayName = "Bone"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Socket's rotation. */
	Socket								UMETA(DisplayName = "Socket"),
	/** SceneComponent's Rotation. The Component is marked as the Beam Component Transform. */
	Component							UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation. */
	Camera								UMETA(DisplayName = "Camera"),
	/** A trace is used to determine the direction. The start and end points of the
		trace are determined by other parameters. */
	Trace								UMETA(DisplayName = "Trace"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsBeamWeaponBeamDirection_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsBeamWeaponBeamDirection : public TCsEnumMap<ECsBeamWeaponBeamDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamWeaponBeamDirection, ECsBeamWeaponBeamDirection)
};

namespace NCsBeamWeaponBeamDirection
{
	typedef ECsBeamWeaponBeamDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type Self;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Socket;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Trace;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsBeamWeaponBeamDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				/**
				* Describes the different methods to get the Direction from which a beam
				* will be performed from a weapon of type: ICsBeamWeapon.
				*/
				enum class EDirection : uint8
				{
					/** Root object's direction (usually a SceneComponent). */
					Self,
					/** Owner's Rotation. If the Owner is of type: AActor, then it will
						be GetActorRotation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon, 
						use the Bone's rotation. */
					Bone,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon,
						use the Socket's rotation. */
					Socket,
					/** SceneComponent's Rotation. The Component is marked as the Beam Component Transform. */
					Component,
					/** Owner's Camera's Rotation. */
					Camera,
					/** A beam is used to determine the direction. The start and end points of the 
						beam are determined by other parameters. 
						TODO: Have a mechanism to determine start and end points of this beam.
						TEMP: Default behavior is for start of beam to the Owner's Camera's Location and
							  direction to be the Owner's Camera's Direction. */
					Trace,
					Custom,
					EDirection_MAX
				};

				struct CSWP_API EMDirection : public TCsEnumMap<EDirection>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
				};

				namespace NDirection
				{
					typedef EDirection Type;

					namespace Ref
					{
						extern CSWP_API const Type Self;
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Bone;
						extern CSWP_API const Type Socket;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Camera;
						extern CSWP_API const Type Trace;
						extern CSWP_API const Type Custom;
						extern CSWP_API const Type EDirection_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion BeamWeaponBeamDirection

// FCsBeamWeaponBeamParamsDirectionInfo
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NParams, NBeam, FDirectionInfo)

/**
* Describes Direction related information for performing a trace from a
* weapon of type: ICsBeamWeapon
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsBeamWeaponBeamParamsDirectionInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a trace
		will be performed from a weapon of type: ICsBeamWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamWeaponBeamDirection Type;

	/** Get the Bone from which Direction information is used.
		Only valid if:
		 Type == ECsBeamWeaponBeamDirection::Bone ||
		 Type == ECsBeamWeaponBeamDirection::Socket */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BoneOrSocket;

	/** The Rules, components (Pitch, Yaw, Roll), to use from a given rotation
		when calculating the Direction.
		See ECsRotationRules */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 Rules;

	FCsBeamWeaponBeamParamsDirectionInfo() :
		Type(ECsBeamWeaponBeamDirection::Owner),
		BoneOrSocket(NAME_None),
		Rules(3) // CS_ROTATION_FLAGS_PITCH_AND_YAW
	{
	}

#define InfoType NCsWeapon::NBeam::NParams::NBeam::FDirectionInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				/**
				* Describes Direction related information for performing a beam from a 
				* weapon of type: ICsBeamWeapon
				*/
				struct CSWP_API FDirectionInfo 
				{
				#define DirectionType NCsWeapon::NBeam::NParams::NBeam::EDirection

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(Type, DirectionType)
					CS_DECLARE_MEMBER_WITH_PROXY(BoneOrSocket, FName)
					CS_DECLARE_MEMBER_WITH_PROXY(Rules, int32)

				public:

					FDirectionInfo() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, DirectionType::Self),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(BoneOrSocket, NAME_None),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Rules, 3) // CS_ROTATION_FLAGS_PITCH_AND_YAW
					{
						CS_CTOR_SET_MEMBER_PROXY(Type);
						CS_CTOR_SET_MEMBER_PROXY(BoneOrSocket);
						CS_CTOR_SET_MEMBER_PROXY(Rules);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, DirectionType)

					/**
					* Get the Bone from which Direction information is used.
					* NOTE: DirectionType (NCsWeapon::NBeam::NParams::NBeam::EDirection)
					* Only valid if:
					*  GetType() == DirectionType::Bone ||
* 					*  GetType() == DirectionType::Socket
					*
					* return Bone or Socket name
					*/
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(BoneOrSocket, FName)

					/**
					* Get the Rules, components (Pitch, Yaw, Roll), to use from a given rotation
					* when calculating the Direction.
					*  See ECsRotationRules
					*
					* return Rules as a mask.
					*/
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Rules, int32)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef DirectionType
				};
			}
		}
	}
}

#pragma endregion FCsBeamWeaponBeamParamsDirectionInfo

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				/**
				* Interface describing the Beam Parameters for a weapon of type: ICsBeamWeapon. The
				* parameters are usually used to location and direction of a projectile being fired from the weapon.
				*/
				struct CSWP_API IBeam : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IBeam() {}

				#define LocationInfoType NCsWeapon::NBeam::NParams::NBeam::FLocationInfo
				#define DirectionInfoType NCsWeapon::NBeam::NParams::NBeam::FDirectionInfo

					/**
					* Get the Location related information for performing a beam for a
					* weapon of type: ICsBeamWeapon.
					*
					* return Location Info
					*/
					virtual const LocationInfoType& GetLocationInfo() const = 0;

					/**
					* Get the Direction related information for performing a beam from a
					* weapon of type: ICsBeamWeapon
					*
					* return Direction Info
					*/
					virtual const DirectionInfoType& GetDirectionInfo() const = 0;

				#undef LocationInfoType
				#undef DirectionInfoType
				};
			}
		}
	}
}

// FCsBeamWeaponBeamParams
#pragma region

// NCsWeapon::NBeam::NParams::NBeam::IBeam
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NBeam, NParams, NBeam, IBeam)

/**
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsBeamWeaponBeamParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The Location related information for performing a trace for a
		weapon of type: ICsBeamWeapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsBeamWeaponBeamParamsLocationInfo LocationInfo;

	/** Get the Direction related information for performing a trace from a
		weapon of type: ICsBeamWeapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsBeamWeaponBeamParamsDirectionInfo DirectionInfo;

	FCsBeamWeaponBeamParams() :
		LocationInfo(),
		DirectionInfo()
	{
	}

#define ParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam
	ParamsType* ConstructAndCopyToParams();
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
			#define BeamParamsType NCsWeapon::NBeam::NParams::NBeam::IBeam

				struct CSWP_API FImpl : public BeamParamsType
				{
				public:

					static const FName Name;

				#define LocationInfoType NCsWeapon::NBeam::NParams::NBeam::FLocationInfo
				#define DirectionInfoType NCsWeapon::NBeam::NParams::NBeam::FDirectionInfo

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// BeamParamsType (NCsWeapon::NBeam::NParams::NBeam::IBeam)

					LocationInfoType LocationInfo;

					DirectionInfoType DirectionInfo;

					FImpl();
					~FImpl();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:
					
					LocationInfoType* GetLocationInfoPtr() { return &LocationInfo; }
					DirectionInfoType* GetDirectionInfoPtr() { return &DirectionInfo; }

				// BeamParamsType (NCsWeapon::NBeam::NParams::NBeam::IBeam)
				#pragma region
				public:

					FORCEINLINE const LocationInfoType& GetLocationInfo() const { return LocationInfo; }
					FORCEINLINE const DirectionInfoType& GetDirectionInfo() const { return DirectionInfo; }

				#pragma endregion BeamParamsType (NCsWeapon::NBeam::NParams::NBeam::IBeam)

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef LocationInfoType
				#undef DirectionInfoType
				};

			#undef BeamParamsType
			}
		}
	}
}

#pragma endregion FCsBeamWeaponBeamParams