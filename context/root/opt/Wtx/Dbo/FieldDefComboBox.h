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


#ifndef __WTX_DBO_FIELDDEFCOMBOBOX_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_FIELDDEFCOMBOBOX_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include "FieldDefBase.h"

namespace Wtx {
  namespace Dbo {

/*!
** \brief Check Box
**
**
*/
class FieldDefComboBox
: public Wtx::Dbo::FieldDefBase
{
  public:

    /*!
    ** \brief ctor
    **
    **
    */
    FieldDefComboBox
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      int          w   = -1,          /// width
      int          h   = -1,          /// height
      Flags        f   = Flags::None, /// flags
      std::string  lb  = "",          /// label
      std::string  ph  = "",          /// placeholder text
      std::string  inf = "",          /// info
      std::string  tt  = "",          /// tooltipText
      int          ht  = -1           /// help topic
    );

    /*!
    ** \brief ctor
    **
    **
    */
    FieldDefComboBox
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      std::string  lb,                /// label
      std::string  ph  = "",          /// placeholder text
      std::string  inf = "",          /// info
      std::string  tt  = "",          /// tooltipText
      int          ht  = -1           /// help topic
    );

    virtual ~FieldDefComboBox() {}

    void addItem( const std::string & text );

    void setNoSelectionEnabled( bool enabled );

    virtual std::unique_ptr<Wt::WWidget> createEditWidget( int sid, Wtx::Dbo::Session & session ) const;

    bool m_noSelectionEnabled = false;
    std::vector< std::string > m_items;

}; // endclass Wtx::Dbo::FieldDefComboBox

  } // endnamespace Dbo
} // endnamespace Wtx

#endif // #ifndef __WTX_DBO_FIELDDEFCOMBOXBOX_H___

