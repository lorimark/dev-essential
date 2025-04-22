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


#ifndef __WTX_SYS_LOG_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_SYS_LOG_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Dbo/PermissionItemTpl.h>
#include <Wtx/Sys/User/Item.h>
#include "Definition.h"

namespace Wtx {
  namespace Sys {
    namespace Log {

template <class C> class Template
: public Wtx::Dbo::PermissionItemTpl<C>
{
  public:

    Template()
    : Wtx::Dbo::PermissionItemTpl<C>()
    {
    }

    Template( const std::string & key )
    : Wtx::Dbo::PermissionItemTpl<C>(key)
    {
    }

    static Definition & TableDef()
    {
      return C::TableDef();
    }

          Wtx::Dbo::Field<std::string> & clip()       { return m_clip; }
    const Wtx::Dbo::Field<std::string> & clip() const { return m_clip; }

          Wtx::Dbo::Field<int> level()       { return m_level; }
    const Wtx::Dbo::Field<int> level() const { return m_level; }

          Wtx::Dbo::Field<std::string> & details()       { return m_details; }
    const Wtx::Dbo::Field<std::string> & details() const { return m_details; }

          Wtx::Dbo::FieldLookup<Wt::Dbo::ptr< Wtx::Sys::User::Item >> & user()       { return m_user; }
    const Wtx::Dbo::FieldLookup<Wt::Dbo::ptr< Wtx::Sys::User::Item >> & user() const { return m_user; }

          Wtx::Dbo::FieldDate & date()       { return m_date; }
    const Wtx::Dbo::FieldDate & date() const { return m_date; }

          Wtx::Dbo::Field<std::string> & extra()       { return m_extra; }
    const Wtx::Dbo::Field<std::string> & extra() const { return m_extra; }

          Wtx::Dbo::Field<int> & sourceId()       { return m_sourceId; }
    const Wtx::Dbo::Field<int> & sourceId() const { return m_sourceId; }

    template<class Action> void persist( Action &a )
    {
      Wtx::Dbo::PermissionItemTpl<C>::persist( a );

      m_clip     .persist( a, &TableDef().ClipFieldDef       );
      m_level    .persist( a, &TableDef().LevelFieldDef      );
      m_details  .persist( a, &TableDef().DetailsFieldDef    );
      m_user     .persist( a, &TableDef().UserFieldDef       );
      m_date     .persist( a, &TableDef().DateFieldDef       );
      m_extra    .persist( a, &TableDef().ExtraFieldDef      );
      m_sourceId .persist( a, &TableDef().SourceIdFieldDef   );

    }

  private:

    Wtx::Dbo::Field<std::string> m_clip;
    Wtx::Dbo::Field<int> m_level;
    Wtx::Dbo::Field<std::string> m_details;
    Wtx::Dbo::FieldLookup< Wt::Dbo::ptr< Wtx::Sys::User::Item > > m_user;
    Wtx::Dbo::FieldDate m_date;
    Wtx::Dbo::Field<std::string> m_extra;
    Wtx::Dbo::Field<int> m_sourceId;

};

    } // endnamespace Log
  } // endnamespace Sys
} // endnamespace Wtx


#endif

