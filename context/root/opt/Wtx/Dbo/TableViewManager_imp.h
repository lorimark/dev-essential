
#include <Wt/WDialog.h>
#include <Wt/WApplication.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WMessageBox.h>

#include <Wtx/Core/Core.h>
#include <Wtx/Util/Util.h>
#include <Wtx/PopupMessage.h>

template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::TableViewManager( Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{
  initHead();

//  auto tv = std::make_unique<Wtx::Dbo::TableView<C>>( s );
//  m_tableView = tv.get();

//  m_lw-> addWidget( std::move(tv) );
//
  initFoot();

}

template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::TableViewManager( const std::string & viewDefName, Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{
  auto tv = std::make_unique<Wtx::Dbo::TableView<C>>( viewDefName, s );
  m_tableView = tv.get();
  m_tableView-> setObjectName( "iv" + m_tableView-> viewDef().m_def.title );

  initHead();

  m_lw-> addWidget( std::move(tv),1 );

//  if( !tableView()-> viewDef().m_def.hideSearch )
    m_tableView-> keyPressed().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_keyPressed );

  initFoot();

}

template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::TableViewManager( const Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{
  auto tv = std::make_unique< Wtx::Dbo::TableView<C> >( viewDef, s );
  m_tableView = tv.get();
  m_tableView-> setObjectName( "iv" + m_tableView-> viewDef().m_def.title );

  initHead();

  m_lw-> addWidget( std::move(tv), 1 );

  m_tableView-> clicked().connect( this, &TableViewManager<C,D>::on_clicked );
  m_tableView-> doubleClicked().connect( this, &TableViewManager<C,D>::on_doubleClicked );

//  if( !tableView()-> viewDef().m_def.hideSearch )
    m_tableView-> keyPressed().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_keyPressed );

  initFoot();

}

template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::TableViewManager( const std::string & viewDefName, const Wtx::TableViewDef::ViewDef & viewDef, Wtx::Dbo::Session * s )
: Wt::WContainerWidget(),
  m_session(s)
{
  auto tv = std::make_unique<Wtx::Dbo::TableView<C>>( viewDefName, viewDef, s );
  m_tableView = tv.get();
  m_tableView-> setObjectName( "iv" + m_tableView-> viewDef().m_def.title );

  initHead();

  lw()-> addWidget( std::move(tv), 1 );

//  if( !tableView()-> viewDef().m_def.hideSearch )
  {
    m_tableView-> keyPressed  ().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_keyPressed  );
    m_tableView-> keyWentDown ().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_keyWentDown );
  }

  initFoot();

}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::initHead()
{
  auto u_lw = std::make_unique<Wt::WVBoxLayout>();
  m_lw = u_lw.get();
  setLayout( std::move(u_lw) );

//  lw()-> setContentsMargins( 0,23,0,23 );
  lw()-> setContentsMargins( 0,0,0,0 );

  {
    auto u_cw = std::make_unique<Wt::WContainerWidget>();
    m_toolBar = u_cw.get();
    lw()-> addWidget( std::move(u_cw) );
  }

  {
    auto u_cw = std::make_unique<Wt::WContainerWidget>();
    m_buttonBar = u_cw.get();

    if( tableView() )
    {
      if( tableView()-> viewDef().m_def.allowAdd )
      {
        m_pbAdd = u_cw-> addNew<Wt::WPushButton>( Wt::WString::tr("Wtx.add") );
        m_pbAdd-> addStyleClass("btn-success btn-xs");
        m_pbAdd-> setMargin( "10px", Wt::Side::Right );
        m_pbAdd-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_add_clicked );
        m_pbAdd-> setObjectName( "tvAdd-" + tableView()-> viewDef().m_def.title );
      }

      if( tableView()-> viewDef().m_def.allowChange )
      {
        m_pbEdit = u_cw-> addNew<Wt::WPushButton>( Wt::WString::tr("Wtx.edit") );
        m_pbEdit-> addStyleClass("btn-success btn-xs");
        m_pbEdit-> setMargin( "10px", Wt::Side::Right );
        m_pbEdit-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_edit_clicked );
        m_pbEdit-> setObjectName( "tvEdit-" + tableView()-> viewDef().m_def.title );
      }

      if( tableView()-> viewDef().m_def.allowDelete )
      {
        m_pbDelete = u_cw-> addNew<Wt::WPushButton>( Wt::WString::tr("Wtx.delete") );
        m_pbDelete-> addStyleClass("btn-success btn-xs");
        m_pbDelete-> setMargin( "10px", Wt::Side::Right );
        m_pbDelete-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::do_on_delete_clicked );
        m_pbDelete-> setObjectName( "tvDelete-" + tableView()-> viewDef().m_def.title );
      }

      if( tableView()-> viewDef().m_def.allowExport )
      {
        m_pbExport = u_cw-> addNew<Wt::WPushButton>( Wt::WString::tr("Wtx.export") );
        m_pbExport-> addStyleClass("btn-success btn-xs");
        m_pbExport-> setMargin( "10px", Wt::Side::Right );
        m_pbExport-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_export_clicked );
        m_pbExport-> setObjectName( "tvExport-" + tableView()-> viewDef().m_def.title );
      }

      if( tableView()-> viewDef().m_def.allowPrint )
      {
        m_pbPrint = u_cw-> addNew<Wt::WPushButton>( Wt::WString::tr("Wtx.print") );
        m_pbPrint-> addStyleClass("btn-success btn-xs");
        m_pbPrint-> setMargin( "10px", Wt::Side::Right );
        m_pbPrint-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_print_clicked );
        m_pbPrint-> setObjectName( "tvPrint-" + tableView()-> viewDef().m_def.title );
      }

      if( tableView()-> viewDef().m_def.additional != "" )
      {
        for( auto add : Wtx::Core::split( tableView()-> viewDef().m_def.additional, ',' ) )
        {
          auto pb = u_cw-> addNew<Wt::WPushButton>( add );
          pb-> addStyleClass("btn-success btn-xs");
          pb-> setMargin( "10px", Wt::Side::Right );
          pb-> setObjectName( "tvAdditional-" + add );
//          pb-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_additional_clicked );
          pb-> clicked().connect( [=]()
          {
             m_additionalClicked.emit( pb-> text().toUTF8() );
          });
        }
      }

    }

    lw()-> addWidget( std::move(u_cw) );

  }

