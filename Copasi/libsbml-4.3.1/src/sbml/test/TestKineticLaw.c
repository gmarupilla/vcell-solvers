/**
 * \file    TestKineticLaw.c
 * \brief   SBML KineticLaw unit tests
 * \author  Ben Bornstein
 *
 * $Id: TestKineticLaw.c 13054 2011-02-26 00:32:46Z fbergmann $
 * $HeadURL: http://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/sbml/test/TestKineticLaw.c $
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
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <sbml/common/common.h>

#include <sbml/math/FormulaFormatter.h>
#include <sbml/math/FormulaParser.h>

#include <sbml/SBase.h>
#include <sbml/Parameter.h>
#include <sbml/KineticLaw.h>
#include <sbml/xml/XMLNamespaces.h>
#include <sbml/SBMLDocument.h>

#include <check.h>

#if __cplusplus
CK_CPPSTART
#endif

static KineticLaw_t *kl;


void
KineticLawTest_setup (void)
{
  kl = KineticLaw_create(2, 4);

  if (kl == NULL)
  {
    fail("KineticLaw_create() returned a NULL pointer.");
  }
}


void
KineticLawTest_teardown (void)
{
  KineticLaw_free(kl);
}


START_TEST (test_KineticLaw_create)
{
  fail_unless( SBase_getTypeCode  ((SBase_t *) kl) == SBML_KINETIC_LAW );
  fail_unless( SBase_getMetaId    ((SBase_t *) kl) == NULL );
  fail_unless( SBase_getNotes     ((SBase_t *) kl) == NULL );
  fail_unless( SBase_getAnnotation((SBase_t *) kl) == NULL );

  fail_unless( KineticLaw_getFormula       (kl) == NULL );
  fail_unless( KineticLaw_getMath          (kl) == NULL );
  fail_unless( KineticLaw_getTimeUnits     (kl) == NULL );
  fail_unless( KineticLaw_getSubstanceUnits(kl) == NULL );

  fail_unless( !KineticLaw_isSetFormula       (kl) );
  fail_unless( !KineticLaw_isSetMath          (kl) );
  fail_unless( !KineticLaw_isSetTimeUnits     (kl) );
  fail_unless( !KineticLaw_isSetSubstanceUnits(kl) );

  fail_unless(KineticLaw_getNumParameters(kl) == 0);
}
END_TEST


//START_TEST (test_KineticLaw_createWith)
//{
//  const ASTNode_t *math;
//  char *formula;
//
//  KineticLaw_t *kl = KineticLaw_createWithFormula("k1 * X0");
//
//
//  fail_unless( SBase_getTypeCode  ((SBase_t *) kl) == SBML_KINETIC_LAW );
//  fail_unless( SBase_getMetaId    ((SBase_t *) kl) == NULL );
//  fail_unless( SBase_getNotes     ((SBase_t *) kl) == NULL );
//  fail_unless( SBase_getAnnotation((SBase_t *) kl) == NULL );
//
//  math = KineticLaw_getMath(kl);
//  fail_unless( math != NULL );
//
//  formula = SBML_formulaToString(math);
//  fail_unless( formula != NULL );
//  fail_unless( !strcmp(formula, "k1 * X0") );
//
//  fail_unless( !strcmp( KineticLaw_getFormula       (kl), formula  ) );
//
//  fail_unless( KineticLaw_isSetMath          (kl) );
//  fail_unless( KineticLaw_isSetFormula       (kl) );
//
//  fail_unless(KineticLaw_getNumParameters(kl) == 0);
//
//  KineticLaw_free(kl);
//  safe_free(formula);
//}
//END_TEST



//START_TEST (test_KineticLaw_createWithMath)
//{
//  ASTNode_t *math1 = SBML_parseFormula("k3 / k2");
//  const ASTNode_t *math;
//  char *formula;
//
//  KineticLaw_t *kl = KineticLaw_createWithMath(math1);
//
//
//  fail_unless( SBase_getTypeCode  ((SBase_t *) kl) == SBML_KINETIC_LAW );
//  fail_unless( SBase_getMetaId    ((SBase_t *) kl) == NULL );
//  fail_unless( SBase_getNotes     ((SBase_t *) kl) == NULL );
//  fail_unless( SBase_getAnnotation((SBase_t *) kl) == NULL );
//
//  math = KineticLaw_getMath(kl);
//  fail_unless( math != NULL );
//
//  formula = SBML_formulaToString(math);
//  fail_unless( formula != NULL );
//  fail_unless( !strcmp(formula, "k3 / k2") );
//
//  fail_unless( !strcmp( KineticLaw_getFormula       (kl), formula  ) );
//
//  fail_unless( KineticLaw_isSetMath          (kl) );
//  fail_unless( KineticLaw_isSetFormula       (kl) );
//  fail_unless( !KineticLaw_isSetTimeUnits     (kl) );
//  fail_unless( !KineticLaw_isSetSubstanceUnits(kl) );
//
//  fail_unless(KineticLaw_getNumParameters(kl) == 0);
//
//  KineticLaw_free(kl);
//  safe_free(formula);
//}
//END_TEST



START_TEST (test_KineticLaw_free_NULL)
{
  KineticLaw_free(NULL);
}
END_TEST


START_TEST (test_KineticLaw_setFormula)
{
  char *formula = "k1*X0";


  KineticLaw_setFormula(kl, formula);

  fail_unless( !strcmp(KineticLaw_getFormula(kl), formula) );
  fail_unless( KineticLaw_isSetFormula(kl)   );

  if (KineticLaw_getFormula(kl) == formula)
  {
    fail("KineticLaw_setFormula(...) did not make a copy of string.");
  }

  /* Reflexive case (pathological) */
  KineticLaw_setFormula(kl, KineticLaw_getFormula(kl));
  fail_unless( !strcmp(KineticLaw_getFormula(kl), formula) );

  KineticLaw_setFormula(kl, NULL);
  fail_unless( !KineticLaw_isSetFormula(kl) );

  if (KineticLaw_getFormula(kl) != NULL)
  {
    fail("KineticLaw_setFormula(kl, NULL) did not clear string.");
  }
}
END_TEST


