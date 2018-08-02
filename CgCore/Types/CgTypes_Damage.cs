namespace CgCore
{
    using System.Collections.Generic;
    using UnityEngine;

    #region "DamageType"

    public sealed class FECgDamageType : FECgEnum_byte
    {
        public FECgDamageType(byte value, string name) : base(value, name) { }
    }

    public class EMCgDamageType : TCgEnumMap<FECgDamageType, byte>
    {
        private static EMCgDamageType _Instance;
        public static EMCgDamageType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgDamageType();
                }
                return _Instance;
            }
        }

        public static EMCgDamageType Get()
        {
            return Instance;
        }
    }

    public sealed class FECgDamageTypeEqualityComparer : IEqualityComparer<FECgDamageType>
    {
        public bool Equals(FECgDamageType lhs, FECgDamageType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgDamageType x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // DamageType

    #region "HitType"

    public sealed class FECgHitType : FECgEnum_byte
    {
        public FECgHitType(byte value, string name) : base(value, name) { }
    }

    public class EMCgHitType : TCgEnumMap<FECgHitType, byte>
    {
        private static EMCgHitType _Instance;
        public static EMCgHitType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgHitType();
                }
                return _Instance;
            }
        }

        public static EMCgHitType Get()
        {
            return Instance;
        }
    }

    public sealed class FECgHitTypeEqualityComparer : IEqualityComparer<FECgHitType>
    {
        public bool Equals(FECgHitType lhs, FECgHitType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgHitType x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // HitType

    public class FCgDamageEvent
    {
        public byte Index;

        public bool bAllocated;

        public float Damage;

        public MonoBehaviour Instigator;

        public MonoBehaviour Causer;

        public FECgDamageType DamageType;

        public FECgHitType HitType;

        public bool bImpulse;

        public FCgHitResult HitInfo;

        public FCgDamageEvent()
        {
            Reset();
        }

        public void Init(byte index)
        {
            Index = index;
        }

        public void Reset()
        {
            bAllocated = false;
            Damage = 0.0f;
            Instigator = null;
            Causer = null;
            DamageType = EMCgDamageType.Get().GetMAX();
            HitType = EMCgHitType.Get().GetMAX();
            bImpulse = false;
            HitInfo.Reset();
        }

        public MonoBehaviour GetInstigator() { return Instigator; }
        public T GetInstigator<T>() where T : MonoBehaviour { return (T)GetInstigator(); }

        public MonoBehaviour GetCauser() { return Causer; }
        public T GetCauser<T>() where T : MonoBehaviour { return (T)GetCauser(); }
    }

    public class FCgDamageResult
    {
        public byte Index;

        public bool bAllocated;

        public float Damage;

        public MonoBehaviour Victim;

        public FECgDamageType DamageType;

        public FECgHitType HitType;

        RaycastHit HitInfo;

        public FCgDamageResult()
        {
            Reset();
        }

        public void Init(byte index)
        {
            Index = index;
        }

        public void Reset()
        {
            bAllocated = false;
            Damage = 0.0f;
            Victim = null;
            DamageType = EMCgDamageType.Get().GetMAX();
            HitType = EMCgHitType.Get().GetMAX();
        }

        public MonoBehaviour GetVictim() { return Victim; }
        public T GetVictim<T>() where T : MonoBehaviour { return (T)GetVictim(); }
    }
}