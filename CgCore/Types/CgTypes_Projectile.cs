namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;

    using UnityEngine;

    public enum ECgProjectileRelevance : byte
    {
        RealVisible,
        RealInvisible,
        Fake,
        MAX
    }

    #region "ProjectileType"

    public sealed class FECgProjectileType : FECgEnum_byte
    {
        public FECgProjectileType(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgProjectileTypeEqualityComparer : IEqualityComparer<FECgProjectileType>
    {
        public bool Equals(FECgProjectileType lhs, FECgProjectileType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgProjectileType x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgProjectileType : TCgEnumMap<FECgProjectileType, byte>
    {
        private static EMCgProjectileType _Instance;
        public static EMCgProjectileType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgProjectileType();
                }
                return _Instance;
            }
        }

        public static EMCgProjectileType Get()
        {
            return Instance;
        }
    }

    #endregion // ProjectileType

    [Serializable]
    public struct S_FCgAssetRef_Projectile
    {
        [SerializeField]
        public string Path;
    }

    [Serializable]
    public struct S_FCgData_ProjectileRef
    {
        [SerializeField]
        public S_FCgAssetRef_Projectile Data;
        [SerializeField]
        public int Data_LoadFlags;
    }

    public class FCgData_ProjectileRef
    {
        public TCgAssetRef<MCgData_Projectile> Data;
        public int Data_LoadFlags;

        private MCgData_Projectile Data_Internal;

        public FCgData_ProjectileRef()
        {
            //CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
        }

        /*
        FCsData_ProjectilePtr& operator=(const FCsData_ProjectilePtr& B)
        {
            Data = B.Data;
            Data_LoadFlags = B.Data_LoadFlags;
            Data_Internal = B.Data_Internal;
            return *this;
        }

        bool operator ==(const FCsData_ProjectilePtr& B) const
	    {
		    return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	    }

        bool operator !=(const FCsData_ProjectilePtr& B) const
	    {
		    return !(*this == B);
        }
        */
        public MCgData_Projectile Get()
	    {
		    return Data_Internal;
	    }

        // TODO: HACK: used to temporarily stop warnings
        public void TempAssign()
        {
            Data_Internal = Data.Get();
        }
    }

    public class FCgProjectileFirePayload
    {
        public bool bAllocated;

        public float Time;
        public float RealTime;
        public ulong Frame;

        public float ChargePercent;

        public Vector3 Direction;
        public Vector3 Location;

        public float AdditionalSpeed;

        public MonoBehaviour HomingTarget;

        public string HomingBoneName;

        public float HomingAccelerationMagnitude;

        public List<FCgItem> Items;

        public FCgProjectileFirePayload()
        {
            Items = new List<FCgItem>();

            Reset();
        }

        public void Reset()
        {
            bAllocated = false;
            Time = 0.0f;
            RealTime = 0.0f;
            Frame = 0;
            ChargePercent = 0.0f;
            Location = Vector3.zero;
            Direction = Vector3.zero;
            AdditionalSpeed = 0.0f;
            HomingTarget = null;
            HomingBoneName = ECgCached.Str.NAME_None;
            HomingAccelerationMagnitude = 0.0f;
            Items.Clear();
        }
    }

    public class FCgProjectilePayload : FCgPooledObjectPayload
    {
        #region "Data Members"

        public ECgProjectileRelevance Relevance;

        public MCgData_Projectile Data;

        public float ChargePercent;

        public Vector3 Direction;

        public Vector3 Location;

        public float AdditionalSpeed;

        public MonoBehaviour HomingTarget;

        public string HomingBone;

        public float HomingAccelerationMagnitude;

        #endregion // Data Members

        public FCgProjectilePayload() : base(){ }

        public void Set(FCgProjectileFirePayload payload)
        {
            ChargePercent               = payload.ChargePercent;
            Location                    = payload.Location;
            Direction                   = payload.Direction;
            AdditionalSpeed             = payload.AdditionalSpeed;
            HomingTarget                = payload.HomingTarget;
            HomingBone                  = payload.HomingBoneName;
            HomingAccelerationMagnitude = payload.HomingAccelerationMagnitude;
        }

        public override void Reset()
	    {
		    base.Reset();

		    Relevance = ECgProjectileRelevance.MAX;
		    ChargePercent = 0.0f;
		    Location = Vector3.zero;
		    Direction = Vector3.zero;
		    AdditionalSpeed = 0.0f;
		    HomingTarget = null;
		    HomingBone = ECgCached.Str.NAME_None;
		    HomingAccelerationMagnitude = 0.0f;
	    }
    }
}
