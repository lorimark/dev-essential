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


#ifndef __WTX_CRM_ACTIVITY_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CRM_ACTIVITY_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wtx/Dbo/PermissionItemTpl.h>
#include "Definition.h"

namespace Wtx {
  namespace Crm {
    namespace Activity {

template <class C> class Template
: public Wtx::Dbo::PermissionItemTpl<C>
{
  public:

    Template()
    : Wtx::Dbo::PermissionItemTpl<C>()
    {
    }

    Template( const std::string & keyField )
    : Wtx::Dbo::PermissionItemTpl<C>( keyField )
    {
    }

    virtual ~Template()
    {
    }

    static Definition & TableDef()
    {
      return C::TableDef();
    }

    Wtx::Dbo::Field<std::string> & note() { return m_note; }
    const Wtx::Dbo::Field<std::string> & note() const { return m_note; }

    Wtx::Dbo::Field<Wt::WDate> & dateStart() { return m_dateStart; }
    const Wtx::Dbo::Field<Wt::WDate> & dateStart() const { return m_dateStart; }
    Wtx::Dbo::Field<Wt::WDate> & dateStop() { return m_dateStop; }
    const Wtx::Dbo::Field<Wt::WDate> & dateStop() const { return m_dateStop; }
    Wtx::Dbo::Field<Wt::WTime> & timeStart() { return m_timeStart; }
    const Wtx::Dbo::Field<Wt::WTime> & timeStart() const { return m_timeStart; }
    Wtx::Dbo::Field<Wt::WTime> & timeStop() { return m_timeStop; }
    const Wtx::Dbo::Field<Wt::WTime> & timeStop() const { return m_timeStop; }


    Wtx::Dbo::Field<std::string> m_note;
    Wtx::Dbo::Field<Wt::WDate> m_dateStart;
    Wtx::Dbo::Field<Wt::WDate> m_dateStop;
    Wtx::Dbo::Field<Wt::WTime> m_timeStart;
    Wtx::Dbo::Field<Wt::WTime> m_timeStop;


    template<class Action> void persist( Action &a )
    {
      Wtx::Dbo::PermissionItemTpl<C>::persist( a );
      m_dateStart.persist( a, &TableDef().DateStartFieldDef );
      m_dateStop.persist( a, &TableDef().DateStopFieldDef );
      m_timeStart.persist( a, &TableDef().TimeStartFieldDef );
      m_timeStop.persist( a, &TableDef().TimeStopFieldDef );
      m_note.persist( a, &TableDef().NoteFieldDef );
    }

  private:

};

    } // endnamespace Activity
  } // endnamespace Crm
} // endnamespace Wtx

#endif // __WTX_CRM_ACTIVITY_TEMPLATE_H___

