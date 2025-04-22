
#ifndef __WTX_SYS_LOOKUP_TEMPLATE_H___
#define __WTX_SYS_LOOKUP_TEMPLATE_H___

#include <Wtx/Dbo/LookupItemTpl.h>
#include "Definition.h"


namespace Wtx {
  namespace Sys {
    namespace Lookup {

template <class C> class Template
: public Wtx::Dbo::LookupItemTpl<C>
{
    void init()
    {
      m_system.setValue( false );
    }

  public:

    Template( const std::string & key )
    : Wtx::Dbo::LookupItemTpl<C>(key)
    {
      init();
    }

    Template( const std::string & key, const std::string & cfy )
    : Wtx::Dbo::LookupItemTpl<C>(key,cfy)
    {
      init();
    }

    Template( const Template<C> & other )
    : Wtx::Dbo::LookupItemTpl<C>( other.keyField().value() )
    {
    }

    static Definition & TableDef()
    {
      return C::TableDef();
    }


    static void MapClass( Wt::Dbo::Session & session )
    {
      Wtx::Dbo::LookupItemTpl<C>::MapClass( session );
      Wt::registerType<Template<C>>();
      Wt::registerType< Wt::Dbo::ptr<Template<C>> > ();
    }

          Wtx::Dbo::Field< std::string > & sort       ()       { return m_sort       ; }
          Wtx::Dbo::Field< bool        > & system     ()       { return m_system     ; }

    const Wtx::Dbo::Field< std::string > & sort       () const { return m_sort       ; }
    const Wtx::Dbo::Field< bool        > & system     () const { return m_system     ; }

    template<class Action> void persist( Action &a )
    {
      Wtx::Dbo::LookupItemTpl<C>::persist( a );

      m_sort       .persist( a, &TableDef().SortFieldDef        );
      m_system     .persist( a, &TableDef().SystemFieldDef      );

    }

  private:

    Wtx::Dbo::Field< std::string > m_sort       ;
    Wtx::Dbo::Field< bool        > m_system     ;

}; // endtemplate <class C> class Template

    } // endnamespace Lookup
  } // endnamespace Sys
} // endnamespace Wtx


#endif // __WTX_SYS_LOOKUP_TEMPLATE_H___