#ifdef NEVER
  {
    auto u_cw = std::make_unique<Wt::WContainerWidget>();
    u_cw-> addNew<Wt::WPushButton>("filter");
//    u_cw-> clicked().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_filter_clicked );
    lw()-> addWidget( std::move(u_cw) );
  }
#endif

}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::setReadOnly( bool value )
{
  m_readOnly = value;

  if( m_pbAdd )
      m_pbAdd-> setEnabled( !value );

  if( m_pbEdit )
      m_pbEdit-> setEnabled( !value );

  if( m_pbDelete )
      m_pbDelete-> setEnabled( !value );

  if( m_pbExport )
      m_pbExport-> setEnabled( !value );

  if( m_pbPrint )
      m_pbPrint-> setEnabled( !value );

}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::setDialogSize( Wt::WLength width, Wt::WLength height )
{
  m_dialogWidth  = width;
  m_dialogHeight = height;
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::initFoot()
{

//  if( tableView()-> viewDef().m_def.allowSearch )
  {
    auto u_searchWidget = std::make_unique<SearchWidget>( tableView()-> viewDef().m_def.hideSearch );
    m_searchWidget = u_searchWidget.get();
    m_searchWidget-> setObjectName( "tvSearchWidget-" + Wtx::replace( tableView()-> viewDef().m_def.title, " ", "") );

    if( tableView()-> viewDef().m_def.hideSearch )
      searchWidget()-> setHidden(true);

    searchWidget()-> m_filter-> enterPressed().connect( this, &Wtx::Dbo::TableViewManager<C,D>::on_filterEntered );
    searchWidget()-> m_filter-> blurred().connect(      this, &Wtx::Dbo::TableViewManager<C,D>::on_filterEntered );
    searchWidget()-> m_filter-> textInput().connect(    this, &Wtx::Dbo::TableViewManager<C,D>::on_filterTyped   );
    lw()-> addWidget( std::move(u_searchWidget) );
  }

  if( tableView()-> viewDef().m_def.showFooter )
  {
    auto u_footerWidget = std::make_unique<FooterWidget>();
    m_footerWidget = u_footerWidget.get();
    lw()-> addWidget( std::move(u_footerWidget) );
  }

  if( tableView()-> viewDef().m_def.showPrevNext )
  {
    auto u_prevNextWidget = std::make_unique< PrevNextWidget >();
    m_prevNextWidget = u_prevNextWidget.get();
    lw()-> addWidget( std::move(u_prevNextWidget) );

    auto _move = [=]( int row )
    {
      auto newIndex = tableView()-> model()-> index( row, 0 );

      tableView()-> select( newIndex );
      tableView()-> scrollTo( newIndex );

      m_prevNextWidget-> setRow( row, tableView()-> model()-> rowCount() );

      on_clicked( newIndex, Wt::WMouseEvent() );

    };

    m_prevNextWidget-> m_top->
      clicked().connect( [=]()
      {
        if( tableView()-> selectedIndexes().size() == 0 )
          return;

        _move( 0 );

      });

    m_prevNextWidget-> m_prev->
      clicked().connect( [=]()
      {
        if( tableView()-> selectedIndexes().size() == 0 )
          return;

        auto index = *(tableView()-> selectedIndexes().begin());

        if( index.row() == 0 )
          return;

        _move( index.row()-1 );

      });

    m_prevNextWidget-> m_next->
      clicked().connect( [=]()
      {
        if( tableView()-> selectedIndexes().size() == 0 )
          return;

        auto index = *(tableView()-> selectedIndexes().begin());

        if( index.row() == tableView()-> model()-> rowCount() )
          return;

        _move( index.row()+1 );

      });

    m_prevNextWidget-> m_bottom->
      clicked().connect( [=]()
      {
        if( tableView()-> selectedIndexes().size() == 0 )
          return;

        _move( tableView()-> model()-> rowCount()-1 );

      });


  }

  updateFooter();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_add_clicked()
{
  Wt::Dbo::ptr<C> item;

  {
    Wt::Dbo::Transaction t(*session());
    item = session()-> template addNew<C>("new item");
  }

  {
    Wt::Dbo::Transaction t(*session());
    item.modify()-> keyField().setValue( Wt::WString("new item {1}").arg( item.id() ).toUTF8() );
  }

  tableView()-> refresh();

  m_addClicked.emit( item );

} // endvoid Wtx::Dbo::TableViewManager<C,D>::on_add_clicked()

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_edit_clicked()
{

  if( m_tableView-> model()-> rowCount() == 1 )
  {
    m_editClicked.emit( tableView()-> model()-> stableResultRow( 0 ) );

    auto index = tableView()-> model()-> index( 0, 0 );
    if( m_openDetail )
      openDetail( index );

    return;
  }

  if( m_tableView-> selectedIndexes().size() < 1 )
  {
    auto dialog = addChild( std::make_unique<Wt::WDialog>("alert") );
    dialog-> setClosable(true);
    dialog-> rejectWhenEscapePressed(true);
    dialog-> setResizable(false);
    dialog-> setMinimumSize( m_dialogWidth, m_dialogHeight );
    dialog-> setMaximumSize( m_dialogWidth, m_dialogHeight );
    dialog-> resize( m_dialogWidth, m_dialogHeight );
    dialog-> addStyleClass("detail-form");
    dialog-> contents()-> addNew<Wt::WText>("You must select an item to edit");
    dialog-> show();

    return;
  }

  auto index = *m_tableView-> selectedIndexes().begin();
  m_editClicked.emit( tableView()-> model()-> stableResultRow( index.row() ) );

  if( m_openDetail )
    openDetail( index );

}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_delete_clicked( bool noask )
{

  if( m_tableView-> selectedIndexes().size() < 1 )
  {
    std::string message = tableView()-> viewDef().m_def.deleteMessage;

    if( message == "" )
        message = "You must select an item to delete";

    Wtx::PopupMessage::show( message );
    return;
  }

  auto selectedItem =
    m_tableView-> item( *m_tableView-> selectedIndexes().begin() );

  if( m_deleteClicked.isConnected() )
  {
    m_deleteClicked.emit( selectedItem );
    return;
  }

  if( !noask )
  {
    auto message =
      Wt::WString("Are you sure you want to delete item<br /> '{1}'?")
      .arg( m_tableView-> item( *m_tableView-> selectedIndexes().begin() )-> keyField().value() )
      .toUTF8()
      ;

    if( Wt::WMessageBox::show( "Alert", message, Wt::StandardButton::Yes | Wt::StandardButton::No ) != Wt::StandardButton::Yes )
      return;
  }

  for( auto index : m_tableView-> selectedIndexes() )
  {
    auto item = m_tableView-> item( index );

    Wt::Dbo::Transaction t(*session());
    item.remove();

  } // endfor( auto index : m_tableView-> selectedIndexes() )

  m_tableView-> refresh();

} // endvoid Wtx::Dbo::TableViewManager<C,D>::on_delete_clicked()

template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::SearchWidget::SearchWidget( bool autohide )
: m_autohide(autohide)
{
  auto u_lw = std::make_unique<Wt::WHBoxLayout>();
  m_lw = u_lw.get();
  setLayout( std::move(u_lw) );

  lw()-> addWidget( std::move( std::make_unique<Wt::WText>( "Search:" ) ) );

  auto u_filter = std::make_unique<Wt::WLineEdit>();
  m_filter = u_filter.get();
  lw()-> addWidget( std::move(u_filter), 1 );

//  lw()-> addWidget( std::move( std::make_unique<Wt::WPushButton>("clear") ), 1 );

} // endWtx::Dbo::TableViewManager<C,D>::SearchWidget::SearchWidget()



template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::FooterWidget::FooterWidget()
{
  auto templt = addNew<Wt::WTemplate>
  (
   "<div>"
   "  <div style=\"float:left; width:200px;\">   ${left}    </div>"
   "  <div style=\"margin:0 auto; width:200px;\"> ${center}  </div>"
   "  <div style=\"float:right; width:200px;\">  ${right}   </div>"
   "</div>"
  );

  auto u_rowCounts = std::make_unique<Wt::WText>();
  m_rowCounts = u_rowCounts.get();
  templt-> bindWidget( "left", std::move(u_rowCounts) );

/*
** BUGBUG: the following two do not lay out properly.  they
**  should be all on one line.
**
*/
  auto u_center = std::make_unique<Wt::WText>("");
  m_center = u_center.get();
  templt-> bindWidget( "center", std::move(u_center) );

  auto u_right = std::make_unique<Wt::WText>("");
  m_right = u_right.get();
  templt-> bindWidget( "right", std::move(u_right) );

//  m_rowCounts = templt-> bindNew<Wt::WText>("left");
  updateWidgets();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::FooterWidget::setRowCount( int filtered, int total )
{
  m_queryRowCount = filtered;
  m_totalRowCount = total;
  updateWidgets();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::FooterWidget::setQueryRowCount( int value )
{
  m_queryRowCount = value;
  updateWidgets();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::FooterWidget::setTotalRowCount( int value )
{
  m_totalRowCount = value;
  updateWidgets();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::FooterWidget::updateWidgets()
{
  if( m_totalRowCount > 0 )
  {
    m_rowCounts->
      setText
      (
       Wt::WString("{1} of {2}")
       .arg( m_queryRowCount )
       .arg( m_totalRowCount )
      );
  }
  else
  {
    m_rowCounts->
      setText
      (
       Wt::WString("{1} items")
       .arg( m_queryRowCount )
      );
  }
}





template <class C, class D>
Wtx::Dbo::TableViewManager<C,D>::PrevNextWidget::PrevNextWidget()
{
  auto _addNew = [=]( const char * text )
  {
    auto pb = addNew< Wt::WPushButton >( text );
         pb-> addStyleClass( "btn-success" );
         pb-> addStyleClass( "btn-xs" );

    return pb;
  };

  m_top    = _addNew( "<<" );
  m_prev   = _addNew( "<"  );
  m_text   = addNew< Wt::WText >( " " );
  m_next   = _addNew( ">"  );
  m_bottom = _addNew( ">>" );

}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::PrevNextWidget::setRow( int row, int rowCount )
{
  m_text->
    setText
    (
     Wt::WString( " {1} of {2} " )
     .arg( row      )
     .arg( rowCount )
    );
}











template <class C, class D>
Wt::WContainerWidget * Wtx::Dbo::TableViewManager<C,D>::toolBar()
{
  return m_toolBar;
}

template <class C, class D>
Wt::WContainerWidget * Wtx::Dbo::TableViewManager<C,D>::buttonBar()
{
  return m_buttonBar;
}


template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_keyPressed( Wt::WKeyEvent keyEvent )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << tableView()-> viewDef().m_def.title << std::endl;

  if( !tableView()-> viewDef().m_def.allowSearch )
    return;

  searchWidget()-> setFilter( keyEvent.text() );

  if( keyEvent.text() == "" )
  {
    m_tableView-> setQuery();
    updateFooter();
  }
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_keyWentDown( Wt::WKeyEvent keyEvent )
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << tableView()-> viewDef().m_def.title << std::endl;

}

template <class C, class D>
const std::string & Wtx::Dbo::TableViewManager<C,D>::filter() const
{
  return m_tableView-> filter();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::SearchWidget::setFilter( const Wt::WString & value )
{
  setHidden( false );

  if( !m_autohide );
    m_filter-> setFocus(true);

  m_filter-> setText( /* m_filter-> text() + */ value );

  if( value == "" && m_autohide )
    setHidden( true );
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::SearchWidget::setSearch( const Wt::WString & value )
{
  setFilter( value );
  m_filter-> enterPressed().emit();
//  on_filterEntered();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::SearchWidget::setToolTip( const Wt::WString & value )
{
  m_filter-> setToolTip( value );
}


template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_filterEntered()
{
  if( searchWidget()-> m_filter-> text() == "" && tableView()-> viewDef().m_def.hideSearch )
    searchWidget()-> setHidden(true);

  m_tableView-> setQuery( searchWidget()-> m_filter-> text().toUTF8() );

  if( tableView()-> viewDef().m_def.hideSearch )
    m_tableView-> setFocus(true);
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_filterTyped()
{
  m_tableView-> setQuery( searchWidget()-> m_filter-> text().toUTF8() );
  updateFooter();
}


template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::updateFooter()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " "
//    << searchWidget()-> m_filter-> text() << " "
//    << tableView()-> queryRowCount() << " "
//    << tableView()-> totalRowCount() << " "
//    << std::endl
//    ;

  if( m_footerWidget )
  {
    m_footerWidget-> setRowCount( tableView()-> queryRowCount(), tableView()-> totalRowCount() );
  }

}




template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_clicked( Wt::WModelIndex index, Wt::WMouseEvent event )
{
  if( !index.isValid() )
    return;

  if( m_prevNextWidget )
  {
    m_prevNextWidget-> setRow( index.row(), tableView()-> model()-> rowCount() );
  }

//  tableView()-> select( index );

  Wt::WApplication::instance()-> processEvents();

  m_itemClicked.emit
  (
   tableView()->
     model()->
       stableResultRow( index.row() )
  );

}

template <class C, class D>
bool Wtx::Dbo::TableViewManager<C,D>::doSave( D * detail )
{
  if( !detail-> beforeUpdate() )
    return false;

  detail-> updateModel();

  if( !detail-> afterUpdate() )
    return false;

  if( !detail-> beforeAccept() )
    return false;

  detail-> formModel()-> accept();

  if( !detail-> afterAccept() )
    return false;

  if( detail-> refreshTableOnSave() )
  {
    tableView()-> refresh();
//    tableView()-> refreshSelected();
  }

  m_itemSaved.emit( detail-> formModel()-> item() );

  return true;
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::doClose( D * detail )
{
}

template <class C, class D>
D * Wtx::Dbo::TableViewManager<C,D>::openDetail( Wt::WModelIndex index )
{
  return openDetail( tableView()-> model()-> stableResultRow( index.row() ) );

}

template <class C, class D>
D * Wtx::Dbo::TableViewManager<C,D>::openDetail( typename C::Ptr item )
{
  auto dialog = addChild( std::make_unique<Wt::WDialog>("Edit") );
  dialog-> setClosable(true);
  dialog-> rejectWhenEscapePressed(true);
  dialog-> setResizable(false);
  dialog-> setMinimumSize( m_dialogWidth, m_dialogHeight );
  dialog-> setMaximumSize( m_dialogWidth, m_dialogHeight );
  dialog-> resize( m_dialogWidth, m_dialogHeight );
  dialog-> addStyleClass("detail-form");

  auto u_lw = std::make_unique<Wt::WVBoxLayout>();
  auto lw = u_lw.get();
  dialog-> contents()-> setOverflow( Wt::Overflow::Auto );
  dialog-> contents()-> setLayout( std::move(u_lw) );

#ifdef NO_LAYOUT

  m_buttonTemplt = dynamic_cast<Wt::WTemplate*>(dialog-> contents()-> addNew<Wt::WTemplate>
  (
   "<div>"
   "  ${submit     class=\"btn-success btn-xs\"}"
   "  ${close      class=\"btn-danger  btn-xs\"}"
   "  ${delete     class=\"btn-success btn-xs\"}"
   "  ${print      class=\"btn-success btn-xs\"}"
   "  ${unlock     class=\"btn-success btn-xs\"}"
   "  ${additional}<br />"
   "  ${toolbar}"
   "</div>"
  ));

  auto detail = dialog-> contents()-> addNew<D>( item );

#else

  auto u_buttonTemplt = std::make_unique<Wt::WTemplate>
  (
    "<div>"
    "  ${submit    class=\"btn-success btn-xs\"}"
    "  ${close     class=\"btn-danger  btn-xs\"}"
    "  ${delete    class=\"btn-success btn-xs\"}"
    "  ${print     class=\"btn-success btn-xs\"}"
    "  ${unlock    class=\"btn-success btn-xs\"}"
    "  ${additional}<br />"
    "  ${toolbar}"
    "</div>"
  );
  m_buttonTemplt = u_buttonTemplt.get();
  lw-> addWidget( std::move(u_buttonTemplt) );

  auto u_detail = std::make_unique<D>( item );
  auto detail = u_detail.get();
  lw-> addWidget( std::move(u_detail) );

#endif

  detail-> doSave().connect( [=]()
  {
    doSave( detail );
  });

  detail-> doClose().connect( [=]()
  {
    dialog-> accept();
  });

  detail-> doDeleteItem().connect( [=]( bool noask )
  {
    on_delete_clicked( noask );
    dialog-> accept();
  });

  if( detail-> allowChange()
  ||  tableView()-> viewDef().m_def.allowChange )
  {
    auto button = m_buttonTemplt-> bindNew<Wt::WPushButton>("submit","submit");
    button-> setObjectName( "dlg-submit" );
    button-> clicked()
      .connect( [=]()
      {
        if( doSave( detail ) )
          dialog-> accept();

      });
  }
  else
  {
    m_buttonTemplt-> bindEmpty("submit");
  }


  if( detail-> allowChange()
  ||  tableView()-> viewDef().m_def.allowChange )
  {
    auto button = m_buttonTemplt-> bindNew<Wt::WPushButton>("close","close");
    button-> setObjectName( "dlg-close" );
    button-> clicked()
      .connect( [=]()
      {
        dialog-> reject();
      });
  }
  else
  {
    m_buttonTemplt-> bindEmpty("close");
  }

  if( detail-> allowDelete()
//  ||  tableView()-> viewDef().m_def.allowDelete
    )
  {
    auto button = m_buttonTemplt-> bindNew<Wt::WPushButton>("delete","delete");
    button-> setObjectName( "dlg-delete" );
    button-> clicked()
      .connect( [=]()
      {
        detail-> onDelete();
      });
  }
  else
  {
    m_buttonTemplt-> bindEmpty("delete");
  }

  if( detail-> allowPrint()
  ||  tableView()-> viewDef().m_def.allowPrint )
  {
    auto button = m_buttonTemplt-> bindNew<Wt::WPushButton>("print","print");
    button-> setObjectName( "dlg-print" );
    button-> clicked()
      .connect( [=]()
      {
        detail-> onPrint();
      });
  }
  else
  {
    m_buttonTemplt-> bindEmpty("print");
  }

  if( detail-> allowUnlock()
  ||   tableView()-> viewDef().m_def.allowUnlock )
  {
    auto button = m_buttonTemplt-> bindNew<Wt::WPushButton>("unlock","unlock");
    button-> setObjectName( "dlg-unlock" );
    button-> clicked()
      .connect( [=]()
      {
        detail-> onUnlock();
      });
  }
  else
  {
    m_buttonTemplt-> bindEmpty("unlock");
  }

  m_buttonTemplt-> bindEmpty( "toolbar" );

  auto _doAdditional = [=]( const std::string & additionals )
  {
    auto adds = Wtx::Core::split( additionals, ',' );
    if( adds.size() == 1 )
    {
      auto pb = m_buttonTemplt-> bindNew<Wt::WPushButton>( "additional", adds.at(0) );
      pb-> setObjectName( "dlg-" + adds.at(0) );
      pb-> setMargin( "5px", Wt::Side::Left | Wt::Side::Right );
      pb-> addStyleClass( "btn-success" );
      pb-> addStyleClass( "btn-xs" );
      pb->
        clicked().connect( [=]()
        {
          detail-> onAdditional( adds.at(0) );
        });
      return;
    }

    auto cwAdditional = m_buttonTemplt-> bindNew<Wt::WContainerWidget>("additional");
    cwAdditional-> setMargin( "10px" );
    for( auto a : Wtx::Core::split( additionals, ',' ) )
    {
      auto pb = cwAdditional-> addNew<Wt::WPushButton>(a);
      pb-> setObjectName( "dlg-" + a );
      pb-> setMargin( "5px", Wt::Side::Left | Wt::Side::Right );
      pb-> addStyleClass( "btn-success" );
      pb-> addStyleClass( "btn-xs"      );
      pb-> clicked().connect( [=]()
      {
        detail-> onAdditional( a );
      });
    }

  };


  _doAdditional( detail-> additional() );
//  BUGBUG _doAdditional( tableView()-> viewDef().m_def.additional );

#ifdef NEVER
  if( detail-> additional() != ""
  ||  tableView()-> viewDef().m_def.additional != "" )
  {
    m_buttonTemplt-> bindNew<Wt::WPushButton>( "additional", detail-> additional() )->
      clicked().connect( [=]()
      {
        detail-> onAdditional();
      });
  }
  else
  {
    m_buttonTemplt-> bindEmpty( "additional" );
  }
#endif

  dialog-> setWindowTitle
  (
   Wt::WString("{1}:{2}")
   .arg( item.id() )
   .arg( detail-> templateName() )
  );

  dialog->
    finished().connect( [=]( Wt::DialogCode code )
    {
      removeChild( dialog );
    });

  dialog-> show();

  return detail;

} // endD * Wtx::Dbo::TableViewManager<C,D>::openDetail( typename C::Ptr item )

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_doubleClicked( Wt::WModelIndex index, Wt::WMouseEvent event )
{
  m_doubleClicked.emit( tableView()-> model()-> stableResultRow( index.row() ) );

  if( m_openDetail )
    openDetail( index );
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_export_clicked()
{
  m_exportClicked.emit( tableView()-> queryValue() );
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_print_clicked()
{
  m_printClicked.emit( tableView()-> filter() );
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_additional_clicked()
{
//  m_additionalClicked.emit();
}

template <class C, class D>
void Wtx::Dbo::TableViewManager<C,D>::on_unlock_clicked()
{
  std::cout << __FILE__ << ":" << __LINE__ << " on_unlock" << std::endl;
}


