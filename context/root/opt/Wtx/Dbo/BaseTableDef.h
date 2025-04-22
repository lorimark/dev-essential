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


#ifndef __WTX_DBO_BASETABLEDEF_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_BASETABLEDEF_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include "FieldDefBase.h"
#include "FieldDefCheckBox.h"
#include "FieldDefIntSpin.h"
#include "FieldDefLineEdit.h"
#include "FieldDefTextArea.h"
#include "TableDef.h"

namespace Wtx {
  namespace Dbo {

class BaseTableDef
: public Wtx::Dbo::TableDef
{
  public:

    BaseTableDef( const char * tn );

    /*!
    ** \brief External-ID
    **
    ** This field is used when synchronizing the database
    **  with an external foreign database.  These databases
    **  usually use integer-based ID numbers, so this field
    **  acts as a 'external-id' value.  Duing import/sync
    **  processes, this value can be set with that external
    **  reference ID so that future sync processes can insure
    **  they are grabbing the correct item.
    **
    */
    Wtx::Dbo::FieldDefLineEdit XidFieldDef;

    /*!
    ** \brief Version-Sync
    **
    ** This field can be used during db-to-db sync processes
    **  where-by it is important to record the version of the
    **  item that it was at when the sync was performed.  If
    **  the item is updated, then the internal item's version()
    **  value will be different than this version-sync value,
    **  and it will be possible to detect changes in the system
    **  that need to get re-synced.
    **
    */
    Wtx::Dbo::FieldDefIntSpin  VersionSyncFieldDef;

    /*!
    ** \brief Item is Active
    **
    ** This is simply a general-purpose flag that indicates if
    **  an item is active or not.
    **
    */
    Wtx::Dbo::FieldDefCheckBox IsActiveFieldDef;

    /*!
    ** \brief Item is Active
    **
    ** This is simply a general-purpose flag that indicates if
    **  an item is active or not.
    **
    */
    Wtx::Dbo::FieldDefCheckBox IsVisibleFieldDef;

    /*!
    ** \brief Item is Deleted
    **
    ** This is a flag that indicates an item has been
    **  'flagged-for-deletion'.
    **
    */
    Wtx::Dbo::FieldDefCheckBox IsDeletedFieldDef;

    /*!
    ** \brief Item KEY field
    **
    ** This is a generic 'key' field, used on most everything.
    **  Usually items (like Person and Company) all have a key-field
    **  value that is used in table-views and whatnot.
    **
    */
    Wtx::Dbo::FieldDefLineEdit KeyFieldDef;

    /*!
    ** \brief Item Clarify Field
    **
    ** This is a general-purpose "clarify" field.  In many cases,
    **  such as within Companies and Persons, there are duplicate names
    **  allowed.  This can make a big mess, so this 'clarify' field
    **  can be used to distinguish one Person/Company from another.
    **
    */
    Wtx::Dbo::FieldDefLineEdit CfyFieldDef;

    /*!
    ** \brief Variable Field Value
    **
    ** This field is used like a 'memo' field to store a variety of things.
    **  It can store any text value, but the system uses it to store
    **  JSON string-values.  This allows variable values to be stored freely
    **  without having to change the schema of the database.
    **
    */
    Wtx::Dbo::FieldDefTextArea VarFieldDef;

    /*!
    ** \brief TAG field
    **
    ** This is a general-purpose tag-field that can be used to 'tag' items
    **  with things that can searched for later.  For instance, a user might
    **  be cleaning up a contacts database, and wants to tag varound items
    **  so that they can be dealt with later.
    **
    */
    Wtx::Dbo::FieldDefLineEdit TagFieldDef;

}; // endclass BaseTableDef

  } // endnamespace Dbo
}// endnamespace Wtx

#endif // #ifndef __WTX_BASETABLEDEF_H___

