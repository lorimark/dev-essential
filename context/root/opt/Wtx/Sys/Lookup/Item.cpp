
#include "Item.h"

Wtx::Sys::Lookup::Definition::Definition()
: Wtx::Dbo::LookupTableDef ( "sysLookup"         ),
  SortFieldDef             ( *this, "sort"       ),
  SystemFieldDef           ( *this, "system"     )
{
  KeyFieldDef.setIsUnique();
}

Wtx::Sys::Lookup::Definition g_sysLookupDef;

DBO_INSTANTIATE_TEMPLATES(Wtx::Sys::Lookup::Item);

Wtx::Sys::Lookup::Definition & Wtx::Sys::Lookup::Item::s_tableDef = g_sysLookupDef;


