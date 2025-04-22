
#include <Wt/WContainerWidget.h>
#include <Wt/WAbstractItemModel.h>
#include <Wt/Dbo/Transaction.h>

#include <Wtx/Dbo/Session.h>

#include "Item.h"
#include "ItemDelegate.h"

Wtx::Sys::User::ItemDelegate::ItemDelegate( const std::string & field, Wtx::Dbo::Session * s )
: m_field( field ),
  m_session(s)
{
}

std::unique_ptr<Wt::WWidget> Wtx::Sys::User::ItemDelegate::update( Wt::WWidget * widget, const Wt::WModelIndex & index, Wt::WFlags< Wt::ViewItemRenderFlag > flags )
{
  auto w = Wt::WItemDelegate::update( widget, index, flags );

  auto _getValue = [=]()
  {
    int id = Wt::asNumber( index.model()-> data( index.row(), index.column() ) );

    if( id > 0 )
    {
      Wt::Dbo::Transaction t(*session());

      auto item =
        session()-> load<Wtx::Sys::User::Item>(id );

      std::string fieldValue;

      if( m_field == "keyField" )
      {
        fieldValue = item-> keyField().value();
      }

      if( m_field == "abbreviation" )
      {
        fieldValue = item-> abbreviation().value();
      }

      if( fieldValue == "" )
          fieldValue = Wt::WString("[sysUser: {1}]").arg( item.id() ).toUTF8();

      return fieldValue;

    }

    return std::string("~ ~ ~");

  };

  auto text = dynamic_cast<Wt::WText *>(w.get());
  if( text )
  {
    text-> setText( _getValue() );

  } // endif( text )

  return std::move(w);

} // endstd::unique_ptr<Wt::WWidget> Wtx::Sys::Lookup::Delegate::update( Wt::WWidget * widget, const Wt::WModelIndex & index, Wt::WFlags< Wt::ViewItemRenderFlag > flags )

Wtx::Dbo::Session * Wtx::Sys::User::ItemDelegate::session()
{
  return m_session;
}

Wt::WItemDelegate * Wtx::Sys::User::ItemDelegate::create( Wtx::Dbo::Session * s )
{
  return new Wtx::Sys::User::ItemDelegate("keyField",s);
}

Wt::WItemDelegate * Wtx::Sys::User::ItemDelegate::createAbbreviation( Wtx::Dbo::Session * s )
{
  return new Wtx::Sys::User::ItemDelegate("abbreviation",s);
}


