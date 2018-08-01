namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgPlayerState
    {
        public MCgPawn Pawn;

        public virtual void OnUpdate(float deltaTime)
        {
            Pawn.OnUpdate(deltaTime);
        }

        public virtual void ProcessGameEvents(List<FECgGameEvent> events) { }
    }
}
