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



#include <Wt/Dbo/Query.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Json/Value.h>
#include <Wt/WDialog.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTemplate.h>
#include <Wt/WComboBox.h>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WTabWidget.h>
#include <Wt/WTableView.h>
#include <Wt/WStringListModel.h>

#include <Wtx/Dbo/Session.h>
#include <Wtx/Sys/Config/Item.h>

#include "TableViewDef.h"

bool Wtx::TableViewDef::load( const std::string & defName, const Wtx::Dbo::TableDef & tableDef, Wtx::Dbo::Session * session )
{
  m_name = defName;

  Wt::Dbo::Transaction t(*session);
  auto item =
    session-> template find<Wtx::Sys::Config::Item>()
    .where( "\"keyField\" = ?" )
    .bind( defName )
    .resultValue()
    ;

  if( item.id() == -1 )
  {
    m_def.columnNames.push_back( "id" );
    for( auto fieldDef : tableDef.fieldDefs() )
      m_def.columnNames.push_back( fieldDef-> fieldName() );
  }

  else
  {
    Wt::Json::Object result;
    try {
      Wt::Json::parse( item-> varField().Field::value(), result );
    }
    catch( std::exception & e )
    {
      return false;
    }

    m_def.title                = result.get("title").orIfNull("");
    m_def.tip                  = result.get("tip").orIfNull("");
    m_def.rowHeaderCount       = result.get("rowHeaderCount").orIfNull(0);
    m_def.columnResizeEnabled  = result.get("columnResizeEnabled").orIfNull(true);
    m_def.alternatingRowColors = result.get("alternatingRowColors").orIfNull(true);
    m_def.sql                  = result.get("sql").orIfNull("");
    m_def.filter               = result.get("filter").orIfNull("");
//    m_def.idin                 = result.get("idin").orIfNull("");
    m_def.showHeader           = result.get("showHeader").orIfNull(true);
    m_def.showFooter           = result.get("showFooter").orIfNull(false);
    m_def.showPrevNext         = result.get("showPrevNext").orIfNull(false);
    m_def.hideSearch           = result.get("hideSearch").orIfNull(false);
    m_def.allowFilter          = result.get("allowFilter").orIfNull(false);
    m_def.allowAdd             = result.get("allowAdd").orIfNull(false);
    m_def.allowChange          = result.get("allowChange").orIfNull(false);
    m_def.allowDelete          = result.get("allowDelete").orIfNull(false);
    m_def.allowExport          = result.get("allowExport").orIfNull(false);
    m_def.allowSearch          = result.get("allowSearch").orIfNull(false);
    m_def.allowPrint           = result.get("allowPrint").orIfNull(false);
    m_def.allowUnlock          = result.get("allowUnlock").orIfNull(false);
    m_def.additional           = result.get("additional").orIfNull("");
    m_def.checkBoxSelect       = result.get("checkBoxSelect").orIfNull(false);
    m_def.deleteMessage        = result.get("deleteMessage").orIfNull("");

    switch( result.get("selectionMode").orIfNull(0) )
    {
      case 0: m_def.selectionMode = Wt::SelectionMode::None;     break;
      case 1: m_def.selectionMode = Wt::SelectionMode::Single;   break;
      case 2: m_def.selectionMode = Wt::SelectionMode::Extended; break;
    }

    {
      Wt::Json::Array ja = result.get("sortFields");
      for( auto field : ja )
        m_def.sortFields.push_back( field );
    }

    {
      Wt::Json::Array ja = result.get("searchFields");
      for( auto field : ja )
        m_def.searchFields.push_back( field );
    }

    {
      Wt::Json::Array ja = result.get("columnDefs");
      for( Wt::Json::Object jobj : ja )
      {
        ColumnDef colDef;
        colDef.field = jobj.get("field").orIfNull("");
        colDef.label = jobj.get("label").orIfNull("");
        colDef.width = jobj.get("width").orIfNull(100);
//        colDef.alignment = jobj.get("alignment").orIfNull(0);
        colDef.toolTip = jobj.get("toolTip").orIfNull("");
        m_def.columnDefs.push_back( colDef );
      }
    }

    {
      Wt::Json::Array ja = result.get("flags");
      for( auto flag : ja )
        m_def.flags.push_back( flag );
    }

  }

  for( auto fieldDef : tableDef.fieldDefs() )
    m_def.columnNames.push_back( fieldDef-> fieldName() );

  return true;

} // endbool Wtx::TableViewDef::load( const std::string & defName, const Wtx::Dbo::TableDef & tableDef, Wtx::Dbo::Session * session )

