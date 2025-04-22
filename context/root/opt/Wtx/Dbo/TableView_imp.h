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

#include <Wt/WLineEdit.h>
#include <Wt/WDialog.h>
#include <Wt/WTemplate.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WPushButton.h>
#include <Wt/WPopupMenu.h>
#include <Wt/Dbo/Json.h>

#include <Wtx/Core/Core.h>


template <class C>
Wtx::Dbo::TableView<C>::~TableView()
{

}

template <class C>
Wtx::Dbo::TableView<C>::TableView( Wtx::Dbo::Session * s )
: Wtx::TableView(),
  m_session(s)
{
  std::cout
    << std::string(session()-> template tableName<C>())
    << std::endl;

  if( !viewDef().load( std::string(session()-> template tableName<C>()), session() ) )
  {
    viewDef().load( C::TableDef(), session() );
  }

  init();
}

template <class C>
Wtx::Dbo::TableView<C>::TableView( const std::string & tableDefName, Wtx::Dbo::Session * s )
: Wtx::TableView(),
  m_session(s)
{
  std::cout
    << layoutName(tableDefName)
    << std::endl;

  if( !loadLayout( layoutName(tableDefName) ) )
  {
    viewDef().load( C::TableDef(), session() );
    viewDef().save( layoutName(tableDefName), session() );
  }

  init();
}

template <class C>
Wtx::Dbo::TableView<C>::TableView( const Wtx::TableViewDef::ViewDef & vd, Wtx::Dbo::Session * s )
: Wtx::TableView(),
  m_session(s)
{
  viewDef().load( vd, s );

  init();

}

template <class C>
Wtx::Dbo::TableView<C>::TableView( const std::string & tableDefName, const Wtx::TableViewDef::ViewDef & vd, Wtx::Dbo::Session * s )
: Wtx::TableView(),
  m_session(s)
{
  std::cout
    << layoutName(tableDefName)
    << std::endl;

  if( !loadLayout( layoutName(tableDefName) ) )
  {
    viewDef().load( vd, session() );
    viewDef().save( layoutName(tableDefName), session() );
  }

  init();
}

template <class C>
void Wtx::Dbo::TableView<C>::init()
{
  m_model =
    std::make_shared
    <
     Wtx::Dbo::QueryModel
     <
       Wt::Dbo::ptr<C>
     >
    >();

  model()-> setSession( session() );
  model()-> m_countTable = C::TableDef().tableName();
  model()-> setViewDef( &viewDef() );

  setQuery();
  setLayout();

  viewDef().changed().connect( std::bind( [=]()
  {
    setQuery();
    setLayout();
  }));

}


template <class C>
std::string Wtx::Dbo::TableView<C>::layoutName( const std::string & name ) const
{
  return
    Wt::WString("viewDef.{1}.{2}")
    .arg( C::TableDef().tableName() )
    .arg( name )
    .toUTF8()
    ;
}


template <class C>
void Wtx::Dbo::TableView<C>::showHeaderPopup( const Wt::WMouseEvent & event )
{
  if( event.button() == Wt::MouseButton::Right )
  {
    Wt::WPopupMenu* pItemPopup = new Wt::WPopupMenu();

    pItemPopup-> addItem( Wt::WString/*::tr*/( "Layout..." ) )->
      triggered().connect( std::bind( [this](){ viewDef().editProperties(); } ) );

    pItemPopup-> addItem( Wt::WString/*::tr*/( "Save Layout" ) )->
      triggered().connect( std::bind( [this]()
      {
        int col = 0;
        for( auto columnDef : viewDef().m_def.columnDefs )
        {
          viewDef().m_def.columnDefs[col].width = columnWidth( col );
          col++;
        }

        if( viewDef().m_name == "" )
        {
          auto dialog = new Wt::WDialog("Save View Layout");
          dialog-> rejectWhenEscapePressed();
          auto templt =
            dialog-> contents()-> addNew<Wt::WTemplate>
            (
             "<div>"
             "  Please enter a name for this view"
             "</div>"
             "<div>${lineEdit}</div>"
             "<div><center>"
             "  ${ok class=\"btn-success btn-xs\"}"
             "  ${cancel class=\"btn-danger btn-xs\"}"
             "</center></div>"
            );

          auto lineEdit =
            templt-> bindNew<Wt::WLineEdit>("lineEdit");

          templt-> bindNew<Wt::WPushButton>("ok","ok")->
            clicked().connect( dialog, &Wt::WDialog::accept );

          templt-> bindNew<Wt::WPushButton>("cancel","cancel")->
            clicked().connect( dialog, &Wt::WDialog::reject );

          dialog-> finished().connect( [=]()
          {
            if( dialog-> result() != Wt::DialogCode::Accepted )
              return;

            if( lineEdit-> text() == "" )
              return;

            viewDef().save( lineEdit-> text().toUTF8(), session() );
          });

          dialog-> exec();
        }
        else
        {
          viewDef().save( viewDef().m_name, session() );
        }

      }));

    pItemPopup-> popup( event );
  }
}


