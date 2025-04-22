
add_subdirectory( Crm )

if( WTX_USING_EML )
  message( "WTX_USING_EML" )
  add_subdirectory( Eml )
endif( WTX_USING_EML )

add_subdirectory( Web )

set( WTX_FILES ${WTX_FILES}
  PARENT_SCOPE
)

