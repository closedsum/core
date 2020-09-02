// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"

#pragma once

template<typename EnumStruct, typename EnumType>
struct TCsEnumStructMap
{
protected:
	FString MapName;
	FName MapFName;
	FString EnumName;
	FName EnumFName;
private:
	TArray<EnumStruct> Enums;
	int32 Count;
	TArray<EnumStruct> UserDefinedEnums;
	TMap<FString, EnumStruct> UserDefinedNameMap;
	TMap<FString, EnumStruct> NameMap;
	TMap<FString, EnumStruct> DisplayNameMap;
	TMap<FName, EnumStruct> NameInternalMap;
	TMap<EnumType, EnumStruct> TypeMap;
	EnumStruct MAX;
protected:
	TCsEnumStructMap()
	{
		Count = 0;
		MAX = EnumStruct((EnumType)0, TEXT("MAX"), TEXT("MAX"));
		bExplicitMAX = false;
		EndPosition = 0;
	}
public:
	virtual ~TCsEnumStructMap() {}

protected:
	bool bExplicitMAX;
private:
	int32 EndPosition;
public:

	// Range-based for loop
	class ConstIterator
	{
		TCsEnumStructMap<EnumStruct, EnumType>* Map;
		int32 Position;
	public:
		ConstIterator(TCsEnumStructMap<EnumStruct, EnumType>* _Map, int32 _Position) :Map(_Map), Position(_Position) {}

		const EnumStruct& operator*() const { return Map->GetEnumAt(Position); }
		ConstIterator& operator++() { ++Position; return *this; }
		bool operator!=(const ConstIterator& It) const { return Position != It.Position; }
	};

public:

	ConstIterator const begin() { return { this, 0 }; }
	ConstIterator const end() { return { this, EndPosition }; }

	FORCEINLINE const FString& GetName() const
	{
		return MapName;
	}

	FORCEINLINE const FName& GetFName() const
	{
		return MapFName;
	}

	FORCEINLINE const FString& GetEnumName() const
	{
		return EnumName;
	}

	FORCEINLINE const FName& GetEnumFName() const
	{
		return EnumFName;
	}

	const EnumStruct& Create(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		EnumType Index = (EnumType)Enums.Num();
		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		EndPosition = bExplicitMAX ? Count - 1 : Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		if (bExplicitMAX)
		{
			MAX = E;
		}
		else
		{
			MAX.SetValue((EnumType)Count);
			MAX.SetName(TEXT("MAX"));
			MAX.SetDisplayName(TEXT("MAX"));
		}
		return Enums.Last();
	}

	FORCEINLINE const EnumStruct& Create(const FString& Name, const bool& UserDefinedEnum = false)
	{
		return Create(Name, Name, UserDefinedEnum);
	}
	
#if WITH_EDITOR

	bool CreateSafe(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		// Check Name already exists
		if (NameMap.Find(Name) != nullptr)
			return false;
		// Check DisplayName already exists
		if (DisplayNameMap.Find(DisplayName) != nullptr)
			return false;

		EnumType Index = (EnumType)Enums.Num();
		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		MAX.SetValue((EnumType)Count);
		return true;
	}

	FORCEINLINE bool CreateSafe(const FString& Name, const bool& UserDefinedEnum = false)
	{
		return CreateSafe(Name, Name, UserDefinedEnum);
	}

#endif // #if WITH_EDITOR
	
	bool Remove(const EnumStruct& Enum)
	{
		bool Success = Enums.Remove(Enum) > 0;
		UserDefinedEnums.Remove(Enum);
		UserDefinedNameMap.Remove(Enum.GetName());
		NameMap.Remove(Enum.GetName());
		DisplayNameMap.Remove(Enum.GetDisplayName());
		NameInternalMap.Remove(Enum.GetFName());
		TypeMap.Remove(Enum.GetValue());

		MAX.Value = (EnumType)Enums.Num();

		// Reset maps with the update values 
		if (Success)
		{
			const int32 Size = Enums.Num();

			for (int32 I = 0; I < Size; ++I)
			{
				EnumStruct& E = Enums[I];
				E.SetValue((EnumType)I);

				NameMap[E.GetName()] = E;
				DisplayNameMap[E.GetDisplayName()] = E;
				NameInternalMap[E.GetFName()] = E;
				TypeMap[E.GetValue()] = E;

				for (EnumStruct& UserEnum : UserDefinedEnums)
				{
					if (UserEnum.GetValue() == (EnumType)I)
					{
						UserEnum = E;
						break;
					}
				}

				if (EnumStruct* EnumPtr = UserDefinedNameMap.Find(E.GetName()))
				{
					*EnumPtr = E;
				}
			}
		}
		return Success;
	}

