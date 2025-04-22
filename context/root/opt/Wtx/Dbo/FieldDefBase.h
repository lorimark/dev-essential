/**************************************************************************
###########################################################################
##
## $SHOWOFFDB_BEGIN_LICENSE$
## Copyright (C) 2011 Lorimark Solutions, LLC and/or its subsidiary(-ies).
##  All rights reserved.
##  Contact: Lorimark Solutions, LLC (info@showoff-db.org)
##
## This file is part of the Showoff Database Application Framework.
##
##  Commercial Usage
##  Licensees holding valid ShowoffDB Commercial licenses may use this file in
##   accordance with the ShowoffDB Commercial License Agreement provided with the
##   Software or, alternatively, in accordance with the terms contained in
##   a written agreement between you and Lorimark Solutions, LLC.
##
## GNU Lesser General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU Lesser
##   General Public License version 2.1 as published by the Free Software
##   Foundation and appearing in the file LICENSE.LGPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU Lesser General Public License version 2.1 requirements
##   will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Lorimark Solutions, LLC gives
##  you certain additional rights.  These rights are described in the
##  Lorimark Solutions, LLC ShowoffDB LGPL Exception version 1.0, included in
##  the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
##  Alternatively, this file may be used under the terms of the GNU
##   General Public License version 3.0 as published by the Free Software
##   Foundation and appearing in the file LICENSE.GPL included in the
##   packaging of this file.  Please review the following information to
##   ensure the GNU General Public License version 3.0 requirements will be
##   met: http://www.gnu.org/copyleft/gpl.html.
##
## If you have questions regarding the use of this file, please contact
##   Lorimark Solutions, LLC at info@showoff-db.org.
## $SHOWOFFDB_END_LICENSE$
##
#############################################################################
****************************************************************************/


#ifndef __WTX_DBO_FIELDDEFBASE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_FIELDDEFBASE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <memory>
#include <string>

#include <Wt/WObject.h>
#include <Wt/WFlags.h>
#include <Wt/WLineEdit.h>
#include "Session.h"

namespace Wt {
  class WWidget;
  class WItemDelegate;
}

namespace Wtx {
  namespace Dbo {

class TableDef;

/*!
** \brief Base Class
**
** This is a back-end database field definition, and a front-end UI field-editor
**  definition.
**
** A field definition object provides definition services such as placeholder
**  text, tool-tips, help-context and various other things useful for a GUI
**  type application.  It also defines the 'column name' or 'field name' for
**  the back-end database, as well as any associated indexes or restraints.
**  The FieldDef object can be thought of as a 'glue' object for the back-to-fronti
**  database design, or part of the 'C' in the 'MVC' programming paradigm.
**  .
** The field definition object requires, at the very least, a reference back to the
**  owning table definition object, and a 'char' pointer to the field-name value.
**  Both of these parameters are required, and cannot be modified after construction,
**  since they represent a constant (non-changing) reference to the table and to the
**  column name within that table.  During construction the field definition object
**  will automatically insert itself in to the table definition 'field list' set.
**
*/
class FieldDefBase
: Wt::WObject
{
  public:

    /*!
    ** \brief Field Definition Flags
    **
    ** These flags can be 'or' together
    **
    ** \todo this should have some other c++ type of construct
    **
    */
    enum Flags
    {
      /// 0x0000 ~ no flags
      None     = 0x0000,

      /// 0x0001 ~ the field is required
      Required = 0x0001,

      /// 0x0002 ~ the field is read-only
      ReadOnly = 0x0002,

      /// 0x0004 ~ the field displays with password masking
      Password = 0x0004,

      /// 0x0008 ~ the field is display-only
      ShowOnly = 0x0008,

      /// 0x0010 ~ the field will not call upon createWidget
      NoUi     = 0x0010,

      /// 0x0020 ~ the field carries a unique constraint
      Unique   = 0x0020,

      /// 0x0040 ~ searchable from table views
      Search   = 0x0040
    };

    /*!
    ** \brief ctor field definition object
    **
    */
    FieldDefBase
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      int          w   = -1,          /// width
      int          h   = -1,          /// height
      Flags        f   = Flags::None, /// flags
      std::string  lb  = "",          /// label
      std::string  ph  = "",          /// placeholder text
      std::string  inf = "",          /// info
      std::string  tt  = "",          /// tooltipText
      int          ht  = -1           /// help topic
    );

