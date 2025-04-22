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


#ifndef __WTX_CRM_PERSON_DEFINITION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CRM_PERSON_DEFINITION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Dbo/PermissionTableDef.h>
#include <Wtx/Dbo/FieldDefPhoneEdit.h>
#include <Wtx/Dbo/FieldDefLookupWidget.h>
#include <Wtx/Dbo/FieldDefDoubleSpin.h>

namespace Wtx {
  namespace Crm {

    /*!
    ** \brief Human Types
    **
    */
    namespace Person {

class Definition
: public Wtx::Dbo::PermissionTableDef
{
  public:

    Definition();

    Wtx::Dbo::FieldDefLineEdit     FirstNameFieldDef         = { *this, "firstName"             };
    Wtx::Dbo::FieldDefLineEdit     LastNameFieldDef          = { *this, "lastName"              };
    Wtx::Dbo::FieldDefLineEdit     MiddleNameFieldDef        = { *this, "middleName"            };
    Wtx::Dbo::FieldDefLineEdit     NickNameFieldDef          = { *this, "nickName"              };
    Wtx::Dbo::FieldDefLineEdit     AbbreviationFieldDef      = { *this, "abbreviation"          };
    Wtx::Dbo::FieldDefPhoneEdit    PhoneFieldDef             = { *this, "phone"                 };
    Wtx::Dbo::FieldDefPhoneEdit    CellFieldDef              = { *this, "cell"                  };
    Wtx::Dbo::FieldDefPhoneEdit    FaxFieldDef               = { *this, "fax"                   };
    Wtx::Dbo::FieldDefLineEdit     EmailFieldDef             = { *this, "email"                 };
    Wtx::Dbo::FieldDefTextArea     NotesFieldDef             = { *this, "notes"                 };
    Wtx::Dbo::FieldDefCheckBox     IsLeadFieldDef            = { *this, "isLead"                };
    Wtx::Dbo::FieldDefCheckBox     IsClientFieldDef          = { *this, "isClient"              };
    Wtx::Dbo::FieldDefLineEdit     Street1FieldDef           = { *this, "street1"               };
    Wtx::Dbo::FieldDefLineEdit     Street2FieldDef           = { *this, "street2"               };
    Wtx::Dbo::FieldDefLineEdit     CityFieldDef              = { *this, "city"                  };
    Wtx::Dbo::FieldDefLineEdit     StateFieldDef             = { *this, "state"                 };
    Wtx::Dbo::FieldDefLineEdit     ZipFieldDef               = { *this, "zip"                   };
    Wtx::Dbo::FieldDefDoubleSpin   DiscountFieldDef          = { *this, "discount"              };
    Wtx::Dbo::FieldDefTextArea     AlertFieldDef             = { *this, "alert"                 };

    Wtx::Dbo::FieldDefLookupWidget ContactForCompanyFieldDef = { *this, "contactFor_crmCompany" };

}; // endclass PersonDef

extern Definition g_PersonDef;

    } // endnamespace Person
  } // endnamespace Crm
} // endnamespace Wtx

#endif // __WTX_CRM_PERSON_DEFINITION_H___

