namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgPlayerController : MonoBehaviour, ICgObject
    {
        #region "Data Members"

            #region "Interface"

        private ulong _UniqueObjectId;
        public ulong UniqueObjectId
        {
            get { return _UniqueObjectId; }
            set { _UniqueObjectId = value; }
        }

            #endregion // Interface

        public FCgManager_Input Manager_Input;

        public List<FCgGameEventInfo> GameEventInfoPriorityList;

        public int Index;

        public MCgPlayerState PlayerState;

        public FCgHud Hud;

        public MCgPawn Pawn;

        #endregion // Data Members

        public virtual void Init()
        {
            MCgGameInstance.Get().RegisterUniqueObject(this);

            GameEventInfoPriorityList = new List<FCgGameEventInfo>();
        }

        // Use this for initialization
        void Start()
        {
        }

        public virtual void OnUpdate(float deltaTime)
        {
            PlayerState.OnUpdate(deltaTime);
        }

        protected virtual void PreProcessInput(float deltaTime)
        {
            Manager_Input.PreProcessInput(deltaTime);
        }

        protected virtual void PostProcessInput(float deltaTime)
        {
        }

        public virtual void GatherInput(float deltaTime)
        {
            PreProcessInput(deltaTime);
            PostProcessInput(deltaTime);
        }


        public virtual void Possess(MCgPawn pawn)
        {
            Pawn = pawn;
        }
    }
}
