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


#ifndef __WTX_WEB_BLOGENTRY_ITEM_H___
#define __WTX_WEB_BLOGENTRY_ITEM_H___

#include "Template.h"

namespace Wtx {
  namespace Web {
    namespace BlogEntry {

class Item
: public Template<Item>
{
  public:

    Item( const std::string & keyField = "" )
    : Template( keyField )
    {
    }

    Item( const Item & other )
    : Template( other.keyField().value() )
    {
    }

    template<class Action> void persist(Action &a)
    {
      Template<Item>::persist( a );
    }

    static Definition & TableDef() { return s_tableDef; }

    static void MapClass( Wt::Dbo::Session & session )
    {
      Template<Item>::MapClass( session );
      Wt::registerType<Item>();
      Wt::registerType< Wt::Dbo::ptr<Item> >();
    }

 

  private:

    static Definition & s_tableDef;

};


    } // endnamespace BlogEntry
  } // endnamespace Web
} // endnamespace Wtx

DBO_EXTERN_TEMPLATES(Wtx::Web::BlogEntry::Item);

#endif

