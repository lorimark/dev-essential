
if( WTX_USING_USERAUTH )
  message( "using AUTH" )
  add_subdirectory( Auth )
endif( WTX_USING_USERAUTH )

message( "doing SYS" )

add_subdirectory( Config )
add_subdirectory( Group )
add_subdirectory( Lookup )
add_subdirectory( Log )
add_subdirectory( Queue )
add_subdirectory( User )

set( WTX_FILES ${WTX_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Sys.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Session.cpp
  PARENT_SCOPE
)