START_TEST (test_KineticLaw_setBadFormula)
{
  char *formula = "k1 X0";


  KineticLaw_setFormula(kl, formula);

  fail_unless( !KineticLaw_isSetFormula(kl)   );
  fail_unless( !KineticLaw_isSetMath(kl)   );

}
END_TEST


/**
 * setFormulaFromMath() is no longer necessary.  LibSBML now keeps formula
 * strings and math ASTs synchronized automatically.  This (now modified)
 * test is kept around to demonstrate the behavioral change.
 */
START_TEST (test_KineticLaw_setFormulaFromMath)
{
  ASTNode_t *math = SBML_parseFormula("k1 * X0");


  fail_unless( !KineticLaw_isSetMath   (kl) );
  fail_unless( !KineticLaw_isSetFormula(kl) );

  KineticLaw_setMath(kl, math);
  fail_unless(  KineticLaw_isSetMath(kl) );
  fail_unless( KineticLaw_isSetFormula(kl) );

  fail_unless( !strcmp(KineticLaw_getFormula(kl), "k1 * X0") );

  ASTNode_free(math);
}
END_TEST


START_TEST (test_KineticLaw_setMath)
{
  ASTNode_t *math = SBML_parseFormula("k3 / k2");
  char *formula;
  const ASTNode_t *math1;


  KineticLaw_setMath(kl, math);

  math1 = KineticLaw_getMath(kl);
  fail_unless( math1 != NULL );

  formula = SBML_formulaToString(math1);
  fail_unless( formula != NULL );
  fail_unless( !strcmp(formula, "k3 / k2") );
  fail_unless( KineticLaw_getMath(kl) != math );
  fail_unless( KineticLaw_isSetMath(kl) );

  /* Reflexive case (pathological) */
  KineticLaw_setMath(kl, (ASTNode_t *) KineticLaw_getMath(kl));
  math1 = KineticLaw_getMath(kl);
  fail_unless( math1 != NULL );

  formula = SBML_formulaToString(math1);
  fail_unless( formula != NULL );
  fail_unless( !strcmp(formula, "k3 / k2") );
  fail_unless( KineticLaw_getMath(kl) != math );

  KineticLaw_setMath(kl, NULL);
  fail_unless( !KineticLaw_isSetMath(kl) );

  if (KineticLaw_getMath(kl) != NULL)
  {
    fail( "KineticLaw_setMath(kl, NULL) did not clear ASTNode." );
  }

  ASTNode_free(math);
}
END_TEST


/**
 * setMathFromFormula() is no longer necessary.  LibSBML now keeps formula
 * strings and math ASTs synchronized automatically.  This (now modified)
 * test is kept around to demonstrate the behavioral change.
 */
START_TEST (test_KineticLaw_setMathFromFormula)
{
  char *formula = "k3 / k2";


  fail_unless( !KineticLaw_isSetMath   (kl) );
  fail_unless( !KineticLaw_isSetFormula(kl) );


  KineticLaw_setFormula(kl, formula);
  fail_unless( KineticLaw_isSetMath   (kl) );
  fail_unless( KineticLaw_isSetFormula(kl) );

  formula = SBML_formulaToString( KineticLaw_getMath(kl) );

  fail_unless( !strcmp(formula, "k3 / k2") );

  safe_free(formula);
}
END_TEST


