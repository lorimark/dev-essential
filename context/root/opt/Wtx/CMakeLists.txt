
if( WTX_USING_ADDONS )
  add_subdirectory( Addons )
endif( WTX_USING_ADDONS )

add_subdirectory( Core )
add_subdirectory( Dbo  )
add_subdirectory( Lib  )
add_subdirectory( Mail )
add_subdirectory( Sys  )
add_subdirectory( Util )
add_subdirectory( Web  )

set( WTX_FILES ${WTX_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/Wtx.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FormModel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MessageBox.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PopupMessage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PopupQuestion.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PopupYesNo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TableView.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TableViewDef.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Template.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TemplateFormView.cpp
  PARENT_SCOPE
  )

