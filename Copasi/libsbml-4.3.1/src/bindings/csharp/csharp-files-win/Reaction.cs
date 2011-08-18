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

public class Reaction : SBase {
	private HandleRef swigCPtr;
	
	internal Reaction(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.Reaction_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.ReactionUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(Reaction obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (Reaction obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~Reaction() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_Reaction(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public Reaction(long level, long version) : this(libsbmlPINVOKE.new_Reaction__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public Reaction(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_Reaction__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public Reaction(Reaction orig) : this(libsbmlPINVOKE.new_Reaction__SWIG_2(Reaction.getCPtr(orig)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  public new Reaction clone() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_clone(swigCPtr);
    Reaction ret = (cPtr == IntPtr.Zero) ? null : new Reaction(cPtr, true);
    return ret;
  }

  public void initDefaults() {
    libsbmlPINVOKE.Reaction_initDefaults(swigCPtr);
  }

  public new string getId() {
    string ret = libsbmlPINVOKE.Reaction_getId(swigCPtr);
    return ret;
  }

  public new string getName() {
    string ret = libsbmlPINVOKE.Reaction_getName(swigCPtr);
    return ret;
  }

  public KineticLaw getKineticLaw() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getKineticLaw__SWIG_0(swigCPtr);
    KineticLaw ret = (cPtr == IntPtr.Zero) ? null : new KineticLaw(cPtr, false);
    return ret;
  }

  public bool getReversible() {
    bool ret = libsbmlPINVOKE.Reaction_getReversible(swigCPtr);
    return ret;
  }

  public bool getFast() {
    bool ret = libsbmlPINVOKE.Reaction_getFast(swigCPtr);
    return ret;
  }

  public string getCompartment() {
    string ret = libsbmlPINVOKE.Reaction_getCompartment(swigCPtr);
    return ret;
  }

  public new bool isSetId() {
    bool ret = libsbmlPINVOKE.Reaction_isSetId(swigCPtr);
    return ret;
  }

  public new bool isSetName() {
    bool ret = libsbmlPINVOKE.Reaction_isSetName(swigCPtr);
    return ret;
  }

  public bool isSetKineticLaw() {
    bool ret = libsbmlPINVOKE.Reaction_isSetKineticLaw(swigCPtr);
    return ret;
  }

  public bool isSetFast() {
    bool ret = libsbmlPINVOKE.Reaction_isSetFast(swigCPtr);
    return ret;
  }

  public bool isSetCompartment() {
    bool ret = libsbmlPINVOKE.Reaction_isSetCompartment(swigCPtr);
    return ret;
  }

  public bool isSetReversible() {
    bool ret = libsbmlPINVOKE.Reaction_isSetReversible(swigCPtr);
    return ret;
  }

  public new int setId(string sid) {
    int ret = libsbmlPINVOKE.Reaction_setId(swigCPtr, sid);
    return ret;
  }

  public new int setName(string name) {
    int ret = libsbmlPINVOKE.Reaction_setName(swigCPtr, name);
    return ret;
  }

  public int setKineticLaw(KineticLaw kl) {
    int ret = libsbmlPINVOKE.Reaction_setKineticLaw(swigCPtr, KineticLaw.getCPtr(kl));
    return ret;
  }

  public int setReversible(bool value) {
    int ret = libsbmlPINVOKE.Reaction_setReversible(swigCPtr, value);
    return ret;
  }

  public int setFast(bool value) {
    int ret = libsbmlPINVOKE.Reaction_setFast(swigCPtr, value);
    return ret;
  }

  public int setCompartment(string sid) {
    int ret = libsbmlPINVOKE.Reaction_setCompartment(swigCPtr, sid);
    return ret;
  }

  public int unsetName() {
    int ret = libsbmlPINVOKE.Reaction_unsetName(swigCPtr);
    return ret;
  }

  public int unsetKineticLaw() {
    int ret = libsbmlPINVOKE.Reaction_unsetKineticLaw(swigCPtr);
    return ret;
  }

  public int unsetFast() {
    int ret = libsbmlPINVOKE.Reaction_unsetFast(swigCPtr);
    return ret;
  }

  public int unsetCompartment() {
    int ret = libsbmlPINVOKE.Reaction_unsetCompartment(swigCPtr);
    return ret;
  }

  public int addReactant(SpeciesReference sr) {
    int ret = libsbmlPINVOKE.Reaction_addReactant(swigCPtr, SpeciesReference.getCPtr(sr));
    return ret;
  }

  public int addProduct(SpeciesReference sr) {
    int ret = libsbmlPINVOKE.Reaction_addProduct(swigCPtr, SpeciesReference.getCPtr(sr));
    return ret;
  }

  public int addModifier(ModifierSpeciesReference msr) {
    int ret = libsbmlPINVOKE.Reaction_addModifier(swigCPtr, ModifierSpeciesReference.getCPtr(msr));
    return ret;
  }

  public SpeciesReference createReactant() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_createReactant(swigCPtr);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, false);
    return ret;
  }

  public SpeciesReference createProduct() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_createProduct(swigCPtr);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, false);
    return ret;
  }

  public ModifierSpeciesReference createModifier() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_createModifier(swigCPtr);
    ModifierSpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new ModifierSpeciesReference(cPtr, false);
    return ret;
  }

  public KineticLaw createKineticLaw() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_createKineticLaw(swigCPtr);
    KineticLaw ret = (cPtr == IntPtr.Zero) ? null : new KineticLaw(cPtr, false);
    return ret;
  }

