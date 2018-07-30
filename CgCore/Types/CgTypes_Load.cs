﻿namespace CgCore
{
    using System.Collections.Generic;

    public sealed class ECgAssetType : ECgEnum_byte
    {
        public ECgAssetType(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgAssetTypeEqualityComparer : IEqualityComparer<ECgAssetType>
    {
        public bool Equals(ECgAssetType lhs, ECgAssetType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgAssetType x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgAssetType : TCgEnumMap<ECgAssetType, byte>
    {
        private static EMCgAssetType _Instance;
        public static EMCgAssetType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgAssetType();
                }
                return _Instance;
            }
        }

        public static EMCgAssetType Get()
        {
            return Instance;
        }
    }

    public enum ECgLoadAsyncOrder : byte
    {
        // Default to Bulk
        None,
        // Process Assets IN ORDER 1 by 1
        FirstToLast,
        // Group Assets, only get a notification once the ENTIRE Group is Finished
        Bulk,
        MAX
    }

    public struct FCgResourceSize
    {
        public int Bytes;
        public float Kilobytes;
        public float Megabytes;

        public static FCgResourceSize operator +(FCgResourceSize lhs, FCgResourceSize rhs)
        {
            lhs.Bytes += rhs.Bytes;
            lhs.Kilobytes += rhs.Kilobytes;
            lhs.Megabytes += rhs.Megabytes;
            return lhs;
        }

        public string ToString_Megabytes()
        {
            return "" + Megabytes + " mb(" + Kilobytes + " kb, " + Bytes + " bytes)";
        }
        public void Reset()
        {
            Bytes = 0;
            Kilobytes = 0.0f;
            Megabytes = 0.0f;
        }
    }

    public struct FCgAssetReferenceLoadedCache
    {
        public string Reference;
        public int Count;
        public FCgResourceSize Size;
        public float Time;
    }
}
