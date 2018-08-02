namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgManager_Damage
    {
        #region "Constants"

        public static readonly int EVENT_POOL_SIZE = 255;
        public static readonly int RESULT_POOL_SIZE = 255;

        #endregion // Constants

        #region "Data Members"

        private static FCgManager_Damage _Instance;
        public static FCgManager_Damage Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new FCgManager_Damage();
                }
                return _Instance;
            }
        }

            #region "Event"

        public FCgDamageEvent[] EventPool;

        public int EventPoolIndex;

            #endregion // Event

            #region "Result"

        public FCgDamageResult[] ResultPool;

        public int ResultPoolIndex;

            #endregion // Result

        #endregion // Data Members

        public FCgManager_Damage()
        {
            EventPool = new FCgDamageEvent[EVENT_POOL_SIZE];
            ResultPool = new FCgDamageResult[RESULT_POOL_SIZE];
        }

        public static FCgManager_Damage Get()
        {
            return Instance;
        }

        #region "Event"

        public virtual FCgDamageEvent AllocateEvent()
        {
            return null;
        }

        #endregion // Event

        #region "Result"

        public virtual FCgDamageResult AllocateResult()
        {
            return null;
        }

        #endregion // Result
    }
}