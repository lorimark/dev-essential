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


#ifndef __WTX_CRM_COMPANY_DEFINITION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CRM_COMPANY_DEFINITION_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

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
    namespace Company {

void mapClasses( Wtx::Dbo::Session & session );
void postCreateTables( Wtx::Dbo::Session & session );

class Definition
: public Wtx::Dbo::PermissionTableDef
{
  public:

    Definition();

    Wtx::Dbo::FieldDefLookupCombo    StatusFieldDef             = { *this, "status_sysLookup"   };
    Wtx::Dbo::FieldDefTextEdit       AccountNameFieldDef        = { *this, "accountName"        };
    Wtx::Dbo::FieldDefTextEdit       AccountNoteFieldDef        = { *this, "accountNote"        };
    Wtx::Dbo::FieldDefTextArea       AlertFieldDef              = { *this, "alert"              };
    Wtx::Dbo::FieldDefDateEdit       ActivityDateFieldDef       = { *this, "activityDate"       };
    Wtx::Dbo::FieldDefDateEdit       ActiveFromFieldDef         = { *this, "activeFrom"         };
    Wtx::Dbo::FieldDefDateEdit       ActiveToFieldDef           = { *this, "activeTo"           };

    Wtx::Dbo::FieldDefLineEdit       CustTypeFieldDef           = { *this, "custType"           };
    Wtx::Dbo::FieldDefLineEdit       NoteFieldDef               = { *this, "note"               };
    Wtx::Dbo::FieldDefLineEdit       NotesFieldDef              = { *this, "notes"              };
    Wtx::Dbo::FieldDefLineEdit       Phone1FieldDef             = { *this, "phone"              };
    Wtx::Dbo::FieldDefLineEdit       Phone2FieldDef             = { *this, "phone2"             };
    Wtx::Dbo::FieldDefLineEdit       AddrFieldDef               = { *this, "addr"               };
    Wtx::Dbo::FieldDefLineEdit       Addr2FieldDef              = { *this, "addr2"              };
    Wtx::Dbo::FieldDefLineEdit       FaxFieldDef                = { *this, "fax"                };
    Wtx::Dbo::FieldDefLookupCombo    TermsFieldDef              = { *this, "terms_sysLookup"    };
    Wtx::Dbo::FieldDefLineEdit       CityFieldDef               = { *this, "city"               };
    Wtx::Dbo::FieldDefLineEdit       StateFieldDef              = { *this, "state"              };
    Wtx::Dbo::FieldDefLineEdit       ZipFieldDef                = { *this, "zip"                };
    Wtx::Dbo::FieldDefLineEdit       CountryFieldDef            = { *this, "country"            };
    Wtx::Dbo::FieldDefLineEdit       PayorFieldDef              = { *this, "payor"              };
    Wtx::Dbo::FieldDefLineEdit       CarrierFieldDef            = { *this, "carrier"            };
    Wtx::Dbo::FieldDefLineEdit       ConsigneeFieldDef          = { *this, "consignee"          };
    Wtx::Dbo::FieldDefLineEdit       CustGroupFieldDef          = { *this, "custGroup"          };
    Wtx::Dbo::FieldDefLineEdit       LastInvoiceFieldDef        = { *this, "lastInvoice"        };
    Wtx::Dbo::FieldDefLineEdit       ExpAdjustFieldDef          = { *this, "expAdjust"          };
    Wtx::Dbo::FieldDefLineEdit       DLongDaysFieldDef          = { *this, "dLongDays"          };
    Wtx::Dbo::FieldDefLineEdit       DLongBreakFieldDef         = { *this, "dLongBreak"         };
    Wtx::Dbo::FieldDefLineEdit       DLongStartFieldDef         = { *this, "dLongStart"         };

    Wtx::Dbo::FieldDefTextArea       EmailFieldDef              = { *this, "email"              };
    Wtx::Dbo::FieldDefTextArea       EmailBillingFieldDef       = { *this, "emailBilling"       };
    Wtx::Dbo::FieldDefLineEdit       ContactFieldDef            = { *this, "contact"            };
    Wtx::Dbo::FieldDefLineEdit       ContactPhoneFieldDef       = { *this, "contactPhone"       };
    Wtx::Dbo::FieldDefLineEdit       BuyerFieldDef              = { *this, "buyer"              };
    Wtx::Dbo::FieldDefLineEdit       BuyerPhoneFieldDef         = { *this, "buyerPhone"         };
    Wtx::Dbo::FieldDefLineEdit       MemoFieldDef               = { *this, "memo"               };
    Wtx::Dbo::FieldDefNumberEdit     ExpAdjFieldDef             = { *this, "expAdj"             };
    Wtx::Dbo::FieldDefCheckBox       CatchWtFieldDef            = { *this, "catchWt"            };
    Wtx::Dbo::FieldDefCheckBox       UseLotNumbersFieldDef      = { *this, "useLotNumbers"      };
    Wtx::Dbo::FieldDefLineEdit       ChargeMinFieldDef          = { *this, "chargeMinDays"      };
    Wtx::Dbo::FieldDefNumberEdit     ChargeDiffDaysFieldDef     = { *this, "chargeDiffDays"     };
    Wtx::Dbo::FieldDefNumberEdit     ChargeLtDaysFieldDef       = { *this, "chargeLtDays"       };
    Wtx::Dbo::FieldDefNumberEdit     ChargeStartFieldDef        = { *this, "chargeStart"        };
    Wtx::Dbo::FieldDefNumberEdit     ChargeMinInvChgInFieldDef  = { *this, "chargeMinInvChgIn"  };
    Wtx::Dbo::FieldDefNumberEdit     ChargeMinInvChgOutFieldDef = { *this, "chargeMinInvChgOut" };

    Wtx::Dbo::FieldDefLineEdit       CompanyNameFieldDef        = { *this, "companyName",    30 };
    Wtx::Dbo::FieldDefLineEdit       ContactNameFieldDef        = { *this, "contactName",    30 };
    Wtx::Dbo::FieldDefPhoneEdit      MainPhoneFieldDef          = { *this, "mainPhone"          };
    Wtx::Dbo::FieldDefLineEdit       CategoryFieldDef           = { *this, "category"           };

    Wtx::Dbo::FieldDefDateEdit       LastBilledEomFieldDef      = { *this, "lastBilledEom"      };
    Wtx::Dbo::FieldDefDateEdit       LastBilledMasterFieldDef   = { *this, "lastBilledMaster"   };

};

    } // endnamespace Company
  } // endnamespace Crm
} // endnamespace Wtx

#endif // __WTX_CRM_COMPANY_DEFINITION_H___

