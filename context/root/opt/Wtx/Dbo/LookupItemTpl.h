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


#ifndef __WTX_DBO_LOOKUPITEMTPL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_LOOKUPITEMTPL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include "LookupTableDef.h"
#include "BaseItemTpl.h"

namespace Wtx {
  namespace Dbo {

template <class C> class LookupItemTpl
: public BaseItemTpl<C>
{
  public:

    LookupItemTpl()
    : BaseItemTpl<C>()
    {
    }

    LookupItemTpl( const std::string & key )
    : BaseItemTpl<C>( key )
    {
    }

    LookupItemTpl( const std::string & key, const std::string cfy )
    : BaseItemTpl<C>( key, cfy )
    {
    }

    virtual ~LookupItemTpl()
    {
    }

    static LookupTableDef & TableDef()
    {
      return C::TableDef();
    }

    const Wtx::Dbo::Field<std::string> & description() const { return m_description; }
          Wtx::Dbo::Field<std::string> & description()       { return m_description; }

          Wtx::Dbo::Field<std::string> & v1()       { return m_v1; }
    const Wtx::Dbo::Field<std::string> & v1() const { return m_v1; }
          Wtx::Dbo::Field<std::string> & v2()       { return m_v2; }
    const Wtx::Dbo::Field<std::string> & v2() const { return m_v2; }
          Wtx::Dbo::Field<std::string> & v3()       { return m_v3; }
    const Wtx::Dbo::Field<std::string> & v3() const { return m_v3; }

    template<class Action> void persist( Action & a )
    {
      Wtx::Dbo::BaseItemTpl<C>::persist(a);
      m_description.persist( a, &TableDef().DescriptionFieldDef );
      m_v1.persist( a, &TableDef().V1FieldDef );
      m_v2.persist( a, &TableDef().V2FieldDef );
      m_v3.persist( a, &TableDef().V3FieldDef );
    }

  private:

    Wtx::Dbo::Field<std::string> m_description;
    Wtx::Dbo::Field<std::string> m_v1;
    Wtx::Dbo::Field<std::string> m_v2;
    Wtx::Dbo::Field<std::string> m_v3;

}; // endtemplate <class C> class LookupItemTpl

  } // endnamespace Dbo
} // endnamespace Wtx


#endif


