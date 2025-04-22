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


#ifndef __WTX_CRM_COMPANY_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CRM_COMPANY_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Dbo/PermissionItemTpl.h>
#include <Wtx/Sys/Lookup/Item.h>

#include "Definition.h"

namespace Wtx {
  namespace Crm {
    namespace Company {

template <class C> class Template
: public Wtx::Dbo::PermissionItemTpl<C>
{
  public:

    Template( const std::string keyField = "" )
    : Wtx::Dbo::PermissionItemTpl<C>( keyField )
    {
    }

    Template( const std::string & key, const std::string & cfy )
    : Wtx::Dbo::PermissionItemTpl<C>( key, cfy )
    {
    }

    Template( const Wtx::Crm::Company::Template<C> & other )
    : Wtx::Dbo::PermissionItemTpl<C>( other.keyField().value(), other.cfyField().value() )
    {
    }

    virtual ~Template()
    {
    }


    static Definition & TableDef()
    {
      return C::TableDef();
    }

//    const Wtx::Dbo::Field< Wtx::Sys::Lookup::Item::Ptr > & status             () const { return m_status             ; }
    const Wtx::Dbo::Field< std::string                 > & accountName        () const { return m_accountName        ; }
    const Wtx::Dbo::Field< std::string                 > & accountNote        () const { return m_accountNote        ; }
    const Wtx::Dbo::Field< Wt::WDate                   > & activityDate       () const { return m_activityDate       ; }
    const Wtx::Dbo::Field< Wt::WDate                   > & activeFrom         () const { return m_activeFrom         ; }
    const Wtx::Dbo::Field< Wt::WDate                   > & activeTo           () const { return m_activeTo           ; }

    const Wtx::Dbo::Field< std::string                 > & custType           () const { return m_custType           ; }
    const Wtx::Dbo::Field< std::string                 > & note               () const { return m_note               ; }
    const Wtx::Dbo::Field< std::string                 > & notes              () const { return m_notes              ; }
    const Wtx::Dbo::Field< std::string                 > & alert              () const { return m_alert              ; }
    const Wtx::Dbo::Field< std::string                 > & phone1             () const { return m_phone1             ; }
    const Wtx::Dbo::Field< std::string                 > & phone2             () const { return m_phone2             ; }
    const Wtx::Dbo::Field< std::string                 > & addr               () const { return m_addr               ; }
    const Wtx::Dbo::Field< std::string                 > & addr2              () const { return m_addr2              ; }
    const Wtx::Dbo::Field< std::string                 > & fax                () const { return m_fax                ; }
    const Wtx::Dbo::Field< Wtx::Sys::Lookup::Item::Ptr > & terms              () const { return m_terms              ; }
    const Wtx::Dbo::Field< std::string                 > & city               () const { return m_city               ; }
    const Wtx::Dbo::Field< std::string                 > & state              () const { return m_state              ; }
    const Wtx::Dbo::Field< std::string                 > & zip                () const { return m_zip                ; }
    const Wtx::Dbo::Field< std::string                 > & country            () const { return m_country            ; }
    const Wtx::Dbo::Field< std::string                 > & payor              () const { return m_payor              ; }
    const Wtx::Dbo::Field< std::string                 > & carrier            () const { return m_carrier            ; }
    const Wtx::Dbo::Field< std::string                 > & email              () const { return m_email              ; }
    const Wtx::Dbo::Field< std::string                 > & emailBilling       () const { return m_emailBilling       ; }
    const Wtx::Dbo::Field< std::string                 > & contact            () const { return m_contact            ; }
    const Wtx::Dbo::Field< std::string                 > & contactPhone       () const { return m_contactPhone       ; }
    const Wtx::Dbo::Field< std::string                 > & buyer              () const { return m_buyer              ; }
    const Wtx::Dbo::Field< std::string                 > & buyerPhone         () const { return m_buyerPhone         ; }
    const Wtx::Dbo::Field< std::string                 > & memo               () const { return m_memo               ; }
    const Wtx::Dbo::Field< int                         > & expAdj             () const { return m_expAdj             ; }
    const Wtx::Dbo::Field< bool                        > & catchWt            () const { return m_catchWt            ; }
    const Wtx::Dbo::Field< bool                        > & useLotNumbers      () const { return m_useLotNumbers      ; }
    const Wtx::Dbo::Field< int                         > & chargeMin          () const { return m_chargeMin          ; }
    const Wtx::Dbo::Field< int                         > & chargeDiffDays     () const { return m_chargeDiffDays     ; }
    const Wtx::Dbo::Field< int                         > & chargeLtDays       () const { return m_chargeLtDays       ; }
    const Wtx::Dbo::Field< int                         > & chargeStart        () const { return m_chargeStart        ; }
    const Wtx::Dbo::Field< float                       > & chargeMinInvChgIn  () const { return m_chargeMinInvChgIn  ; }
    const Wtx::Dbo::Field< float                       > & chargeMinInvChgOut () const { return m_chargeMinInvChgOut ; }

    const Wtx::Dbo::Field< std::string                 > & companyName        () const { return m_companyName        ; }
    const Wtx::Dbo::Field< std::string                 > & contactName        () const { return m_contactName        ; }
    const Wtx::Dbo::Field< std::string                 > & mainPhone          () const { return m_mainPhone          ; }
    const Wtx::Dbo::Field< std::string                 > & category           () const { return m_category           ; }

    const Wtx::Dbo::Field< Wt::WDate                   > & lastBilledEom      () const { return m_lastBilledEom      ; }
    const Wtx::Dbo::Field< Wt::WDate                   > & lastBilledMaster   () const { return m_lastBilledMaster   ; }

          Wtx::Dbo::Field< Wtx::Sys::Lookup::Item::Ptr > & status             ()       { return m_status             ; }
          Wtx::Dbo::Field< std::string                 > & accountName        ()       { return m_accountName        ; }
          Wtx::Dbo::Field< std::string                 > & accountNote        ()       { return m_accountNote        ; }
          Wtx::Dbo::Field< Wt::WDate                   > & activityDate       ()       { return m_activityDate       ; }
          Wtx::Dbo::Field< Wt::WDate                   > & activeFrom         ()       { return m_activeFrom         ; }
          Wtx::Dbo::Field< Wt::WDate                   > & activeTo           ()       { return m_activeTo           ; }

          Wtx::Dbo::Field< std::string                 > & custType           ()       { return m_custType           ; }
          Wtx::Dbo::Field< std::string                 > & note               ()       { return m_note               ; }
          Wtx::Dbo::Field< std::string                 > & notes              ()       { return m_notes              ; }
          Wtx::Dbo::Field< std::string                 > & alert              ()       { return m_alert              ; }
          Wtx::Dbo::Field< std::string                 > & phone1             ()       { return m_phone1             ; }
          Wtx::Dbo::Field< std::string                 > & phone2             ()       { return m_phone2             ; }
          Wtx::Dbo::Field< std::string                 > & addr               ()       { return m_addr               ; }
          Wtx::Dbo::Field< std::string                 > & addr2              ()       { return m_addr2              ; }
          Wtx::Dbo::Field< std::string                 > & fax                ()       { return m_fax                ; }
          Wtx::Dbo::Field< Wtx::Sys::Lookup::Item::Ptr > & terms              ()       { return m_terms              ; }
          Wtx::Dbo::Field< std::string                 > & city               ()       { return m_city               ; }
          Wtx::Dbo::Field< std::string                 > & state              ()       { return m_state              ; }
          Wtx::Dbo::Field< std::string                 > & zip                ()       { return m_zip                ; }
          Wtx::Dbo::Field< std::string                 > & country            ()       { return m_country            ; }
          Wtx::Dbo::Field< std::string                 > & payor              ()       { return m_payor              ; }
          Wtx::Dbo::Field< std::string                 > & carrier            ()       { return m_carrier            ; }
          Wtx::Dbo::Field< std::string                 > & email              ()       { return m_email              ; }
          Wtx::Dbo::Field< std::string                 > & emailBilling       ()       { return m_emailBilling       ; }
          Wtx::Dbo::Field< std::string                 > & contact            ()       { return m_contact            ; }
          Wtx::Dbo::Field< std::string                 > & contactPhone       ()       { return m_contactPhone       ; }
          Wtx::Dbo::Field< std::string                 > & buyer              ()       { return m_buyer              ; }
          Wtx::Dbo::Field< std::string                 > & buyerPhone         ()       { return m_buyerPhone         ; }
          Wtx::Dbo::Field< std::string                 > & memo               ()       { return m_memo               ; }
          Wtx::Dbo::Field< int                         > & expAdj             ()       { return m_expAdj             ; }
          Wtx::Dbo::Field< bool                        > & catchWt            ()       { return m_catchWt            ; }
          Wtx::Dbo::Field< bool                        > & useLotNumbers      ()       { return m_useLotNumbers      ; }
          Wtx::Dbo::Field< int                         > & chargeMin          ()       { return m_chargeMin          ; }
          Wtx::Dbo::Field< int                         > & chargeDiffDays     ()       { return m_chargeDiffDays     ; }
          Wtx::Dbo::Field< int                         > & chargeLtDays       ()       { return m_chargeLtDays       ; }
          Wtx::Dbo::Field< int                         > & chargeStart        ()       { return m_chargeStart        ; }
          Wtx::Dbo::Field< float                       > & chargeMinInvChgIn  ()       { return m_chargeMinInvChgIn  ; }
          Wtx::Dbo::Field< float                       > & chargeMinInvChgOut ()       { return m_chargeMinInvChgOut ; }

          Wtx::Dbo::Field< std::string                 > & companyName        ()       { return m_companyName        ; }
          Wtx::Dbo::Field< std::string                 > & contactName        ()       { return m_contactName        ; }
          Wtx::Dbo::Field< std::string                 > & mainPhone          ()       { return m_mainPhone          ; }
          Wtx::Dbo::Field< std::string                 > & category           ()       { return m_category           ; }

          Wtx::Dbo::Field< Wt::WDate                   > lastBilledEom        ()       { return m_lastBilledEom      ; }
          Wtx::Dbo::Field< Wt::WDate                   > lastBilledMaster     ()       { return m_lastBilledMaster   ; }

          std::string cityStateZip() const
          {
            std::string retVal = city().value();

            if( state().value() != "" )
            {
              retVal += ", " + state().value();
            }

            if( zip().value() != "" )
            {
              retVal += "  " + zip().value();
            }

            return retVal;
          }

    template<class Action> void persist( Action & a )
    {
      Wtx::Dbo::PermissionItemTpl<C>::persist( a );

      m_status                .persist( a, &TableDef(). StatusFieldDef                 );
      m_accountName           .persist( a, &TableDef(). AccountNameFieldDef            );
      m_accountNote           .persist( a, &TableDef(). AccountNoteFieldDef            );
      m_activityDate          .persist( a, &TableDef(). ActivityDateFieldDef           );
      m_activeFrom            .persist( a, &TableDef(). ActiveFromFieldDef             );
      m_activeTo              .persist( a, &TableDef(). ActiveToFieldDef               );

      m_custType              .persist( a, &TableDef(). CustTypeFieldDef               );
      m_note                  .persist( a, &TableDef(). NoteFieldDef                   );
      m_notes                 .persist( a, &TableDef(). NotesFieldDef                  );
      m_alert                 .persist( a, &TableDef(). AlertFieldDef                  );
      m_phone1                .persist( a, &TableDef(). Phone1FieldDef                 );
      m_phone2                .persist( a, &TableDef(). Phone2FieldDef                 );
      m_addr                  .persist( a, &TableDef(). AddrFieldDef                   );
      m_addr2                 .persist( a, &TableDef(). Addr2FieldDef                  );
      m_fax                   .persist( a, &TableDef(). FaxFieldDef                    );
      m_terms                 .persist( a, &TableDef(). TermsFieldDef                  );
      m_city                  .persist( a, &TableDef(). CityFieldDef                   );
      m_state                 .persist( a, &TableDef(). StateFieldDef                  );
      m_zip                   .persist( a, &TableDef(). ZipFieldDef                    );
      m_country               .persist( a, &TableDef(). CountryFieldDef                );
      m_payor                 .persist( a, &TableDef(). PayorFieldDef                  );
      m_carrier               .persist( a, &TableDef(). CarrierFieldDef                );
      m_email                 .persist( a, &TableDef(). EmailFieldDef                  );
      m_emailBilling          .persist( a, &TableDef(). EmailBillingFieldDef           );
      m_contact               .persist( a, &TableDef(). ContactFieldDef                );
      m_contactPhone          .persist( a, &TableDef(). ContactPhoneFieldDef           );
      m_buyer                 .persist( a, &TableDef(). BuyerFieldDef                  );
      m_buyerPhone            .persist( a, &TableDef(). BuyerPhoneFieldDef             );
      m_memo                  .persist( a, &TableDef(). MemoFieldDef                   );
      m_expAdj                .persist( a, &TableDef(). ExpAdjFieldDef                 );
      m_catchWt               .persist( a, &TableDef(). CatchWtFieldDef                );
      m_useLotNumbers         .persist( a, &TableDef(). UseLotNumbersFieldDef          );
      m_chargeMin             .persist( a, &TableDef(). ChargeMinFieldDef              );
      m_chargeDiffDays        .persist( a, &TableDef(). ChargeDiffDaysFieldDef         );
      m_chargeLtDays          .persist( a, &TableDef(). ChargeLtDaysFieldDef           );
      m_chargeStart           .persist( a, &TableDef(). ChargeStartFieldDef            );
      m_chargeMinInvChgIn     .persist( a, &TableDef(). ChargeMinInvChgInFieldDef      );
      m_chargeMinInvChgOut    .persist( a, &TableDef(). ChargeMinInvChgOutFieldDef     );

      m_companyName           .persist( a, &TableDef(). CompanyNameFieldDef            );
      m_contactName           .persist( a, &TableDef(). ContactNameFieldDef            );
      m_mainPhone             .persist( a, &TableDef(). MainPhoneFieldDef              );
      m_category              .persist( a, &TableDef(). CategoryFieldDef               );

      m_lastBilledEom         .persist( a, &TableDef(). LastBilledEomFieldDef          );
      m_lastBilledMaster      .persist( a, &TableDef(). LastBilledMasterFieldDef       );

    }

  private:

    Wtx::Dbo::Field< Wtx::Sys::Lookup::Item::Ptr > m_status             ;
    Wtx::Dbo::Field< std::string                 > m_accountName        ;
    Wtx::Dbo::Field< std::string                 > m_accountNote        ;
    Wtx::Dbo::Field< Wt::WDate                   > m_activityDate       ;
    Wtx::Dbo::Field< Wt::WDate                   > m_activeFrom         ;
    Wtx::Dbo::Field< Wt::WDate                   > m_activeTo           ;

    Wtx::Dbo::Field< std::string                 > m_custType           ;
    Wtx::Dbo::Field< std::string                 > m_note               ;
    Wtx::Dbo::Field< std::string                 > m_notes              ;
    Wtx::Dbo::Field< std::string                 > m_alert              ;
    Wtx::Dbo::Field< std::string                 > m_phone1             ;
    Wtx::Dbo::Field< std::string                 > m_phone2             ;
    Wtx::Dbo::Field< std::string                 > m_addr               ;
    Wtx::Dbo::Field< std::string                 > m_addr2              ;
    Wtx::Dbo::Field< std::string                 > m_fax                ;
    Wtx::Dbo::Field< Wtx::Sys::Lookup::Item::Ptr > m_terms              ;
    Wtx::Dbo::Field< std::string                 > m_city               ;
    Wtx::Dbo::Field< std::string                 > m_state              ;
    Wtx::Dbo::Field< std::string                 > m_zip                ;
    Wtx::Dbo::Field< std::string                 > m_country            ;
    Wtx::Dbo::Field< std::string                 > m_payor              ;
    Wtx::Dbo::Field< std::string                 > m_carrier            ;
    Wtx::Dbo::Field< std::string                 > m_email              ;
    Wtx::Dbo::Field< std::string                 > m_emailBilling       ;
    Wtx::Dbo::Field< std::string                 > m_contact            ;
    Wtx::Dbo::Field< std::string                 > m_contactPhone       ;
    Wtx::Dbo::Field< std::string                 > m_buyer              ;
    Wtx::Dbo::Field< std::string                 > m_buyerPhone         ;
    Wtx::Dbo::Field< std::string                 > m_memo               ;
    Wtx::Dbo::Field< int                         > m_expAdj             ;
    Wtx::Dbo::Field< bool                        > m_catchWt            ;
    Wtx::Dbo::Field< bool                        > m_useLotNumbers      ;
    Wtx::Dbo::Field< int                         > m_chargeMin          ;
    Wtx::Dbo::Field< int                         > m_chargeDiffDays     ;
    Wtx::Dbo::Field< int                         > m_chargeLtDays       ;
    Wtx::Dbo::Field< int                         > m_chargeStart        ;
    Wtx::Dbo::Field< float                       > m_chargeMinInvChgIn  ;
    Wtx::Dbo::Field< float                       > m_chargeMinInvChgOut ;

    Wtx::Dbo::Field< std::string                 > m_companyName        ;
    Wtx::Dbo::Field< std::string                 > m_contactName        ;
    Wtx::Dbo::Field< std::string                 > m_mainPhone          ;
    Wtx::Dbo::Field< std::string                 > m_category           ;

    Wtx::Dbo::Field< Wt::WDate                   > m_lastBilledEom      ;
    Wtx::Dbo::Field< Wt::WDate                   > m_lastBilledMaster   ;

}; // endpublic Wtx::Dbo::PermissionItemTpl<C>

    } // endnamespace Company
  } // endnamespace Crm
} // endnamespace Wtx

#endif // __WTX_CRM_COMPANY_TEMPLATE_H___