  public ListOfSpeciesReferences getListOfReactants() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getListOfReactants__SWIG_0(swigCPtr);
    ListOfSpeciesReferences ret = (cPtr == IntPtr.Zero) ? null : new ListOfSpeciesReferences(cPtr, false);
    return ret;
  }

  public ListOfSpeciesReferences getListOfProducts() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getListOfProducts__SWIG_0(swigCPtr);
    ListOfSpeciesReferences ret = (cPtr == IntPtr.Zero) ? null : new ListOfSpeciesReferences(cPtr, false);
    return ret;
  }

  public ListOfSpeciesReferences getListOfModifiers() {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getListOfModifiers__SWIG_0(swigCPtr);
    ListOfSpeciesReferences ret = (cPtr == IntPtr.Zero) ? null : new ListOfSpeciesReferences(cPtr, false);
    return ret;
  }

  public SpeciesReference getReactant(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getReactant__SWIG_0(swigCPtr, n);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, false);
    return ret;
  }

  public SpeciesReference getReactant(string species) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getReactant__SWIG_2(swigCPtr, species);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, false);
    return ret;
  }

  public SpeciesReference getProduct(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getProduct__SWIG_0(swigCPtr, n);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, false);
    return ret;
  }

  public SpeciesReference getProduct(string species) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getProduct__SWIG_2(swigCPtr, species);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, false);
    return ret;
  }

  public ModifierSpeciesReference getModifier(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getModifier__SWIG_0(swigCPtr, n);
    ModifierSpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new ModifierSpeciesReference(cPtr, false);
    return ret;
  }

  public ModifierSpeciesReference getModifier(string species) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_getModifier__SWIG_2(swigCPtr, species);
    ModifierSpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new ModifierSpeciesReference(cPtr, false);
    return ret;
  }

  public long getNumReactants() { return (long)libsbmlPINVOKE.Reaction_getNumReactants(swigCPtr); }

  public long getNumProducts() { return (long)libsbmlPINVOKE.Reaction_getNumProducts(swigCPtr); }

  public long getNumModifiers() { return (long)libsbmlPINVOKE.Reaction_getNumModifiers(swigCPtr); }

  public SpeciesReference removeReactant(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_removeReactant__SWIG_0(swigCPtr, n);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, true);
    return ret;
  }

  public SpeciesReference removeReactant(string species) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_removeReactant__SWIG_1(swigCPtr, species);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, true);
    return ret;
  }

  public SpeciesReference removeProduct(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_removeProduct__SWIG_0(swigCPtr, n);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, true);
    return ret;
  }

  public SpeciesReference removeProduct(string species) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_removeProduct__SWIG_1(swigCPtr, species);
    SpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new SpeciesReference(cPtr, true);
    return ret;
  }

  public ModifierSpeciesReference removeModifier(long n) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_removeModifier__SWIG_0(swigCPtr, n);
    ModifierSpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new ModifierSpeciesReference(cPtr, true);
    return ret;
  }

  public ModifierSpeciesReference removeModifier(string species) {
    IntPtr cPtr = libsbmlPINVOKE.Reaction_removeModifier__SWIG_1(swigCPtr, species);
    ModifierSpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new ModifierSpeciesReference(cPtr, true);
    return ret;
  }

  public override int getTypeCode() {
    int ret = libsbmlPINVOKE.Reaction_getTypeCode(swigCPtr);
    return ret;
  }

  public override string getElementName() {
    string ret = libsbmlPINVOKE.Reaction_getElementName(swigCPtr);
    return ret;
  }

  public override bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.Reaction_hasRequiredAttributes(swigCPtr);
    return ret;
  }

}

}
