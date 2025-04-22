/**************************************************************************
###########################################################################
##
## $SHOWOFFDB_BEGIN_LICENSE$
## Copyright (C) 2011 Lorimark Solutions, LLC and/or its subsidiary(-ies).
##  All rights reserved.
##  Contact: Lorimark Solutions, LLC (info@showoff-db.org)
##
## This file is part of the Showoff Database Application Framework.
##
##  Commercial Usage
##  Licensees holding valid ShowoffDB Commercial licenses may use this file in
##   accordance with the ShowoffDB Commercial License Agreement provided with the
##   Software or, alternatively, in accordance with the terms contained in
##   a written agreement between you and Lorimark Solutions, LLC.
##
## GNU Lesser General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU Lesser
##   General Public License version 2.1 as published by the Free Software
##   Foundation and appearing in the file LICENSE.LGPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU Lesser General Public License version 2.1 requirements
##   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Lorimark Solutions, LLC gives
##  you certain additional rights.  These rights are described in the
##  Lorimark Solutions, LLC ShowoffDB LGPL Exception version 1.0, included in
##  the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU
##   General Public License version 3.0 as published by the Free Software
##   Foundation and appearing in the file LICENSE.GPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU General Public License version 3.0 requirements will be
##   met: http://www.gnu.org/copyleft/gpl.html.
##
## If you have questions regarding the use of this file, please contact
##   Lorimark Solutions, LLC at info@showoff-db.org.
## $SHOWOFFDB_END_LICENSE$
##
#############################################################################
****************************************************************************/


#ifndef __WTX_CRM_PERSON_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CRM_PERSON_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Util/Util.h>
#include <Wtx/Dbo/PermissionItemTpl.h>

#include <Wtx/Addons/Crm/Company/Item.h>

#include "Definition.h"

