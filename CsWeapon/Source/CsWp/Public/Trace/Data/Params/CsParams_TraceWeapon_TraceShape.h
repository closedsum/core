// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
			// FLineImpl
			#pragma region
				/**
				*/
				struct CSWP_API FLineImpl : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// ITrace

					FLocationInfo LocationInfo;

					FDirectionInfo DirectionInfo;

				private:

					TArray<ECollisionChannel> ObjectTypes;

					FCollisionShape Shape;

					float* Distance;

				public:

					FLineImpl();
					~FLineImpl();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetObjectTypes(TArray<TEnumAsByte<ECollisionChannel>>& Value) 
					{ 
						ObjectTypes.Reset(Value.Num());

						for (const TEnumAsByte<ECollisionChannel>& Enum : Value)
						{
							ObjectTypes.Add((ECollisionChannel)Enum.GetValue());
						}
					}
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const FLocationInfo& GetLocationInfo() const { return LocationInfo; }
					FORCEINLINE const FDirectionInfo& GetDirectionInfo() const { return DirectionInfo; }
					FORCEINLINE const TArray<ECollisionChannel>& GetObjectTypes() const { return ObjectTypes; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FLineImpl

			// FBoxImpl
			#pragma region
				/**
				*/
				struct CSWP_API FBoxImpl : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// ITrace

					FLocationInfo LocationInfo; 

					FDirectionInfo DirectionInfo;

				private:

					TArray<ECollisionChannel> ObjectTypes;

					FCollisionShape Shape;

					float* Distance;

				public:

					FBoxImpl();
					~FBoxImpl();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetObjectTypes(TArray<TEnumAsByte<ECollisionChannel>>& Value)
					{
						ObjectTypes.Reset(Value.Num());

						for (const TEnumAsByte<ECollisionChannel>& Enum : Value)
						{
							ObjectTypes.Add((ECollisionChannel)Enum.GetValue());
						}
					}
					void SetShape(FCsTraceCollisionBox* Value);
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const FLocationInfo& GetLocationInfo() const { return LocationInfo; }
					FORCEINLINE const FDirectionInfo& GetDirectionInfo() const { return DirectionInfo; }
					FORCEINLINE const TArray<ECollisionChannel>& GetObjectTypes() const { return ObjectTypes; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FBoxImpl

			// FSphereImpl
			#pragma region
				/**
				*/
				struct CSWP_API FSphereImpl : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// ITrace

					FLocationInfo LocationInfo; 

					FDirectionInfo DirectionInfo;

				private:

					TArray<ECollisionChannel> ObjectTypes;

					FCollisionShape Shape;

					float* Distance;

				public:

					FSphereImpl();
					~FSphereImpl();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetObjectTypes(TArray<TEnumAsByte<ECollisionChannel>>& Value)
					{
						ObjectTypes.Reset(Value.Num());

						for (const TEnumAsByte<ECollisionChannel>& Enum : Value)
						{
							ObjectTypes.Add((ECollisionChannel)Enum.GetValue());
						}
					}
					void SetShape(FCsTraceCollisionSphere* Value);
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const FLocationInfo& GetLocationInfo() const { return LocationInfo; }
					FORCEINLINE const FDirectionInfo& GetDirectionInfo() const { return DirectionInfo; }
					FORCEINLINE const TArray<ECollisionChannel>& GetObjectTypes() const { return ObjectTypes; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FSphereImpl

			// FCapsuleImpl
			#pragma region
				/**
				*/
				struct CSWP_API FCapsuleImpl : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// ITrace

					FLocationInfo LocationInfo; 

					FDirectionInfo DirectionInfo;

				private:

					TArray<ECollisionChannel> ObjectTypes;

					FCollisionShape Shape;

					float* Distance;

				public:

					FCapsuleImpl();
					~FCapsuleImpl();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetObjectTypes(TArray<TEnumAsByte<ECollisionChannel>>& Value)
					{
						ObjectTypes.Reset(Value.Num());

						for (const TEnumAsByte<ECollisionChannel>& Enum : Value)
						{
							ObjectTypes.Add((ECollisionChannel)Enum.GetValue());
						}
					}
					void SetShape(FCsTraceCollisionCapsule* Value);
					FORCEINLINE void SetDistance(float* Value) { Distance = Value; }

				// ITrace
				#pragma region
				public:

					FORCEINLINE const FLocationInfo& GetLocationInfo() const { return LocationInfo; }
					FORCEINLINE const FDirectionInfo& GetDirectionInfo() const { return DirectionInfo; }
					FORCEINLINE const TArray<ECollisionChannel>& GetObjectTypes() const { return ObjectTypes; }
					FORCEINLINE const FCollisionShape& GetShape() const { return Shape; }
					FORCEINLINE const float& GetDistance() const { return *Distance; }

				#pragma endregion ITrace
				};
			#pragma endregion FCapsuleImpl
			}
		}
	}
}