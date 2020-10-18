// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Trace/Data/Params/CsParams_TraceWeapon_Trace.h"

class UObject;
struct FCsInterfaceMap;
struct FCsTraceCollisionBox;
struct FCsTraceCollisionSphere;
struct FCsTraceCollisionCapsule;

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
			// FLineEmu
			#pragma region
				/**
				*/
				struct CSWP_API FLineEmu : public ITrace 
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ITrace

					ELocation* Location;

					EDirection* Direction;

					int32* DirectionRules;

					ECollisionChannel ObjectType;

					FCollisionShape Shape;

					float* Distance;

				public:

					FLineEmu();
					~FLineEmu();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetLocationType(ELocation* Value) { Location = Value; }
					FORCEINLINE void SetDirectionType(EDirection* Value) { Direction = Value; }
					FORCEINLINE void SetDirectionRules(int32* Value) { DirectionRules = Value; }
					FORCEINLINE void SetObjectType(TEnumAsByte<ECollisionChannel>& Value) { ObjectType = Value.GetValue(); }
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const ELocation& GetLocationType() const { return *Location; }
					FORCEINLINE const EDirection& GetDirectionType() const { return *Direction; }
					FORCEINLINE const int32& GetDirectionRules() const { return *DirectionRules; }
					FORCEINLINE const ECollisionChannel& GetObjectType() const { return ObjectType; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FLineEmu

			// FBoxEmu
			#pragma region
				/**
				*/
				struct CSWP_API FBoxEmu : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ITrace

					ELocation* Location; 

					EDirection* Direction;

					int32* DirectionRules;

					ECollisionChannel ObjectType;

					FCollisionShape Shape;

					float* Distance;

				public:

					FBoxEmu();
					~FBoxEmu();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetLocationType(ELocation* Value) { Location = Value; }
					FORCEINLINE void SetDirectionType(EDirection* Value) { Direction = Value; }
					FORCEINLINE void SetDirectionRules(int32* Value) { DirectionRules = Value; }
					FORCEINLINE void SetObjectType(TEnumAsByte<ECollisionChannel>& Value) { ObjectType = Value.GetValue(); }
					void SetShape(FCsTraceCollisionBox* Value);
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const ELocation& GetLocationType() const { return *Location; }
					FORCEINLINE const EDirection& GetDirectionType() const { return *Direction; }
					FORCEINLINE const int32& GetDirectionRules() const { return *DirectionRules; }
					FORCEINLINE const ECollisionChannel& GetObjectType() const { return ObjectType; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FBoxEmu

			// FSphereEmu
			#pragma region
				/**
				*/
				struct CSWP_API FSphereEmu : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ITrace

					ELocation* Location; 

					EDirection* Direction;

					int32* DirectionRules;

					ECollisionChannel ObjectType;

					FCollisionShape Shape;

					float* Distance;

				public:

					FSphereEmu();
					~FSphereEmu();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetLocationType(ELocation* Value) { Location = Value; }
					FORCEINLINE void SetDirectionType(EDirection* Value) { Direction = Value; }
					FORCEINLINE void SetDirectionRules(int32* Value) { DirectionRules = Value; }
					FORCEINLINE void SetObjectType(TEnumAsByte<ECollisionChannel>& Value) { ObjectType = Value.GetValue(); }
					void SetShape(FCsTraceCollisionSphere* Value);
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const ELocation& GetLocationType() const { return *Location; }
					FORCEINLINE const EDirection& GetDirectionType() const { return *Direction; }
					FORCEINLINE const int32& GetDirectionRules() const { return *DirectionRules; }
					FORCEINLINE const ECollisionChannel& GetObjectType() const { return ObjectType; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FSphereEmu

			// FCapsuleEmu
			#pragma region
				/**
				*/
				struct CSWP_API FCapsuleEmu : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ITrace

					ELocation* Location; 

					EDirection* Direction;

					int32* DirectionRules;

					ECollisionChannel ObjectType;

					FCollisionShape Shape;

					float* Distance;

				public:

					FCapsuleEmu();
					~FCapsuleEmu();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetLocationType(ELocation* Value) { Location = Value; }
					FORCEINLINE void SetDirectionType(EDirection* Value) { Direction = Value; }
					FORCEINLINE void SetDirectionRules(int32* Value) { DirectionRules = Value; }
					FORCEINLINE void SetObjectType(TEnumAsByte<ECollisionChannel>& Value) { ObjectType = Value.GetValue(); }
					void SetShape(FCsTraceCollisionCapsule* Value);
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const ELocation& GetLocationType() const { return *Location; }
					FORCEINLINE const EDirection& GetDirectionType() const { return *Direction; }
					FORCEINLINE const int32& GetDirectionRules() const { return *DirectionRules; }
					FORCEINLINE const ECollisionChannel& GetObjectType() const { return ObjectType; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FCapsuleEmu
			}
		}
	}
}