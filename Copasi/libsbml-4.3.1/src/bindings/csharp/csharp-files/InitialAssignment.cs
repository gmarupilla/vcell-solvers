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

public class InitialAssignment : SBase {
	private HandleRef swigCPtr;
	
	internal InitialAssignment(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.InitialAssignment_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.InitialAssignmentUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(InitialAssignment obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (InitialAssignment obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~InitialAssignment() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_InitialAssignment(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public InitialAssignment(long level, long version) : this(libsbmlPINVOKE.new_InitialAssignment__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public InitialAssignment(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_InitialAssignment__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public InitialAssignment(InitialAssignment orig) : this(libsbmlPINVOKE.new_InitialAssignment__SWIG_2(InitialAssignment.getCPtr(orig)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public new InitialAssignment clone() {
    IntPtr cPtr = libsbmlPINVOKE.InitialAssignment_clone(swigCPtr);
    InitialAssignment ret = (cPtr == IntPtr.Zero) ? null : new InitialAssignment(cPtr, true);
    return ret;
  }

  public string getSymbol() {
    string ret = libsbmlPINVOKE.InitialAssignment_getSymbol(swigCPtr);
    return ret;
  }

  public ASTNode getMath() {
    IntPtr cPtr = libsbmlPINVOKE.InitialAssignment_getMath(swigCPtr);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    return ret;
  }

  public bool isSetSymbol() {
    bool ret = libsbmlPINVOKE.InitialAssignment_isSetSymbol(swigCPtr);
    return ret;
  }

  public bool isSetMath() {
    bool ret = libsbmlPINVOKE.InitialAssignment_isSetMath(swigCPtr);
    return ret;
  }

  public int setSymbol(string sid) {
    int ret = libsbmlPINVOKE.InitialAssignment_setSymbol(swigCPtr, sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int setMath(ASTNode math) {
    int ret = libsbmlPINVOKE.InitialAssignment_setMath(swigCPtr, ASTNode.getCPtr(math));
    return ret;
  }

  public UnitDefinition getDerivedUnitDefinition() {
    IntPtr cPtr = libsbmlPINVOKE.InitialAssignment_getDerivedUnitDefinition__SWIG_0(swigCPtr);
    UnitDefinition ret = (cPtr == IntPtr.Zero) ? null : new UnitDefinition(cPtr, false);
    return ret;
  }

  public bool containsUndeclaredUnits() {
    bool ret = libsbmlPINVOKE.InitialAssignment_containsUndeclaredUnits__SWIG_0(swigCPtr);
    return ret;
  }

  public override int getTypeCode() {
    int ret = libsbmlPINVOKE.InitialAssignment_getTypeCode(swigCPtr);
    return ret;
  }

  public override string getElementName() {
    string ret = libsbmlPINVOKE.InitialAssignment_getElementName(swigCPtr);
    return ret;
  }

  public override bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.InitialAssignment_hasRequiredAttributes(swigCPtr);
    return ret;
  }

  public override bool hasRequiredElements() {
    bool ret = libsbmlPINVOKE.InitialAssignment_hasRequiredElements(swigCPtr);
    return ret;
  }

  public new string getId() {
    string ret = libsbmlPINVOKE.InitialAssignment_getId(swigCPtr);
    return ret;
  }

}

}
