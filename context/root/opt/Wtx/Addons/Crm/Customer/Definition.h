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


#ifndef __WTX_CRM_CUSTOMER_DEFINITION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CRM_CUSTOMER_DEFINITION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Dbo/PermissionTableDef.h>
#include <Wtx/Dbo/FieldDefPhoneEdit.h>
#include <Wtx/Dbo/FieldDefDateEdit.h>
#include <Wtx/Dbo/FieldDefTextEdit.h>
#include <Wtx/Dbo/FieldDefCurrencyEdit.h>
#include <Wtx/Dbo/FieldDefCheckBox.h>
#include <Wtx/Dbo/FieldDefYearEdit.h>
#include <Wtx/Dbo/FieldDefLineEdit.h>
#include <Wtx/Dbo/FieldDefNumberEdit.h>
#include <Wtx/Dbo/FieldDefLookupCombo.h>
#include <Wtx/Dbo/FieldDefCollectionEdit.h>


namespace Wtx {
  namespace Crm {

    /*!
    ** \brief Business Entities
    **
    */
    namespace Customer {

void mapClasses( Wtx::Dbo::Session & session );
void postCreateTables( Wtx::Dbo::Session & session );

class Definition
: public Wtx::Dbo::PermissionTableDef
{
  public:

    Definition();

    Wtx::Dbo::FieldDefTextEdit       AccountNoteFieldDef;
    Wtx::Dbo::FieldDefDateEdit       ActivityDateFieldDef;
    Wtx::Dbo::FieldDefDateEdit       ActiveFromFieldDef;
    Wtx::Dbo::FieldDefDateEdit       ActiveToFieldDef;

    Wtx::Dbo::FieldDefLineEdit       CustTypeFieldDef;
    Wtx::Dbo::FieldDefLineEdit       NotesFieldDef;
    Wtx::Dbo::FieldDefLineEdit       CountryFieldDef;
    Wtx::Dbo::FieldDefLineEdit       CustGroupFieldDef;
    Wtx::Dbo::FieldDefLineEdit       LastInvoiceFieldDef;

    Wtx::Dbo::FieldDefLineEdit       ContactFieldDef;
    Wtx::Dbo::FieldDefLineEdit       BuyerFieldDef;
    Wtx::Dbo::FieldDefLineEdit       PayorFieldDef;
    Wtx::Dbo::FieldDefLineEdit       CarrierFieldDef;
    Wtx::Dbo::FieldDefLineEdit       ConsigneeFieldDef;

    Wtx::Dbo::FieldDefLineEdit CompanyNameFieldDef;
    Wtx::Dbo::FieldDefLineEdit ContactNameFieldDef;
    Wtx::Dbo::FieldDefPhoneEdit MainPhoneFieldDef;

};

    } // endnamespace Customer
  } // endnamespace Crm
} // endnamespace Wtx

#endif // __WTX_CRM_CUSTOMER_DEFINITION_H___

