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


#ifndef __WTX_DBO_BASEITEMTPL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_BASEITEMTPL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/Dbo/Dbo.h>
#include <Wt/WFormModel.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include "BaseTableDef.h"
#include "FieldNumber.h"
#include "FieldTextLine.h"
#include "FieldInt.h"
#include "FieldVar.h"
#include "FieldDate.h"

#include <Wt/Dbo/ptr.h>

namespace Wtx {
  namespace Dbo {

template <class C> class BasePtr
: public Wt::Dbo::ptr<C>
{
  public:

    int lastVersion() const
    {
      return m_lastVersion;
    }

    void setLastVersion( int value )
    {
      m_lastVersion = value;
    }

    int m_lastVersion = -1;

};

template <class C> class BaseItemTpl
: public Wt::Dbo::Dbo<C>
{
  public:

    using Ptr = Wt::Dbo::ptr< C >;
    using Collection = Wt::Dbo::collection< Ptr >;
    using Vector = std::vector< Ptr >;

    BaseItemTpl()
    : Wt::Dbo::Dbo<C>()
    {
    }

    BaseItemTpl( const std::string & key, const std::string & cfy = "" )
    : BaseItemTpl<C>()
    {
      init();
      keyField().setValue( key );
      cfyField().setValue( cfy );
    }

#ifdef NEVER_BUGBUG_NEEDS_COPY_OPERATOR
    BaseItemTpl( const C & other )
    : Wt::Dbo::Dbo<C>()
    {
      init();
      keyField.setValue( other.keyField.value() );
      cfyField.setValue( other.cfyField.value() );
    }
#endif

    virtual ~BaseItemTpl()
    {
    }

    static void MapClass( Wt::Dbo::Session & session )
    {
      Wt::Dbo::Transaction t(session);
      session.mapClass<C>( C::TableDef().tableName() );
      Wt::registerType<C>();
      Wt::registerType< Wt::Dbo::ptr<C> >();
      Wt::registerType< Wt::Dbo::ptr<C> >();

    }

    /*!
    ** \brief Post Table Create
    **
    ** This procedure will loop through all the fields in the table
    **  and in the case of 'unique' fields, it will apply the appropriate
    **  sql codes to make the column unique.
    **
    ** Anything else that needs to be done to the table immediately after
    **  its creation should be applied here in one of the sub-classes.
    **
    */
    static void PostCreateTable( Wt::Dbo::Session & session )
    {

      Wt::Dbo::Transaction t(session);
      for( auto fieldDef : TableDef().fieldDefs() )
      {
        if( fieldDef-> isUnique() )
        {

#ifndef WTX_USING_POSTGRES
#ifndef WTX_USING_SQLITE
#ifndef WTX_USING_MSSQL
#error you must define either WTX_USING_POSTGRES or WTX_USING_SQLITE or WTX_USING_MSSQL
#endif
#endif
#endif

#ifdef WTX_USING_POSTGRES
          auto sql =
            Wt::WString("ALTER TABLE \"{1}\" ADD UNIQUE (\"{2}\")")
            .arg( TableDef().tableName() )
            .arg( fieldDef-> fieldName() )
            .toUTF8()
            ;
#endif

#ifdef WTX_USING_MSSQL
          auto sql =
            Wt::WString("ALTER TABLE \"{1}\" ADD UNIQUE (\"{2}\")")
            .arg( TableDef().tableName() )
            .arg( fieldDef-> fieldName() )
            .toUTF8()
            ;
#endif

#ifdef WTX_USING_SQLITE
            //
            // this works for sqlite
            //
          auto sql =
            Wt::WString
            (
             "CREATE UNIQUE INDEX \"{1}_{2}\" ON \"{1}\" (\"{2}\")"
            )
            .arg( TableDef().tableName() )
            .arg( fieldDef-> fieldName() )
            .toUTF8()
            ;
#endif
          session.execute( sql );
        }

      }

    } // endstatic void PostCreateTable( Wt::Dbo::Session & session )

    static BaseTableDef & TableDef()
    {
      return C::TableDef();
    }

    bool operator== ( const BaseItemTpl<C> & other ) const
    {
      return other.keyField().value() == keyField().value();
    }

    bool operator< ( const BaseItemTpl<C> & other ) const
    {
      return other.keyField().value() < keyField().value();
    }

    bool isInitialized() const
    {
      return m_initialized;
    }

    int lastVersion() const
    {
      return m_lastVersion;
    }

    void setLastVersion( int value ) const
    {
      m_lastVersion = value;
    }

    /*!
    ** \brief Pre-write
    **
    ** Do the things that need to be done before the item is written
    **  to the back-end DB.
    **
    */
    virtual void preWrite()
    {
    }

    /*!
    ** \brief Post-read
    **
    ** Do the things that need to be done after the item is read from
    **  the back-end DB.
    **
    */
    virtual void postRead()
    {
    }

    const Wtx::Dbo::Field<int> & versionSync() const
    {
      return m_versionSync;
    }

    const Wtx::Dbo::Field<bool> & isActive() const
    {
      return m_isActive;
    }

    const Wtx::Dbo::Field<bool> & isVisible() const
    {
      return m_isVisible;
    }

    const Wtx::Dbo::Field<bool> & isDeleted() const
    {
      return m_isDeleted;
    }

    const Wtx::Dbo::Field<std::string> & xid() const
    {
      return m_xid;
    }

    const Wtx::Dbo::Field<std::string> & keyField() const
    {
      return m_keyField;
    }

    const Wtx::Dbo::Field<std::string> & cfyField() const
    {
      return m_cfyField;
    }

    const Wtx::Dbo::FieldVar & varField() const
    {
      return m_varField;
    }

    std::string varField( const std::string & fieldName ) const
    {
      return varField().value( fieldName );
    }

    Wtx::Dbo::Field<int> & versionSync()
    {
      return m_versionSync;
    }

    Wtx::Dbo::Field<bool> & isActive()
    {
      return m_isActive;
    }

    Wtx::Dbo::Field<bool> & isVisible()
    {
      return m_isVisible;
    }

    Wtx::Dbo::Field<bool> & isDeleted()
    {
      return m_isDeleted;
    }

    Wtx::Dbo::Field<std::string> & xid()
    {
      return m_xid;
    }

    Wtx::Dbo::Field<std::string> & keyField()
    {
      return m_keyField;
    }

    Wtx::Dbo::Field<std::string> & cfyField()
    {
      return m_cfyField;
    }

    Wtx::Dbo::FieldVar & varField()
    {
      return m_varField;
    }

    Wtx::Dbo::Field<std::string> & tag()
    {
      return m_tag;
    }

    const Wtx::Dbo::Field<std::string> & tag() const
    {
      return m_tag;
    }

#ifdef THIS_DOESNT_WORK_PROPERLY_USE_THE_STATIC_VERSIONS_OF_THIS_PROGRAM
    bool setId( int newId )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      if( !(this-> session()) )
        return false;

      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      int thisId = this-> self().id();
      auto s = this-> session();
      auto tn = this-> session()-> template tableName<C>();

      Wt::Dbo::Transaction t( *s );

      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      this-> session()-> flush();
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      this-> self().purge();

      std::cout << __FILE__ << ":" << __LINE__ << " " << thisId << " " << newId << std::endl;

      if( thisId != newId )
      {
        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        auto sql =
          Wt::WString("UPDATE \"{1}\" SET id = ? WHERE id = ?")
          .arg( tn )
          .toUTF8()
          ;

        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        s->
          execute( sql )
          .bind( newId )
          .bind( thisId )
          ;

      }

      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      return true;
    }
#endif

