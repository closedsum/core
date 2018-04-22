// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgInput_Location : CgInput_Base
    {
        public class CgInputLocation_Event : TCgDelegate_TwoParams<MonoBehaviour, Vector3> { }

        #region "Data Members"

        private Dictionary<ECgInputEvent, CgInputLocation_Event> Events;

        #endregion // Data Members

        public CgInput_Location()
        {
            Info = new CgInputInfo(ECgInputType.Location, ECgInputValue.Vector);
            Info.Event = ECgInputEvent.Stationary;
            Info.Last_Event = Info.Event;

            Events = new Dictionary<ECgInputEvent, CgInputLocation_Event>(new ECgInputEventEqualityComparer());
            Events.Add(ECgInputEvent.FirstMoved, new CgInputLocation_Event());
            Events.Add(ECgInputEvent.Moved, new CgInputLocation_Event());
            Events.Add(ECgInputEvent.FirstStationary, new CgInputLocation_Event());
            Events.Add(ECgInputEvent.Stationary, new CgInputLocation_Event());
        }

        public void Raw(Vector3 location)
        {
            if ((Manager_Input.CurrentInputActionMap & (ActionMap)) == ECgInputActionMap.NONE)
                return;

            CgInput input = Manager_Input.GetPreviousPreviousInputAction(Action);

            if (input == null && Info.Location != location)
                FirstMoved(location);
            else
            if (Info.Location != location)
                Moved(location);
            else
            if ((input == null && Info.Location == location) || (input != null && input.Location != Info.Location && Info.Location == location))
                FirstStationary(location);
            else
            if (Info.Location == location)
                Stationary(location);
        }

        public void FirstMoved(Vector3 location)
        {
            ECgInputEvent e = ECgInputEvent.FirstMoved;
            Info.Set(e, location);
            Manager_Input.AddInput(Action, e, 0.0f, location);

            Broadcast(e, Manager_Input.InputOwner, location);
        }

        public void Moved(Vector3 location)
        {
            ECgInputEvent e = ECgInputEvent.Moved;
            Info.Set(e, location);
            Manager_Input.AddInput(Action, e, 0.0f, location);

            Broadcast(e, Manager_Input.InputOwner, location);
        }

        public void FirstStationary(Vector3 location)
        {
            ECgInputEvent e = ECgInputEvent.FirstStationary;
            Info.Set(e, location);
            Manager_Input.AddInput(Action, e, 0.0f, location);

            Broadcast(e, Manager_Input.InputOwner, location);
        }

        public void Stationary(Vector3 location)
        {
            ECgInputEvent e = ECgInputEvent.Stationary;
            Info.Set(e, location);
            Manager_Input.AddInput(Action, e, 0.0f, location);

            Broadcast(e, Manager_Input.InputOwner, location);
        }

        public void AddEvent(ECgInputEvent e, CgInputLocation_Event.Event del)
        {
            CgInputLocation_Event handler;
            Events.TryGetValue(e, out handler);
            handler.Add(del);
        }

        private void Broadcast(ECgInputEvent e, MonoBehaviour mb, Vector3 location)
        {
            CgInputLocation_Event del;
            Events.TryGetValue(e, out del);
            del.Broadcast(mb, location);
        }
    }
}
