namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgPlayerStateBase : MonoBehaviour
    {
        #region "Data Members"

        [FCgReadOnly]
        public byte UniqueMappingId;

        [FCgReadOnly]
        public MCgPawn LinkedPawn;

            #region "OnBoard"

        [FCgReadOnly]
        public bool bOnBoardCompleted;

            #endregion // OnBoard

        #endregion // Data Members

        public virtual void Init() { }
        public virtual void OnUpdate(float deltaTime) { }

        public virtual MCgPawn GetMyPawn()
        {
            if (LinkedPawn != null)
                return LinkedPawn;

            MCgGameState gameState = MCgGameState.Get();

            foreach (MCgPawn pawn in gameState.Pawns)
            {
                if (pawn.PlayerState == this)
                {
                    LinkedPawn = pawn;
                }
            }
            return LinkedPawn;
        }

        public virtual T GetMyPawn<T>()
            where T : MCgPawn
        {
            return (T)GetMyPawn();
        }

        #region "OnBoard"

        public virtual bool IsOnBoardCompleted_Game()
        {
            //if (!bOnBoardCompleted)
            //    return false;

            MCgPawn pawn = GetMyPawn();

            if (pawn == null)
                return false;
            if (pawn.PlayerState != this)
                return false;
            return true;
        }

        #endregion // OnBoard

        public virtual void ProcessCurrentLocalSnapShot(float deltaTime) { }
    }
}