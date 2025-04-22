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

template <class C>
FormModel<C>::~FormModel()
{
}

template <class C>
Wt::Dbo::ptr<C> FormModel<C>::load( int id, Wt::Dbo::Session * s )
{
  if( id == -1 )
    return Wt::Dbo::ptr<C>();

  Wt::Dbo::Transaction t(*s);
  return s-> load<C>(id);
}

template <class C>
FormModel<C>::FormModel( int id, Wt::Dbo::Session * s )
: Wtx::FormModel( C::TableDef() ),
  m_item( load(id,s) )
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  read();
}

template <class C>
FormModel<C>::FormModel( const Wt::Dbo::ptr<C> & itm )
: Wtx::FormModel( C::TableDef() ),
  m_item(itm)
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  read();
}

template <class C>
std::string FormModel<C>::tableName() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return C::TableDef().tableName();
}

template <class C>
int FormModel<C>::itemId() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return item().id();
}

template <class C>
const Wt::Dbo::ptr<C> & FormModel<C>::item() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return m_item;
}

template <class C>
Wt::Dbo::ptr<C> & FormModel<C>::item()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return m_item;
}

template <class C>
Wt::Dbo::Session * FormModel<C>::session() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return item().session();
}

template <class C>
bool FormModel<C>::remove()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  if( itemId() != -1 )
  {
    Wt::Dbo::Transaction t(*session());
    item().remove();
    item().purge();
    return true;
  }

  return false;
}

template <class C>
int FormModel<C>::read()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif

  m_isReadMode = true;
  Wt::Dbo::Transaction t(*session());
  refresh();
  return itemId();
}

template <class C>
void FormModel<C>::refresh()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif

  if( itemId() == -1 )
    return;

  const_cast<C*>(item().get())-> persist(*this);
  const_cast<C*>(item().get())-> postRead();
}

template <class C>
std::unique_ptr<Wt::WWidget> FormModel<C>::createEditWidget( Wt::WFormModel::Field f ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << f << std::endl;
#endif
  if( item() )
    return item()-> createEditWidget( f );

  return std::make_unique<Wt::WLineEdit>();
}

template <class C>
void FormModel<C>::staleRefresh()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  if( isStale() )
  {
    Wt::Dbo::Transaction t(*session());
    item().reread();
    read();
  }
}

template <class C>
bool FormModel<C>::isStale() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  if( itemId() == -1 )
    return false;

  return diskVersion() != itemVersion();
}

template <class C>
int FormModel<C>::diskVersion() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  if( !session() )
    return -1;

  Wt::Dbo::Transaction t(*session());
  int version = session()->
    template query<int>("SELECT version FROM \"" + tableName() + "\"")
    .where("id=?").bind( item().id() )
    ;

  return version;
}

template <class C>
int FormModel<C>::itemVersion() const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return m_item.version();
}

template <class C>
const Wt::WFormModel::Field FormModel<C>::field( const std::string & fieldName ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
#ifdef NEVER
  std::string c = "if:";
  std::string f = fieldName;
  if( f.substr( 0, c.size() ) == c )
  {
    f = f.substr(c.size());
  }

  for( unsigned int i=0; i< fields().size(); i++ )
    if( fields()[i] == f )
      return fields()[i];
#endif

  auto fieldDef = item()-> TableDef().fieldDef(fieldName);

  if( fieldDef )
    return fieldDef-> fieldName();

#ifdef NEVER
  /*!
  ** If the field has not been properly set up in the fields
  **  array, then this function is not going to be able to find
  **  the field properly.  This is a total failure and represents
  **  a mistake in the definition of the Dbo item object.  It
  **  usually means that the field is defined in the table, but
  **  it has not been added to the fieldDefs[] array object.
  **
  */
  std::cout << __FILE__ << " " << __LINE__ << " "
    << "WARNING (possibly fatal): cannot find: " << tableName() << "::" << fieldName << " in fields array"
    << std::endl
    ;
#endif

  return 0;
}

template <class C>
const Wt::cpp17::any & FormModel<C>::value( const std::string & fieldName ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::value( field(fieldName) );
}

