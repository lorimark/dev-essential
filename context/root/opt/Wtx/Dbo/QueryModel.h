
#ifndef __WTX_QUERYMODEL_H___
#define __WTX_QUERYMODEL_H___

#include <Wt/Dbo/QueryModel.h>

#include <Wtx/TableViewDef.h>

namespace Wtx {
  namespace Dbo {

template <class C>
class QueryModel
: public Wt::Dbo::QueryModel<C>
{
  typedef Wt::Dbo::QueryModel<C> Base;

  public:

    virtual int rowCount( const Wt::WModelIndex & parent = Wt::WModelIndex() ) const
    {
      if( m_countTable != "" && session() )
      {
        if( m_cachedRowCount == -1 )
        {
          /*
          ** the following is the normal way to quickly count
          **  rows in a table.  It supports the addition of
          **  a where clause that can affect the row count.
          **
          */
#ifndef DO_TRADITIONAL_COUNT
          auto query =
            Wt::WString( "SELECT COUNT(1) FROM \"{1}\" " )
            .arg( m_countTable )
            .toUTF8()
            ;
#else
          /*
          ** the following is not a normal way to quickly count
          **  rows in a table.  While it can count the raw row
          **  count, it does not support filters on the data
          **  and it is also subject to count accuracy deterioration
          **  if vacuum is not run periodically on the system.
          **
          **  https://wiki.postgresql.org/wiki/Count_estimate
          **
          */
          auto query =
            Wt::WString( "SELECT reltuples::BIGINT FROM pg_class WHERE relname = '{1}'" )
            .arg( m_countTable )
            .toUTF8()
            ;
#endif

          if( m_countWhere != "" )
          {
            query += m_countWhere;
          }

          Wt::Dbo::Transaction t(*session());
          m_cachedRowCount = session()-> template query<int>(query);

        } // endif( m_cachedRowCount == -1 )

        return m_cachedRowCount;

      } // endif( m_countTable != "" && session() )

      return Wt::Dbo::QueryModel<C>::rowCount( parent );

    } // endvirtual int rowCount( const Wt::WModelIndex & parent = Wt::WModelIndex() ) const

    Wt::Dbo::Session * session() const
    {
      return m_session;
    }

    void setSession( Wt::Dbo::Session * value )
    {
      m_session = value;
    }

    void setCountTable( const std::string & table )
    {
      m_countTable = table;
    }

    void setCountWhere( const std::string & where )
    {
      m_countWhere = where;
      m_cachedRowCount = -1;
    }

    void setViewDef( Wtx::TableViewDef * viewDef )
    {
      m_viewDef = viewDef;
    }

    virtual Wt::WFlags<Wt::ItemFlag> flags( const Wt::WModelIndex & index ) const
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      auto result = Base::flags(index);

      if( index.column() == 0 )
        result |= Wt::ItemFlag::UserCheckable;

//      result |= Wt::ItemFlag::Editable;

      return result;
    }

    virtual Wt::cpp17::any data( const Wt::WModelIndex& index, Wt::ItemDataRole role ) const
    {

      if( m_viewDef )
      {
        if( m_viewDef-> m_def.checkBoxSelect )
        {
          if( index.column() == 0 && role == Wt::ItemDataRole::Checked )
          {
//          if( editSelection_-> find( this->resultRow(index.row()) ) != editSelection_->end() )

//            return true;
//          else
            return false;
          }
        }
      }

      return Base::data( index, role );
    }

    void refreshModelData()
    {
//      Base::reset();
      Base::reload();
    }

    Wtx::TableViewDef * m_viewDef = nullptr;
    Wt::Dbo::Session * m_session = nullptr;
    std::string m_countTable;
    std::string m_countWhere;
    mutable int m_cachedRowCount = -1;

}; // endclass QueryModel

  } // endnamespace Dbo
} // endnamespace Wtx

#endif // __WTX_QUERYMODEL_H___


