
add_subdirectory( Activity )
add_subdirectory( Company )
add_subdirectory( Group )
add_subdirectory( Person )
add_subdirectory( PrivateInfo )

set( WTX_FILES ${WTX_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Crm.cpp
  PARENT_SCOPE
)


