
#include <Wtx/Dbo/QueryModel.h>
#include <Wtx/Core/Core.h>

#include "Activity.h"

void Wtx::Crm::Activity::mapClasses( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Activity::Item::MapClass( session );
}

void Wtx::Crm::Activity::postCreateTables( Wtx::Dbo::Session & session )
{
  Wtx::Crm::Activity::Item::PostCreateTable( session );

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
Wt::Dbo::ptr< Wtx::Crm::Activity::Item > Wtx::Crm::Activity::add( const std::string & key, const Wt::WDate & date, Wtx::Dbo::Session & session )
{
  Wt::Dbo::ptr< Wtx::Crm::Activity::Item > retVal;

  if( key != "" )
  {
    Wt::Dbo::Transaction t(session);
    retVal =
      session.find<Wtx::Crm::Activity::Item>()
      .where( "UPPER(\"keyField\") = UPPER(?)").bind( key )
      .where( "\"dateStart\" = ?").bind( date )
      .resultValue()
      ;

  }

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << retVal
    << " " << date.toString()
    << " " << retVal-> keyField().value()
    << std::endl
    ;
#endif

  /*!
  ** If an item cannot be found it is simply added.
  **
  */
  if( !retVal )
  {
    Wt::Dbo::Transaction t(session);
    retVal = session.addNew<Wtx::Crm::Activity::Item>( key );
    retVal.modify()-> dateStart().setValue( date );
  }

  return retVal;

} // endWt::Dbo::ptr< Wtx::Crm::Activity::Item > Wtx::Crm::Activity::add( const std::string & key, const Wt::WDateTime & dateTime, Wtx::Dbo::Session & session )

/*!
** \brief Add an item to the lookup table
**
** This will add an item to the look-up table, and return that newly added item.
**
*/
Wt::Dbo::ptr< Wtx::Crm::Activity::Item > Wtx::Crm::Activity::add( const std::string & key, const Wt::WDateTime & dateTime, Wtx::Dbo::Session & session )
{
  Wt::Dbo::ptr< Wtx::Crm::Activity::Item > retVal;

  if( key != "" )
  {
    Wt::Dbo::Transaction t(session);
    retVal =
      session.find<Wtx::Crm::Activity::Item>()
      .where( "UPPER(\"keyField\") = UPPER(?)").bind( key )
      .where( "\"dateStart\" = ?").bind( dateTime.date() )
      .where( "\"timeStart\" = ?").bind( dateTime.time() )
      .resultValue()
      ;

  }

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << retVal << retVal-> keyField().value()
    << " " << dateTime.toString()
    << std::endl
    ;
#endif

  /*!
  ** If an item cannot be found it is simply added.
  **
  */
  if( !retVal )
  {
    Wt::Dbo::Transaction t(session);
    retVal = session.addNew<Wtx::Crm::Activity::Item>( key );
    retVal.modify()-> dateStart().setValue( dateTime.date() );
    retVal.modify()-> timeStart().setValue( dateTime.time() );
  }

  return retVal;

} // endWt::Dbo::ptr< Wtx::Crm::Activity::Item > Wtx::Crm::Activity::add( const std::string & key, const Wt::WDateTime & dateTime, Wtx::Dbo::Session & session )

// static std::map<std::string,Wt::Dbo::ptr<Wtx::Sys::Lookup::Item>> cache;

#ifdef NEVER
Wt::Dbo::ptr< Wtx::Sys::Lookup::Item > Wtx::Sys::Lookup::find( const std::string & key, Wtx::Dbo::Session & session )
{
  Wt::Dbo::ptr< Wtx::Sys::Lookup::Item > retVal;

  if( key != "" )
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

Wt::Dbo::ptr< Wtx::Sys::Lookup::Item > Wtx::Sys::Lookup::ifind( const std::string & key, Wtx::Dbo::Session & session )
{
  Wt::Dbo::ptr< Wtx::Sys::Lookup::Item > retVal;

  if( key != "" )
  {
//    retVal = cache[key];

    if( !retVal )
    {
      Wt::Dbo::Transaction t(session);
      retVal =
        session.find<Wtx::Sys::Lookup::Item>()
        .where( "UPPER(\"keyField\") = UPPER(?)")
        .bind( key )
        .resultValue()
        ;
//      cache[key] = retVal;
    }

  }

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
std::shared_ptr<Wt::WAbstractItemModel> Wtx::Sys::Lookup::getComboBoxModel( int tid, const std::string & group, Wtx::Dbo::Session & session )
{
  auto retVal = std::make_shared< Wtx::Dbo::QueryModel< Wt::Dbo::ptr<Wtx::Sys::Lookup::Item> > >();

  Wt::Dbo::Transaction t(session);

  if( tid == -1 )
  {
    auto query =
      session.find<Wtx::Sys::Lookup::Item>()
      .where("UPPER(\"cfyField\") LIKE UPPER(?) OR \"cfyField\" LIKE '%%*%%'")
      .bind( Wt::WString("%%{1}%%").arg(group) )
      .orderBy("\"keyField\"")
      ;

    retVal-> setQuery( query );
  }

  else
  {
    auto query =
      session.find<Wtx::Sys::Lookup::Item>()
      .where("id = ?")
      .bind( tid )
      ;

    retVal-> setQuery( query );
  }

  retVal-> addColumn("id");
  retVal-> addColumn("keyField");

  return retVal;
}
#endif

