namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;

    using UnityEngine;

    #region "SoundType"

    [Serializable]
    public struct S_FECgSoundType
    {
        [SerializeField]
        public string name;
    }

    public sealed class FECgSoundType : FECgEnum_byte
    {
        public FECgSoundType(byte value, string name) : base(value, name) { }
    }

    public class EMCgSoundType : TCgEnumMap<FECgSoundType, byte>
    {
        private static EMCgSoundType _Instance;
        public static EMCgSoundType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgSoundType();
                }
                return _Instance;
            }
        }

        public static EMCgSoundType Get()
        {
            return Instance;
        }
    }

    public sealed class FECgSoundTypeEqualityComparer : IEqualityComparer<FECgSoundType>
    {
        public bool Equals(FECgSoundType lhs, FECgSoundType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgSoundType x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // SoundType

    public enum ECgSoundPriority : byte
    {
        VeryLow,
        Low,
        Medium,
        High,
        VeryHigh,
        MAX
    }

    [Serializable]
    public struct S_FCgSoundElement
    {
        [SerializeField]
        public AudioClip Sound;
        [SerializeField]
        public int Sound_LoadFlags;
        [SerializeField]
        public S_FECgSoundType SoundType;
        [SerializeField]
        public ECgSoundPriority Priority;
        [SerializeField]
        public bool bSpatialize;
        [SerializeField]
        public float Duration;
        [SerializeField]
        public bool bLooping;
        [SerializeField]
        public float VolumeMultiplier;
        [SerializeField]
        public float PitchMultiplier;
        [SerializeField]
        public string Bone;
    }

    public class FCgSoundElement
    {
        //TSoftObjectPtr<class USoundCue> Sound;
        public AudioClip Sound;

        public int Sound_LoadFlags;

        public FECgSoundType SoundType;

        public ECgSoundPriority Priority;

        public bool bSpatialize;
        public float Duration;
        public bool bLooping;
        public float VolumeMultiplier;
        public float PitchMultiplier;
        public string Bone;

        private AudioClip Sound_Internal;

        public FCgSoundElement()
        {
            //CS_SET_BLUEPRINT_BITFLAG(Sound_LoadFlags, ECgLoadFlags.Game);

            SoundType = EMCgSoundType.Get().GetMAX();
            Priority = ECgSoundPriority.Medium;
            Duration = 0.05f;
            VolumeMultiplier = 1.0f;
            PitchMultiplier = 1.0f;
            Bone = "";
        }
        /*
        FORCEINLINE FCsSoundElement& operator=(const FCsSoundElement& B)
        {
            Sound = B.Sound;
            Sound_LoadFlags = B.Sound_LoadFlags;
            Type = B.Type;
            Priority = B.Priority;
            Duration = B.Duration;
            IsLooping = B.IsLooping;
            VolumeMultiplier = B.VolumeMultiplier;
            PitchMultiplier = B.PitchMultiplier;
            Bone = B.Bone;
            return *this;
        }

        FORCEINLINE bool operator ==(const FCsSoundElement& B) const
	    {
		    return Sound == B.Sound &&
				    Sound_LoadFlags == B.Sound_LoadFlags &&
				    Type == B.Type &&
				    Priority == B.Priority &&
				    Duration == B.Duration &&
				    IsLooping == B.IsLooping &&
				    VolumeMultiplier == B.VolumeMultiplier &&
				    PitchMultiplier == B.PitchMultiplier &&
				    Bone == B.Bone;
	    }

        FORCEINLINE bool operator !=(const FCsSoundElement& B) const
	    {
		    return !(*this == B);
        }

        FORCEINLINE void Set(USoundCue* InSound)
        {
            Sound = TSoftObjectPtr<USoundCue>(InSound);
            Sound_Internal = InSound;
        }
        */
        public AudioClip Get()
        {
            return Sound_Internal;
        }
    }

    public class FCgFpvSoundElement
    {
        public FCgFpvSoundElement() { }
    }
}