namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgSnapShot_Player
    {
        #region "Data Members"

        public List<FCgGameEventInfo> GameEventInfos;

        #endregion // Data Members

        public FCgSnapShot_Player()
        {
            GameEventInfos = new List<FCgGameEventInfo>();
        }

        public virtual void Reset()
        {
            GameEventInfos.Clear();
        }

        public void AddGameEvent(FECgGameEvent e)
        {
            FCgGameEventInfo info = new FCgGameEventInfo();
            info.Event            = e;

            GameEventInfos.Add(info);
        }

        public bool HasGameEvent(FECgGameEvent e)
        {
            return GameEventInfos.Find(info => info.Event == e) != null;
        }
    }

    public class MCgPlayerState : MCgPlayerStateBase
    {
        #region "Data Members"

        public FCgSnapShot_Player CurrentSnapShot;

        #endregion // Data Members
    }
}