START_TEST (test_KineticLaw_addParameter)
{
  Parameter_t * p = Parameter_create(2, 4);
  Parameter_setId(p, "p");
  KineticLaw_addParameter(kl, p);

  fail_unless( KineticLaw_getNumParameters(kl) == 1 );

  Parameter_free(p);
}
END_TEST


START_TEST (test_KineticLaw_getParameter)
{
  Parameter_t *k1 = Parameter_create(2, 4);
  Parameter_t *k2 = Parameter_create(2, 4);

  Parameter_setId(k1, "k1");
  Parameter_setId(k2, "k2");

  Parameter_setValue(k1, 3.14);
  Parameter_setValue(k2, 2.72);

  KineticLaw_addParameter(kl, k1);
  KineticLaw_addParameter(kl, k2);

  Parameter_free(k1);
  Parameter_free(k2);
  fail_unless( KineticLaw_getNumParameters(kl) == 2 );

  k1 = KineticLaw_getParameter(kl, 0);
  k2 = KineticLaw_getParameter(kl, 1);

  fail_unless( !strcmp(Parameter_getId(k1), "k1") );
  fail_unless( !strcmp(Parameter_getId(k2), "k2") );
  fail_unless( Parameter_getValue(k1) == 3.14 );
  fail_unless( Parameter_getValue(k2) == 2.72 );


}
END_TEST


START_TEST (test_KineticLaw_getParameterById)
{
  Parameter_t *k1 = Parameter_create(2, 4);
  Parameter_t *k2 = Parameter_create(2, 4);

  Parameter_setId(k1, "k1");
  Parameter_setId(k2, "k2");

  Parameter_setValue(k1, 3.14);
  Parameter_setValue(k2, 2.72);

  KineticLaw_addParameter(kl, k1);
  KineticLaw_addParameter(kl, k2);

  Parameter_free(k1);
  Parameter_free(k2);
  fail_unless( KineticLaw_getNumParameters(kl) == 2 );

  k1 = KineticLaw_getParameterById(kl, "k1");
  k2 = KineticLaw_getParameterById(kl, "k2");

  fail_unless( !strcmp(Parameter_getId(k1), "k1") );
  fail_unless( !strcmp(Parameter_getId(k2), "k2") );
  fail_unless( Parameter_getValue(k1) == 3.14 );
  fail_unless( Parameter_getValue(k2) == 2.72 );

}
END_TEST


START_TEST (test_KineticLaw_createWithNS )
{
  XMLNamespaces_t *xmlns = XMLNamespaces_create();
  XMLNamespaces_add(xmlns, "http://www.sbml.org", "testsbml");
  SBMLNamespaces_t *sbmlns = SBMLNamespaces_create(2,1);
  SBMLNamespaces_addNamespaces(sbmlns,xmlns);

  KineticLaw_t *object = 
    KineticLaw_createWithNS (sbmlns);


  fail_unless( SBase_getTypeCode  ((SBase_t *) object) == SBML_KINETIC_LAW );
  fail_unless( SBase_getMetaId    ((SBase_t *) object) == NULL );
  fail_unless( SBase_getNotes     ((SBase_t *) object) == NULL );
  fail_unless( SBase_getAnnotation((SBase_t *) object) == NULL );

  fail_unless( SBase_getLevel       ((SBase_t *) object) == 2 );
  fail_unless( SBase_getVersion     ((SBase_t *) object) == 1 );

  fail_unless( KineticLaw_getNamespaces     (object) != NULL );
  fail_unless( XMLNamespaces_getLength(KineticLaw_getNamespaces(object)) == 2 );

  KineticLaw_free(object);
}
END_TEST


START_TEST (test_KineticLaw_removeParameter)
{
  Parameter_t *o1, *o2, *o3;

  o1 = KineticLaw_createParameter(kl);
  o2 = KineticLaw_createParameter(kl);
  o3 = KineticLaw_createParameter(kl);
  Parameter_setId(o3,"test");

  fail_unless( KineticLaw_removeParameter(kl,0) == o1 );
  fail_unless( KineticLaw_getNumParameters(kl)  == 2  );
  fail_unless( KineticLaw_removeParameter(kl,0) == o2 );
  fail_unless( KineticLaw_getNumParameters(kl)  == 1  );
  fail_unless( KineticLaw_removeParameterById(kl,"test") == o3 );
  fail_unless( KineticLaw_getNumParameters(kl)  == 0  );

  Parameter_free(o1);
  Parameter_free(o2);
  Parameter_free(o3);
}
END_TEST