namespace Wtx {
  namespace Crm {
    namespace Person {

template <class C> class Template
: public Wtx::Dbo::PermissionItemTpl<C>
{
  public:

    Template()
    : Wtx::Dbo::PermissionItemTpl<C>()
    {
    }

    Template( const std::string & keyField )
    : Wtx::Dbo::PermissionItemTpl<C>( keyField )
    {
      isLead   ().setValue( false );
      isClient ().setValue( false );
    }

    virtual ~Template()
    {
    }

    static Definition & TableDef()
    {
      return C::TableDef();
    }

          Wtx::Dbo::Field<std::string> & firstName    ()       { return m_firstName    ; }
          Wtx::Dbo::Field<std::string> & lastName     ()       { return m_lastName     ; }
          Wtx::Dbo::Field<std::string> & middleName   ()       { return m_middleName   ; }
          Wtx::Dbo::Field<std::string> & nickName     ()       { return m_nickName     ; }
          Wtx::Dbo::Field<std::string> & abbreviation ()       { return m_abbreviation ; }
          Wtx::Dbo::Field<std::string> & phone        ()       { return m_phone        ; }
          Wtx::Dbo::Field<std::string> & cell         ()       { return m_cell         ; }
          Wtx::Dbo::Field<std::string> & fax          ()       { return m_fax          ; }
          Wtx::Dbo::Field<std::string> & email        ()       { return m_email        ; }
          Wtx::Dbo::Field<std::string> & notes        ()       { return m_notes        ; }
          Wtx::Dbo::Field<bool>        & isLead       ()       { return m_isLead       ; }
          Wtx::Dbo::Field<bool>        & isClient     ()       { return m_isClient     ; }

          Wtx::Dbo::Field<std::string> & street1      ()       { return m_street1      ; }
          Wtx::Dbo::Field<std::string> & street2      ()       { return m_street2      ; }
          Wtx::Dbo::Field<std::string> & city         ()       { return m_city         ; }
          Wtx::Dbo::Field<std::string> & state        ()       { return m_state        ; }
          Wtx::Dbo::Field<std::string> & zip          ()       { return m_zip          ; }
          Wtx::Dbo::Field<double>      & discount     ()       { return m_discount     ; }
          Wtx::Dbo::Field<std::string> & alert        ()       { return m_alert        ; }

          Wtx::Dbo::FieldBelongsTo< Wtx::Crm::Company::Item::Ptr > & contactForCompany () { return m_contactForCompany; }

    const Wtx::Dbo::Field<std::string> & firstName    () const { return m_firstName    ; }
    const Wtx::Dbo::Field<std::string> & lastName     () const { return m_lastName     ; }
    const Wtx::Dbo::Field<std::string> & middleName   () const { return m_middleName   ; }
    const Wtx::Dbo::Field<std::string> & nickName     () const { return m_nickName     ; }
    const Wtx::Dbo::Field<std::string> & abbreviation () const { return m_abbreviation ; }
    const Wtx::Dbo::Field<std::string> & phone        () const { return m_phone        ; }
    const Wtx::Dbo::Field<std::string> & cell         () const { return m_cell         ; }
    const Wtx::Dbo::Field<std::string> & fax          () const { return m_fax          ; }
    const Wtx::Dbo::Field<std::string> & email        () const { return m_email        ; }
    const Wtx::Dbo::Field<std::string> & notes        () const { return m_notes        ; }
    const Wtx::Dbo::Field<bool>        & isLead       () const { return m_isLead       ; }
    const Wtx::Dbo::Field<bool>        & isClient     () const { return m_isClient     ; }

    const Wtx::Dbo::Field<std::string> & street1      () const { return m_street1      ; }
    const Wtx::Dbo::Field<std::string> & street2      () const { return m_street2      ; }
    const Wtx::Dbo::Field<std::string> & city         () const { return m_city         ; }
    const Wtx::Dbo::Field<std::string> & state        () const { return m_state        ; }
    const Wtx::Dbo::Field<std::string> & zip          () const { return m_zip          ; }
    const Wtx::Dbo::Field<double>      & discount     () const { return m_discount     ; }
    const Wtx::Dbo::Field<std::string> & alert        () const { return m_alert        ; }

    const Wtx::Dbo::FieldBelongsTo< Wtx::Crm::Company::Item::Ptr > & contactForCompany () const { return m_contactForCompany; }

    std::string csz() const
    {
      std::string retVal = city().value();

      retVal = Wtx::append( retVal, state ().value(), ", " );
      retVal = Wtx::append( retVal, zip   ().value(), "  " );

      return retVal;
    }

    template<class Action> void persist( Action &a )
    {
      Wtx::Dbo::PermissionItemTpl<C>::persist( a );
      m_firstName         .persist( a, &TableDef(). FirstNameFieldDef         );
      m_lastName          .persist( a, &TableDef(). LastNameFieldDef          );
      m_middleName        .persist( a, &TableDef(). MiddleNameFieldDef        );
      m_nickName          .persist( a, &TableDef(). NickNameFieldDef          );
      m_abbreviation      .persist( a, &TableDef(). AbbreviationFieldDef      );
      m_phone             .persist( a, &TableDef(). PhoneFieldDef             );
      m_cell              .persist( a, &TableDef(). CellFieldDef              );
      m_fax               .persist( a, &TableDef(). FaxFieldDef               );
      m_email             .persist( a, &TableDef(). EmailFieldDef             );
      m_notes             .persist( a, &TableDef(). NotesFieldDef             );
      m_isLead            .persist( a, &TableDef(). IsLeadFieldDef            );
      m_isClient          .persist( a, &TableDef(). IsClientFieldDef          );

      m_street1           .persist( a, &TableDef(). Street1FieldDef           );
      m_street2           .persist( a, &TableDef(). Street2FieldDef           );
      m_city              .persist( a, &TableDef(). CityFieldDef              );
      m_state             .persist( a, &TableDef(). StateFieldDef             );
      m_zip               .persist( a, &TableDef(). ZipFieldDef               );
      m_discount          .persist( a, &TableDef(). DiscountFieldDef          );
      m_alert             .persist( a, &TableDef(). AlertFieldDef             );
      m_contactForCompany .persist( a, &TableDef(). ContactForCompanyFieldDef );

    }

  private:

    Wtx::Dbo::Field<std::string> m_firstName    ;
    Wtx::Dbo::Field<std::string> m_lastName     ;
    Wtx::Dbo::Field<std::string> m_middleName   ;
    Wtx::Dbo::Field<std::string> m_nickName     ;
    Wtx::Dbo::Field<std::string> m_abbreviation ;
    Wtx::Dbo::Field<std::string> m_phone        ;
    Wtx::Dbo::Field<std::string> m_cell         ;
    Wtx::Dbo::Field<std::string> m_fax          ;
    Wtx::Dbo::Field<std::string> m_email        ;
    Wtx::Dbo::Field<std::string> m_notes        ;
    Wtx::Dbo::Field<bool>        m_isLead       ;
    Wtx::Dbo::Field<bool>        m_isClient     ;

    Wtx::Dbo::Field<std::string> m_street1      ;
    Wtx::Dbo::Field<std::string> m_street2      ;
    Wtx::Dbo::Field<std::string> m_city         ;
    Wtx::Dbo::Field<std::string> m_state        ;
    Wtx::Dbo::Field<std::string> m_zip          ;
    Wtx::Dbo::Field<double>      m_discount     ;
    Wtx::Dbo::Field<std::string> m_alert        ;

    Wtx::Dbo::FieldBelongsTo< Wtx::Crm::Company::Item::Ptr > m_contactForCompany;

}; // endclass Wtx::Crm::Person::Template

    } // endnamespace Person
  } // endnamespace Crm
} // endnamespace Wtx

#endif // end#ifndef __PERSONTPL_H___