template <class C>
bool Wtx::Dbo::TableView<C>::loadLayout( const std::string & name )
{
  return viewDef().load( layoutName(name), C::TableDef(), session() );
}


template <class C>
void Wtx::Dbo::TableView<C>::saveLayout( const std::string & name )
{
  viewDef().save( layoutName(name), session() );
}

template <class C>
const std::string & Wtx::Dbo::TableView<C>::filter() const
{
  return m_filterValue;
}

template <class C>
void Wtx::Dbo::TableView<C>::setFilter()
{
  Wt::Dbo::Transaction t(*session());

  auto where = m_filterValue;
  if( m_subFilterValue != "" )
  {
    if( where != "" )
    {
      where += " AND ";
    }

    where += m_subFilterValue;
  }

  auto query =
    session()-> template find<C>()
    .where( where )
    ;

  model()-> setCountWhere( "WHERE " + where );

  m_queryRowCount = query.resultList().size();

  for( auto sortField : viewDef().m_def.sortFields )
  {
    query = query.orderBy( sortField );
  }

  model()-> setQuery( query, true );

  setupLayout();

  setModel( model() );

}

template <class C>
void Wtx::Dbo::TableView<C>::setFilter( const std::string & f )
{
  viewDef().m_def.filter = f;
  m_filterValue = f;

  setFilter();

} // endvoid Wtx::Dbo::TableView<C>::setFilter( const std::string & f )

template <class C>
void Wtx::Dbo::TableView<C>::setSearch( const std::string & s )
{
  std::cout << __FILE__ << ":" << __LINE__ << " todo setSearch:" << s << std::endl;

} // endvoid Wtx::Dbo::TableView<C>::setFilter( const std::string & f )

template <class C>
void Wtx::Dbo::TableView<C>::setSubFilter( const std::string & f )
{
  m_subFilterValue = f;

  setFilter();

} // endvoid Wtx::Dbo::TableView<C>::setFilter( const std::string & f )

template <class C>
const std::string & Wtx::Dbo::TableView<C>::queryValue() const
{
  return m_queryValue;

}

