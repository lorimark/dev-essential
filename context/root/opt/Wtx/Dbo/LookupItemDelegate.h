
#ifndef __WTX_DBO_LOOKUPITEMDELEGATE_H___
#define __WTX_DBO_LOOKUPITEMDELEGATE_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WText.h>
#include <Wt/Dbo/Transaction.h>
#include <Wt/WString.h>
#include <Wt/WModelIndex.h>
#include <Wt/WAbstractItemModel.h>

namespace Wtx {
  namespace Dbo {

class Session;

/*!
** \brief Lookup Item Delegate
**
** This class can be used in table-views so a lookup-value can
**  show the target lookup.
**
*/
template <class C> class LookupItemDelegate
: public Wt::WItemDelegate
{
  public:

    enum Options
    {
      NoOptions,
      NoCfy
    };

    Options m_options = NoOptions;

    LookupItemDelegate( Options options, Wtx::Dbo::Session * s )
    : m_session(s)
    {
      m_options = options;
    }

    virtual std::unique_ptr<Wt::WWidget> update( Wt::WWidget * widget, const Wt::WModelIndex & index, Wt::WFlags< Wt::ViewItemRenderFlag > flags )
    {
      auto w = Wt::WItemDelegate::update( widget, index, flags );

      Wt::WText * text = static_cast<Wt::WText *>(w.get());

      if( text )
      {
        int id = Wt::asNumber( index.model()-> data( index.row(), index.column() ) );

        if( id > 0 )
        {
          Wt::Dbo::Transaction t(*session());

          std::string filter =
            Wt::WString("SELECT COUNT(1) FROM \"{1}\" WHERE id = {2}")
            .arg( std::string(C::TableDef().tableName()) )
            .arg( id )
            .toUTF8()
            ;

          int totalRows =
            session()->
            template query<int>( filter );

          if( totalRows > 0 )
          {
            auto item = session()-> template load<C>(id);

            auto textValue =
              Wt::WString("{1}").arg( item-> keyField().value() );

            if( m_options != NoCfy )
              if( item-> cfyField().value() != "" )
                textValue +=
                  Wt::WString("~{1}").arg( item-> cfyField().value() );

            text-> setText( textValue );
          }
          else // if( totalRows not > 0 )
          {
            text-> setText( Wt::WString("not found: {1}").arg(id) );
          }

        }
        else // if( id not > 0 )
        {
          text-> setText( "~ ~ ~" );
        }

      } // endif( text )

      return std::move(w);
    }

    static Wt::WItemDelegate * create( Wtx::Dbo::Session * s )
    {
      return new LookupItemDelegate<C>( NoOptions, s );
    }

    static Wt::WItemDelegate * create_nocfy( Wtx::Dbo::Session * s )
    {
      return new LookupItemDelegate<C>( NoCfy, s );
    }

    Wtx::Dbo::Session * session() { return m_session; }

    Wtx::Dbo::Session * m_session;

}; // endtemplate <class C> class LookupItemDelegate

  } // endnamespace Dbo
} //endnamespace Wtx

#endif // #ifndef __WTX_DBO_LOOKUPITEMDELEGATE_H___