    /*!
    ** \brief ctor field definition object
    **
    */
    FieldDefBase
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      std::string  lb  = "",          /// label
      std::string  ph  = "",          /// placeholder text
      std::string  inf = "",          /// info
      std::string  tt  = "",          /// tooltipText
      int          ht  = -1           /// help topic
    );

#ifdef NEVER
    /*!
    ** \brief ctor field definition object
    **
    */
    FieldDef
    (
      TableDef &   td,                /// owning table definition (ro required)
      const char * fn,                /// field name (ro required)
      Flags        f   = Flags::None /// flags
//      int          w   = -1,          /// width
//      int          h   = -1,          /// height
//      std::string  lb  = "",          /// label
//      std::string  ph  = "",          /// placeholder text
//      std::string  inf = "",          /// info
//      std::string  tt  = "",          /// tooltipText
//      int          ht  = -1           /// help topic
    );
#endif

    virtual ~FieldDefBase() {}

    virtual Wtx::Dbo::TableDef & tableDef() const;

    virtual const char * fieldName() const;

    /*
    ** this alias name is useful for when implementing new database
    **  systems, when importing data from some other system, it is
    **  sometimes useful to encode the foreign column name here so
    **  that import/export can be more seamless.
    **
    */
    virtual const std::string & aliasName() const;

    virtual int width() const;
    virtual void setWidth( int value );

    virtual int height() const;
    virtual void setHeight( int value );

    virtual bool isVisible() const;
    virtual void setIsVisible( bool value=true );

    virtual bool isReadOnly() const;
    virtual void setIsReadOnly( bool value=true );

    virtual bool isUnique() const;
    virtual void setIsUnique( bool value=true );

    virtual const std::string & label() const;
    virtual void setLabel( const std::string & value );

    virtual const std::string & placeholderText() const;
    virtual void setPlaceholderText( const std::string & value );

    virtual const std::string & info() const;
    virtual void setInfo( const std::string & value );

    virtual const std::string & toolTip() const;
    virtual void setToolTip( const std::string & value );

    virtual int helpTopic() const;
    virtual void setHelpTopic( int value );

    virtual const Flags & flags() const;
    virtual void setFlags( const Flags value );

    virtual const std::string & defaultValue() const;
    virtual void setDefaultValue( const std::string & value );

    virtual bool forceUppercase() const;
    virtual void setForceUppercase( bool value = true );

    virtual const std::string & inputMask() const;
    virtual void setInputMask( const std::string & mask = "", Wt::WFlags< Wt::InputMaskFlag > flags = Wt::None  );

    virtual std::unique_ptr<Wt::WItemDelegate> createItemDelegate( int sid, Wtx::Dbo::Session & session ) const;
    virtual std::unique_ptr<Wt::WWidget> createLabelWidget( int sid, Wtx::Dbo::Session & session ) const;
    virtual std::unique_ptr<Wt::WWidget> createEditWidget( int sid, Wtx::Dbo::Session & session ) const;
    virtual std::unique_ptr<Wt::WWidget> createDisplayWidget( int sid, Wtx::Dbo::Session & session ) const;

    virtual std::string toJson() const;
    virtual void fromJson( const std::string & valud );

  private:

    void init();

    TableDef & m_tableDef;
    const char * m_fieldName;
    std::string m_aliasName;

    int m_width = -1;
    int m_height = -1;
    bool m_isReadOnly = false;
    bool m_isVisible = true;
    bool m_isUnique = false;
    bool m_forceUppercase = false;
    Flags m_flags = None;
    std::string m_label;
    std::string m_placeholderText;
    std::string m_info;
    std::string m_toolTip;
    std::string m_defaultValue;
    std::string m_inputMask;
    Wt::WFlags< Wt::InputMaskFlag > m_inputMaskFlags;
    int m_helpTopic = 0;


}; // endclass Wtx::Dbo::FieldDef

  } // endnamespace Dbo
} // endnamespace Wtx

#endif // #ifndef __WTX_DBO_FIELDDEF_H___