bool Wtx::TableViewDef::load( const Wtx::Dbo::TableDef & tableDef, Wtx::Dbo::Session * session )
{
  (void)session;

  /*
  ** Give the view some sort of default name.
  **
  */
  m_name =
    Wt::WString("viewDef.{1}.Default")
    .arg( tableDef.tableName() )
    .toUTF8()
    ;

  m_def.title = "Default";

  m_def.columnNames.push_back( "id" );
  for( auto fieldDef : tableDef.fieldDefs() )
    m_def.columnNames.push_back( fieldDef-> fieldName() );

  return true;

} // endbool Wtx::TableViewDef::load( const Wtx::Dbo::TableDef & tableDef, Wtx::Dbo::Session * session )

bool Wtx::TableViewDef::load( const Wtx::TableViewDef::ViewDef & def, Wtx::Dbo::Session * session )
{
  m_def.title                = def.title;
  m_def.tip                  = def.tip;
  m_def.rowHeaderCount       = def.rowHeaderCount;
  m_def.selectionMode        = def.selectionMode;
  m_def.columnResizeEnabled  = def.columnResizeEnabled;
  m_def.alternatingRowColors = def.alternatingRowColors;
  m_def.sql                  = def.sql;
  m_def.filter               = def.filter;
  m_def.idin                 = def.idin;
  m_def.doubleClick          = def.doubleClick;
  m_def.showHeader           = def.showHeader;
  m_def.showFooter           = def.showFooter;
  m_def.showPrevNext         = def.showPrevNext;
  m_def.hideSearch           = def.hideSearch;
  m_def.allowFilter          = def.allowFilter;
  m_def.allowAdd             = def.allowAdd;
  m_def.allowChange          = def.allowChange;
  m_def.allowDelete          = def.allowDelete;
  m_def.allowExport          = def.allowExport;
  m_def.allowSearch          = def.allowSearch;
  m_def.allowPrint           = def.allowPrint;
  m_def.allowUnlock          = def.allowUnlock;
  m_def.additional           = def.additional;
  m_def.delegate             = def.delegate;
  m_def.checkBoxSelect       = def.checkBoxSelect;
  m_def.deleteMessage        = def.deleteMessage;

  for( auto sortField : def.sortFields )
    m_def.sortFields.push_back( sortField );

  for( auto searchField : def.searchFields )
    m_def.searchFields.push_back( searchField );

  for( auto colDef : def.columnDefs )
    m_def.columnDefs.push_back( colDef );

  for( auto colName : def.columnNames )
    m_def.columnNames.push_back( colName );

  for( auto flag : def.flags )
    m_def.flags.push_back( flag );

  return true;
}

