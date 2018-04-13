namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgManagerInput_Action_Default : TCgDelegate_TwoParams<ECgInputAction, ECgInputEvent> { }
    public class CgManagerInput_Action : TCgDelegate_OneParam<ECgInputAction> { }
    public class CgManagerInput_Axis_Default : TCgDelegate_ThreeParams<ECgInputAction, ECgInputEvent, float> { }
    public class CgManagerInput_Axis : TCgDelegate_TwoParams<ECgInputAction, float> { }
    public class CgManagerInput_Location_Default : TCgDelegate_ThreeParams<ECgInputAction, ECgInputEvent, Vector3> { }
    public class CgManagerInput_Location : TCgDelegate_TwoParams<ECgInputAction, Vector3> { }
    public class CgManagerInput_Location_Raw : TCgDelegate_OneParam<Vector3> { }
    public class CgManagerInput_Rotation_Default : TCgDelegate_ThreeParams<ECgInputAction, ECgInputEvent, Vector3> { }
    public class CgManagerInput_Rotation : TCgDelegate_TwoParams<ECgInputAction, Vector3> { }
    public class CgManagerInput_Rotation_Raw : TCgDelegate_OneParam<Vector3> { }

    public class CgManager_Input
    {
        #region "Constants"

        public static readonly int INPUT_POOL_SIZE = 65535;
        public static readonly int MAX_INPUT_FRAMES = 300;

        #endregion // Constants

        #region "Delegates"

        #endregion // Delegates

        #region "Data Members"

        public MonoBehaviour InputOwner;

        private CgKeyInput[] RawKeyInputs;
        public List<CgKeyInput> RawKeyInputsPressed;

        protected ECgInputAction InputAction_MAX;
        protected byte INPUT_ACTION_MAX;

        public CgInput[] InputPool;

        public List<CgInput> QueuedInputsForNextFrame;

        private int CurrentInputPoolIndex;

        public CgInputFrame[] InputFrames;

        public int CurrentInputFrameIndex;

        CgInputFrame CurrentInputFrame;

        public int CurrentInputActionMap;

        #region "Actions"

        protected List<CgInput_Base> Inputs;
        protected List<CgInputInfo> Infos;
        protected List<ECgInputEvent> Actions;
        protected List<ECgInputEvent> Last_Actions;

                #region "Pressed Events"

        public CgManagerInput_Action_Default Action_Event;
        public CgManagerInput_Action FirstPressed_Event;
        public CgManagerInput_Action Pressed_Event;
        public CgManagerInput_Action FirstReleased_Event;

                #endregion // Pressed Events

                #region "Axis Events

        public CgManagerInput_Axis_Default Axis_Event;
        public CgManagerInput_Axis Axis_FirstMoved_Event;
        public CgManagerInput_Axis Axis_Moved_Event;
        public CgManagerInput_Axis Axis_FirstStationary_Event;
        public CgManagerInput_Axis Axis_Stationary_Event;

                #endregion // Axis Events

                #region "Location Events"

        public CgManagerInput_Location_Default Location_Event;
        public CgManagerInput_Location Location_FirstMoved_Event;
        public CgManagerInput_Location Location_Moved_Event;
        public CgManagerInput_Location Location_FirstStationary_Event;
        public CgManagerInput_Location Location_Stationary_Event;

                    // Mouse

        public Vector3 CurrentMousePosition;

        public CgManagerInput_Location_Raw Mouse_Location_Raw;

                    // VR

        public CgManagerInput_Location_Raw HMD_Location_Raw;
        public CgManagerInput_Location_Raw LeftHand_Location_Raw;
        public CgManagerInput_Location_Raw RightHand_Location_Raw;

                #endregion // Location Events

                #region "Rotation Events"

        public CgManagerInput_Rotation_Default Rotation_Event;
        public CgManagerInput_Rotation Rotation_FirstMoved_Event;
        public CgManagerInput_Rotation Rotation_Moved_Event;
        public CgManagerInput_Rotation Rotation_FirstStationary_Event;
        public CgManagerInput_Rotation Rotation_Stationary_Event;

                    // VR

        public CgManagerInput_Rotation_Raw HMD_Rotation_Raw;
        public CgManagerInput_Rotation_Raw LeftHand_Rotation_Raw;
        public CgManagerInput_Rotation_Raw RigthHand_Rotation_Raw;

                #endregion // Rotation Events

        #endregion // Action

        #endregion // Data Members

        public CgManager_Input()
        {
            // InputPool
            InputPool = new CgInput[INPUT_POOL_SIZE];

            for (ushort i = 0; i < INPUT_POOL_SIZE; ++i)
            {
                InputPool[i] = new CgInput(i);
            }

            QueuedInputsForNextFrame = new List<CgInput>();

            // InputFrames
            InputFrames = new CgInputFrame[MAX_INPUT_FRAMES];

            for (ushort i = 0; i < MAX_INPUT_FRAMES; ++i)
            {
                InputFrames[i] = new CgInputFrame();
            }

            // Initialize array of RawKeyInputs
            Array keyValues = Enum.GetValues(typeof(KeyCode));
            int keyCodeCount = keyValues.Length;

            RawKeyInputs = new CgKeyInput[keyCodeCount];

            for (int i = 0; i < keyCodeCount; ++i)
            {
                KeyCode key = (KeyCode)keyValues.GetValue(i);

                RawKeyInputs[i] = new CgKeyInput(key);
            }

            RawKeyInputsPressed = new List<CgKeyInput>();

            // Events
            Action_Event = new CgManagerInput_Action_Default();
            FirstPressed_Event = new CgManagerInput_Action();
            Pressed_Event = new CgManagerInput_Action();
            FirstReleased_Event = new CgManagerInput_Action();

            Axis_Event = new CgManagerInput_Axis_Default();
            Axis_FirstMoved_Event = new CgManagerInput_Axis();
            Axis_Moved_Event = new CgManagerInput_Axis();
            Axis_FirstStationary_Event = new CgManagerInput_Axis();
            Axis_Stationary_Event = new CgManagerInput_Axis();

            Location_Event = new CgManagerInput_Location_Default();
            Location_FirstMoved_Event = new CgManagerInput_Location();
            Location_Moved_Event = new CgManagerInput_Location();
            Location_FirstStationary_Event = new CgManagerInput_Location();
            Location_Stationary_Event = new CgManagerInput_Location();

            Mouse_Location_Raw = new CgManagerInput_Location_Raw();

            HMD_Location_Raw = new CgManagerInput_Location_Raw();
            LeftHand_Location_Raw = new CgManagerInput_Location_Raw();
            RightHand_Location_Raw = new CgManagerInput_Location_Raw();

            Rotation_Event = new CgManagerInput_Rotation_Default();
            Rotation_FirstMoved_Event = new CgManagerInput_Rotation();
            Rotation_Moved_Event = new CgManagerInput_Rotation();
            Rotation_FirstStationary_Event = new CgManagerInput_Rotation();
            Rotation_Stationary_Event = new CgManagerInput_Rotation();

            HMD_Rotation_Raw = new CgManagerInput_Rotation_Raw();
            LeftHand_Rotation_Raw = new CgManagerInput_Rotation_Raw();
            RigthHand_Rotation_Raw = new CgManagerInput_Rotation_Raw();
        }

        private void RecordRawInputs()
        {
            RawKeyInputsPressed.Clear();

            int len = RawKeyInputs.Length;

            for (int i = 0; i < len; ++i)
            {
                CgKeyInput keyInput = RawKeyInputs[i];
                KeyCode key         = keyInput.Key;
                ECgInputEvent e     = keyInput.Event;

                // Pressed
                if (Input.GetKey(key))
                {
                    if (e == ECgInputEvent.FirstPressed)
                        keyInput.Set(ECgInputEvent.Pressed, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstPressed, Time.time, Time.unscaledTime, 0);
                    RawKeyInputsPressed.Add(keyInput);
                }
                // Released
                else
                {
                    if (e == ECgInputEvent.FirstStationary)
                        keyInput.Set(ECgInputEvent.FirstReleased, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.Released, Time.time, Time.unscaledTime, 0);
                }
            }
        }

        public virtual void PreProcessInput(float deltaTime)
        {
            RecordRawInputs();

            CurrentMousePosition = Input.mousePosition;

            if (Mouse_Location_Raw != null)
                Mouse_Location_Raw.Broadcast(CurrentMousePosition);

            // VR
        }

        public virtual void PostProcessInput(float deltaTime)
        {
            // TODO: Potentially also capture sustained "released" inputs

            // TODO: This would be the place to process an action that is a combination of multiple inputs in a frame (or over multiple frames)

            CgInputFrame InputFrame = InputFrames[CurrentInputFrameIndex];

            // Add Queued Inputs
            int QueuedInputCount = QueuedInputsForNextFrame.Capacity;

            for (int i = 0; i < QueuedInputCount; ++i)
            {
                InputFrame.Inputs.Add(QueuedInputsForNextFrame[i]);
            }
            QueuedInputsForNextFrame.Clear();

            // Set FirstReleased Events to Released after 1 Frame

            // TODO: Potentially Optimize to O(n) versus O(n^2)
            for (byte i = 0; i < INPUT_ACTION_MAX; ++i)
            {
                CgInputInfo info      = Infos[i];
                ECgInputAction action = ECgInputAction.Get(i);
                int inputCount        = InputFrame.Inputs.Capacity;

                // Transition From FirstPressed to Pressed
                if (info.Event == ECgInputEvent.FirstPressed &&
                    info.Last_Event == ECgInputEvent.FirstPressed)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Pressed;
                }
                // Transition from FirstReleased to Released
                if (info.Event == ECgInputEvent.FirstReleased &&
                    info.Last_Event == ECgInputEvent.FirstReleased)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Released;
                }
                // Transition From FireMoved to Moved
                if (info.Event == ECgInputEvent.FirstMoved &&
                    info.Last_Event == ECgInputEvent.FirstMoved)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Moved;
                }
                // Transition from FirstStationary to Stationary
                if (info.Event == ECgInputEvent.FirstStationary &&
                    info.Last_Event == ECgInputEvent.FirstStationary)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Stationary;
                }
                // Update Last_Actions.
                info.Last_Event = info.Event;

                // Currently NO Bindings for PRESSED Inputs, so manually add them
                if (info.Event == ECgInputEvent.Pressed)
                    AddInput(action, ECgInputEvent.Pressed);
            }
            // Process Inputs
            int _inputCount = InputFrame.Inputs.Capacity;

            for (byte i = 0; i < _inputCount; ++i)
            {
                ProcessInput(InputOwner, null, InputFrame.Inputs[i], deltaTime);
            }

            /*
            // Log Actions
            if (CsCVarLogInputs->GetInt() == CS_CVAR_SHOW_LOG)
            {
                const FString InputActionMapAsString = (*InputActionMapMaskToString)(CurrentInputActionMap);

                UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: ActionMap: %s Frame: %d Time: %f DeltaTime: %f Count: %d"), *InputActionMapAsString, InputFrame.Frame, InputFrame.Time, InputFrame.DeltaTime, InputFrame.Inputs.Num());

                for (uint8 I = 0; I < InputCount; ++I)
                {
                    const FCsInput* Input = InputFrame.Inputs[I];

                    const FString&Action = (*InputActionToString)(Input->Action);
                    const FString&Event = ECsInputEvent::ToString(Input->Event);

                    // Void - No Value
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputActions->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Void)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s"), *Action, *Event);
                    }
                    // Float
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputAxis->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Float)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %f"), *Action, *Event, Input->Value);
                    }
                    // Vector
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputLocations->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Vector)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %s"), *Action, *Event, *Input->Location.ToString());
                    }
                    // Rotator
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputRotations->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Rotator)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %s"), *Action, *Event, *Input->Rotation.ToString());
                    }
                }
            }
            */
            // Copy the Current Input Frame
            CurrentInputFrame = InputFrame;
            // Determine Game Events
            //DetermineGameEvents(InputFrame.Inputs);
        }

        public virtual void ProcessInput(MonoBehaviour actionOwner, CgInput previousInput, CgInput currentInput, float deltaTime)
        {
            if (currentInput == null)
                return;

            ECgInputAction action   = currentInput.Action;
            ECgInputEvent e         = currentInput.Event;
            ECgInputEvent last_e    = Infos[(byte)action].Last_Event;
            float value             = currentInput.Value;
            Vector3 location        = currentInput.Location;
            Vector3 rotation        = currentInput.Rotation;

            CgInputInfo info = Infos[(byte)action];

            // Action
            if (info.Type == ECgInputType.Action)
            {
                if (e == ECgInputEvent.Pressed &&
                    (last_e == ECgInputEvent.FirstPressed || last_e == ECgInputEvent.Pressed))
                {
                    info.Duration += deltaTime;
                }
                else
                {
                    info.Duration = 0.0f;
                }

                Action_Event.Broadcast(action, e);

                // FirstPressed
                if (e == ECgInputEvent.FirstPressed)
                    FirstPressed_Event.Broadcast(action);
                // Pressed
                else
                if (e == ECgInputEvent.Pressed)
                    Pressed_Event.Broadcast(action);
                // FirstReleased
                else
                if (e == ECgInputEvent.FirstReleased)
                    FirstReleased_Event.Broadcast(action);
            }
            // Axis
            if (info.Type == ECgInputType.Axis)
            {
                if ((e == ECgInputEvent.FirstMoved || e == ECgInputEvent.Moved) &&
                    (last_e == ECgInputEvent.FirstMoved || last_e == ECgInputEvent.Moved))
                {
                    info.Duration += deltaTime;
                }
                else
                {
                    info.Duration = 0.0f;
                }

                Axis_Event.Broadcast(action, e, value);

                // FirstMoved
                if (e == ECgInputEvent.FirstMoved)
                    Axis_FirstMoved_Event.Broadcast(action, value);
                // Moved
                else
                if (e == ECgInputEvent.Moved)
                    Axis_Moved_Event.Broadcast(action, value);
                // FirstStationary
                else
                if (e == ECgInputEvent.FirstStationary)
                    Axis_FirstStationary_Event.Broadcast(action, value);
                // Stationary
                else
                if (e == ECgInputEvent.Stationary)
                    Axis_Stationary_Event.Broadcast(action, value);
            }
            // Location
            else
            if (info.Type == ECgInputType.Location)
            {
                Location_Event.Broadcast(action, e, location);

                // FirstMoved
                if (e == ECgInputEvent.FirstMoved)
                    Location_FirstMoved_Event.Broadcast(action, location);
                // Moved
                else
                if (e == ECgInputEvent.Moved)
                    Location_Moved_Event.Broadcast(action, location);
                // FirstStationary
                else
                if (e == ECgInputEvent.FirstStationary)
                    Location_FirstStationary_Event.Broadcast(action, location);
                // Stationary
                else
                if (e == ECgInputEvent.Stationary)
                    Location_Stationary_Event.Broadcast(action, location);
            }
            // Rotation
            else
            if (info.Type == ECgInputType.Rotation)
            {
                Rotation_Event.Broadcast(action, e, rotation);

                // FirstMoved
                if (e == ECgInputEvent.FirstMoved)
                    Rotation_FirstMoved_Event.Broadcast(action, rotation);
                // Moved
                else
                if (e == ECgInputEvent.Moved)
                    Rotation_Moved_Event.Broadcast(action, rotation);
                // FirstStationary
                else
                if (e == ECgInputEvent.FirstStationary)
                    Rotation_FirstStationary_Event.Broadcast(action, rotation);
                // Stationary
                else
                if (e == ECgInputEvent.Stationary)
                    Rotation_Stationary_Event.Broadcast(action, rotation);
            }
        }

        public CgInput AllocateInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
            for (int i = 0; i < INPUT_POOL_SIZE; ++i)
            {
                CurrentInputPoolIndex = (CurrentInputPoolIndex + i) % INPUT_POOL_SIZE;
                CgInput input         = InputPool[CurrentInputPoolIndex];

                // Add Input to InputFrame
                if (!input.IsAllocated)
                {
                    input.Allocate(action, e, value, location, rotation);
                    return input;
                }
            }
            Debug.LogError("CgManager_Input::AllocateInput: Input Pool has been exhaused.");
            return null;
        }

        public virtual void AddInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
            CgInput input = AllocateInput(action, e, value, location, rotation);
            InputFrames[CurrentInputFrameIndex].Inputs.Add(input);
        }

        public virtual void QueueInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 location = new Vector3(), Vector3 rotation = new Vector3())
        {
	        CgInput input = AllocateInput(action, e, value, location, rotation);

            QueuedInputsForNextFrame.Add(input);
        }

        public void ConsumeInput(ECgInputAction action)
        {
            CgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Capacity;

            for (int i = 0; i < count; ++i)
            {
                CgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                {
                    input.IsConsumed = true;
                    break;
                }
            }

            count = CurrentInputFrame.Inputs.Capacity;

            for (int i = count - 1; i >= 0; --i)
            {
                CgInput input = CurrentInputFrame.Inputs[i];

                if (input.Action == action)
                {
                    CurrentInputFrame.Inputs.RemoveAt(i);
                    break;
                }
            }
        }
    }
}
