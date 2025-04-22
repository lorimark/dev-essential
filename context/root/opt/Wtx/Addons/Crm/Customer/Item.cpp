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


#include "Item.h"

Wtx::Crm::Company::Definition::Definition()
: Wtx::Dbo::PermissionTableDef("crmCompany"),
  CompanyNameFieldDef        ( *this, "companyName",    30 ),
  ContactNameFieldDef        ( *this, "contactName",    30 ),
  MainPhoneFieldDef          ( *this, "mainPhone"          ),
  AccountNoteFieldDef        ( *this, "accountNote"        ),
  ActivityDateFieldDef       ( *this, "activityDate"       ),
  ActiveFromFieldDef         ( *this, "activeFrom"         ),
  ActiveToFieldDef           ( *this, "activeTo"           ),
  CustTypeFieldDef           ( *this, "custType"           ),
  NoteFieldDef               ( *this, "note"               ),
  NotesFieldDef              ( *this, "notes"              ),
  Phone1FieldDef             ( *this, "phone"              ), // BUGBUG: fix this, should be 'phone1'
  Phone2FieldDef             ( *this, "phone2"             ),
  FaxFieldDef                ( *this, "fax"                ),
  AddrFieldDef               ( *this, "addr"               ),
  Addr2FieldDef              ( *this, "addr2"              ),
  TermsFieldDef              ( *this, "terms"              ),
  CityFieldDef               ( *this, "city"               ),
  StateFieldDef              ( *this, "state"              ),
  ZipFieldDef                ( *this, "zip"                ),
  CountryFieldDef            ( *this, "country"            ),
  PayorFieldDef              ( *this, "payor"              ),
  CarrierFieldDef            ( *this, "carrier"            ),
  ConsigneeFieldDef          ( *this, "consignee"          ),
  CustGroupFieldDef          ( *this, "custGroup"          ),
  LastInvoiceFieldDef        ( *this, "lastInvoice"        ),
  ExpAdjustFieldDef          ( *this, "expAdjust"          ),
  DLongDaysFieldDef          ( *this, "dLongDays"          ),
  DLongBreakFieldDef         ( *this, "dLongBreak"         ),
  DLongStartFieldDef         ( *this, "dLongStart"         ),
  EmailFieldDef              ( *this, "email"              ),
  ContactFieldDef            ( *this, "contact"            ),
  ContactPhoneFieldDef       ( *this, "contactPhone"       ),
  BuyerFieldDef              ( *this, "buyer"              ),
  BuyerPhoneFieldDef         ( *this, "buyerPhone"         ),
  MemoFieldDef               ( *this, "memo"               ),
  ExpAdjFieldDef             ( *this, "expAdj"             ),
  CatchWtFieldDef            ( *this, "catchWt"            ),
  ChargeMinFieldDef          ( *this, "chargeMinDays"      ),
  ChargeDiffDaysFieldDef     ( *this, "chargeDiffDays"     ),
  ChargeLtDaysFieldDef       ( *this, "chargeLtDays"       ),
  ChargeStartFieldDef        ( *this, "chargeStart"        ),
  ChargeMinInvChgInFieldDef  ( *this, "chargeMinInvChgIn"  ),
  ChargeMinInvChgOutFieldDef ( *this, "chargeMinInvChgOut" )
{
  KeyFieldDef                .setIsVisible(true);
  KeyFieldDef                .setLabel( "Cust Code"    );
  CfyFieldDef                .setLabel( "Name"         );
  ChargeDiffDaysFieldDef     .setLabel( "Diff Days"    );
  ChargeLtDaysFieldDef       .setLabel( "LT Days"      );
  ChargeStartFieldDef        .setLabel( "Start"        );
  ChargeMinInvChgInFieldDef  .setLabel( "MinInvChgIn"  );
  ChargeMinInvChgOutFieldDef .setLabel( "MinInvChgOut" );

}

Wtx::Crm::Company::Definition g_CompanyDef;

DBO_INSTANTIATE_TEMPLATES(Wtx::Crm::Company::Item);

Wtx::Crm::Company::Definition & Wtx::Crm::Company::Item::s_tableDef = g_CompanyDef;

void Wtx::Crm::Company::mapClasses( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Company::Item::MapClass( session );

};

void Wtx::Crm::Company::postCreateTables( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Company::Item::PostCreateTable( session );

};




