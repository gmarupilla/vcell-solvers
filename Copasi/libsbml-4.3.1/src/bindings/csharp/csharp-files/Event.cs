/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace libsbml {

using System;
using System.Runtime.InteropServices;

public class Event : SBase {
	private HandleRef swigCPtr;
	
	internal Event(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.Event_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.EventUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(Event obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (Event obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~Event() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_Event(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public Event(long level, long version) : this(libsbmlPINVOKE.new_Event__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public Event(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_Event__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public Event(Event orig) : this(libsbmlPINVOKE.new_Event__SWIG_2(Event.getCPtr(orig)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public new Event clone() {
    IntPtr cPtr = libsbmlPINVOKE.Event_clone(swigCPtr);
    Event ret = (cPtr == IntPtr.Zero) ? null : new Event(cPtr, true);
    return ret;
  }

  public new string getId() {
    string ret = libsbmlPINVOKE.Event_getId(swigCPtr);
    return ret;
  }

  public new string getName() {
    string ret = libsbmlPINVOKE.Event_getName(swigCPtr);
    return ret;
  }

  public Trigger getTrigger() {
    IntPtr cPtr = libsbmlPINVOKE.Event_getTrigger__SWIG_0(swigCPtr);
    Trigger ret = (cPtr == IntPtr.Zero) ? null : new Trigger(cPtr, false);
    return ret;
  }

  public Delay getDelay() {
    IntPtr cPtr = libsbmlPINVOKE.Event_getDelay__SWIG_0(swigCPtr);
    Delay ret = (cPtr == IntPtr.Zero) ? null : new Delay(cPtr, false);
    return ret;
  }

  public Priority getPriority() {
    IntPtr cPtr = libsbmlPINVOKE.Event_getPriority__SWIG_0(swigCPtr);
    Priority ret = (cPtr == IntPtr.Zero) ? null : new Priority(cPtr, false);
    return ret;
  }

  public string getTimeUnits() {
    string ret = libsbmlPINVOKE.Event_getTimeUnits(swigCPtr);
    return ret;
  }

  public bool getUseValuesFromTriggerTime() {
    bool ret = libsbmlPINVOKE.Event_getUseValuesFromTriggerTime(swigCPtr);
    return ret;
  }

  public new bool isSetId() {
    bool ret = libsbmlPINVOKE.Event_isSetId(swigCPtr);
    return ret;
  }

  public new bool isSetName() {
    bool ret = libsbmlPINVOKE.Event_isSetName(swigCPtr);
    return ret;
  }

  public bool isSetTrigger() {
    bool ret = libsbmlPINVOKE.Event_isSetTrigger(swigCPtr);
    return ret;
  }

  public bool isSetDelay() {
    bool ret = libsbmlPINVOKE.Event_isSetDelay(swigCPtr);
    return ret;
  }

  public bool isSetPriority() {
    bool ret = libsbmlPINVOKE.Event_isSetPriority(swigCPtr);
    return ret;
  }

  public bool isSetTimeUnits() {
    bool ret = libsbmlPINVOKE.Event_isSetTimeUnits(swigCPtr);
    return ret;
  }

  public bool isSetUseValuesFromTriggerTime() {
    bool ret = libsbmlPINVOKE.Event_isSetUseValuesFromTriggerTime(swigCPtr);
    return ret;
  }

  public new int setId(string sid) {
    int ret = libsbmlPINVOKE.Event_setId(swigCPtr, sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new int setName(string name) {
    int ret = libsbmlPINVOKE.Event_setName(swigCPtr, name);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int setTrigger(Trigger trigger) {
    int ret = libsbmlPINVOKE.Event_setTrigger(swigCPtr, Trigger.getCPtr(trigger));
    return ret;
  }

  public int setDelay(Delay delay) {
    int ret = libsbmlPINVOKE.Event_setDelay(swigCPtr, Delay.getCPtr(delay));
    return ret;
  }

  public int setPriority(Priority priority) {
    int ret = libsbmlPINVOKE.Event_setPriority(swigCPtr, Priority.getCPtr(priority));
    return ret;
  }

  public int setTimeUnits(string sid) {
    int ret = libsbmlPINVOKE.Event_setTimeUnits(swigCPtr, sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int setUseValuesFromTriggerTime(bool value) {
    int ret = libsbmlPINVOKE.Event_setUseValuesFromTriggerTime(swigCPtr, value);
    return ret;
  }

  public int unsetId() {
    int ret = libsbmlPINVOKE.Event_unsetId(swigCPtr);
    return ret;
  }

  public int unsetName() {
    int ret = libsbmlPINVOKE.Event_unsetName(swigCPtr);
    return ret;
  }

  public int unsetDelay() {
    int ret = libsbmlPINVOKE.Event_unsetDelay(swigCPtr);
    return ret;
  }

  public int unsetPriority() {
    int ret = libsbmlPINVOKE.Event_unsetPriority(swigCPtr);
    return ret;
  }

  public int unsetTimeUnits() {
    int ret = libsbmlPINVOKE.Event_unsetTimeUnits(swigCPtr);
    return ret;
  }

  public int addEventAssignment(EventAssignment ea) {
    int ret = libsbmlPINVOKE.Event_addEventAssignment(swigCPtr, EventAssignment.getCPtr(ea));
    return ret;
  }

  public EventAssignment createEventAssignment() {
    IntPtr cPtr = libsbmlPINVOKE.Event_createEventAssignment(swigCPtr);
    EventAssignment ret = (cPtr == IntPtr.Zero) ? null : new EventAssignment(cPtr, false);
    return ret;
  }

  public Trigger createTrigger() {
    IntPtr cPtr = libsbmlPINVOKE.Event_createTrigger(swigCPtr);
    Trigger ret = (cPtr == IntPtr.Zero) ? null : new Trigger(cPtr, false);
    return ret;
  }

  public Delay createDelay() {
    IntPtr cPtr = libsbmlPINVOKE.Event_createDelay(swigCPtr);
    Delay ret = (cPtr == IntPtr.Zero) ? null : new Delay(cPtr, false);
    return ret;
  }

  public Priority createPriority() {
    IntPtr cPtr = libsbmlPINVOKE.Event_createPriority(swigCPtr);
    Priority ret = (cPtr == IntPtr.Zero) ? null : new Priority(cPtr, false);
    return ret;
  }

  public ListOfEventAssignments getListOfEventAssignments() {
    IntPtr cPtr = libsbmlPINVOKE.Event_getListOfEventAssignments__SWIG_0(swigCPtr);
    ListOfEventAssignments ret = (cPtr == IntPtr.Zero) ? null : new ListOfEventAssignments(cPtr, false);
    return ret;
  }

  public EventAssignment getEventAssignment(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Event_getEventAssignment__SWIG_0(swigCPtr, n);
    EventAssignment ret = (cPtr == IntPtr.Zero) ? null : new EventAssignment(cPtr, false);
    return ret;
  }

  public EventAssignment getEventAssignment(string variable) {
    IntPtr cPtr = libsbmlPINVOKE.Event_getEventAssignment__SWIG_2(swigCPtr, variable);
    EventAssignment ret = (cPtr == IntPtr.Zero) ? null : new EventAssignment(cPtr, false);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public long getNumEventAssignments() { return (long)libsbmlPINVOKE.Event_getNumEventAssignments(swigCPtr); }

  public EventAssignment removeEventAssignment(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Event_removeEventAssignment__SWIG_0(swigCPtr, n);
    EventAssignment ret = (cPtr == IntPtr.Zero) ? null : new EventAssignment(cPtr, true);
    return ret;
  }

  public EventAssignment removeEventAssignment(string variable) {
    IntPtr cPtr = libsbmlPINVOKE.Event_removeEventAssignment__SWIG_1(swigCPtr, variable);
    EventAssignment ret = (cPtr == IntPtr.Zero) ? null : new EventAssignment(cPtr, true);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public override int getTypeCode() {
    int ret = libsbmlPINVOKE.Event_getTypeCode(swigCPtr);
    return ret;
  }

  public override string getElementName() {
    string ret = libsbmlPINVOKE.Event_getElementName(swigCPtr);
    return ret;
  }

  public override bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.Event_hasRequiredAttributes(swigCPtr);
    return ret;
  }

  public override bool hasRequiredElements() {
    bool ret = libsbmlPINVOKE.Event_hasRequiredElements(swigCPtr);
    return ret;
  }

}

}
