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


#ifndef __WTX_DBO_FORMMODEL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_DBO_FORMMODEL_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <Wt/Dbo/Query.h>
#include <Wt/WAny.h>

#include <Wtx/Core/Core.h>

#include "FieldDefBase.h"
#include "Session.h"
#include "../FormModel.h"

namespace Wtx {
  namespace Dbo {

template <class C> class FormModel
: public Wtx::FormModel
{
  public:

    enum State
    {
      /*!
      ** state is unknown - data has not been read
      **  in from the database yet.
      **
      */
      Unknown = -1,

      /*!
      ** model is clean - this is true after a read or
      **  immediately after a write to the database.
      **
      */
      Clean = 0,

      /*!
      ** field data has been changed, but the model has
      **  not been pushed back out to the back-end db.
      **
      */
      Dirty = 1,

      /*!
      ** we tried to write the data out to the back-end
      **  db but the version on the back-end db is out
      **  of sync with our in-memory copy.  Data will not
      **  be written.
      **
      */
      Collision = 2

    }; // endenum State

    virtual ~FormModel();

    /*!
    ** \brief Return a loaded item
    **
    ** This is used in a constructor to return an item pointer
    **  based on the ID number provided.  In order for this task
    **  to be completed, a Wt::Transaction must exist.  So it is
    **  all done here, so that the result can be used in a 
    **  constructor.
    **
    */
    Wt::Dbo::ptr<C> load( int id, Wt::Dbo::Session * s );

    /*!
    ** \brief ctor
    **
    ** Initialize this model based solely on the item ID
    **
    */
    FormModel( int id, Wt::Dbo::Session * s );

    /*!
    ** \brief ctor
    **
    ** Initialize this model based on an item reference
    **
    */
    FormModel( const Wt::Dbo::ptr<C> & itm );

    /*!
    ** \brief Table Name
    **
    **
    */
    virtual std::string tableName() const;

    /*!
    ** \brief Item ID
    **
    **
    */
    virtual int itemId() const;

    /*!
    ** \brief Referenced Item
    **
    ** This returns a const reference to item.
    **
    */
    const Wt::Dbo::ptr<C> & item() const;

    /*!
    ** \brief Referenced Item
    **
    ** This returns a non-const reference to item.
    **
    */
    Wt::Dbo::ptr<C> & item();

    /*!
    ** \brief Session Reference
    **
    ** This returns a pointer to the current session.
    **
    */
    Wt::Dbo::Session * session() const;

    /*!
    ** \brief Delete Item from DB
    **
    ** This will remove the item from the back-end DB and purge
    **  it from memory as well.
    **
    */
    virtual bool remove();

    /*!
    ** \brief Read Item
    **
    ** This will read the item in from the back-end DB.
    **
    */
    virtual int read();

    /*!
    ** \brief Refresh Item
    **
    ** This will refresh the item from the back-end DB.
    **
    */
    virtual void refresh();

    virtual std::unique_ptr<Wt::WWidget> createEditWidget( Wt::WFormModel::Field f ) const;

    virtual void staleRefresh();

    /*!
    ** \brief Check Memory against Disk
    **
    ** This will return true if the item in back-end storage
    **  is out of sync with the memory item.  This is based on
    **  the assumption that at least the item we are referencing
    **  actually has an ID assigned.  For those items that have
    **  no ID assigned yet, this function simply returns 'false'
    **  that the item we are referencing is not stale ~ it has
    **  no storage yet, how can it be stale?
    **
    */
    virtual bool isStale() const;

    /*!
    ** \brief Report disk version
    **
    ** This function will check the version of the item on the
    **  back-end storage and return the version number of it
    **  there.  This is used to check if the item is stale
    **  before any attempt is made to write the item back
    **  to disk ~ a task that will surely fail.
    **
    */
    virtual int diskVersion() const;

    virtual int itemVersion() const;

    /*!
    ** \brief Return Field Element
    **
    ** This returns the field element based on a string-representation
    **  of that same field name.
    **
    */
    const Field field( const std::string & fieldName ) const;

    virtual const Wt::cpp17::any & value( const std::string & fieldName ) const;

    virtual const Wt::cpp17::any & value( const Wtx::Dbo::FieldDefBase & fieldDef ) const;

    virtual const Wt::cpp17::any & value( const Wt::WFormModel::Field field ) const;

    virtual int accept();

    virtual void reset();

    virtual bool validate();

    virtual bool isVisible( Wt::WFormModel::Field field ) const;

    virtual bool isReadOnly( Wt::WFormModel::Field field ) const;

    virtual Wt::WString label( Wt::WFormModel::Field field ) const;

    virtual void setValue( Wt::WFormModel::Field field, const Wt::cpp17::any &value );

    virtual Wt::WString valueText( Wt::WFormModel::Field field ) const;

    virtual void setValidator( Wt::WFormModel::Field field, const std::shared_ptr< Wt::WValidator > &validator );

    virtual std::shared_ptr< Wt::WValidator > validator( Wt::WFormModel::Field field ) const;

    virtual bool validateField( Wt::WFormModel::Field field );

    virtual void setValidated( Wt::WFormModel::Field field, bool validated );

    virtual bool isValidated( Wt::WFormModel::Field field ) const;

    virtual void setValidation( Wt::WFormModel::Field field, const Wt::WValidator::Result &result );

    template <typename T> void act( Wt::Dbo::FieldRef<T> ref );

    template <typename T> void actPtr( const Wt::Dbo::PtrRef<T> & ref );

    template <typename T> void actWeakPtr( const Wt::Dbo::WeakPtrRef<T> & ref );

    template <typename T> void actCollection( const Wt::Dbo::CollectionRef<T> & ret );

  protected:

    Wt::Dbo::ptr<C> m_item;

  private:

    bool m_isReadMode = true;

}; // endclass FormModel

#include "FormModel_imp.h"

  } // endnamespace Dbo
} // endnamespace Wtx

#endif

