# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue
from typing import Callable, TypeVar, Generic, Any, Optional, Tuple, Union, Dict
import weakref
from dataclasses import dataclass
import uuid

# "alias" - library (c++)
CsObjectLibrary = ue.CsScriptLibrary_Object

# "alias" - class (c++)
UObject = ue.Object

T = TypeVar('T')

class FPyDelegateHandle:
    """Represents a handle to a delegate entry, similar to Unreal's FDelegateHandle."""
    def __init__(self):
        self._id = str(uuid.uuid4())
    
    def __eq__(self, other):
        if not isinstance(other, FPyDelegateHandle):
            return False
        return self._id == other._id
    
    def __hash__(self):
        return hash(self._id)
    
    def __repr__(self):
        return f'FPyDelegateHandle({self._id})'
        
    def Reset(self):
        self._id = ""

    def IsValid(self) -> bool:
        """Returns True if the delegate handle is valid (has a non-empty ID)."""
        return bool(self._id)

@dataclass
class FPyDelegateEntry:
    """Stores a callback function and its associated object reference.
    
    Example:
        entry = FPyDelegateEntry(callback=my_function, obj_ref=weakref.ref(my_object))
    """
    callback: Callable[..., Any]
    obj_ref: Optional[Union[weakref.ReferenceType, Any]] = None  # Can be weakref or UObject

