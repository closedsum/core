// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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

        public ECgInputActionHelper InputActionHelper;

        public MonoBehaviour InputOwner;

        float CurrentDeltaTime;

        private Dictionary<KeyCode, CgKeyInput> RawKeyInputs;
        public List<CgKeyInput> RawKeyInputsPressed;

        protected ECgInputAction InputAction_MAX;
        protected byte INPUT_ACTION_MAX;

        public CgInput[] InputPool;

        public List<CgInput> QueuedInputsForNextFrame;

        private int CurrentInputPoolIndex;

        public CgInputFrame[] InputFrames;

        public int CurrentInputFrameIndex;

        public CgInputFrame CurrentInputFrame;

        public int CurrentInputActionMap;

        public List<ECgGameEvent> QueuedGameEventsForNextFrame;

        public CgInputProfile InputProfile;

        #region "Actions"

        protected List<CgInput_Base> Inputs;
        protected List<CgInputInfo> Infos;

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
            InputActionHelper = new ECgInputActionHelper();

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
            Array keyValues  = Enum.GetValues(typeof(KeyCode));
            int keyCodeCount = keyValues.Length;

            RawKeyInputs = new Dictionary<KeyCode, CgKeyInput>(new KeyCodeEqualityComparer());

            for (int i = 0; i < keyCodeCount; ++i)
            {
                KeyCode key = (KeyCode)keyValues.GetValue(i);
                // RightCommand and RightApple have the same value
                if (RawKeyInputs.ContainsKey(key))
                    continue;
                RawKeyInputs.Add(key, new CgKeyInput(key));
            }

            RawKeyInputsPressed = new List<CgKeyInput>();

            QueuedGameEventsForNextFrame = new List<ECgGameEvent>();

            Inputs = new List<CgInput_Base>();
            Infos = new List<CgInputInfo>();

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

        protected void DefineInputActionValue(CgInput_Action input, ECgInputAction action, int ActionMap)
        {
            input.Manager_Input = this;
            input.Action = action;
            input.ActionMap = ActionMap;
            Inputs[(byte)action] = input;
            Infos[(byte)action] = input.Info;
        }

        protected virtual void BindInputs()
        {
        }

        protected void BindInput(KeyCode key, ECgInputAction action, ECgInputEvent e, CgDelegate.Event del)
        {
            CgKeyInput keyInput;
            RawKeyInputs.TryGetValue(key, out keyInput);
            keyInput.Bind(action, e, del);
        }

        protected void BindInputAction(KeyCode key, CgInput_Action input)
        {
            BindInput(key, input.Action, ECgInputEvent.FirstPressed, input.FirstPressed);
            BindInput(key, input.Action, ECgInputEvent.FirstReleased, input.FirstReleased);
        }

        private void RecordRawInputs()
        {
            RawKeyInputsPressed.Clear();

            Dictionary<KeyCode, CgKeyInput>.ValueCollection keyInputs = RawKeyInputs.Values;

            foreach (CgKeyInput keyInput in keyInputs)
            {
                KeyCode key     = keyInput.Key;
                ECgInputEvent e = keyInput.Event;

                // Pressed
                if (Input.GetKey(key))
                {
                    if (e == ECgInputEvent.FirstPressed || e == ECgInputEvent.Pressed)
                        keyInput.Set(ECgInputEvent.Pressed, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstPressed, Time.time, Time.unscaledTime, 0);
                    RawKeyInputsPressed.Add(keyInput);
                }
                // Released
                else
                {
                    if (e == ECgInputEvent.FirstReleased || e == ECgInputEvent.Released)
                        keyInput.Set(ECgInputEvent.Released, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstReleased, Time.time, Time.unscaledTime, 0);
                }
            }
        }

        public virtual void PreProcessInput(float deltaTime)
        {
            CurrentDeltaTime       = deltaTime;
            CurrentInputFrameIndex = (CurrentInputFrameIndex + 1) % MAX_INPUT_FRAMES;
            InputFrames[CurrentInputFrameIndex].Init(Time.time, Time.unscaledTime, deltaTime, (ulong)Time.frameCount);

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

            CgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            // Add Queued Inputs
            int queuedInputCount = QueuedInputsForNextFrame.Count;

            for (int i = 0; i < queuedInputCount; ++i)
            {
                inputFrame.Inputs.Add(QueuedInputsForNextFrame[i]);
            }
            QueuedInputsForNextFrame.Clear();

            // Set FirstReleased Events to Released after 1 Frame

            // TODO: Potentially Optimize to O(n) versus O(n^2)
            for (byte i = 0; i < INPUT_ACTION_MAX; ++i)
            {
                CgInputInfo info      = Infos[i];
                ECgInputAction action = (ECgInputAction)InputActionHelper.Get(i);
                int inputCount        = inputFrame.Inputs.Count;

                // Transition From FirstPressed to Pressed
                if (info.Event == ECgInputEvent.FirstPressed &&
                    info.Last_Event == ECgInputEvent.FirstPressed)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (inputFrame.Inputs[j].Action == action)
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
                        if (inputFrame.Inputs[j].Action == action)
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
                        if (inputFrame.Inputs[j].Action == action)
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
                        if (inputFrame.Inputs[j].Action == action)
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
            int _inputCount = inputFrame.Inputs.Count;

            for (byte i = 0; i < _inputCount; ++i)
            {
                ProcessInput(InputOwner, null, inputFrame.Inputs[i], deltaTime);
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
            CurrentInputFrame = inputFrame;
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

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                CgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                {
                    input.IsConsumed = true;
                    break;
                }
            }

            count = CurrentInputFrame.Inputs.Count;

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

        public void SetCurrentInputActionMap(ECgInputActionMap actionMap)
        {
	        CurrentInputActionMap |= actionMap;
        }

        public void SetCurrentInputActionMap(int actionMap)
        {
            CurrentInputActionMap |= actionMap;
        }

        public void ClearCurrentInputActionMap(ECgInputActionMap actionMap)
        {
            CurrentInputActionMap &= actionMap;
        }

        public void ClearCurrentInputActionMap(int actionMap)
        {
            CurrentInputActionMap &= actionMap;
        }

        public CgInput GetPreviousInputAction(ECgInputAction action)
        {
	        int lastInputFrame  = CgMath.Mod(CurrentInputFrameIndex - 1, MAX_INPUT_FRAMES);
            CgInput input       = InputFrames[lastInputFrame].GetInput(action);

	        return input;
        }

        public CgInput GetPreviousInputAction(ECgInputAction action, ECgInputEvent e)
        {
            int lastInputFrame  = CgMath.Mod(CurrentInputFrameIndex - 1, MAX_INPUT_FRAMES);
            CgInput input       = InputFrames[lastInputFrame].GetInput(action, e);

            return input;
        }

        public CgInput GetPreviousInputAction(ECgInputAction action, List<ECgInputEvent> events)
        {
            int lastInputFrame  = CgMath.Mod(CurrentInputFrameIndex - 1, MAX_INPUT_FRAMES);
            CgInput input       = InputFrames[lastInputFrame].GetInput(action, events);

            return input;
        }

        public CgInput GetPreviousPreviousInputAction(ECgInputAction action)
        {
	        int lastInputFrame  = CgMath.Mod(CurrentInputFrameIndex - 2, MAX_INPUT_FRAMES);
            CgInput input       = InputFrames[lastInputFrame].GetInput(action);

	        return input;
        }

        public void QueueGameEvent(ECgGameEvent e)
        {
            QueuedGameEventsForNextFrame.Add(e);
        }

        public void ClearQueuedGameEvents()
        {
            QueuedGameEventsForNextFrame.Clear();
        }

        public void DetermineGameEvents(List<CgInput> inputs)
        {
        }

        public bool HasActionEventOccured(ECgInputAction action, ECgInputEvent e)
        {
            CgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                CgInput input = inputFrame.Inputs[i];

                if (input.Action == action && input.Event == e)
                    return true;
            }
            return false;
        }

        public float GetInputValue(ECgInputAction action)
        {
	        CgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

	        int count = inputFrame.Inputs.Count;

	        for (int i = 0; i < count; ++i)
	        {
		        CgInput input = inputFrame.Inputs[i];

		        if (input.Action == action)
			        return input.Value;
	        }
	        return 0.0f;
        }

        public Vector3 GetInputLocation(ECgInputAction action)
        {
            CgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                CgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                    return input.Location;
            }
            return Vector3.zero;
        }

        public ECgInputEvent GetInputEvent(ECgInputAction action)
        {
            CgInputFrame inputFrame = InputFrames[CurrentInputFrameIndex];

            int count = inputFrame.Inputs.Count;

            for (int i = 0; i < count; ++i)
            {
                CgInput input = inputFrame.Inputs[i];

                if (input.Action == action)
                    return input.Event;
            }
            return ECgInputEvent.MAX;
        }

        public float GetInputDuration(ECgInputAction action)
        {
            return Infos[(byte)action].Duration;
        }

        #region "Profile"

        public bool CanSaveInputActionMapping(ECgInputDevice device, ECgInputAction action)
        {
	        return true;
        }

        public string GetSavePath()
        {
            //return FPaths::ConvertRelativePathToFull(FPaths::GameSavedDir()) + TEXT("/");
            return "";
        }

        public string GetInputProfileFilenameAndPath()
        {
            //return GetSavePath() + TEXT("InputProfile") + FString::FromInt(ControllerId) + TEXT(".json");
            return "";
        }

        public void SaveInputProfile()
        {
            /*
            FString OutputString;
            TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory <>::Create(&OutputString);

            JsonWriter->WriteObjectStart();

            UCsCommon_Load::WriteStructToJson(JsonWriter, (void*)(&InputProfile), FCsInputProfile::StaticStruct(), nullptr);

            JsonWriter->WriteObjectEnd();

            JsonWriter->Close();

            const FString Filename = GetInputProfileFilenameAndPath();

            FFileHelper::SaveStringToFile(OutputString, *Filename);
            */
        }

        public void LoadDefaultInputProfile()
        {
            /*
            InputProfile.Reset();

            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            // ActionMappings
            int actionCount = PlayerInput->ActionMappings.Count;

            for (int i = 0; i < actionCount; ++i)
            {
                FInputActionKeyMapping & Mapping = PlayerInput->ActionMappings[i];

                ECgInputAction action = ECgInputAction.ToType(Mapping.ActionName);

                if (Action == InputAction_MAX)
                    continue;

                string actionName     = action.name;;
                KeyCode key           = Mapping.Key;
                const FString keyName = key.ToString();

                // MouseAndKeyboard
                if (CanSaveInputActionMapping(ECgInputDevice.MouseAndKeyboard, action) &&
                    IsValidKey(ECgInputDevice.MouseAndKeyboard, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.MouseAndKeyboard, actionName, action, keyName, Key);
                }
                // Gamepad
                if (CanSaveInputActionMapping(ECgInputDevice.Gamepad, action) &&
                    IsValidKey(ECgInputDevice.Gamepad, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.Gamepad, actionName, action, keyName, key);
                }
            }
            // AxisMappings
            int axisCount = PlayerInput->AxisMappings.Count;

            for (int i = 0; i < axisCount; ++i)
            {
                FInputAxisKeyMapping & Mapping = PlayerInput->AxisMappings[i];

                ECgInputAction action = ECgInputAction.ToType(Mapping.AxisName);

                if (action == null)
                    continue;

                string actionName   = ECgInputAction.ToStr(Action);
                KeyCode key         = Mapping.Key;
                string keyName      = key.ToString();

                // MouseAndKeyboard
                if (CanSaveInputActionMapping(ECgInputDevice.MouseAndKeyboard, action) &&
                    IsValidKey(ECgInputDevice.MouseAndKeyboard, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.MouseAndKeyboard, actionName, action, keyName, key);
                }
                // Gamepad
                if (CanSaveInputActionMapping(ECgInputDevice.Gamepad, action) &&
                    IsValidKey(ECgInputDevice.Gamepad, key))
                {
                    InputProfile.AddMapping(ECgInputDevice.Gamepad, actionName, action, keyName, key);
                }
            }
            */
        }

        public void LoadInputProfile()
        {
            /*
            string inputProfileFilename = GetInputProfileFilenameAndPath();

            string dataJson;

            if (FFileHelper::LoadFileToString(DataJson, *InputProfileFilename))
            {
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory < TCHAR >::Create(DataJson);

                TSharedPtr<FJsonObject> JsonParsed;

                if (FJsonSerializer::Deserialize(JsonReader, JsonParsed) && JsonParsed.IsValid())
                {
                    UCsCommon_Load::ReadStructFromJson(JsonParsed, &InputProfile, FCsInputProfile::StaticStruct(), nullptr);
                    // Update Action and Key members

                    for (int32 I = 0; I < ECS_INPUT_DEVICE_MAX; ++I)
                    {
                        FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[I];
                        TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

                        const int32 Count = Mappings.Num();

                        for (int32 J = 0; J < Count; J++)
                        {
                            FCsInputActionMapping & Mapping = Mappings[J];

                            Mapping.Action = (*StringToInputAction)(Mapping.ActionName);
                            Mapping.Key = GetKey(Mapping.KeyName);
                        }
                    }
                }
                else
                {
                    UE_LOG(LogCs, Warning, TEXT("ACsManager_Input::LoadInputProfile: %s is NOT Valid"), *InputProfileFilename);
                }
            }
            else
            {
                UE_LOG(LogCs, Warning, TEXT("ACsManager_Input::LoadInputProfile: %s NOT found. Loading Default Input Profile."), *InputProfileFilename);

                LoadDefaultInputProfile();
            }
            */
        }

        public bool IsValidKey(ECgInputDevice device, KeyCode key)
        {
	        if (key == KeyCode.None)
		        return false;

	        // MouseAndKeyboard
	        if (device == ECgInputDevice.MouseAndKeyboard)
	        {
		        if (CgKey.IsGamepadKey(key))
			        return false;
	        }
	        // Gamepad
	        if (device == ECgInputDevice.Gamepad)
	        {
		        if (!CgKey.IsGamepadKey(key))
			        return false;
	        }
	        return true;
        }

        public KeyCode GetKey(string keyName)
        {
            if (keyName == "")
                return KeyCode.None;

            return (KeyCode)Enum.Parse(typeof(KeyCode), keyName);
        }

        public ECgInputAction GetActionFromKey(ECgInputDevice device, KeyCode key)
        {
            /*
            FCsInputActionMappings & DeviceMapping   = InputProfile.DeviceMappings[(uint8)Device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            count = Mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (Mapping.Key == key)
                    return Mapping.Action;
            }
            */
            return null;
        }

        public KeyCode GetKeyFromAction(ECgInputDevice device, ECgInputAction action)
        {
            /*
            FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[(uint8)Device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            const count = Mappings.Count;

            for (int i = 0; i < count; ++i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (Mapping.Action == action)
                    return Mapping.Key;
            }
            */
            return KeyCode.None;
        }

        public KeyCode GetKeyFromAction(ECgInputAction action)
        {
            /*
            UPlayerInput* PlayerInput = UCsCommon::GetLocalPlayerInput(GetWorld());

            string ActionName = ECgInputAction.ToStr(action);

            int actionCount = PlayerInput->ActionMappings.Count;

            for (int i = 0; i < actionCount; ++i)
            {
                FInputActionKeyMapping & Mapping = PlayerInput->ActionMappings[i];

                if (actionName == Mapping.ActionName)
                    return Mapping.Key;
            }

            int axisCount = PlayerInput->AxisMappings.Count;

            for (int i = 0; i < axisCount; ++i)
            {
                FInputAxisKeyMapping & Mapping = PlayerInput->AxisMappings[i];

                if (actionName == Mapping.AxisName)
                    return Mapping.Key;
            }
            */
            return KeyCode.None;
        }

        public void UnbindActionMapping(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput       = Controller->PlayerInput;

            string actionName = ECgInputAction.ToStr(action);
            // Remove binding from PlayerInput ActionMapping
            int mappingCount = PlayerInput->ActionMappings.Count;

            for (int i = mappingCount - 1; i >= 0; --i)
            {
                FInputActionKeyMapping & Mapping = PlayerInput->ActionMappings[I];

                if (actionName == Mapping.ActionName &&
                    key == Mapping.Key)
                {
                    PlayerInput->ActionMappings.RemoveAt(i);
                    break;
                }
            }
            // Clear Key on Mapping from InputProfile
            FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[(uint8)Device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            int count = Mappings.Count;

            for (i = count - 1; i >= 0; --i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (actionName == Mapping.ActionName &&
                    Key == Mapping.Key)
                {
                    Mapping.KeyName = "";
                    Mapping.Key = KeyCode.None;
                    break;
                }
            }
            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void UnbindAxisMapping(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            string actionName = ECgInputAction.ToStr(action);
            // Remove binding from PlayerInput ActionMapping
            int mappingCount = PlayerInput->AxisMappings.Count;

            for (int i = mappingCount - 1; i >= 0; --i)
            {
                FInputAxisKeyMapping & Mapping = PlayerInput->AxisMappings[i];

                if (actionName == Mapping.AxisName &&
                    key == Mapping.Key)
                {
                    PlayerInput->AxisMappings.RemoveAt(i);
                    break;
                }
            }
            // Clear Key on Mapping from InputProfile
            FCsInputActionMappings & DeviceMapping = InputProfile.DeviceMappings[(byte)device];
            TArray<FCsInputActionMapping> & Mappings = DeviceMapping.Mappings;

            int count = Mappings.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                FCsInputActionMapping & Mapping = Mappings[i];

                if (actionName == Mapping.ActionName &&
                    key == Mapping.Key)
                {
                    Mapping.KeyName = "";
                    Mapping.Key = KeyCode.None;
                    break;
                }
            }
            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void UnbindMapping(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            if (Infos[(byte)action].Type == ECgInputType.Action)
                UnbindActionMapping(device, action, key);
            if (Infos[(byte)action].Type == ECgInputType.Axis)
                UnbindAxisMapping(device, action, key);
        }

        // TODO: Need to store the original Key "Keyboard" mappings for Input. Do similar for control setup

        public void RebindActionMapping(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            if (!IsValidKey(device, key))
                return;
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            FCsInputActionMapping & Mapping = InputProfile.GetMapping(device, action);
            KeyCode previousKey = Mapping.Key;

            // If it is the SAME Key, Do Nothing
            if (key == previousKey)
                return;

            // Check if another Action is already mapped to the Key
            ECgInputAction otherAction = GetActionFromKey(device, key);

            // Unbind ActionMapping for OtherAction bound to Key
            if (otherAction != ECgInputAction.GetMAX())
            {
                UnbindMapping(Device, OtherAction, Key);
            }

            string actionName = ECgInputAction.ToStr(action);
            int count         = PlayerInput->ActionMappings.Count;

            bool found = false;

            for (int i = 0; i < count; ++i)
            {
                FInputActionKeyMapping & ActionMapping = PlayerInput->ActionMappings[i];

                if (actionName == ActionMapping.ActionName &&
                    previousKey == ActionMapping.Key)
                {
                    ActionMapping.Key = key;
                    found = true;
                    break;
                }
            }
            // Add Mapping if it is NOT found
            if (!found)
            {
                PlayerInput->ActionMappings.AddDefaulted();

                FInputActionKeyMapping & ActionMapping = PlayerInput->ActionMappings[count];
                ActionMapping.ActionName = Mapping.ActionName;
                ActionMapping.Key = Mapping.Key;
            }

            InputProfile.SetKey(device, action, key);

            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void RebindAxisMapping(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            if (!IsValidKey(device, key))
                return;
            /*
            ACsPlayerController* Controller = Cast<ACsPlayerController>(GetInputOwner());
            UPlayerInput* PlayerInput = Controller->PlayerInput;

            FCsInputActionMapping & Mapping = InputProfile.GetMapping(device, action);
            KeyCode previousKey = Mapping.Key;

            // If it is the SAME Key, Do Nothing
            if (key == previousKey)
                return;

            // Check if another Action is already mapped to the Key
            ECgInputAction otherAction = GetActionFromKey(device, key);

            // Unbind ActionMapping for OtherAction bound to Key
            if (otherAction != ECgInputAction.GetMAX())
            {
                UnbindMapping(device, otherAction, key);
            }

            string actionName = ECgInputAction.ToStr(action);
            int count         = PlayerInput->AxisMappings.Count;

            bool found = false;

            for (int i = 0; i < count; ++i)
            {
                FInputAxisKeyMapping & AxisMapping = PlayerInput->AxisMappings[i];

                if (actionName == AxisMapping.AxisName &&
                    previousKey == AxisMapping.Key)
                {
                    AxisMapping.Key = key;
                    found = true;
                    break;
                }
            }
            // Add Mapping if it is NOT found
            if (!found)
            {
                PlayerInput->AxisMappings.AddDefaulted();

                FInputAxisKeyMapping & AxisMapping = PlayerInput->AxisMappings[dount];
                AxisMapping.AxisName = Mapping.ActionName;
                AxisMapping.Key = Mapping.Key;
                AxisMapping.Scale = Mapping.Scale;
            }
            InputProfile.SetKey(device, action, key);

            PlayerInput->ForceRebuildingKeyMaps(false);
            */
        }

        public void RebindMapping(ECgInputDevice device, ECgInputAction action, KeyCode key)
        {
            if (Infos[(byte)action].Type == ECgInputType.Action)
                RebindActionMapping(device, action, key);
            if (Infos[(byte)action].Type == ECgInputType.Axis)
                RebindAxisMapping(device, action, key);
        }

        #endregion // Profile

        #region "Game Events"

        public void CreateGameEventDefinitionSimple(List<CgGameEventDefinition> definitions, ECgGameEvent gameEvent, ECgInputAction action, ECgInputEvent e)
        {
            definitions.Add(new CgGameEventDefinition());
            CgGameEventDefinition def = definitions[definitions.Count - 1];
	        def.Event = gameEvent;
	        // Sentence
	        {
		        CgInputSentence sentence = def.Sentence;
		        sentence.Phrases.Add(new CgInputPhrase());
		        // Phrase
		        {
			        CgInputPhrase phrase = sentence.Phrases[sentence.Phrases.Count - 1];
			        phrase.Words.Add(new CgInputWord());
			        // Word
			        {
				        CgInputWord word = phrase.Words[phrase.Words.Count - 1];
				        word.AddOrInput(action, e);
			        }
                }
	        }
        }

        #endregion // Game Events
    }
}