template <class C>
void Wtx::Dbo::TableView<C>::setQuery( const std::string & s )
{
  std::string qry;
  std::string search = s;

  qry = viewDef().m_def.filter;

  /*
  ** parse the search string to produce an SQL statement
  **  to attempt to find files.
  **
  */
  if( search != "" )
  {
    /*!
    ** \todo fix this
    **
    ** BUGBUG: this will replace a single-quote character
    **  with a double-single-quote character.  This is bad
    **  because the search string can still produce a sql-injection
    **  issue.
    **
    */
    {
      std::size_t start_pos = 0;
      while( (start_pos = search.find("'",start_pos)) != std::string::npos )
      {
        search.replace( start_pos, size_t(1), std::string("''") );
        start_pos += 2;
      }

    }

    /*!
    ** \todo fix this
    **
    ** BUGBUG: need to audit the 'search' string to make
    ** sure there is no risk of SQL injection.  Or, instead
    ** of trying to parse the sql string if we can figure
    ** out how to call upon query.where().bind() repeatedly
    ** in seperate calls
    **
    ** When assigning this search to the regular filter, make
    **  sure the regular filter is wrapped with parenthesis so
    **  the logic doesn't get blown if there's more than one
    **  clause in the regular filter.  Ideally you'd expect the
    **  author of the base filter to already wrap things in
    **  parenthesis, but we can't rely on it.
    **
    */
    if( qry != "" )
      qry = "\n  (" + qry + ") AND ";

    /*
    ** see if the search string can be converted to
    **  an integer and if so search the id number of
    **  the items
    **
    */
    try
    {
      int id = std::stoi(search);

      qry +=
        Wt::WString( "(id = {1}) OR " )
        .arg(id)
        .toUTF8()
        ;

    }
    catch(...)
    {
    }

    auto searches = Wtx::Core::split( search, ' ' );

//    std::cout << __FILE__ << ":" << __LINE__ << " " << search << " " << searches.size() << std::endl;
    bool x = false;
    for( auto s : searches )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " '" << s << "'" << std::endl;

      if( x )
        qry += " AND (";
      else
        qry += "(";

      /*
      ** the key field is pretty-much guaranteed to be
      **  a part of the table, but we should check in the
      **  event this report view is used on a different
      **  table
      **
      */
      qry +=
        Wt::WString( "\n  (UPPER(\"keyField\") LIKE UPPER('%{1}%'))" )
        .arg(s)
        .toUTF8()
        ;

      /*
      ** the cfy field is pretty-much guaranteed to be
      **  a part of the table, but we should check in the
      **  event this report view is used on a different
      **  table
      **
      */
      qry +=
        Wt::WString( "\n  OR (UPPER(\"cfyField\") LIKE UPPER('%{1}%'))" )
        .arg(s)
        .toUTF8()
        ;

      /*
      ** the tag field is pretty-much guaranteed to be
      **  a part of the table, but we should check in the
      **  event this report view is used on a different
      **  table
      **
      */
      qry +=
        Wt::WString( "\n  OR (UPPER(\"tag\") LIKE UPPER('%{1}%'))" )
        .arg(s)
        .toUTF8()
        ;

      /*
      ** the tag field is pretty-much guaranteed to be
      **  a part of the table, but we should check in the
      **  event this report view is used on a different
      **  table
      **
      */
      qry +=
        Wt::WString( "\n  OR (\"xid\" LIKE '%{1}%')" )
        .arg(s)
        .toUTF8()
        ;

      /*
      ** walk through the list of 'searchFields' and apply
      **  them as additional OR search criteria
      **
      */
      for( auto searchField : viewDef().m_def.searchFields )
      {
        qry +=
          Wt::WString( "\n  OR (UPPER(\"{1}\") LIKE UPPER('%{2}%'))" )
          .arg( searchField )
          .arg( s )
          .toUTF8()
          ;
      }

      /// \todo add function to probe field defs for searchable fields

      qry += ")\n";

      x = true;

    } // endfor( auto s : searches )

    if( viewDef().m_def.idin.size() > 0 )
    {
      if( viewDef().m_def.idin.at(0).find("id in") != std::string::npos )
      {
        auto f =
          Wt::WString( viewDef().m_def.idin.at(0) )
          .arg( search )
          .toUTF8()
          ;

        qry +=
          Wt::WString(" OR ({1}) ")
          .arg( f )
          .toUTF8()
          ;
      }
      else
      {
        auto idin = Wtx::Core::split( viewDef().m_def.idin.at(0), '_' );

        if( idin.size() == 3 )
        {
          qry +=
            Wt::WString(" OR \"{1}\" IN ")
            .arg( viewDef().m_def.idin.at(0) )
            .toUTF8()
            ;

          auto f =
            Wt::WString("(UPPER(\"keyField\") LIKE UPPER('%{1}%'))" )
            .arg( search )
            .toUTF8()
            ;

          f += " OR ";

          f +=
            Wt::WString("(UPPER(\"cfyField\") LIKE UPPER('%{1}%'))" )
            .arg( search )
            .toUTF8()
            ;

          qry +=
            Wt::WString( "(SELECT id FROM \"{1}\" WHERE ({2}))" )
            .arg( idin.at(1) )
            .arg( f )
            .toUTF8()
            ;


        } // endif( idin.size() == 3 )

      }

    } // endif( viewDef().m_def.idin.size() > 0 )

//    std::cout << __FILE__ << ":" << __LINE__ << " " << qry << std::endl;

  } // endif( search != "" )

  m_queryValue = qry;

  /*
  ** if the query string has ~anything~ in it, then
  **  we need to prepend the WHERE clause
  **
  */
  if( qry != "" )
    qry = " WHERE (" + qry + ")";

