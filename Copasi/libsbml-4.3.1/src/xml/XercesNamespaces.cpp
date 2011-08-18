/**
 * @file    XercesNamespaces.cpp
 * @brief   Extracts XML namespace declarations from Xerces-C++ attributes.
 * @author  Ben Bornstein
 *
 * $Id: XercesNamespaces.cpp 12780 2011-02-08 04:12:54Z mhucka $
 * $HeadURL: http://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/xml/XercesNamespaces.cpp $
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <sbml/xml/XercesTranscode.h>
#include <sbml/xml/XercesNamespaces.h>

/** @cond doxygen-ignored */

using namespace std;
using namespace xercesc;

LIBSBML_CPP_NAMESPACE_BEGIN

/** @endcond */


/** @cond doxygen-libsbml-internal */

/**
 * Creates a new list of XML namespaces declarations from a "raw" Xerces-C++
 * Attributes set.
 */
XercesNamespaces::XercesNamespaces (const xercesc::Attributes& attrs)
{
  unsigned int size = attrs.getLength();
  mNamespaces.reserve(size);


  for (unsigned int n = 0; n < size; ++n)
  {
    const string            name  = XercesTranscode( attrs.getLocalName(n) );
    const string            qname = XercesTranscode( attrs.getQName    (n) );
    const string            value = XercesTranscode( attrs.getValue    (n) );
    const string::size_type pos   = qname.find(":", 0);

    const string prefix = (pos != string::npos) ? qname.substr(0, pos) : "";

         if (prefix == "xmlns") add( value, name );
    else if (name   == "xmlns") add( value );
  }
}


/**
 * Destroys this list of XML namespace declarations.
 */
XercesNamespaces::~XercesNamespaces ()
{
}

LIBSBML_CPP_NAMESPACE_END

/** @endcond */