START_TEST (test_KineticLaw_accessWithNULL)
{
  fail_unless( KineticLaw_addLocalParameter(NULL, NULL) == LIBSBML_INVALID_OBJECT );
  fail_unless( KineticLaw_addParameter(NULL, NULL) == LIBSBML_INVALID_OBJECT );
  fail_unless( KineticLaw_clone(NULL) == NULL);
  fail_unless( KineticLaw_containsUndeclaredUnits(NULL) == 0);
  fail_unless( KineticLaw_createLocalParameter(NULL) == NULL);
  fail_unless( KineticLaw_createParameter(NULL) == NULL);
  fail_unless( KineticLaw_createWithNS(NULL) == NULL);  

  KineticLaw_free(NULL);

  fail_unless( KineticLaw_getDerivedUnitDefinition(NULL) == NULL);
  fail_unless( KineticLaw_getFormula(NULL) == NULL);
  fail_unless( KineticLaw_getListOfLocalParameters(NULL) == NULL);
  fail_unless( KineticLaw_getListOfParameters(NULL) == NULL);
  fail_unless( KineticLaw_getLocalParameter(NULL, 0) == NULL);
  fail_unless( KineticLaw_getLocalParameterById(NULL, NULL) == NULL);
  fail_unless( KineticLaw_getMath(NULL) == NULL);
  fail_unless( KineticLaw_getNamespaces(NULL) == NULL);
  fail_unless( KineticLaw_getNumLocalParameters(NULL) == SBML_INT_MAX);
  fail_unless( KineticLaw_getNumParameters(NULL) == SBML_INT_MAX);
  fail_unless( KineticLaw_getParameter(NULL, 0) == NULL);
  fail_unless( KineticLaw_getParameterById(NULL, NULL) == NULL);
  fail_unless( KineticLaw_getSubstanceUnits(NULL) == NULL);
  fail_unless( KineticLaw_getTimeUnits(NULL) == NULL);
  fail_unless( KineticLaw_isSetFormula(NULL) == 0);
  fail_unless( KineticLaw_isSetMath(NULL) == 0);
  fail_unless( KineticLaw_isSetSubstanceUnits(NULL) == 0);
  fail_unless( KineticLaw_isSetTimeUnits(NULL) == 0);
  fail_unless( KineticLaw_removeLocalParameter(NULL, 0) == NULL);
  fail_unless( KineticLaw_removeLocalParameterById(NULL, NULL) == NULL);
  fail_unless( KineticLaw_removeParameter(NULL, 0) == NULL);
  fail_unless( KineticLaw_removeParameterById(NULL, NULL) == NULL);
  fail_unless( KineticLaw_setFormula(NULL, NULL) == LIBSBML_INVALID_OBJECT);
  fail_unless( KineticLaw_setMath(NULL, NULL) == LIBSBML_INVALID_OBJECT);
  fail_unless( KineticLaw_setSubstanceUnits(NULL, NULL) == LIBSBML_INVALID_OBJECT);
  fail_unless( KineticLaw_setTimeUnits(NULL, NULL) == LIBSBML_INVALID_OBJECT);
  fail_unless( KineticLaw_unsetSubstanceUnits(NULL) == LIBSBML_INVALID_OBJECT);
  fail_unless( KineticLaw_unsetTimeUnits(NULL) == LIBSBML_INVALID_OBJECT);
}
END_TEST

Suite *
create_suite_KineticLaw (void)
{
  Suite *suite = suite_create("KineticLaw");
  TCase *tcase = tcase_create("KineticLaw");


  tcase_add_checked_fixture( tcase,
                             KineticLawTest_setup,
                             KineticLawTest_teardown );

  tcase_add_test( tcase, test_KineticLaw_create             );
  //tcase_add_test( tcase, test_KineticLaw_createWith       );
  //tcase_add_test( tcase, test_KineticLaw_createWithMath   );
  tcase_add_test( tcase, test_KineticLaw_free_NULL          );
  tcase_add_test( tcase, test_KineticLaw_setFormula         );
  tcase_add_test( tcase, test_KineticLaw_setBadFormula      );
  tcase_add_test( tcase, test_KineticLaw_setFormulaFromMath );
  tcase_add_test( tcase, test_KineticLaw_setMath            );
  tcase_add_test( tcase, test_KineticLaw_setMathFromFormula );
  tcase_add_test( tcase, test_KineticLaw_addParameter       );
  tcase_add_test( tcase, test_KineticLaw_getParameter       );
  tcase_add_test( tcase, test_KineticLaw_getParameterById   );
  tcase_add_test( tcase, test_KineticLaw_createWithNS       );
  tcase_add_test( tcase, test_KineticLaw_removeParameter    );
  tcase_add_test( tcase, test_KineticLaw_accessWithNULL     );

  suite_add_tcase(suite, tcase);

  return suite;
}

#if __cplusplus
CK_CPPEND
#endif