    /*!
    ** \brief Create an Edit Widget
    **
    ** This function creates a new edit widget from this item.  It calls upon the
    **  field definition 
    **
    */
    virtual std::unique_ptr<Wt::WWidget> createEditWidget( Wt::WFormModel::Field f ) const
    {
      auto s = dynamic_cast<Wtx::Dbo::Session*>( BaseItemTpl<C>::session() );

//      std::cout << __FILE__ << ":" << __LINE__ << " createEditWidget: '" << f << "'" << " sid:" << BaseItemTpl<C>::id() << std::endl;

      for( auto fieldDef : C::TableDef().fieldDefs() )
      {
        if( f == fieldDef-> fieldName() )
        {
          return fieldDef-> createEditWidget( BaseItemTpl<C>::id(), *s );
        }
      }

      std::cout << __FILE__ << ":" << __LINE__ << " unable to create widget: '" << f << "'" << std::endl;

      return std::make_unique<Wt::WLineEdit>();
    }

    template<class Action> void persist( Action & a )
    {
      m_xid         .persist ( a, &TableDef() .XidFieldDef         );
      m_versionSync .persist ( a, &TableDef() .VersionSyncFieldDef );
      m_isActive    .persist ( a, &TableDef() .IsActiveFieldDef    );
      m_isVisible   .persist ( a, &TableDef() .IsVisibleFieldDef   );
      m_isDeleted   .persist ( a, &TableDef() .IsDeletedFieldDef   );
      m_keyField    .persist ( a, &TableDef() .KeyFieldDef         );
      m_cfyField    .persist ( a, &TableDef() .CfyFieldDef         );
      m_varField    .persist ( a, &TableDef() .VarFieldDef         );
      m_tag         .persist ( a, &TableDef() .TagFieldDef         );
    }

  protected:

    void init()
    {
      versionSync() .setValue( -1    );
      isActive()    .setValue( true  );
      isVisible()   .setValue( true  );
      isDeleted()   .setValue( false );
      m_initialized = true;
    }


  private:

    bool m_initialized = false;

    Wtx::Dbo::Field<std::string> m_xid;
    Wtx::Dbo::FieldInt m_versionSync;
    Wtx::Dbo::Field<bool> m_isActive;
    Wtx::Dbo::Field<bool> m_isVisible;
    Wtx::Dbo::Field<bool> m_isDeleted;
    Wtx::Dbo::Field<std::string> m_keyField;
    Wtx::Dbo::Field<std::string> m_cfyField;
    Wtx::Dbo::FieldVar m_varField;
    Wtx::Dbo::Field<std::string> m_tag;

    mutable int m_lastVersion = -1;

}; // endtemplate <class C> class BaseItemTpl

template <class C>
std::ostream & operator<< ( std::ostream & s, const BaseItemTpl<C> & o )
{
  return s << o.keyField().value();
}

  } // endnamespace Dbo
} // endnamespace Wtx

#endif