template <class C>
const Wt::cpp17::any & FormModel<C>::value( const Wtx::Dbo::FieldDefBase & fieldDef ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::value( fieldDef.fieldName() );
}

template <class C>
int FormModel<C>::accept()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  /*
  ** before writing to the item, check the version of the item
  **  on disk before attempting to write out our item.  If there
  **  is a discrepancy then we cannot write out the item since it
  **  will cause an exception fault.
  **
  */
  if( isStale() )
  {
    std::cout << __FILE__ << " " << __LINE__ << " "
      << " stale object: "
      << "\"" << tableName() << "\" "
      << "id=" << item().id() << " "
      << "itemVersion=" << itemVersion() << " "
      << "diskVersion=" << diskVersion() << " "
      << std::endl
      ;
    exit(-1);
    return itemId();
  }

  {
    m_isReadMode = false;
    Wt::Dbo::Transaction t(*session());

    if( itemId() == -1 )
      session()-> add( m_item );

    item().modify()-> persist(*this);
    item().modify()-> preWrite();
  }

  staleRefresh();

  return itemId();
}

template <class C>
void FormModel<C>::reset ()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  Wtx::FormModel::reset();
}

template <class C>
bool FormModel<C>::validate ()
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::validate();
}

template <class C>
bool FormModel<C>::isVisible( Wt::WFormModel::Field field ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::isVisible( field );
}

template <class C>
bool FormModel<C>::isReadOnly( Wt::WFormModel::Field field ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::isReadOnly( field );
}

template <class C>
Wt::WString FormModel<C>::label( Wt::WFormModel::Field field ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::label( field );
}

template <class C>
void FormModel<C>::setValue( Wt::WFormModel::Field field, const Wt::cpp17::any &value )
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << field << " " << Wt::asString(value) << std::endl;
#endif
  Wtx::FormModel::setValue( field, value );
}

template <class C>
const Wt::cpp17::any & FormModel<C>::value( Wt::WFormModel::Field field ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << field << std::endl;
#endif
  return Wtx::FormModel::value( field );
}

template <class C>
Wt::WString FormModel<C>::valueText( Wt::WFormModel::Field field ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::valueText( field );
}

template <class C>
void FormModel<C>::setValidator (Wt::WFormModel::Field field, const std::shared_ptr< Wt::WValidator > &validator )
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  Wtx::FormModel::setValidator( field, validator );
}

template <class C>
std::shared_ptr< Wt::WValidator > FormModel<C>::validator( Wt::WFormModel::Field field ) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::validator( field );
}

template <class C>
bool FormModel<C>::validateField( Wt::WFormModel::Field field )
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::validateField( field );
}

template <class C>
void FormModel<C>::setValidated (Wt::WFormModel::Field field, bool validated)
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  Wtx::FormModel::setValidated( field, validated );
}

template <class C>
bool FormModel<C>::isValidated (Wt::WFormModel::Field field) const
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  return Wtx::FormModel::isValidated( field );
}

template <class C>
void FormModel<C>::setValidation( Wt::WFormModel::Field field, const Wt::WValidator::Result &result )
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
  Wtx::FormModel::setValidation( field, result );
}