bool Wtx::TableViewDef::save( const std::string & defName, Wtx::Dbo::Session * session )
{
  m_name = defName;

  Wt::Dbo::Transaction t(*session);
  auto item =
    session-> template find<Wtx::Sys::Config::Item>()
    .where( "\"keyField\" = ?" )
    .bind( defName )
    .resultValue()
    ;

  if( item.id() == -1 )
    item =
      session-> template addNew<Wtx::Sys::Config::Item>( m_name );

  Wt::Json::Object jobj;
  jobj[ "title"                ] = Wt::WString( m_def.title );
  jobj[ "tip"                  ] = Wt::WString( m_def.tip );
  jobj[ "rowHeaderCount"       ] = m_def.rowHeaderCount;
  jobj[ "selectionMode"        ] = (int)m_def.selectionMode;
  jobj[ "columnResizeEnabled"  ] = m_def.columnResizeEnabled;
  jobj[ "alternatingRowColors" ] = m_def.alternatingRowColors;
  jobj[ "sql"                  ] = Wt::WString( m_def.sql );
  jobj[ "filter"               ] = Wt::WString( m_def.filter );
//  jobj[ "idin"                 ] = Wt::WString( m_def.idin ); /// \todo
  jobj[ "showHeader"           ] = m_def.showHeader;
  jobj[ "showFooter"           ] = m_def.showFooter;
  jobj[ "showPrevNext"         ] = m_def.showPrevNext;
  jobj[ "hideSearch"           ] = m_def.hideSearch;
  jobj[ "allowFilter"          ] = m_def.allowFilter;
  jobj[ "allowAdd"             ] = m_def.allowAdd;
  jobj[ "allowChange"          ] = m_def.allowChange;
  jobj[ "allowDelete"          ] = m_def.allowDelete;
  jobj[ "allowExport"          ] = m_def.allowExport;
  jobj[ "allowSearch"          ] = m_def.allowSearch;
  jobj[ "allowPrint"           ] = m_def.allowPrint;
  jobj[ "allowUnlock"          ] = m_def.allowUnlock;
  jobj[ "additional"           ] = Wt::WString( m_def.additional );
  jobj[ "checkBoxSelect"       ] = m_def.checkBoxSelect;
  jobj[ "deleteMessage"        ] = Wt::WString( m_def.deleteMessage );

  {
    Wt::Json::Array ja;
    for( auto sortField : m_def.sortFields )
      ja.push_back( Wt::WString(sortField) );
    jobj[ "sortFields" ] = ja;
  }

  {
    Wt::Json::Array ja;
    for( auto searchField : m_def.searchFields )
      ja.push_back( Wt::WString(searchField) );
    jobj[ "searchFields" ] = ja;
  }

  {
    Wt::Json::Array ja;
    for( auto colDef : m_def.columnDefs )
    {
      Wt::Json::Object jo;
      jo[ "field"   ] = Wt::WString(colDef.field);
      jo[ "label"   ] = Wt::WString(colDef.label);
      jo[ "width"   ] = colDef.width.value();
      jo[ "toolTip" ] = Wt::WString(colDef.toolTip);
      ja.push_back( jo );
    }
    jobj[ "columnDefs" ] = ja;
  }

  {
    Wt::Json::Array ja;
    for( auto flag : m_def.flags )
      ja.push_back( Wt::WString(flag) );
    jobj[ "flags" ] = ja;
  }

  item.modify()-> varField().setValue( Wt::Json::serialize(jobj) );

  /*
  ** return true if an item was found and written to
  **
  */
  return item.id() != -1;

} // endbool Wtx::TableViewDef::save( const std::string & defName, Wtx::Dbo::Session * session )

