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

    Wtx::Dbo::Field<std::string> companyName;
    Wtx::Dbo::Field<std::string> contactName;
    Wtx::Dbo::Field<std::string> mainPhone;

    Wtx::Dbo::Field<std::string> accountNote;
    Wtx::Dbo::Field<Wt::WDate> activityDate;
    Wtx::Dbo::Field<Wt::WDate> activeFrom;
    Wtx::Dbo::Field<Wt::WDate> activeTo;

    Wtx::Dbo::Field<std::string> m_custType;
    Wtx::Dbo::Field<std::string> m_note;
    Wtx::Dbo::Field<std::string> m_notes;
    Wtx::Dbo::Field<std::string> m_phone1;
    Wtx::Dbo::Field<std::string> m_phone2;
    Wtx::Dbo::Field<std::string> m_addr;
    Wtx::Dbo::Field<std::string> m_addr2;
    Wtx::Dbo::Field<std::string> m_fax;
    Wtx::Dbo::Field<std::string> m_terms;
    Wtx::Dbo::Field<std::string> m_city;
    Wtx::Dbo::Field<std::string> m_state;
    Wtx::Dbo::Field<std::string> m_zip;
    Wtx::Dbo::Field<std::string> m_country;
    Wtx::Dbo::Field<std::string> m_payor;
    Wtx::Dbo::Field<std::string> m_carrier;
    Wtx::Dbo::Field<std::string> m_email;
    Wtx::Dbo::Field<std::string> m_contact;
    Wtx::Dbo::Field<std::string> m_contactPhone;
    Wtx::Dbo::Field<std::string> m_buyer;
    Wtx::Dbo::Field<std::string> m_buyerPhone;
    Wtx::Dbo::Field<std::string> m_memo;
    Wtx::Dbo::Field<int>         m_expAdj;
    Wtx::Dbo::Field<bool>        m_catchWt;
    Wtx::Dbo::Field<int>         m_chargeMin;
    Wtx::Dbo::Field<int>         m_chargeDiffDays;
    Wtx::Dbo::Field<int>         m_chargeLtDays;
    Wtx::Dbo::Field<int>         m_chargeStart;
    Wtx::Dbo::Field<float>       m_chargeMinInvChgIn;
    Wtx::Dbo::Field<float>       m_chargeMinInvChgOut;


    template<class Action> void persist( Action & a )
    {
      Wtx::Dbo::PermissionItemTpl<C>::persist( a );
      companyName.persist( a, &TableDef().CompanyNameFieldDef );
      contactName.persist( a, &TableDef().ContactNameFieldDef );
      mainPhone.persist(   a, &TableDef().MainPhoneFieldDef   );

      accountNote             .persist( a, &TableDef().AccountNoteFieldDef            );
      activityDate            .persist( a, &TableDef().ActivityDateFieldDef           );
      activeFrom              .persist( a, &TableDef().ActiveFromFieldDef             );
      activeTo                .persist( a, &TableDef().ActiveToFieldDef               );

      m_custType              .persist( a, &TableDef().CustTypeFieldDef               );
      m_note                  .persist( a, &TableDef().NoteFieldDef                   );
      m_notes                 .persist( a, &TableDef().NotesFieldDef                  );
      m_phone1                .persist( a, &TableDef().Phone1FieldDef                 );
      m_phone2                .persist( a, &TableDef().Phone2FieldDef                 );
      m_addr                  .persist( a, &TableDef().AddrFieldDef                   );
      m_addr2                 .persist( a, &TableDef().Addr2FieldDef                  );
      m_fax                   .persist( a, &TableDef().FaxFieldDef                    );
      m_terms                 .persist( a, &TableDef().TermsFieldDef                  );
      m_city                  .persist( a, &TableDef().CityFieldDef                   );
      m_state                 .persist( a, &TableDef().StateFieldDef                  );
      m_zip                   .persist( a, &TableDef().ZipFieldDef                    );
      m_country               .persist( a, &TableDef().CountryFieldDef                );
      m_payor                 .persist( a, &TableDef().PayorFieldDef                  );
      m_carrier               .persist( a, &TableDef().CarrierFieldDef                );
      m_email                 .persist( a, &TableDef().EmailFieldDef                  );
      m_contact               .persist( a, &TableDef().ContactFieldDef                );
      m_contactPhone          .persist( a, &TableDef().ContactPhoneFieldDef           );
      m_buyer                 .persist( a, &TableDef().BuyerFieldDef                  );
      m_buyerPhone            .persist( a, &TableDef().BuyerPhoneFieldDef             );
      m_memo                  .persist( a, &TableDef().MemoFieldDef                   );
      m_expAdj                .persist( a, &TableDef().ExpAdjFieldDef                 );
      m_catchWt               .persist( a, &TableDef().CatchWtFieldDef                );
      m_chargeMin             .persist( a, &TableDef().ChargeMinFieldDef              );
      m_chargeDiffDays        .persist( a, &TableDef().ChargeDiffDaysFieldDef         );
      m_chargeLtDays          .persist( a, &TableDef().ChargeLtDaysFieldDef           );
      m_chargeStart           .persist( a, &TableDef().ChargeStartFieldDef            );
      m_chargeMinInvChgIn     .persist( a, &TableDef().ChargeMinInvChgInFieldDef      );
      m_chargeMinInvChgOut    .persist( a, &TableDef().ChargeMinInvChgOutFieldDef     );

    }

  private:

};

    } // endnamespace Company
  } // endnamespace Crm
} // endnamespace Wtx

#endif // __WTX_CRM_COMPANY_TEMPLATE_H___

