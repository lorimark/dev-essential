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


#ifndef __WTX_SYS_USER_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_SYS_USER_TEMPLATE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/Auth/Dbo/AuthInfo.h>

#include <Wtx/Dbo/PermissionItemTpl.h>
#include <Wtx/Sys/Group/Item.h>
#include "Definition.h"

namespace Wtx {
  namespace Sys {
    namespace User {

template <class C> class Template
: public Wtx::Dbo::BaseItemTpl<C>
{
  public:

    Template( const std::string & key = "", const std::string & cfy = "" )
    : Wtx::Dbo::BaseItemTpl<C>( key, cfy )
    {
    }

    virtual ~Template()
    {
    }

    static Definition & TableDef()
    {
      return C::TableDef();
    }

          Wtx::Dbo::Field<std::string> & firstName()       { return m_firstName; }
    const Wtx::Dbo::Field<std::string> & firstName() const { return m_firstName; }

          Wtx::Dbo::Field<std::string> & lastName()       { return m_lastName; }
    const Wtx::Dbo::Field<std::string> & lastName() const { return m_lastName; }

          Wtx::Dbo::Field<std::string> & middleName()       { return m_middleName; }
    const Wtx::Dbo::Field<std::string> & middleName() const { return m_middleName; }

          Wtx::Dbo::Field<std::string> & abbreviation()       { return m_abbreviation; }
    const Wtx::Dbo::Field<std::string> & abbreviation() const { return m_abbreviation; }

          Wtx::Dbo::Field<std::string> & alias()       { return m_alias; }
    const Wtx::Dbo::Field<std::string> & alias() const { return m_alias; }

          Wtx::Dbo::Field<std::string> & phone()       { return m_phone; }
    const Wtx::Dbo::Field<std::string> & phone() const { return m_phone; }

          Wtx::Dbo::Field<std::string> & mobile()       { return m_mobile; }
    const Wtx::Dbo::Field<std::string> & mobile() const { return m_mobile; }

          Wtx::Dbo::Field<std::string> & email()       { return m_email; }
    const Wtx::Dbo::Field<std::string> & email() const { return m_email; }

          Wtx::Dbo::Field<std::string> & alert()       { return m_alert; }
    const Wtx::Dbo::Field<std::string> & alert() const { return m_alert; }

          Wtx::Dbo::Field<std::string> & groups()       { return m_groups; }
    const Wtx::Dbo::Field<std::string> & groups() const { return m_groups; }

          Wtx::Dbo::Field<std::string> & storage()       { return m_storage; }
    const Wtx::Dbo::Field<std::string> & storage() const { return m_storage; }

          Wtx::Dbo::Field<std::string> & notes()       { return m_notes; }
    const Wtx::Dbo::Field<std::string> & notes() const { return m_notes; }

          Wtx::Dbo::Field<std::string> & nickName()       { return m_nickName; }
    const Wtx::Dbo::Field<std::string> & nickName() const { return m_nickName; }

          Wt::Dbo::collection< Wt::Dbo::ptr<Wtx::Sys::Group::Item> > & inGroup()       { return m_inGroup; }
    const Wt::Dbo::collection< Wt::Dbo::ptr<Wtx::Sys::Group::Item> > & inGroup() const { return m_inGroup; }

#ifdef WTX_USING_USERAUTH
          Wt::Dbo::weak_ptr< Wt::Auth::Dbo::AuthInfo<C> > authInfo()       { return m_authInfo; }
    const Wt::Dbo::weak_ptr< Wt::Auth::Dbo::AuthInfo<C> > authInfo() const { return m_authInfo; }
#endif

    template<class Action> void persist( Action &a )
    {
      Wtx::Dbo::BaseItemTpl<C>::persist( a );
      m_firstName    .persist( a, &TableDef(). FirstNameFieldDef    );
      m_lastName     .persist( a, &TableDef(). LastNameFieldDef     );
      m_middleName   .persist( a, &TableDef(). MiddleNameFieldDef   );
      m_nickName     .persist( a, &TableDef(). NicknameFieldDef     );
      m_abbreviation .persist( a, &TableDef(). AbbreviationFieldDef );
      m_alias        .persist( a, &TableDef(). AliasFieldDef        );
      m_phone        .persist( a, &TableDef(). PhoneFieldDef        );
      m_mobile       .persist( a, &TableDef(). MobileFieldDef       );
      m_email        .persist( a, &TableDef(). EmailFieldDef        );
      m_alert        .persist( a, &TableDef(). AlertFieldDef        );
      m_groups       .persist( a, &TableDef(). GroupsFieldDef       );
      m_storage      .persist( a, &TableDef(). StorageFieldDef      );
      m_notes        .persist( a, &TableDef(). NotesFieldDef        );

#ifdef WTX_USING_USERAUTH
      Wt::Dbo::hasOne( a, m_authInfo, "user" );
#endif

      Wt::Dbo::hasMany( a, m_inGroup, Wt::Dbo::RelationType::ManyToMany, "zcUserGroup" );

    }

  private:

    Wtx::Dbo::Field<std::string> m_firstName;
    Wtx::Dbo::Field<std::string> m_lastName;
    Wtx::Dbo::Field<std::string> m_middleName;
    Wtx::Dbo::Field<std::string> m_nickName;
    Wtx::Dbo::Field<std::string> m_abbreviation;
    Wtx::Dbo::Field<std::string> m_alias;
    Wtx::Dbo::Field<std::string> m_phone;
    Wtx::Dbo::Field<std::string> m_mobile;
    Wtx::Dbo::Field<std::string> m_email;
    Wtx::Dbo::Field<std::string> m_alert;
    Wtx::Dbo::Field<std::string> m_groups;
    Wtx::Dbo::Field<std::string> m_storage;
    Wtx::Dbo::Field<std::string> m_notes;
    Wt::Dbo::collection< Wt::Dbo::ptr<Wtx::Sys::Group::Item> > m_inGroup;

#ifdef WTX_USING_USERAUTH
    Wt::Dbo::weak_ptr< Wt::Auth::Dbo::AuthInfo<C> > m_authInfo;
#endif

};

    } // endnamespace User
  } // endnamespace Sys
} // endnamespace Wtx


#endif