void Wtx::TableViewDef::editProperties()
{
  auto dialog = addChild( std::make_unique<Wt::WDialog>("View Properties") );
  dialog-> rejectWhenEscapePressed(true);

  auto templt = dialog-> contents()-> addNew<Wt::WTemplate>
  (
   Wt::WString
   (
    "${tabWidget}"
    "<center>"
    " <table>"
    "  <tr><td> ${ok} </td><td> ${cancel} </td></tr>"
    " </table>"
    "</center>"
   )
  );

  auto tabWidget = templt-> bindNew<Wt::WTabWidget>("tabWidget");

  auto props_ = std::make_unique<Wt::WTemplate>
  (
   Wt::WString
   (
    "<table>"
    " <tr><td> Title:                  </td><td> ${title}                </td>"
    "     <td> Tool Tip:               </td><td> ${tip}                  </td></tr>"
    " <tr><td> Selection:              </td><td> ${selectionMode}        </td></tr>"
    " <tr><td> SQL:                    </td><td colspan=\"3\"> ${sql}    </td></tr>"
    " <tr><td> Filter:                 </td><td colspan=\"3\"> ${filter} </td></tr>"
    " <tr><td> ID in:                  </td><td colspan=\"3\"> ${idin}   </td></tr>"
    " <tr><td> Column Resize Enabled:  </td><td> ${columnResizeEnabled}  </td>"
    "     <td> Alternating Row Colors: </td><td> ${alternatingRowColors} </td></tr>"
    " <tr><td> Show Header:            </td><td> ${showHeader}           </td>"
    "     <td> Show Footer:            </td><td> ${showFooter}           </td></tr>"
    "     <td> Show Prev/Next:         </td><td> ${showPrevNext}         </td></tr>"
    " <tr><td> Hide Search:            </td><td> ${hideSearch}           </td></tr>"
    " <tr><td> Allow Filter:           </td><td> ${allowFilter}          </td>"
    "     <td> Allow Add:              </td><td> ${allowAdd}             </td></tr>"
    " <tr><td> Allow Change:           </td><td> ${allowChange}          </td>"
    "     <td> Allow Delete:           </td><td> ${allowDelete}          </td></tr>"
    " <tr><td> Allow Export:           </td><td> ${allowExport}          </td>"
    "     <td> Allow Search:           </td><td> ${allowSearch}          </td></tr>"
    "     <td> Allow Print:            </td><td> ${allowPrint}           </td></tr>"
    "     <td> Allow Unlock:           </td><td> ${allowUnlock}          </td></tr>"
    "     <td> Additional:             </td><td> ${additional}           </td></tr>"
    "     <td> CheckBoxSelect:         </td><td> ${checkBoxSelect}       </td></tr>"
    "     <td> DeleteMessage:          </td><td> ${deleteMessage}        </td></tr>"
    "</table>"
   )
  );
  auto props = props_.get();
  tabWidget-> addTab( std::move(props_), "Display" );

  props-> bindNew<Wt::WLineEdit>( "title",  m_def.title  );
  props-> bindNew<Wt::WLineEdit>( "tip",    m_def.tip    );
  props-> bindNew<Wt::WLineEdit>( "sql",    m_def.sql    );
  props-> bindNew<Wt::WLineEdit>( "filter", m_def.filter );
//  props-> bindNew<Wt::WLineEdit>( "idin",   m_def.idin   );

  auto cbSelectionMode = props-> bindNew<Wt::WComboBox>("selectionMode");
  cbSelectionMode-> addItem( "No Selections" );
  cbSelectionMode-> addItem( "Single Selection Only" );
  cbSelectionMode-> addItem( "Multiple Selection" );
  cbSelectionMode-> setCurrentIndex( (int)m_def.selectionMode );

  auto _checkState = []( bool value )
  {
    if( value )
      return( Wt::CheckState::Checked );

    return( Wt::CheckState::Unchecked );
  };

  props-> bindNew<Wt::WCheckBox>( "columnResizeEnabled" )->
    setCheckState( _checkState( m_def.columnResizeEnabled ) );

  props-> bindNew<Wt::WCheckBox>( "alternatingRowColors" )->
    setCheckState( _checkState( m_def.alternatingRowColors ) );

  props-> bindNew<Wt::WCheckBox>( "showHeader" )->
    setCheckState( _checkState( m_def.showHeader ) );

  props-> bindNew<Wt::WCheckBox>( "showFooter" )->
    setCheckState( _checkState( m_def.showFooter ) );

  props-> bindNew<Wt::WCheckBox>( "showPrevNext" )->
    setCheckState( _checkState( m_def.showPrevNext ) );

  props-> bindNew<Wt::WCheckBox>( "hideSearch" )->
    setCheckState( _checkState( m_def.hideSearch ) );

  props-> bindNew<Wt::WCheckBox>( "allowFilter" )->
    setCheckState( _checkState( m_def.allowFilter ) );

  props-> bindNew<Wt::WCheckBox>( "allowAdd" )->
    setCheckState( _checkState( m_def.allowAdd ) );

  props-> bindNew<Wt::WCheckBox>( "allowChange" )->
    setCheckState( _checkState( m_def.allowChange ) );

  props-> bindNew<Wt::WCheckBox>( "allowDelete" )->
    setCheckState( _checkState( m_def.allowDelete ) );

  props-> bindNew<Wt::WCheckBox>( "allowExport" )->
    setCheckState( _checkState( m_def.allowExport ) );

  props-> bindNew<Wt::WCheckBox>( "allowSearch" )->
    setCheckState( _checkState( m_def.allowSearch ) );

  props-> bindNew<Wt::WCheckBox>( "allowPrint" )->
    setCheckState( _checkState( m_def.allowPrint ) );

  props-> bindNew<Wt::WCheckBox>( "allowUnlock" )->
    setCheckState( _checkState( m_def.allowUnlock ) );

  props-> bindNew<Wt::WCheckBox>( "checkBoxSelect" )->
    setCheckState( _checkState( m_def.checkBoxSelect ) );

  props-> bindNew<Wt::WLineEdit>( "additional" )->
    setValueText( m_def.additional );

  templt-> bindNew<Wt::WPushButton>( "ok", "Ok" )->
    clicked().connect( dialog, &Wt::WDialog::accept );

  templt-> bindNew<Wt::WPushButton>( "cancel", "Cancel" )->
    clicked().connect( dialog, &Wt::WDialog::reject );





  auto cols_ = std::make_unique<Wt::WTemplate>
  (
   Wt::WString
   (
    "<center><table>"
    " <tr>"
    "  <td> Columns in View </td>"
    "  <td> Columns not in View </td>"
    " </tr>"
    " <tr>"
    "  <td> ${colsIn} </td>"
    "  <td> ${colsNo} </td>"
    " </tr>"
    " <tr>"
    "  <td> ${removeCol} </td>"
    "  <td> ${appendCol} </td>"
    " </tr>"
    " <tr>"
    "  <td> ${colOption} </td>"
    "  <td> ${insertCol} </td>"
    " </tr>"
    "</table></center>"
   )
  );
  auto cols = cols_.get();
  tabWidget-> addTab( std::move(cols_), "Columns" );

  auto tvColsIn = cols-> bindNew<Wt::WTableView>("colsIn");
  auto tvColsNo = cols-> bindNew<Wt::WTableView>("colsNo");

  auto slColsIn = std::make_shared<Wt::WStringListModel>();
  for( auto colDef : m_def.columnDefs )
    slColsIn-> addString( colDef.field );
  tvColsIn-> setModel( slColsIn );
  tvColsIn-> setHeight( 200 );
  tvColsIn-> setSelectionMode( Wt::SelectionMode::Single );
  tvColsIn-> setEditTriggers( Wt::EditTrigger::None );

  auto pbRemoveCol = cols-> bindNew<Wt::WPushButton>( "removeCol", "Remove Column"  );
  auto pbColOption = cols-> bindNew<Wt::WPushButton>( "colOption", "Column Options" );


  auto slColsNo = std::make_shared<Wt::WStringListModel>();
  tvColsNo-> setModel( slColsNo );
  tvColsNo-> setHeight( 200 );
  tvColsNo-> setSelectionMode( Wt::SelectionMode::Single );
  tvColsNo-> setEditTriggers( Wt::EditTrigger::None );

  auto pbAppendCol = cols-> bindNew<Wt::WPushButton>( "appendCol", "Append Column"  );
  auto pbInsertCol = cols-> bindNew<Wt::WPushButton>( "insertCol", "Insert Column"  );

  auto _refreshCols = [=]()
  {
    if( slColsNo-> rowCount() > 0 )
      slColsNo-> removeRows( 0, slColsNo-> rowCount() );

    for( auto colName : m_def.columnNames )
      if( std::find( slColsIn-> stringList().begin(), slColsIn-> stringList().end(), colName ) == slColsIn-> stringList().end() )
        slColsNo-> addString( colName );
  };

  auto _enableButtons = [=]()
  {
    if( slColsIn-> rowCount() > 0 )
    {
      pbRemoveCol-> setEnabled( true );
      pbColOption-> setEnabled( true );
    }
    else
    {
      pbRemoveCol-> setEnabled( false );
      pbColOption-> setEnabled( false );
    }

    if( slColsNo-> rowCount() > 0 )
    {
      pbAppendCol-> setEnabled( true );
      pbInsertCol-> setEnabled( true );
    }
    else
    {
      pbAppendCol-> setEnabled( false );
      pbInsertCol-> setEnabled( false );
    }

  };

  auto _removeCol = [=]()
  {
    if( tvColsIn-> selectedIndexes().size() > 0 )
    {
      auto index = *(tvColsIn-> selectedIndexes().begin());

      if( index.isValid() )
      {
        slColsIn-> removeRows( index.row(), 1 );
      }
    }

    _refreshCols();
    _enableButtons();
  };

  auto _appendCol = [=]()
  {
    if( tvColsNo-> selectedIndexes().size() > 0 )
    {
      auto index = *(tvColsNo-> selectedIndexes().begin());

      if( index.isValid() )
      {
        slColsIn-> addString( Wt::asString( slColsNo-> data( index ) ) );
      }
    }

    _refreshCols();
    _enableButtons();
  };

  auto _insertCol = [=]()
  {
    if( tvColsIn-> selectedIndexes().size() > 0
    &&  tvColsNo-> selectedIndexes().size() > 0 )
    {
      auto indexIn = *(tvColsIn-> selectedIndexes().begin());
      auto indexNo = *(tvColsNo-> selectedIndexes().begin());

      if( indexIn.isValid()
      &&  indexNo.isValid() )
      {
        slColsIn-> insertString
        (
          indexIn.row(),
          Wt::asString( slColsNo-> data( indexNo ) )
        );
      }
    }

    _refreshCols();
    _enableButtons();
  };



  pbRemoveCol-> clicked().connect(       std::bind( [=](){ _removeCol();     } ) );
  pbAppendCol-> clicked().connect(       std::bind( [=](){ _appendCol();     } ) );
  pbInsertCol-> clicked().connect(       std::bind( [=](){ _insertCol();     } ) );
  tvColsIn->    clicked().connect(       std::bind( [=](){ _enableButtons(); } ) );
  tvColsIn->    doubleClicked().connect( std::bind( [=](){ _removeCol();     } ) );
  tvColsNo->    clicked().connect(       std::bind( [=](){ _enableButtons(); } ) );
  tvColsNo->    doubleClicked().connect( std::bind( [=](){ _appendCol();     } ) );

  _refreshCols();
  _enableButtons();

  pbColOption-> clicked().connect( std::bind( [tvColsIn,slColsIn,this]()
  {
    if( tvColsIn-> selectedIndexes().size() == 0 )
      return;

    auto index = *(tvColsIn-> selectedIndexes().begin());

    if( !index.isValid() )
      return;

    auto colName = slColsIn-> stringList().at( index.row() );

    for( int i = 0; i < m_def.columnDefs.size(); i++ )
    {
      if( m_def.columnDefs[i].field == colName )
      {
        m_def.columnDefs[i].editProperties();
        break;
      }
    }

#ifdef NEVER

#endif

  }));



  dialog-> finished().connect( std::bind( [=]()
  {
    if( dialog-> result() != Wt::DialogCode::Accepted )
      return;

    auto _getString = [props]( const std::string & varName, std::string & value )
    {
      auto w = static_cast<Wt::WLineEdit*>( props-> resolveWidget(varName) );
      value = w-> valueText().toUTF8();
    };

    _getString( "title",  m_def.title  );
    _getString( "tip",    m_def.tip    );
    _getString( "sql",    m_def.sql    );
    _getString( "filter", m_def.filter );
//    _getString( "idin",   m_def.idin   );

    auto _getChecked = [props]( const std::string & varName, bool & value )
    {
      auto w = static_cast<Wt::WCheckBox*>( props-> resolveWidget(varName) );

      if( w-> checkState() == Wt::CheckState::Checked )
        value = true;
      else
        value = false;
    };

    _getChecked( "columnResizeEnabled",  m_def.columnResizeEnabled  );
    _getChecked( "alternatingRowColors", m_def.alternatingRowColors );
    _getChecked( "showHeader",           m_def.showHeader           );
    _getChecked( "showFooter",           m_def.showFooter           );
    _getChecked( "showPrevNext",         m_def.showPrevNext         );
    _getChecked( "hideSearch",           m_def.hideSearch           );
    _getChecked( "allowFilter",          m_def.allowFilter          );
    _getChecked( "allowAdd",             m_def.allowAdd             );
    _getChecked( "allowChange",          m_def.allowChange          );
    _getChecked( "allowDelete",          m_def.allowDelete          );
    _getChecked( "allowExport",          m_def.allowExport          );
    _getChecked( "allowSearch",          m_def.allowSearch          );
    _getChecked( "allowPrint",           m_def.allowPrint           );
    _getChecked( "allowUnlock",          m_def.allowUnlock          );
    _getChecked( "checkBoxSelect",       m_def.checkBoxSelect       );
/// \todo fix this
//    _getChecked( "additional",           m_def.additional           );

    auto w = static_cast<Wt::WComboBox*>( props-> resolveWidget("selectionMode") );
    switch( w-> currentIndex() )
    {
      case 0: m_def.selectionMode = Wt::SelectionMode::None;     break;
      case 1: m_def.selectionMode = Wt::SelectionMode::Single;   break;
      case 2: m_def.selectionMode = Wt::SelectionMode::Extended; break;
    }

    std::vector<ColumnDef> columnDefs;
    for( auto slColIn : slColsIn-> stringList() )
    {
      auto _defExists = [=]( const Wt::WString & value )
      {
        for( auto colDef : m_def.columnDefs )
          if( colDef.field == value )
            return true;

        return false;
      };


      if( _defExists( slColIn ) )
      {
        for( auto colDef : m_def.columnDefs )
          if( colDef.field == slColIn )
            columnDefs.push_back( colDef );
      }
      else
      {
        ColumnDef colDef;
        colDef.field = slColIn.toUTF8();
        colDef.width = 100;
        columnDefs.push_back( colDef );
      }

    }

    m_def.columnDefs.clear();
    for( auto colDef : columnDefs )
      m_def.columnDefs.push_back( colDef );

    m_changed.emit();

  })); // enddialog.finished()

  dialog-> show();

} // endvoid Wtx::TableViewDef::editProperties()

