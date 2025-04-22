
#include <Wt/WContainerWidget.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/Dbo/Transaction.h>

#include <Wtx/Dbo/Session.h>

#include "Item.h"
#include "ItemDelegate.h"

Wtx::Sys::Lookup::ItemDelegate::ItemDelegate( Wtx::Dbo::Session * s )
: m_session(s)
{
}

std::unique_ptr<Wt::WWidget> Wtx::Sys::Lookup::ItemDelegate::update( Wt::WWidget * widget, const Wt::WModelIndex & index, Wt::WFlags< Wt::ViewItemRenderFlag > flags )
{
  auto w = Wt::WItemDelegate::update( widget, index, flags );

  auto _getValue = [=]()
  {
    int id = Wt::asNumber( index.model()-> data( index.row(), index.column() ) );

    if( id > 0 )
    {
      Wt::Dbo::Transaction t(*session());

      std::string filter =
        Wt::WString("SELECT COUNT(1) FROM \"{1}\" WHERE id = {2}")
        .arg( /*std::string(*/ Wtx::Sys::Lookup::Item::TableDef().tableName() /*)*/ )
        .arg( id )
        .toUTF8()
        ;

      int totalRows =
        session()->
        template query<int>( filter );

      if( totalRows > 0 )
      {
        Wt::Dbo::Transaction t(*session());
        auto item = session()-> template load<Wtx::Sys::Lookup::Item>(id);
        return item-> keyField().value();
      }
      else // if( totalRows not > 0 )
      {
        return Wt::WString("not found: {1}").arg(id).toUTF8();
      }

    }
    else // if( id not > 0 )
    {
      return std::string("~ ~ ~");
    }

  };

  auto text = dynamic_cast<Wt::WText *>(w.get());
  if( text )
  {
    text-> setText( _getValue() );

  } // endif( text )

  auto checkBox = dynamic_cast<Wt::WCheckBox *>(w.get());
  if( checkBox )
  {
    checkBox-> setText( _getValue() );

  } // endif( checkBox )

  /*
  ** if the widget has other things on it, such as a check-box or an icon, then
  **  the widget is assembled as a container widget. Inside that container
  **  are the text field, and the check-box and so on.  So we have to
  **  first grab the container, then try to find the child widget
  **
  */
  auto containerWidget = dynamic_cast<Wt::WContainerWidget *>(w.get());
  if( containerWidget )
  {
    auto t = dynamic_cast<Wt::WText*>( containerWidget-> find("t") );

    if( t )
      t-> setText( _getValue() );


    auto cb = dynamic_cast<Wt::WCheckBox*>( containerWidget-> find("c") );
    if( cb )
    {
      cb-> setMargin( 0 );
      cb-> setCheckState( checkState( index ) );
    }


  } // endif( containerWidget )


  return std::move(w);

} // endstd::unique_ptr<Wt::WWidget> Wtx::Sys::Lookup::Delegate::update( Wt::WWidget * widget, const Wt::WModelIndex & index, Wt::WFlags< Wt::ViewItemRenderFlag > flags )

Wt::CheckState Wtx::Sys::Lookup::ItemDelegate::checkState( const Wt::WModelIndex & index )
{
  return Wt::CheckState::Unchecked;
}

Wtx::Dbo::Session * Wtx::Sys::Lookup::ItemDelegate::session()
{
  return m_session;
}

Wt::WItemDelegate * Wtx::Sys::Lookup::ItemDelegate::create( Wtx::Dbo::Session * s )
{
  return new Wtx::Sys::Lookup::ItemDelegate(s);
}


