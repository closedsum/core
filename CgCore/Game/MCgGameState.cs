namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

    public sealed class FECgGameStateRoutine : FECgEnum_byte
    {
        public FECgGameStateRoutine(byte value, string name) : base(value, name) { }
    }

    public sealed class FECgGameStateRoutineEqualityComparer : IEqualityComparer<FECgGameStateRoutine>
    {
        public bool Equals(FECgGameStateRoutine lhs, FECgGameStateRoutine rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgGameStateRoutine x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgGameStateRoutine : TCgEnumMap<FECgGameStateRoutine, byte>
    {
        private static EMCgGameStateRoutine _Instance;
        public static EMCgGameStateRoutine Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgGameStateRoutine();
                }
                return _Instance;
            }
        }

        public static EMCgGameStateRoutine Get()
        {
            return Instance;
        }
    }

    #endregion // Enums

    public class MCgGameState : MonoBehaviour
    {
        #region "Data Members"

        private static MCgGameState _Instance;

        #endregion // Data Members

        public static MCgGameState Get()
        {
            return _Instance;
        }

        public static T Get<T>() where T : MCgGameState
        {
            return (T)_Instance;
        }

        public virtual void Init()
        {
            if (_Instance != null)
                return;

            _Instance = this;
        }

        #region "Routines"

        public virtual bool AddRoutine(FCgRoutine routine)
        {
            return false;
        }

        public virtual bool RemoveRoutine(FCgRoutine routine)
        {
            return false;
        }

        #endregion // Routines
    }
}
