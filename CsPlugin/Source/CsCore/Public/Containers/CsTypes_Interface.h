// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

/**
*/
struct CSCORE_API FCsInterfaceBitInfo
{
private:

	/** */
	uint8 Group;

	/** The number of bits 1 is left-shifted (i.e. 1 << 0, 1 << 1, ... etc).
	    This is used as a look up index into which bit mask array to check in 
		FCsInterfaceMap. */
	uint8 Index;

	/** The result of 1 << Index. */
	uint32 Flag;

private:

	FCsInterfaceBitInfo(){}

public:

	FCsInterfaceBitInfo(const uint8& InGroup, const uint8& InIndex)
	{
		Group = InGroup;
		Index = InIndex;
		Flag  = 1 << Index;
	}

	FORCEINLINE const uint8& GetGroup() const
	{
		return Group;
	}

	FORCEINLINE const uint8& GetIndex() const
	{
		return Index;
	}

	FORCEINLINE const uint32& GetFlag() const
	{
		return Flag;
	}
};

/**
*/
struct CSCORE_API FCsInterfaceInfo
{
private:

	FName Name

	FCsInterfaceBitInfo BitInfo;

private:

	FCsInterfaceInfo(){}

public:

	FCsInterfaceInfo(const FName& InName, const uint8& InGroup, const uint8& InIndex)
	{
		Name = InName;
		BitInfo = FCsInterfaceBitInfo(InGroup, InIndex);
	}

	FORCEINLINE const FName& GetName() const
	{
		return Name;
	}

	FORCEINLINE const uint8& GetGroup() const
	{
		return BitInfo.GetGroup();
	}

	FORCEINLINE const uint8& GetIndex() const
	{
		return BitInfo.GetIndex();
	}

	FORCEINLINE const uint8& GetFlag() const
	{
		return BitInfo.GetFlag();
	}

	FORCEINLINE bool IsValid() const
	{
		return Name != NAME_None;
	}
};

/**
*/
struct CSCORE_API FCsInterfaceBaseSliceHelper
{
private:
	/** Counter to track last Group "index" */
	uint8 GroupCounter;
	/** Counter to track the last Index "index" */
	int32 IndexCounter;
protected:
	FCsInterfaceBaseSliceHelper() :
		GroupIndex(0),
		IndexCounter(INDEX_NONE)
	{
	}
public:
	virtual ~FCsInterfaceBaseSliceHelper() {}

	const FCsInterfaceBitInfo& Create(const FName& Name)
	{
		if (IndexCounter < 31)
		{
			++IndexCounter;
		}
		else
		{
			++GroupCounter;
			IndexCounter = 0;
		}
		return FCsInterfaceInfo(Name, GroupCounter, (uint8)IndexCounter);
	}
};

#define CS_INTERFACE_BASE_SLICE_HELPER_BODY(Helper) \
	private: \
		typedef FCsInterfaceBaseSliceHelper Super; \
	protected: \
		Helper() : Super(){} \
		Helper(const Helper &) = delete; \
		Helper(Helper &&) = delete; \
	public: \
		~Helper() {} \
		\
		static Helper& Get() \
		{ \
			static Helper Instance; \
			return Instance; \
		}