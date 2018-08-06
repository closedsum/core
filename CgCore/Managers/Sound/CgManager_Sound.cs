namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgSoundPayload : FCgPooledObjectPayload
    {
        public FCgSoundPayload() : base()
        {
        }
    }

    /*
    public class FCgManager_Sound : TCgManager_PooledMonoObjects<FECgSoundType, MCgSound, FCgSoundPayload>
    {
        private static readonly int PAYLOAD_COUNT = 8;

        public FCgManager_Sound() : base()
        {
            for (int i = 0; i < PAYLOAD_COUNT; ++i)
            {
                Payloads.Add(new FCgSoundPayload());
            }
        }
    }
    */

    public class ICgManager_Sound
    {
        #region "Data Members"

        private static ICgManager_Sound _Instance;
        public static ICgManager_Sound Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new ICgManager_Sound();
                }
                return _Instance;
            }
        }

        #endregion // Data Members

        public ICgManager_Sound() { }

        public static ICgManager_Sound Get()
        {
            return Instance;
        }
    }
}
