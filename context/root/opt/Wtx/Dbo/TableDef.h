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


#ifndef __WTX_DBO_TABLEDEF_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_TABLEDEF_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <iostream>
#include <vector>

namespace Wtx {
  namespace Dbo {

class FieldDefBase;
class ConnectionDef;

/*!
** \brief Table Definition
**
** This object encapsulates the functionality of a complete database-table
**  definition.  This object contains all the necessary definition components
**  to run the application.
**
** The object contains lists of fields and connections and indexes and so on
**  once these components are fully defined within the table definition then
**  it can be used to manufacture the database object within the database
**  server.
**
**
*/
class TableDef
{
  public:

    /*!
    ** \brief ctor
    **
    ** This initializes the table name to the object.  The table name is
    **  constant and will never change throughout the life of this object.
    **
    */
    TableDef( const char * tn )
    : m_tableName(tn)
    {
    }

    const char * tableName() const { return m_tableName; }

    void push_back( FieldDefBase & fd );

    FieldDefBase * fieldDef( const std::string & fieldName ) const;

    const std::vector<FieldDefBase*> & fieldDefs() const { return m_fieldDefs; }

    std::string toJson() const;

  private:

    const char * m_tableName;
    std::vector<FieldDefBase*> m_fieldDefs;
    std::vector<FieldDefBase*> m_formFieldDefs;
    std::vector<ConnectionDef*> m_connectionDefs;

};

  } // endnamespace Dbo
} // endnamespace Wtx

#endif // #ifndef __WTX_TABLEDEF_H___