template <class C>
template <typename T> void FormModel<C>::act( Wt::Dbo::FieldRef<T> ref )
{
#ifdef FM_DEBUG_TRACE
  std::cout << __LINE__ << ":" << __FILE__ << " " << std::endl;
#endif
#ifdef FM_DEBUG_ACTIVITY
  std::cout << __FILE__ << " " << __LINE__ << " "
    << "read="  << (m_isReadMode? std::string("true"):std::string("false")) << " "
    << "id="    << itemId() << " "
    << "name="  << ref.name() << " "
    << "value=" << item()-> keyField().value() << " "
    << field(ref.name()) << " "
//    << ref.value() << " "
    << "'" << Wt::asString( value( field( ref.name() ) ) ) << "' "
    << std::endl
    ;
#endif

  if( m_isReadMode )
  {
    setValue
    (
      field(ref.name()),
      Wt::cpp17::any(ref.value())
    );
  }
  else
  {
    /*
    ** fields that are designated as 'showOnly' are absolutely
    **  NOT written back to the back-end database.  This is different
    **  from fields that are designated as 'readOnly' in which case,
    **  when the fields are shown they fields cannot be edited.
    **  However, fields marked as 'readOnly' can be modified through
    **  the model whereas fields marked as 'showOnly' cannot.
    **
    ** The fundamental principal here is that in some cases, when
    **  showing a field value, the 'field-write-to-db' function
    **  (this function you're looking at now) is writing bad data
    **  to the back-end database.  This became a problem with the
    **  back-end database on field types WDateTime.  Something about
    **  the conversion from a front-end WLineEdit to a back-end
    **  WDateTime was causing total failure of the database, since
    **  after the write, the back-end database contained a date-time
    **  value of '-infinity' and then not even the table-views would
    **  load the data - it would just crash the system.
    **
    ** UPDATE: the issue with writing date fields back to the back-end
    **  database had something to do with the locale conversion of
    **  the WDateTime input field.  The field was not honoring locale
    **  whereas the back-end database was, and so there was a date
    **  local/style formatting conflict causing crap data to be push
    **  to the database.  A bug report was submitted to Wt and they
    **  fixed the library.
    **
    */
#ifndef NEVER
//    if( !isShowOnly( fieldDef( field(ref.name()) ) ) )
    {
      ref.setValue
      (
        Wt::cpp17::any_cast<T>
        (
          Wt::convertAnyToAny
          (
            value
            (
              field
              (
                ref.name()
              )
            ),
            typeid(T)
          )
        )
      );
    }
#else
//    if( !isShowOnly( fieldDef( field(ref.name()) ) ) )
    {
      ref.setValue
      (
        value
        (
          field
          (
            ref.name()
          )
        )
      );
    }
#endif
  }

#ifdef FM_DEBUG_ACTIVITY
  if( std::string(ref.name()) == "dateStart" || std::string(ref.name()) == "keyField" || std::string(ref.name()) == "cfyField" )
      std::cout << __FILE__ << " " << __LINE__ << " "
        << std::string( isReadMode? "read":"write" ) << " "
        << ref.name() << " "
        << "'" << Wt::asString( value( field( ref.name() ) ) ) << "' "
        << "'" << Wt::asString( ref.value() ) << "' "
        << std::endl
        ;

  if( std::string(ref.name()) == "dateStart" )
  {
    Wt::WString s = Wt::asString( value( field( ref.name() ) ) );
    std::cout << __FILE__ << " " << __LINE__ << " "
      << Wt::WLocale::currentLocale().dateFormat().toUTF8() << " "
      << s << " "
      << Wt::WDate::fromString(s,Wt::WLocale::currentLocale().dateFormat()).toString()
      << std::endl
      ;

  }
#endif


} // endtemplate <typename T> void FormModel<C>::act( Wt::Dbo::FieldRef<T> ref )

