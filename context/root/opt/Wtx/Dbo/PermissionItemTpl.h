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


#ifndef __WTX_DBO_PERMISSIONITEMTPL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_PERMISSIONITEMTPL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/WLocalDateTime.h>

#include <Wtx/Dbo/PermissionTableDef.h>
#include <Wtx/Dbo/BaseItemTpl.h>
#include <Wtx/Dbo/FieldNumber.h>
#include <Wtx/Dbo/FieldFloat.h>
#include <Wtx/Dbo/FieldInt.h>
#include <Wtx/Dbo/FieldBigInt.h>
#include <Wtx/Dbo/FieldCurrency.h>
#include <Wtx/Dbo/FieldLookup.h>
#include <Wtx/Dbo/FieldBoolean.h>
#include <Wtx/Dbo/FieldTextLine.h>
#include <Wtx/Dbo/FieldTextMemo.h>
#include <Wtx/Dbo/FieldDate.h>
#include <Wtx/Dbo/FieldDateTime.h>
#include <Wtx/Dbo/FieldHasMany.h>
#include <Wtx/Dbo/FieldBelongsTo.h>
#include <Wtx/Dbo/FieldWeak.h>

#ifdef UIDFIELD_FORMAT_UUID
#include <uuid/uuid.h>
#else
#include <Wt/WRandom.h>
#endif

namespace Wtx {
  namespace Dbo {

template <class C> class PermissionItemTpl
: public BaseItemTpl<C>
{
  public:

    PermissionItemTpl()
    : BaseItemTpl<C>()
    {
    }

    PermissionItemTpl( const std::string & key, const std::string & cfy = "" )
    : BaseItemTpl<C>( key, cfy )
    {
      createdOn().setValue( Wt::WDateTime( Wt::WLocalDateTime::currentDateTime().date(), Wt::WLocalDateTime::currentDateTime().time() ) );
      changedOn().setValue( Wt::WDateTime( Wt::WLocalDateTime::currentDateTime().date(), Wt::WLocalDateTime::currentDateTime().time() ) );

#ifdef UIDFIELD_FORMAT_UUID
      /*
      ** generate a more complicated uuid string
      **
      ** In order to generate a uuid string, a few libraries need to be
      **  linked in to the project.  On linux this is done with the
      **  following:
      **
      ** sudo apt-get install uuid-dev
      **
      ** To use the uuid method the following things need to be added
      **  to the CMAKE:
      **
      **  add_definitions(-DUIDFIELD_FORMAT_UUID)
      **  target_link_libraries(myproject wt wthttp wtdbo wtdbosqlite3 uuid)
      **
      */
      uuid_t uuid;
      uuid_generate(uuid);

      char uuidout[41];
      uuidout[0] = '{';
      uuid_unparse_lower( uuid, uuidout+1 );
      uuidout[37] = '}';
      uuidout[38] = 0;
      uidField.setValue( std::string( uuidout ) );
#else
      /*
      ** generate simple random string
      **
      */
      uidField().setValue( Wt::WRandom::generateId(20) );
#endif

      pMode().setValue(0);
      pUser().setValue(0);
      pGroup().setValue(0);
    }

    virtual ~PermissionItemTpl()
    {
    }

    static PermissionTableDef & TableDef()
    {
      return C::TableDef();
    }

    Wtx::Dbo::Field<std::string> & uidField() { return m_uidField; }
    const Wtx::Dbo::Field<std::string> & uidField() const { return m_uidField; }

    Wtx::Dbo::FieldNumber & pMode() { return m_pMode; }
    const Wtx::Dbo::FieldNumber & pMode() const { return m_pMode; }

    Wtx::Dbo::FieldDateTime & createdOn() { return m_createdOn; }
    const Wtx::Dbo::Field<Wt::WDateTime> & createdOn() const { return m_createdOn; }

    Wtx::Dbo::FieldDateTime & changedOn() { return m_changedOn; }
    const Wtx::Dbo::Field<Wt::WDateTime> & changedOn() const { return m_changedOn; }

    Wtx::Dbo::Field<int> & pUser() { return m_pUser; }
    const Wtx::Dbo::Field<int> & pUser() const { return m_pUser; }

    Wtx::Dbo::Field<int> & pGroup() { return m_pGroup; }
    const Wtx::Dbo::Field<int> & pGroup() const { return m_pGroup; }

    Wtx::Dbo::Field<std::string> & sessionLock() { return m_sessionLock; }
    const Wtx::Dbo::Field<std::string> & sessionLock() const { return m_sessionLock; }

    bool setLock( const std::string & value )
    {
      sessionLock()
        .setValue
        (
         Wt::WString("{1},{2}")
         .arg( Wt::WDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz").toUTF8() )
         .arg( value )
         .toUTF8()
        );

      return true;
    }

    bool unLock()
    {
      sessionLock()
        .setValue("");

      return true;
    }

    bool isLocked() const
    {
      return sessionLock().value() != "";
    }

    Wt::WDateTime lockTime() const
    {
      return Wt::WDateTime::fromString( sessionLock().value(), "yyyyMMddhhmmsszzz" );
    }

    Wtx::Dbo::Field<std::string> m_uidField;
    Wtx::Dbo::FieldNumber m_pMode;
    Wtx::Dbo::FieldDateTime m_createdOn;
    Wtx::Dbo::FieldDateTime m_changedOn;
    Wtx::Dbo::Field<int> m_pUser;
    Wtx::Dbo::Field<int> m_pGroup;
    Wtx::Dbo::Field<std::string> m_sessionLock;

    template<class Action> void persist( Action & a )
    {
      Wtx::Dbo::BaseItemTpl<C>::persist(a);
      m_uidField.persist(    a, &TableDef().UidFieldDef         );
      m_pMode.persist(       a, &TableDef().PModeFieldDef       );
      m_createdOn.persist(   a, &TableDef().CreatedOnFieldDef   );
      m_changedOn.persist(   a, &TableDef().ChangedOnFieldDef   );
//      pUser.persist(       a, &TableDef().PUserFieldDef       );
//      pGroup.persist(      a, &TableDef().PGroupFieldDef      );
      m_sessionLock.persist( a, &TableDef().SessionLockFieldDef );
    }

  private:

}; // endtemplate <class C> class PermissionItemTpl

  } // endnamespace Dbo
} // endnamespace Wtx


#endif


