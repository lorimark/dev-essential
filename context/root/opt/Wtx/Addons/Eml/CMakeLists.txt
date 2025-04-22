
add_subdirectory( Composer )
add_subdirectory( Service )

set( WTX_FILES ${WTX_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Eml.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ManagerWidget.cpp
  PARENT_SCOPE
)

include_directories(
  /opt/vmime/include
  )

link_directories(/opt/vmime/lib)