	FORCEINLINE const EnumStruct& operator[](const EnumType &Type) const
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& operator[](const FString &Name) const
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& operator[](const FName &Name) const
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumStruct& Enum) const
	{
		return Enum.IsValid() && Enum != MAX && Enum.GetValue() < Count && Enums.Find(Enum) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name) const
	{
		return NameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name) const
	{
		return NameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnumByDisplayName(const FString& Name) const
	{
		return DisplayNameMap.Find(Name) != nullptr;
	}

	FORCEINLINE const EnumStruct& GetEnumAt(const int32& Index) const
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumAt(const int32& Index) const
	{
		return Index < Count ? Enums[Index] : MAX;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FString& Name) const
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FString& Name) const
	{
		return IsValidEnum(Name) ? NameMap[Name] : MAX;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FName& Name) const
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FName& Name) const
	{
		return IsValidEnum(Name) ? NameInternalMap[Name] : MAX;
	}

	FORCEINLINE const EnumStruct& GetEnum(const EnumType& Type) const
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& GetEnumByDisplayName(const FString& DisplayName) const
	{
		return DisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumByDisplayName(const FString& DisplayName) const
	{
		if (const EnumStruct* EnumPtr = DisplayNameMap.Find(DisplayName))
			return *EnumPtr;
		return MAX;
	}

	FORCEINLINE const int32& Num() const
	{
		return Count;
	}

	FORCEINLINE const EnumStruct& GetMAX() const
	{
		return MAX;
	}
	
	void ClearUserDefinedEnums()
	{
		const int32 StartSize = Enums.Num();

		for (int32 I = StartSize - 1; I >= 0; --I)
		{
			const EnumStruct& E = Enums[I];

			if (EnumStruct* EnumPtr = UserDefinedNameMap.Find(E.GetName()))
			{
				NameMap.Remove(E.GetName());
				DisplayNameMap.Remove(E.GetDisplayName());
				NameInternalMap.Remove(E.GetFName());
				TypeMap.Remove((EnumType)E.GetValue());
				Enums.RemoveAt(I);
			}
		}

		// Reset maps with the update values 
		Count = Enums.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			EnumStruct& E = Enums[I];
			E.SetValue((EnumType)I);

			NameMap[E.GetName()] = E;
			DisplayNameMap[E.GetDisplayName()] = E;
			NameInternalMap[E.GetFName()] = E;
			TypeMap[E.GetValue()] = E;
		}

		if (bExplicitMAX)
			MAX = Enums.Last();
		else
			MAX.SetValue((EnumType)Count);

		UserDefinedEnums.Reset();
		UserDefinedNameMap.Reset();
	}
};

#define CS_ENUM_STRUCT_MAP_BODY(EnumMap, EnumStruct, EnumType) \
	private: \
		typedef TCsEnumStructMap<EnumStruct, EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			MapFName = FName(*MapName); \
			EnumName = #EnumStruct; \
			EnumFName = FName(*EnumName); \
		} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
		\
		static EnumMap& Get() \
		{ \
			static EnumMap Instance; \
			return Instance; \
		}

#define CS_ENUM_STRUCT_MAP_BODY_WITH_EXPLICIT_MAX(EnumMap, EnumStruct, EnumType) \
	private: \
		typedef TCsEnumStructMap<EnumStruct, EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			MapFName = FName(*MapName); \
			EnumName = #EnumStruct; \
			EnumFName = FName(*EnumName); \
			bExplicitMAX = true; \
		} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
		\
		static EnumMap& Get() \
		{ \
			static EnumMap Instance; \
			return Instance; \
		}

#define CS_DECLARE_ENUM_STRUCT_MAP_BODY(EnumMap) \
	protected: \
		EnumMap() {} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
	private: \
		static EnumMap* Instance; \
		\
	public: \
		static EnumMap& Get();

#define CS_DEFINE_ENUM_STRUCT_MAP_BODY(EnumMap) \
	EnumMap* EnumMap::Instance; \
	\
	EnumMap& EnumMap::Get() \
	{ \
		if (!Instance) \
			Instance = new EnumMap(); \
		return *Instance; \
	}

#define CS_CREATE_ENUM_STRUCT(EnumMap, EnumElementName) const Type EnumElementName = EnumMap::Get().Create(#EnumElementName, false)
#define CS_CREATE_ENUM_STRUCT_CUSTOM(EnumMap, EnumElementName, DisplayName) const Type EnumElementName = EnumMap::Get().Create(#EnumElementName, TEXT(DisplayName), false)