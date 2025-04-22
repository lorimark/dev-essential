
#ifndef __WTX_SYS_LOOKUP_ITEM_H___
#define __WTX_SYS_LOOKUP_ITEM_H___

#include "Template.h"

namespace Wtx {
  namespace Sys {
    namespace Lookup {

class Item
: public Template<Item>
{
  public:

    Item( const std::string & key = "", const std::string & cfy = "" )
    : Template( key, cfy )
    {
    }

    Item( const Item & other )
    : Template( other.keyField().value() )
    {
    }

    template<class Action> void persist(Action &a)
    {
      Template<Item>::persist( a );
    }

    static void MapClass( Wt::Dbo::Session & session )
    {
      Template<Item>::MapClass( session );
      Wt::registerType<Item>();
      Wt::registerType< Wt::Dbo::ptr<Item> >();
    }

    static Definition & TableDef() { return s_tableDef; }

  private:

    static Definition & s_tableDef;

};

    } // endnamespace Lookup
  } // endnamespace Sys
} // endnamespace Wtx

DBO_EXTERN_TEMPLATES(Wtx::Sys::Lookup::Item);

#endif // __WTX_SYS_LOOKUP_ITEM_H___


