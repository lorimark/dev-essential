
#include <Wtx/Util.h>
#include <Wtx/Dbo/QueryModel.h>
#include <Wtx/Core/Core.h>

#include "Lookup.h"
#include "ItemDelegate.h"

void Wtx::Sys::Lookup::mapClasses( Wtx::Dbo::Session & session )
{
  Wtx::Sys::Lookup::Item::MapClass( session );
}

void Wtx::Sys::Lookup::postCreateTables( Wtx::Dbo::Session & session )
{
  Wtx::Sys::Lookup::Item::PostCreateTable( session );

//  Wt::Dbo::Transaction t(session);
//  auto sysLookup = session.addNew< Wtx::Sys::Lookup::Item >( "" );
//  sysLookup.modify()-> cfyField().setValue( "*" );

}

/*!
** \brief Add an item to the lookup table
**
** This will add an item to the look-up table, and return that newly added item.
**
*/
Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::add( const std::string & key, const std::string & group, Wtx::Dbo::Session & session )
{
  /*!
  ** This procedure first checks the look-up table to see if an item exists.
  **
  */
  auto item = ifind( key, session );

  /*!
  ** If an item cannot be found it is simply added.
  **
  */
  if( !item )
  {
    Wt::Dbo::Transaction t(session);
    item = session.addNew<Wtx::Sys::Lookup::Item>( key, group );
  }

  /*!
  **  The item is then checked to see if the 'group' field (aka; cfyField)
  **  contains the group-value of this look-up item, and if it is not present,
  **  it is added to the group string, preserving any existing
  **  group-values contained in that field.
  **
  */
  if( item )
  {
    auto v = item-> cfyField().value();
    if( v.find(group) == std::string::npos )
    {
      if( v != "" )
          v += ",";
      v += group;
      Wt::Dbo::Transaction t(session);
      item.modify()-> cfyField().setValue( v );
    }

  }

  return item;

} // endWtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::add( const std::string & key, const std::string & group, Wtx::Dbo::Session & session )

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::load( int id, Wtx::Dbo::Session & session )
{
  return find( id, session );
}

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::load( const std::string & id, Wtx::Dbo::Session & session )
{
  return load( Wtx::stof( id ) , session );
}

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::load( const Wt::WString & id, Wtx::Dbo::Session & session )
{
  return load( id.toUTF8() , session );
}

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::find( int id, Wtx::Dbo::Session & session )
{

  Wt::Dbo::Transaction t(session);
  auto retVal = session.template load<Wtx::Sys::Lookup::Item>(id);
  return retVal;

}

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::find( const std::string & key, Wtx::Dbo::Session & session )
{
  Wtx::Sys::Lookup::Item::Ptr retVal;

  if( key != "" && key != "[null]" )
  {
    if( key.at(0) == '[' )
    {
      auto v = Wtx::Core::split( key, ':' );
      int idVal = std::stoi(v.at(1));

      if( idVal != -1 )
      {
        Wt::Dbo::Transaction t(session);
        retVal = session.template load<Wtx::Sys::Lookup::Item>(idVal);
      }
    }
    else
    {
//      retVal = cache[key];

      if( !retVal )
      {
        Wt::Dbo::Transaction t(session);
        retVal =
          session.find<Wtx::Sys::Lookup::Item>()
          .where( "\"keyField\" = ?")
          .bind( key )
          .resultValue()
          ;
//        cache[key] = retVal;
      }
    }

  }

  return retVal;
}

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::ifind( const std::string & key, Wtx::Dbo::Session & session )
{
  Wtx::Sys::Lookup::Item::Ptr retVal;

  if( key != "" )
  {
    if( !retVal )
    {
      Wt::Dbo::Transaction t(session);
      retVal =
        session.find<Wtx::Sys::Lookup::Item>()
        .where( "UPPER(\"keyField\") = UPPER(?)")
        .bind( key )
        .resultValue()
        ;
    }

  }

  return retVal;
}

Wtx::Sys::Lookup::Item::Ptr Wtx::Sys::Lookup::xfind( const std::string & xid, Wtx::Dbo::Session & session )
{
  Wtx::Sys::Lookup::Item::Ptr retVal;

  if( xid != "" )
  {
    Wt::Dbo::Transaction t(session);
    retVal =
      session.find< Wtx::Sys::Lookup::Item >()
      .where( "UPPER(\"xid\") = UPPER(?)")
      .bind( xid )
      .resultValue()
      ;

  }

  return retVal;
}


Wtx::Sys::Lookup::Item::Vector Wtx::Sys::Lookup::vectorGroup( const std::string & group, Wtx::Dbo::Session & session )
{
  Wt::Dbo::Transaction t(session);
  auto items =
    session.find< Wtx::Sys::Lookup::Item >()
    .where
    (
     Wt::WString("\"cfyField\" LIKE '%{1}%'")
     .arg( group )
     .toUTF8()
    )
    .orderBy( "id desc" )
    .resultList()
    ;

  Wtx::Sys::Lookup::Item::Vector retVal( items.begin(), items.end() );

  return retVal;

}

/*!
** \brief Get a Combo-Box Model
**
** This will create a item model from the Lookup table based on the 'group'
**  value.  It is possible to specify the .tid. or 'target-ID' for the item.
**  When the .tid. is provided (isn't -1) then the model will be filled with
**  only that one item.  This is useful when the combo-box needs to be populated
**  with the current target value, but doesn't need to (yet) carry _all_ the
**  possible combo-box selection items - as this can result in literally 100's
**  of items populating the combo box result values.  It is unnecessary to
**  populate all the combo boxes on an input forms with all the possible
**  selection choices, as this just leads to a slow-loading user interface.
**
*/
std::shared_ptr<Wt::WAbstractItemModel> Wtx::Sys::Lookup::getComboBoxModel( int tid, const std::string & group, Wtx::Dbo::Session & session, bool includeBlank )
{
  auto retVal = std::make_shared< Wtx::Dbo::QueryModel< Wtx::Sys::Lookup::Item::Ptr > >();

  Wt::Dbo::Transaction t(session);

  if( tid == -1 )
  {
    if( includeBlank )
    {
      typedef std::tuple< int, std::string > Tuple;

      auto retVal = std::make_shared< Wtx::Dbo::QueryModel< Tuple > >();

      auto sql =
        Wt::WString::tr( "Wtx.sysLookup.combobox.sql" )
        .toUTF8()
        ;

      auto query =
      session.query< Tuple >( sql )
        ;

      retVal-> setQuery( query );

      retVal-> addAllFieldsAsColumns();

      return retVal;
    }

    else
    {
      auto query =
        session.find<Wtx::Sys::Lookup::Item>()
        .where("\"isActive\" is true AND (UPPER(\"cfyField\") LIKE UPPER(?) OR \"cfyField\" LIKE '%%*%%')")
        .bind( Wt::WString("%%{1}%%").arg(group) )
        .orderBy("\"keyField\"")
        ;

      retVal-> setQuery( query );
      retVal-> addColumn("id");
      retVal-> addColumn("keyField");
    }

  }

  else
  {
    auto query =
      session.find<Wtx::Sys::Lookup::Item>()
      .where("id = ?")
      .bind( tid )
      ;

    retVal-> setQuery( query );
    retVal-> addColumn("id");
    retVal-> addColumn("keyField");

  }

  return retVal;
}


Wt::WItemDelegate * Wtx::Sys::Lookup::delegate( Wtx::Dbo::Session * s )
{
  auto retVal = Wtx::Sys::Lookup::ItemDelegate::create(s);

  return retVal;
}