//      m_model.setCountTable( C::TableName );
//      m_model.setCountWhere( qry );


  if( viewDef().hasFlag( "show-sql" ) )
    std::cout << __FILE__ << ":" << __LINE__ << " " << qry << std::endl;

  Wt::Dbo::Transaction t(*session());

  auto query =
    session()-> template find<C>(qry)
    ;

  model()-> setCountWhere( qry );

  m_queryRowCount = query.resultList().size();

  for( auto sortField : viewDef().m_def.sortFields )
  {
    query = query.orderBy( sortField );
  }

  model()-> setQuery( query, true );

  setupLayout();

  setModel( model() );

} // endvoid Wtx::Dbo::TableView<C>::setQuery( const std::string & s )


template <class C>
void Wtx::Dbo::TableView<C>::selectItem( Wt::Dbo::ptr<C> item )
{
  auto row = model()-> indexOf( item );

  auto index = model()-> index( row, 0 );

  select( index );
  scrollTo( index );

}

template <class C>
void Wtx::Dbo::TableView<C>::setupLayout( )
{
  setRowHeaderCount( viewDef().m_def.rowHeaderCount );

  if( viewDef().m_def.columnDefs.size() == 0 )
  {
    model()-> addAllFieldsAsColumns();
  }
  else
  {

    if( !colsSet )
    {
      int c=0;
      for( auto columnDef : viewDef().m_def.columnDefs )
      {
        model()-> addColumn( columnDef.field );

        if( columnDef.label != "" )
          model()-> setHeaderData( c, Wt::Orientation::Horizontal, columnDef.label, Wt::ItemDataRole::Display );

        if( columnDef.toolTip != "" )
          model()-> setHeaderData( c, Wt::Orientation::Horizontal, columnDef.toolTip, Wt::ItemDataRole::ToolTip );

        if( columnDef.delegate )
          setItemDelegateForColumn( c, std::shared_ptr<Wt::WItemDelegate>( columnDef.delegate( session() ) ) );

        setColumnAlignment( c, columnDef.alignment );

        c++;
      }
      colsSet = true;
    }
  }

}

template <class C>
void Wtx::Dbo::TableView<C>::setLayout()
{
  setAlternatingRowColors( viewDef().m_def.alternatingRowColors );

  setSelectionMode( viewDef().m_def.selectionMode );

  if( std::find( viewDef().m_def.flags.begin(), viewDef().m_def.flags.end(), "nosort" ) != viewDef().m_def.flags.end() )
    setSortingEnabled( false );

  int col = 0;
  for( auto columnDef : viewDef().m_def.columnDefs )
    setColumnWidth( col++, columnDef.width );

}


template <class C>
void Wtx::Dbo::TableView<C>::refresh()
{
  setQuery();
  setLayout();
}

template <class C>
void Wtx::Dbo::TableView<C>::refreshSelected()
{
  auto selectedIndex = *(selectedIndexes().begin());

  auto indexBeg = model()-> index( selectedIndex.row(), 0 );
  auto indexEnd = model()-> index( selectedIndex.row(), model()-> columnCount()-1 );

  model()-> dataChanged().emit( indexBeg, indexEnd );

  select(   selectedIndex );
  scrollTo( selectedIndex );

}

template <class C>
Wt::Dbo::ptr<C> Wtx::Dbo::TableView<C>::selectedItem()
{
  return item( *(selectedIndexes().begin()) );

}





