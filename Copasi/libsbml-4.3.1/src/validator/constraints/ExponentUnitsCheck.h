/**
 * @cond doxygen-libsbml-internal
 *
 * @file    ExponentUnitsCheck.h
 * @brief   Ensures units consistent with math
 * @author  Sarah Keating
 *
 * $Id: ExponentUnitsCheck.h 13266 2011-03-21 22:26:50Z mhucka $
 * $HeadURL: http://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/validator/constraints/ExponentUnitsCheck.h $
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
 * the Free Software Foundation.  A copy of the license agreement is
 * provided in the file named "LICENSE.txt" included with this software
 * distribution.  It is also available online at
 * http://sbml.org/software/libsbml/license.html
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */


#ifndef ExponentUnitsCheck_h
#define ExponentUnitsCheck_h


#ifdef __cplusplus


#include <string>
#include <sstream>
#include <math.h>

#include <sbml/validator/VConstraint.h>

#include "UnitsBase.h"

LIBSBML_CPP_NAMESPACE_BEGIN

class ASTNode;


class ExponentUnitsCheck: public UnitsBase
{
public:

  /**
   * Creates a new Constraint with the given id.
   */
  ExponentUnitsCheck (unsigned int id, Validator& v);

  /**
   * Destroys this Constraint.
   */
  virtual ~ExponentUnitsCheck ();


protected:

  /**
   * Checks that the units of the ASTnode 
   * are appropriate for the function being performed
   *
   * If inconsistent units are found, an error message is logged.
   */
  virtual void checkUnits (const Model& m, const ASTNode& node, const SBase & sb,
    bool inKL = false, int reactNo = -1);
  
  /**
   * @return the preamble to use when logging constraint violations.  The
   * preamble will be prepended to each log message.  If not overriden,
   * returns an empty string.
   */
  virtual const char* getPreamble ();


  /**
   * Checks that the units of the power function are consistent
   *
   * If inconsistent units are found, an error message is logged.
   */
  void checkUnitsFromRoot (const Model& m, const ASTNode& node, 
                              const SBase & sb, bool inKL, int reactNo);

  /**
   * @return the error message to use when logging constraint violations.
   * This method is called by logFailure.
   *
   * If at all possible please use getPreamble() and getFieldname() when
   * constructing error messages.  This will help to make your constraint
   * easily customizable.
   */
  virtual const std::string
  getMessage (const ASTNode& node, const SBase& object);

  void logRationalPowerConflict (const ASTNode & node, 
                                             const SBase & sb);
  void logNonIntegerPowerConflict (const ASTNode & node, 
                                             const SBase & sb);

};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* ExponentUnitsCheck_h */

/** @endcond */
