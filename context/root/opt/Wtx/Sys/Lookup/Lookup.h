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


#ifndef __WTX_SYS_LOOKUP_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_SYS_LOOKUP_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include "Item.h"

namespace Wtx {
  namespace Sys {

    /*!
    ** \brief Lookups (things for combo-boxes)
    **
    ** This utility is used to populate combo-boxes in the user interface.
    **  Each entry in to a combo-box is referenced by specifying a group
    **  value.  The group value can be any key word.  Multiple group
    **  values are separated by a ',' (comma).  A '*' (asterisk) resolves
    **  all group values.  There is at least 1 item (usually the first
    **  item) that has no keyField value.  This item is used to offer the
    **  combo-box a (null-like) value, allowing users to clear the combo-box.
    **
    ** \code
    ** warehouse_demo=> select * from "sysLookup" order by id;
    **  id | keyField  |             cfyField              | description | system
    ** ----+-----------+-----------------------------------+-------------+--------
    **   1 |           | *                                 |             | f
    **   2 | Active    | mrpInventoryStatus,mrpOrderStatus |             | f
    **   3 | Inactive  | mrpInventoryStatus                |             | f
    **   4 | Hold      | mrpInventoryStatus                |             | f
    **   5 | Destroyed | mrpInventoryStatus                |             | f
    **   6 | New       | mrpOrderStatus                    |             | f
    **   7 | InWork    | mrpOrderStatus                    |             | f
    ** (7 rows)
    ** \endcode
    **
    */
    namespace Lookup {

void mapClasses( Wtx::Dbo::Session & session );
void postCreateTables( Wtx::Dbo::Session & session );

Wtx::Sys::Lookup::Item::Ptr load( int id, Wtx::Dbo::Session & session );
Wtx::Sys::Lookup::Item::Ptr load( const std::string & id, Wtx::Dbo::Session & session );
Wtx::Sys::Lookup::Item::Ptr load( const Wt::WString & id, Wtx::Dbo::Session & session );

Wtx::Sys::Lookup::Item::Ptr add( const std::string & key, const std::string & group, Wtx::Dbo::Session & session );
Wtx::Sys::Lookup::Item::Ptr find( int id, Wtx::Dbo::Session & session );
Wtx::Sys::Lookup::Item::Ptr find( const std::string & key, Wtx::Dbo::Session & session );
Wtx::Sys::Lookup::Item::Ptr ifind( const std::string & key, Wtx::Dbo::Session & session );
Wtx::Sys::Lookup::Item::Ptr xfind( const std::string & xid, Wtx::Dbo::Session & session );

Wtx::Sys::Lookup::Item::Vector vectorGroup( const std::string & group, Wtx::Dbo::Session & session );

std::shared_ptr<Wt::WAbstractItemModel> getComboBoxModel( int tid, const std::string & group, Wtx::Dbo::Session & session, bool includeBlank = false );

Wt::WItemDelegate * delegate( Wtx::Dbo::Session * s );

    } // endnamespace Lookup
  } // endnamespace Sys
} // endnamespace Wtx

#endif // end#ifndef __WTX_SYS_LOOKUP_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__


