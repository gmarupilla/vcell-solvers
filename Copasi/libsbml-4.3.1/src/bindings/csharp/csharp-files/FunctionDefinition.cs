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

public class FunctionDefinition : SBase {
	private HandleRef swigCPtr;
	
	internal FunctionDefinition(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.FunctionDefinition_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.FunctionDefinitionUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(FunctionDefinition obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (FunctionDefinition obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~FunctionDefinition() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_FunctionDefinition(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public FunctionDefinition(long level, long version) : this(libsbmlPINVOKE.new_FunctionDefinition__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public FunctionDefinition(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_FunctionDefinition__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public FunctionDefinition(FunctionDefinition orig) : this(libsbmlPINVOKE.new_FunctionDefinition__SWIG_2(FunctionDefinition.getCPtr(orig)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public new FunctionDefinition clone() {
    IntPtr cPtr = libsbmlPINVOKE.FunctionDefinition_clone(swigCPtr);
    FunctionDefinition ret = (cPtr == IntPtr.Zero) ? null : new FunctionDefinition(cPtr, true);
    return ret;
  }

  public new string getId() {
    string ret = libsbmlPINVOKE.FunctionDefinition_getId(swigCPtr);
    return ret;
  }

  public new string getName() {
    string ret = libsbmlPINVOKE.FunctionDefinition_getName(swigCPtr);
    return ret;
  }

  public ASTNode getMath() {
    IntPtr cPtr = libsbmlPINVOKE.FunctionDefinition_getMath(swigCPtr);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    return ret;
  }

  public new bool isSetId() {
    bool ret = libsbmlPINVOKE.FunctionDefinition_isSetId(swigCPtr);
    return ret;
  }

  public new bool isSetName() {
    bool ret = libsbmlPINVOKE.FunctionDefinition_isSetName(swigCPtr);
    return ret;
  }

  public bool isSetMath() {
    bool ret = libsbmlPINVOKE.FunctionDefinition_isSetMath(swigCPtr);
    return ret;
  }

  public new int setId(string sid) {
    int ret = libsbmlPINVOKE.FunctionDefinition_setId(swigCPtr, sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new int setName(string name) {
    int ret = libsbmlPINVOKE.FunctionDefinition_setName(swigCPtr, name);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int setMath(ASTNode math) {
    int ret = libsbmlPINVOKE.FunctionDefinition_setMath(swigCPtr, ASTNode.getCPtr(math));
    return ret;
  }

  public int unsetName() {
    int ret = libsbmlPINVOKE.FunctionDefinition_unsetName(swigCPtr);
    return ret;
  }

  public ASTNode getArgument(long n) {
    IntPtr cPtr = libsbmlPINVOKE.FunctionDefinition_getArgument__SWIG_0(swigCPtr, n);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    return ret;
  }

  public ASTNode getArgument(string name) {
    IntPtr cPtr = libsbmlPINVOKE.FunctionDefinition_getArgument__SWIG_1(swigCPtr, name);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public ASTNode getBody() {
    IntPtr cPtr = libsbmlPINVOKE.FunctionDefinition_getBody__SWIG_0(swigCPtr);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    return ret;
  }

  public long getNumArguments() { return (long)libsbmlPINVOKE.FunctionDefinition_getNumArguments(swigCPtr); }

  public override int getTypeCode() {
    int ret = libsbmlPINVOKE.FunctionDefinition_getTypeCode(swigCPtr);
    return ret;
  }

  public override string getElementName() {
    string ret = libsbmlPINVOKE.FunctionDefinition_getElementName(swigCPtr);
    return ret;
  }

  public override bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.FunctionDefinition_hasRequiredAttributes(swigCPtr);
    return ret;
  }

  public override bool hasRequiredElements() {
    bool ret = libsbmlPINVOKE.FunctionDefinition_hasRequiredElements(swigCPtr);
    return ret;
  }

}

}
