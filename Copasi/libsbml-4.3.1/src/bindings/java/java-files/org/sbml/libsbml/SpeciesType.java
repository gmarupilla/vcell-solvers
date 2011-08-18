/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * LibSBML implementation of SBML Level&nbsp;2's SpeciesType construct.
 * <p>
 * The term <em>species</em> <em>type</em> refers to reacting entities independent of
 * location.  These include simple ions (e.g., protons, calcium), simple
 * molecules (e.g., glucose, ATP), large molecules (e.g., RNA,
 * polysaccharides, and proteins), and others.
 * <p>
 * SBML Level&nbsp;2 Versions&nbsp;2&ndash;4 provide an explicit
 * {@link SpeciesType} class of object to enable {@link Species} objects of the same type
 * to be related together.  {@link SpeciesType} is a conceptual construct; the
 * existence of {@link SpeciesType} objects in a model has no effect on the model's
 * numerical interpretation.  Except for the requirement for uniqueness of
 * species/species type combinations located in compartments, simulators
 * and other numerical analysis software may ignore {@link SpeciesType} definitions
 * and references to them in a model.
 * <p>
 * There is no mechanism in SBML Level 2 for representing hierarchies of
 * species types.  One {@link SpeciesType} object cannot be the subtype of another
 * {@link SpeciesType} object; SBML provides no means of defining such
 * relationships.
 * <p>
 * As with other major structures in SBML, {@link SpeciesType} has a mandatory
 * attribute, 'id', used to give the species type an identifier.  The
 * identifier must be a text string conforming to the identifer syntax
 * permitted in SBML.  {@link SpeciesType} also has an optional 'name' attribute,
 * of type <code>string.</code>  The 'id' and 'name' must be used according to the
 * guidelines described in the SBML specification (e.g., Section 3.3 in
 * the Level&nbsp;2 Version&nbsp;4 specification).
 * <p>
 * {@link SpeciesType} was introduced in SBML Level 2 Version 2.  It is not
 * available in SBML Level&nbsp;1 nor in Level&nbsp;3.
 * <p>
 * @see Species
 * @see ListOfSpeciesTypes
 * @see CompartmentType
 * @see ListOfCompartmentTypes
 * @see ListOfCompartmentTypes
 * <p>
 * <!---------------------------------------------------------------------- -->
 * <p>
 */

public class SpeciesType extends SBase {
   private long swigCPtr;

   protected SpeciesType(long cPtr, boolean cMemoryOwn)
   {
     super(libsbmlJNI.SpeciesType_SWIGUpcast(cPtr), cMemoryOwn);
     swigCPtr = cPtr;
   }