class FPyMulticastDelegate(Generic[T]):
    """
    A generic event handler that mimics Unreal Engine's TMulticastDelegate.
    Supports adding, removing, and broadcasting to multiple callbacks.
    Can store references to owning objects (UObject or Python objects).
    
    Example:
        # Create a delegate for a specific signature
        delegate = FPyMulticastDelegate[Tuple[str, int]]()  # Callbacks take (str, int) parameters
        
        # Add callbacks
        def callback1(text: str, number: int):
            print(f"Callback 1: {text}, {number}")
            
        class MyClass:
            def callback2(self, text: str, number: int):
                print(f"Callback 2: {text}, {number}")
                
        obj = MyClass()
        handle1 = delegate.Add(callback1)
        handle2 = delegate.AddObject(obj.callback2, obj)
        
        # Broadcast to all callbacks
        delegate.Broadcast("Hello", 42)
        
        # Remove specific callbacks using handles
        delegate.Remove(handle1)
        delegate.Remove(handle2)
    """
    
    def __init__(self):
        """Initialize a new FPyMulticastDelegate.
        
        Example:
            # For callbacks taking no parameters
            delegate = FPyMulticastDelegate[None]()
            
            # For callbacks taking specific parameters
            delegate = FPyMulticastDelegate[Tuple[str, int]]()
        """
        self._delegates: Dict[FPyDelegateHandle, FPyDelegateEntry] = {}
    
    def Add(self, callback: Callable[..., T]) -> FPyDelegateHandle:
        """
        Add a callback function without any object binding.
        
        Args:
            callback: The callback function to add, must match the delegate's signature
            
        Returns:
            FPyDelegateHandle: A handle that can be used to remove this callback later
            
        Example:
            # For a delegate taking (str, int) parameters
            delegate = FPyMulticastDelegate[Tuple[str, int]]()
            
            def my_callback(text: str, number: int):
                print(f"{text}: {number}")
                
            handle = delegate.Add(my_callback)  # Add standalone callback
            # Later...
            delegate.Remove(handle)  # Remove the callback
        """
        if not callable(callback):
            raise TypeError("Callback must be callable")
        return self._add_internal(callback, None)
    
    def AddObject(self, obj: Any, callback: Callable[..., T]) -> FPyDelegateHandle:
        """
        Add a callback function bound to a Python object.
        Creates a weak reference to the object to prevent memory leaks.
        
        Args:
            obj:      (any):              The Python object to bind the callback to
            callback: (Callable[..., T]): The callback function to add, must match the delegate's signature       
            
        Returns:
            FPyDelegateHandle: A handle that can be used to remove this callback later
            
        Example:
            # For a delegate taking (str, int) parameters
            delegate = FPyMulticastDelegate[Tuple[str, int]]()
            
            class MyClass:
                def callback(self, text: str, number: int):
                    print(f"{text}: {number}")
                    
            obj = MyClass()
            handle = delegate.AddObject(obj, obj.callback)  # Add callback bound to object
            # Later...
            delegate.Remove(handle)  # Remove the callback
        """
        if not callable(callback):
            raise TypeError("Callback must be callable")
        if obj is None:
            raise ValueError("Object cannot be None for AddObject")
        if isinstance(obj, UObject):
            raise TypeError("Use AddUObject for UObject instances")
        return self._add_internal(callback, obj)
    
    def AddUObject(self, uobject: Any, callback: Callable[..., T]) -> FPyDelegateHandle:
        """
        Add a callback function bound to a UObject.
        The UObject must be valid.
        
        Args:
            uobject: (UObject):           The UObject to bind the callback to
            callback: (Callable[..., T]): The callback function to add, must match the delegate's signature
                 
        Returns:
            FPyDelegateHandle: A handle that can be used to remove this callback later
            
        Example:
            # For a delegate taking (str, int) parameters
            delegate = FPyMulticastDelegate[Tuple[str, int]]()
            
            # Assuming uobject is a valid UObject
            handle = delegate.AddUObject(uobject, uobject.callback)  # Add callback bound to UObject
            # Later...
            delegate.Remove(handle)  # Remove the callback
        """
        if not callable(callback):
            raise TypeError("Callback must be callable")
        if uobject is None:
            raise ValueError("UObject cannot be None for AddUObject")
        if not isinstance(uobject, UObject):
            raise TypeError("Object must be a UObject for AddUObject")
        if not CsObjectLibrary.is_valid_object(uobject):
            raise ValueError(f"UObject is not valid")
        return self._add_internal(callback, uobject)
    
    def _add_internal(self, callback: Callable[..., T], obj: Optional[Any] = None) -> FPyDelegateHandle:
        """
        Internal method to add a callback with an optional object reference.
        
        Args:
            callback: (Callable[..., T]): The callback function to add, must match the delegate's signature
            obj:      (any):              Optional object reference (UObject or Python object)
            
        Returns:
            FPyDelegateHandle: A handle that can be used to remove this callback later
            
        Raises:
            ValueError: If the callback has already been added to this delegate
            
        Example:
            def my_callback(text: str, number: int):
                print(f"{text}: {number}")
                
            handle = delegate._add_internal(my_callback)  # First add works
            delegate._add_internal(my_callback)  # Raises ValueError
        """
        # Clean up any invalid references first
        self.cleanup()
        
        # Check if this exact callback is already registered
        for entry in self._delegates.values():
            if entry.callback == callback:
                # Get object information for error message
                obj_info = "Anonymous"
                if entry.obj_ref is not None:
                    if isinstance(entry.obj_ref, UObject):
                        # UObject case
                        obj_info = f"UObject {entry.obj_ref.get_name()} Class: {entry.obj_ref.get_class().get_name()}"
                    elif isinstance(entry.obj_ref, weakref.ReferenceType):
                        # Python object case
                        obj = entry.obj_ref()
                        if obj is not None:
                            obj_info = f"Python {obj.__class__.__name__}"
                
                raise ValueError(
                    f"Callback {callback} has already been added to this delegate "
                    f"(bound to {obj_info})"
                )
                
        # Create appropriate reference type
        obj_ref = None
        if obj is not None:
            if isinstance(obj, UObject):
                # UObject case - store directly
                obj_ref = obj
            else:
                # Python object case - create weakref
                obj_ref = weakref.ref(obj)
        
        # Create new handle and entry
        handle = FPyDelegateHandle()
        self._delegates[handle] = FPyDelegateEntry(callback, obj_ref)
        return handle
    
    def Remove(self, handle: FPyDelegateHandle) -> None:
        """
        Remove a callback using its handle.
        
        Args:
            handle: (FPyDelegateHandle): The handle returned when adding the callback
            
        Example:
            handle = delegate.Add(my_callback)
            delegate.Remove(handle)  # Remove the callback
        """
        if handle is None:
            raise ValueError(f"Handle is None")
        if not handle.IsValid():
            raise ValueError(f"Handle is not valid")
        if handle in self._delegates:
            del self._delegates[handle]
            handle.Reset()
    
    def RemoveAll(self, obj: Any) -> None:
        """
        Remove all delegates associated with a specific object (UObject or Python object).
        
        Args:
            obj: (any): The object whose delegates should be removed
            
        Raises:
            ValueError: If obj is None
            ValueError: If obj is a UObject and is not valid
            
        Example:
            # For a Python object
            class MyClass:
                def callback1(self, text: str, number: int):
                    print(f"Callback 1: {text}, {number}")
                def callback2(self, text: str, number: int):
                    print(f"Callback 2: {text}, {number}")
                    
            obj = MyClass()
            delegate.AddObject(obj.callback1, obj)
            delegate.AddObject(obj.callback2, obj)
            delegate.RemoveAll(obj)  # Removes both callbacks
            
            # For a UObject
            delegate.AddUObject(uobject.callback, uobject)
            delegate.RemoveAll(uobject)  # Removes the callback
        """
        if obj is None:
            raise ValueError("Cannot remove delegates for None object")
            
        # Create appropriate reference type
        if isinstance(obj, UObject):
            if not CsObjectLibrary.is_valid_object(obj):
                raise ValueError(f"UObject is not valid")
            # UObject case - store directly
            obj_ref = obj
        else:
            # Python object case - create weakref
            obj_ref = weakref.ref(obj)
        
        # Remove all delegates that match the object reference
        handles_to_remove = [
            handle for handle, entry in self._delegates.items()
            if entry.obj_ref == obj_ref
        ]
        for handle in handles_to_remove:
            del self._delegates[handle]
            handle.Reset()
    
    def Clear(self) -> None:
        """Clear all callbacks from the delegate list.
        
        Example:
            delegate.Add(callback1)
            delegate.Add(callback2)
            delegate.Clear()  # Remove all callbacks
        """
        self._delegates.clear()
    
    def cleanup(self) -> None:
        """
        Remove all delegates whose object references are no longer valid.
        This should be called periodically to clean up dead references.
        
        Example:
            class MyClass:
                def callback(self, text: str, number: int):
                    print(f"{text}: {number}")
                    
            obj = MyClass()
            delegate.AddObject(obj.callback, obj)
            del obj  # Object is destroyed
            
            delegate.cleanup()  # Removes the callback since obj is gone
        """
        valid_handles = []
        for handle, entry in self._delegates.items():
            if entry.obj_ref is None:
                valid_handles.append(handle)
                continue
                
            # Check if it's a UObject
            if isinstance(entry.obj_ref, UObject):
                if CsObjectLibrary.is_valid_object(entry.obj_ref):
                    valid_handles.append(handle)
            # Check if it's a weakref
            elif isinstance(entry.obj_ref, weakref.ReferenceType):
                if entry.obj_ref() is not None:
                    valid_handles.append(handle)
            # Direct reference (should be valid)
            else:
                valid_handles.append(handle)
        
        # Remove invalid handles
        for handle in list(self._delegates.keys()):
            if handle not in valid_handles:
                del self._delegates[handle]
    
    def Broadcast(self, *args: Any, **kwargs: Any) -> None:
        """
        Call all registered callbacks with the given arguments.
        Automatically cleans up invalid references before broadcasting.
        
        Args:
            *args:      (any): Positional arguments to pass to callbacks
            **kwargs:   (any): Keyword arguments to pass to callbacks
            
        Example:
            def callback1(text: str, number: int):
                print(f"Callback 1: {text}, {number}")
                
            def callback2(text: str, number: int):
                print(f"Callback 2: {text}, {number}")
                
            delegate.Add(callback1)
            delegate.Add(callback2)
            delegate.Broadcast("Hello", 42)  # Calls both callbacks with ("Hello", 42)
        """
        self.cleanup()
        
        for entry in self._delegates.values():
            try:
                entry.callback(*args, **kwargs)
            except Exception as e:
                print(f"Error in delegate callback: {e}")
    
    def __iadd__(self, callback: Union[Callable[..., T], Tuple[Callable[..., T], Any]]) -> 'FPyMulticastDelegate':
        """
        Support += operator for adding delegates.
        Can accept either just a callback or a tuple of (callback, obj).
        
        Example:
            # Add callback without object reference
            delegate += lambda text, number: print(f"{text}: {number}")
            
            # Add callback with object reference
            class MyClass:
                def callback(self, text: str, number: int):
                    print(f"{text}: {number}")
            obj = MyClass()
            delegate += (obj.callback, obj)
        """
        if isinstance(callback, tuple):
            self.AddObject(callback[0], callback[1])
        else:
            self.Add(callback)
        return self
    
    def __isub__(self, callback: Callable[..., T]) -> 'FPyMulticastDelegate':
        """
        Support -= operator for removing delegates.
        
        Example:
            def my_callback(text: str, number: int):
                print(f"{text}: {number}")
                
            delegate += my_callback
            delegate -= my_callback  # Remove the callback
        """
        # Find and remove the callback
        for handle, entry in self._delegates.items():
            if entry.callback == callback:
                del self._delegates[handle]
                break
        return self
    
    def __len__(self) -> int:
        """
        Get the number of registered delegates.
        
        Example:
            delegate.Add(callback1)
            delegate.Add(callback2)
            count = len(delegate)  # Returns 2
        """
        return len(self._delegates)
    
    def __bool__(self) -> bool:
        """
        Check if any delegates are registered.
        
        Example:
            if delegate:  # True if any callbacks are registered
                print("Delegate has callbacks")
        """
        return bool(self._delegates)