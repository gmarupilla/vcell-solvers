/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * Log of errors and other events encountered while processing an XML
 * file or data stream.
 * <p>
 * <p style='color: #555; font-style: italic'>
This class of objects is defined by libSBML only and has no direct
equivalent in terms of SBML components.  This class is not prescribed by
the SBML specifications, although it is used to implement features
defined in SBML.
</p>

 * <p>
 * The error log is a list.  The XML layer of libSBML maintains an error
 * log associated with a given XML document or data stream.  When an
 * operation results in an error, or when there is something wrong with the
 * XML content, the problem is reported as an {@link XMLError} object stored in the
 * {@link XMLErrorLog} list.  Potential problems range from low-level issues (such
 * as the inability to open a file) to XML syntax errors (such as
 * mismatched tags or other problems).
 * <p>
 * A typical approach for using this error log is to first use
 * {@link XMLErrorLog#getNumErrors()} to inquire how many {@link XMLError}
 * object instances it contains, and then to iterate over the list of
 * objects one at a time using getError(long n) const.  Indexing in
 * the list begins at 0.
 * <p>
 * In normal circumstances, programs using libSBML will actually obtain an
 * {@link SBMLErrorLog} rather than an {@link XMLErrorLog}.  The former is subclassed from
 * {@link XMLErrorLog} and simply wraps commands for working with {@link SBMLError} objects
 * rather than the low-level {@link XMLError} objects.  Classes such as
 * {@link SBMLDocument} use the higher-level {@link SBMLErrorLog}.
 */

public class XMLErrorLog {
   private long swigCPtr;
   protected boolean swigCMemOwn;

   protected XMLErrorLog(long cPtr, boolean cMemoryOwn)
   {
     swigCMemOwn = cMemoryOwn;
     swigCPtr    = cPtr;
   }

   protected static long getCPtr(XMLErrorLog obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (XMLErrorLog obj)
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
        libsbmlJNI.delete_XMLErrorLog(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  /**
   * Equality comparison method for XMLErrorLog.
   * <p>
   * Because the Java methods for libSBML are actually wrappers around code
   * implemented in C++ and C, certain operations will not behave as
   * expected.  Equality comparison is one such case.  An instance of a
   * libSBML object class is actually a <em>proxy object</em>
   * wrapping the real underlying C/C++ object.  The normal <code>==</code>
   * equality operator in Java will <em>only compare the Java proxy objects</em>,
   * not the underlying native object.  The result is almost never what you
   * want in practical situations.  Unfortunately, Java does not provide a
   * way to override <code>==</code>.
   *  <p>
   * The alternative that must be followed is to use the
   * <code>equals()</code> method.  The <code>equals</code> method on this
   * class overrides the default java.lang.Object one, and performs an
   * intelligent comparison of instances of objects of this class.  The
   * result is an assessment of whether two libSBML Java objects are truly 
   * the same underlying native-code objects.
   *  <p>
   * The use of this method in practice is the same as the use of any other
   * Java <code>equals</code> method.  For example,
   * <em>a</em><code>.equals(</code><em>b</em><code>)</code> returns
   * <code>true</code> if <em>a</em> and <em>b</em> are references to the
   * same underlying object.
   *
   * @param sb a reference to an object to which the current object
   * instance will be compared
   *
   * @return <code>true</code> if <code>sb</code> refers to the same underlying 
   * native object as this one, <code>false</code> otherwise
   */
  public boolean equals(Object sb)
  {
    if ( this == sb ) 
    {
      return true;
    }
    return swigCPtr == getCPtr((XMLErrorLog)(sb));
  }

  /**
   * Returns a hashcode for this XMLErrorLog object.
   *
   * @return a hash code usable by Java methods that need them.
   */
  public int hashCode()
  {
    return (int)(swigCPtr^(swigCPtr>>>32));
  }

  
  /**
   * Returns the number of errors that have been logged.
   * <p>
   * To retrieve individual errors from the log, callers may use
   * {@link XMLErrorLog#getError(long n)} const.
   * <p>
   * @return the number of errors that have been logged.
   */
 public long getNumErrors() {
    return libsbmlJNI.XMLErrorLog_getNumErrors(swigCPtr, this);
  }

  
  /**
   * Returns the <i>n</i>th {@link XMLError} object in this log.
   * <p>
   * Index <code>n</code> is counted from 0.  Callers should first inquire about the
   * number of items in the log by using the method
   * {@link XMLErrorLog#getNumErrors()}.
   * Attempts to use an error index number that exceeds the actual number
   * of errors in the log will result in a <code>null</code> being returned.
   * <p>
   * @param n the index number of the error to retrieve (with 0 being the
   * first error).
   * <p>
   * @return the <i>n</i>th {@link XMLError} in this log, or <code>null</code> if <code>n</code> is
   * greater than or equal to
   * {@link XMLErrorLog#getNumErrors()}.
   * <p>
   * @see #getNumErrors()
   */
 public XMLError getError(long n) {
    long cPtr = libsbmlJNI.XMLErrorLog_getError(swigCPtr, this, n);
    return (cPtr == 0) ? null : new XMLError(cPtr, false);
  }

  
  /**
   * Deletes all errors from this log.
   */
 public void clearLog() {
    libsbmlJNI.XMLErrorLog_clearLog(swigCPtr, this);
  }

}