   protected static long getCPtr(SpeciesType obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (SpeciesType obj)
   {
     long ptr = 0;

     if (obj != null)
     {
       ptr             = obj.swigCPtr;
       obj.swigCMemOwn = false;
     }

     return ptr;
   }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        libsbmlJNI.delete_SpeciesType(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  
  /**
   * Creates a new {@link SpeciesType} using the given SBML <code>level</code> and <code>version</code>
   * values.
   * <p>
   * @param level a long integer, the SBML Level to assign to this {@link SpeciesType}
   * <p>
   * @param version a long integer, the SBML Version to assign to this
   * {@link SpeciesType}
   * <p>
   * @note Upon the addition of a {@link SpeciesType} object to an {@link SBMLDocument}
   * (e.g., using {@link Model#addSpeciesType(SpeciesType st)}),
   * the SBML Level, SBML Version and XML namespace of the document 
   * <em>override</em> the values used when creating the {@link SpeciesType} object via this
   * constructor.  This is necessary to ensure that an SBML document is a
   * consistent structure.  Nevertheless, the ability to supply the values
   * at the time of creation of a {@link SpeciesType} is an important aid to
   * producing valid SBML.  Knowledge of the intented SBML Level and
   * Version determine whether it is valid to assign a particular value to
   * an attribute, or whether it is valid to add an object to an existing
   * {@link SBMLDocument}.
   */
 public SpeciesType(long level, long version) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_SpeciesType__SWIG_0(level, version), true);
  }

  
  /**
   * Creates a new {@link SpeciesType} using the given {@link SBMLNamespaces} object
   * <code>sbmlns</code>.
   * <p>
   * The {@link SBMLNamespaces} object encapsulates SBML Level/Version/namespaces
   * information.  It is used to communicate the SBML Level, Version, and
   * (in Level&nbsp;3) packages used in addition to SBML Level&nbsp;3 Core.
   * A common approach to using this class constructor is to create an
   * {@link SBMLNamespaces} object somewhere in a program, once, then pass it to
   * object constructors such as this one when needed.
   * <p>
   * It is worth emphasizing that although this constructor does not take
   * an identifier argument, in SBML Level&nbsp;2 and beyond, the 'id'
   * (identifier) attribute of a {@link SpeciesType} object is required to have a value.
   * Thus, callers are cautioned to assign a value after calling this
   * constructor.  Setting the identifier can be accomplished using the
   * method {@link SBase#setId(String id)}.
   * <p>
   * @param sbmlns an {@link SBMLNamespaces} object.
   * <p>
   * @note Upon the addition of a {@link SpeciesType} object to an {@link SBMLDocument}
   * (e.g., using {@link Model#addSpeciesType(SpeciesType st)}),
   * the SBML XML namespace of the document <em>overrides</em> the value used
   * when creating the {@link SpeciesType} object via this constructor.  This is
   * necessary to ensure that an SBML document is a consistent structure.
   * Nevertheless, the ability to supply the values at the time of creation
   * of a {@link SpeciesType} is an important aid to producing valid SBML.
   * Knowledge of the intented SBML Level and Version determine whether it
   * is valid to assign a particular value to an attribute, or whether it
   * is valid to add an object to an existing {@link SBMLDocument}.
   */
 public SpeciesType(SBMLNamespaces sbmlns) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_SpeciesType__SWIG_1(SBMLNamespaces.getCPtr(sbmlns), sbmlns), true);
  }

  
  /**
  * Copy constructor; creates a copy of this {@link SpeciesType}.
  */
 public SpeciesType(SpeciesType orig) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_SpeciesType__SWIG_2(SpeciesType.getCPtr(orig), orig), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link SpeciesType}.
   * <p>
   * @return a (deep) copy of this {@link SpeciesType}.
   */
 public SpeciesType cloneObject() {
    long cPtr = libsbmlJNI.SpeciesType_cloneObject(swigCPtr, this);
    return (cPtr == 0) ? null : new SpeciesType(cPtr, true);
  }

  
  /**
   * Returns the value of the 'id' attribute of this {@link SpeciesType}.
   * <p>
   * @return the id of this {@link SpeciesType}.
   */
 public String getId() {
    return libsbmlJNI.SpeciesType_getId(swigCPtr, this);
  }

  
  /**
   * Returns the value of the 'name' attribute of this {@link SpeciesType}.
   * <p>
   * @return the name of this {@link SpeciesType}.
   */
 public String getName() {
    return libsbmlJNI.SpeciesType_getName(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> if this
   * {@link SpeciesType}'s 'id' attribute is set.
   * <p>
   * @return <code>true</code> if the 'id' attribute of this {@link SpeciesType} is
   * set, <code>false</code> otherwise.
   */
 public boolean isSetId() {
    return libsbmlJNI.SpeciesType_isSetId(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> if this
   * {@link SpeciesType}'s 'name' attribute is set.
   * <p>
   * @return <code>true</code> if the 'name' attribute of this {@link SpeciesType} is
   * set, <code>false</code> otherwise.
   */
 public boolean isSetName() {
    return libsbmlJNI.SpeciesType_isSetName(swigCPtr, this);
  }

  
  /**
   * Sets the value of the 'id' attribute of this {@link SpeciesType}.
   * <p>
   * The string <code>sid</code> is copied.  Note that SBML has strict requirements
   * for the syntax of identifiers.  The following is a summary of the definition of the SBML identifier type 
<code>SId</code>, which defines the permitted syntax of identifiers.  We
express the syntax using an extended form of BNF notation: 
<p>
<code style='margin-left: 2em'>letter .= 'a'..'z','A'..'Z'</code><br>
<code style='margin-left: 2em'>digit  .= '0'..'9'</code><br>
<code style='margin-left: 2em'>idChar .= letter | digit | '_'</code><br>
<code style='margin-left: 2em'>SId    .= ( letter | '_' ) idChar*</code><br>
<p>
The characters <code>(</code> and <code>)</code> are used for grouping, the
character <code>*</code> 'zero or more times', and the character
<code>|</code> indicates logical 'or'.  The equality of SBML identifiers is
determined by an exact character sequence match; i.e., comparisons must be
performed in a case-sensitive manner.  In addition, there are a few
conditions for the uniqueness of identifiers in an SBML model.  Please
consult the SBML specifications for the exact formulations.
<p>

   * <p>
   * @param sid the string to use as the identifier of this {@link SpeciesType}
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE }
   */
 public int setId(String sid) {
    return libsbmlJNI.SpeciesType_setId(swigCPtr, this, sid);
  }

  
  /**
   * Sets the value of the 'name' attribute of this {@link SpeciesType}.
   * <p>
   * The string in <code>name</code> is copied.
   * <p>
   * @param name the new name for the {@link SpeciesType}
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE }
   */
 public int setName(String name) {
    return libsbmlJNI.SpeciesType_setName(swigCPtr, this, name);
  }

  
  /**
   * Unsets the value of the 'name' attribute of this {@link SpeciesType}.
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_FAILED LIBSBML_OPERATION_FAILED }
   */
 public int unsetName() {
    return libsbmlJNI.SpeciesType_unsetName(swigCPtr, this);
  }

  
  /**
   * Returns the libSBML type code for this SBML object.
   * <p>
   * LibSBML attaches an identifying code to every
   * kind of SBML object.  These are known as <em>SBML type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libSBML, the type codes are defined as
   * static integer constants in the interface class {@link
   * libsbmlConstants}.  The names of the type codes all begin with the
   * characters <code>SBML_.</code> 
   * <p>
   * @return the SBML type code for this object, or {@link  libsbmlConstants#SBML_UNKNOWN SBML_UNKNOWN} (default).
   * <p>
   * @see #getElementName()
   */
 public int getTypeCode() {
    return libsbmlJNI.SpeciesType_getTypeCode(swigCPtr, this);
  }

  
  /**
   * Returns the XML element name of this object, which for
   * {@link SpeciesType}, is always <code>'compartmentType'.</code>
   * <p>
   * @return the name of this element, i.e., <code>'compartmentType'.</code>
   */
 public String getElementName() {
    return libsbmlJNI.SpeciesType_getElementName(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> if
   * all the required attributes for this {@link SpeciesType} object
   * have been set.
   * <p>
   * @note The required attributes for a {@link SpeciesType} object are:
   * <li> 'id'
   * <p>
   * @return a boolean value indicating whether all the required
   * attributes for this object have been defined.
   */
 public boolean hasRequiredAttributes() {
    return libsbmlJNI.SpeciesType_hasRequiredAttributes(swigCPtr, this);
  }

}