/*
** process pointer values to other classes
**
*/
template <class C>
template <typename T> void FormModel<C>::actPtr( const Wt::Dbo::PtrRef<T> & ref )
{
  /*
  ** in read mode we store the pointer value
  **  in to the model
  **
  */
  if( m_isReadMode )
  {
#ifdef FM_DEBUG_ACTIVITY
    std::cout << __FILE__ << " " << __LINE__ << " read: "
      << "ref.type="   << ref.type()-> name()                          << " "
      << "ref.name="   << ref.name()                                   << " "
      << "id="         << ref.id()                                     << " "
      << "value.type=" << value( field( ref.name() ) ).type().name()   << " "
      << "value="      << Wt::asString( value( field( ref.name() ) ) ) << " "
      << std::endl
      ;
#endif
    setValue
    (
      field(ref.name()), ref.value()
//      boost::any(ref.value())
    );

#ifdef FM_DEBUG_ACTIVITY
    std::cout << __FILE__ << " " << __LINE__ << " read: "
      << "ref.type="   << ref.type()-> name()                          << " "
      << "ref.name="   << ref.name()                                   << " "
      << "id="         << ref.id()                                     << " "
      << "value.type=" << value( field( ref.name() ) ).type().name()   << " "
      << "value="      << Wt::asString( value( field( ref.name() ) ) ) << " "
      << std::endl
      ;
#endif

  }

  /*
  ** in write mode, we have to determine if the stored
  **  value is still in a pointer representation, or
  **  if it was converted to a text value (which can happen).
  **  If the original pointer was converted to a text
  **  value then we need to convert it to an integer and then
  **  use that integer to find the original item so that
  **  we can assign the item properly.
  **
  */
  else
  {
    Wt::Dbo::ptr<T> newPtr;

    if( value(field(ref.name())).type() == typeid(Wt::Dbo::ptr<T>) )
    {
      newPtr = Wt::cpp17::any_cast< Wt::Dbo::ptr<T> >
      (
        value
        (
          field
          (
            ref.name()
          )
        )
      );
    }

    if( value(field(ref.name())).type() == typeid(std::string) )
    {
      std::cout << __FILE__ << " " << __LINE__ << " converting from std::string " << std::endl;
    }

    /*
    ** BUGBUG: this function should be returning a value() type
    **  from the model that is a Dbo::ptr<> and not a string, but
    **  it will come back as a WString if the editor used to modify
    **  the field value is a WTextEdit.  If we split apart string
    **  we can extricate the id() value embedded in it, but this is
    **  risky at best, and should not be required at all.  But,
    **  it is important to use the correct editor for these field
    **  values.
    **
    */
    if( value(field(ref.name())).type() == typeid(Wt::WString) )
    {
      auto idv = Wt::asString( value( field( ref.name() ) ) ).toUTF8();

      if( idv != "[null]" )
      {
        auto v = Wtx::Core::split( idv, ':' );
        int idVal = std::stoi(v.at(1));

        if( idVal != -1 )
          newPtr = session()-> template load<T>(idVal);
      }
    }

#ifdef FM_DEBUG_ACTIVITY
    std::cout << __FILE__ << " " << __LINE__ << " write: "
      << "ref.name="       << ref.name()                                        << " "
      << "value.typename=" << value( field( ref.name() ) ).type().name()        << " "
      << "value.type="     << value( field( ref.name() ) ).type().hash_code()   << " "
      << "typeid<T>="      << typeid(Wt::Dbo::ptr<T>).hash_code()               << " "
      << "value="          << Wt::asString( value( field( ref.name() ) ) )      << " "
      << "newPtr="         << newPtr.id()
      << std::endl
      ;
#endif

    /*
    ** update the original pointer object with the
    **  new value.  if the id value is -1 then the
    **  ref.value() will be cleared to nothing, which
    **  is what's supposed to happen.
    **
    */
//        if( newPtr.id() != -1 )
    {
      ref.value() = newPtr;
    }

  } // endif( ..write mode.. )

} // endtemplate <typename T> void actPtr( const Wt::Dbo::PtrRef<T> & ptrRef )