void Wtx::TableViewDef::ColumnDef::editProperties()
{
  auto dialog = new Wt::WDialog("Column Properties");
  dialog-> rejectWhenEscapePressed(true);

  auto templt = dialog-> contents()-> addNew<Wt::WTemplate>
  (
   Wt::WString
   (
    "<center>"
    " Field Name: ${fieldName}"
    " <table>"
    "  <tr><td> Label:   </td><td> ${label}   </td></tr>"
    "  <tr><td> Width:   </td><td> ${width}   </td></tr>"
    "  <tr><td> Tooltip: </td><td> ${toolTip} </td></tr>"
    " </table>"
    " <table>"
    "  <tr><td> ${ok} </td><td> ${cancel} </td></tr>"
    " </table>"
    "</center>"
   )
  );

  templt-> bindString( "fieldName", field );
  templt-> bindNew<Wt::WPushButton>( "ok", "Ok" )->
    clicked().connect( dialog, &Wt::WDialog::accept );

  templt-> bindNew<Wt::WPushButton>( "cancel", "Cancel" )->
    clicked().connect( dialog, &Wt::WDialog::reject );

  templt-> bindNew<Wt::WLineEdit>( "label",   label   );
  templt-> bindNew<Wt::WLineEdit>( "width",   Wt::WString("{1}").arg( width.value() ) );
  templt-> bindNew<Wt::WLineEdit>( "toolTip", toolTip );

  dialog-> finished().connect( std::bind( [templt,dialog,this]()
  {
    if( dialog-> result() != Wt::DialogCode::Accepted )
      return;

    auto _getString2 = [templt]( const std::string & varName )
    {
      auto w = static_cast<Wt::WLineEdit*>( templt-> resolveWidget(varName) );
      return w-> valueText().toUTF8();
    };

    label   = _getString2( "label" );
    width   = std::stoi( _getString2( "width" ) );
    toolTip = _getString2( "toolTip" );

    delete dialog;
  }));

  dialog-> show();

}


bool Wtx::TableViewDef::hasFlag( const std::string & value )
{
  return std::find( m_def.flags.begin(), m_def.flags.end(), value ) != m_def.flags.end();
}