/*
** process pointer values to other classes
**
*/
template <class C>
template <typename T> void FormModel<C>::actWeakPtr( const Wt::Dbo::WeakPtrRef<T> & ref )
{
#ifdef NEVER
  /*
  ** in read mode we store the pointer value
  **  in to the model
  **
  */
  if( m_isReadMode )
  {
#ifdef FM_DEBUG_ACTIVITY
    std::cout << __FILE__ << " " << __LINE__ << " read: "
      << "ref.type="   << ref.type()-> name()                          << " "
      << "ref.name="   << ref.name()                                   << " "
      << "id="         << ref.id()                                     << " "
      << "value.type=" << value( field( ref.name() ) ).type().name()   << " "
      << "value="      << Wt::asString( value( field( ref.name() ) ) ) << " "
      << std::endl
      ;
#endif
    setValue
    (
      field(ref.name()), ref.value()
//      boost::any(ref.value())
    );

#ifdef FM_DEBUG_ACTIVITY
    std::cout << __FILE__ << " " << __LINE__ << " read: "
      << "ref.type="   << ref.type()-> name()                          << " "
      << "ref.name="   << ref.name()                                   << " "
      << "id="         << ref.id()                                     << " "
      << "value.type=" << value( field( ref.name() ) ).type().name()   << " "
      << "value="      << Wt::asString( value( field( ref.name() ) ) ) << " "
      << std::endl
      ;
#endif

  }

  /*
  ** in write mode, we have to determine if the stored
  **  value is still in a pointer representation, or
  **  if it was converted to a text value (which can happen).
  **  If the original pointer was converted to a text
  **  value then we need to convert it to an integer and then
  **  use that integer to find the original item so that
  **  we can assign the item properly.
  **
  */
  else
  {
    Wt::Dbo::ptr<T> newPtr;

    if( value(field(ref.name())).type() == typeid(Wt::Dbo::ptr<T>) )
    {
      newPtr = Wt::cpp17::any_cast< Wt::Dbo::ptr<T> >
      (
        value
        (
          field
          (
            ref.name()
          )
        )
      );
    }

    if( value(field(ref.name())).type() == typeid(std::string) )
    {
      std::cout << __FILE__ << " " << __LINE__ << " converting from std::string " << std::endl;
    }

    /*
    ** BUGBUG: this function should be returning a value() type
    **  from the model that is a Dbo::ptr<> and not a string, but
    **  it will come back as a WString if the editor used to modify
    **  the field value is a WTextEdit.  If we split apart string
    **  we can extricate the id() value embedded in it, but this is
    **  risky at best, and should not be required at all.  But,
    **  it is important to use the correct editor for these field
    **  values.
    **
    */
    if( value(field(ref.name())).type() == typeid(Wt::WString) )
    {
      auto idv = Wt::asString( value( field( ref.name() ) ) ).toUTF8();

      if( idv != "[null]" )
      {
        int idVal = std::stoi( idv );

        if( idVal != -1 )
          newPtr = session()-> template load<T>(idVal);
      }
    }

#ifdef FM_DEBUG_ACTIVITY
    std::cout << __FILE__ << " " << __LINE__ << " write: "
      << "ref.name="       << ref.name()                                        << " "
      << "value.typename=" << value( field( ref.name() ) ).type().name()        << " "
      << "value.type="     << value( field( ref.name() ) ).type().hash_code()   << " "
      << "typeid<T>="      << typeid(Wt::Dbo::ptr<T>).hash_code()               << " "
      << "value="          << Wt::asString( value( field( ref.name() ) ) )      << " "
      << "newPtr="         << newPtr.id()
      << std::endl
      ;
#endif

    /*
    ** update the original pointer object with the
    **  new value.  if the id value is -1 then the
    **  ref.value() will be cleared to nothing, which
    **  is what's supposed to happen.
    **
    */
//        if( newPtr.id() != -1 )
    {
      ref.value() = newPtr;
    }

  } // endif( ..write mode.. )
#endif

} // endtemplate <typename T> void actPtr( const Wt::Dbo::PtrRef<T> & ptrRef )

template <class C>
template <typename T> void FormModel<C>::actCollection( const Wt::Dbo::CollectionRef<T> & ref )
{
  (void)ref;
#ifdef STILL_WORKING_ON_THIS
#ifndef DEBUG_ACTIVITY
  std::cout << __FILE__ << " " << __LINE__ << " "
    << ref.value().size()  << " "
    << ref.joinName()      << " "
    << ref.joinId()        << " "
    << ref.literalJoinId() << " "
    << (ref.type() == Wt::Dbo::RelationType::ManyToOne? std::string("mto"):std::string("mtm")) << " "
    << ref.fkConstraints() << " "
    << std::endl
    ;

  for( auto item : ref.value() )
    std::cout << __FILE__ << " " << __LINE__ << " "
      << item.id() << " "
      << std::endl
      ;
#endif

  if( isReadMode )
  {
    /*
    ** save all the ID numbers of all the items in this
    **  collection.
    **
    */
    std::cout << __FILE__ << ":" << __LINE__ << " " << ref.joinName() << std::endl;
//        Wt::Dbo::collection<Wt::Dbo::ptr<T>> ids; //  = new std::vector<int>();
    std::vector<int> ids;
    for( auto item : ref.value() )
    ids.push_back( item.id() );
//        m_collections[ref.joinName()] = ids;

    std::cout << __FILE__ << ":" << __LINE__ << " " << m_collections[ref.joinName()].size() << std::endl;

    setValue( field(ref.joinName()), boost::any(ids) );
  }
  else
  {
  }
#endif

} // endtemplate <typename T> void actCollection( const Wt::Dbo::CollectionRef<T> & ref )




