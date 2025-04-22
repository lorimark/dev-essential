// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef CONTACT_H_
#define CONTACT_H_

#include <string>

/*! \brief An email contact.
 *
 * This widget is part of the %Wt composer example.
 */
struct Contact
{
  /*! \brief The contact name.
   */
  std::string name;

  /*! \brief The contact email address.
   */
  std::string email;

  /*! \brief Create a new contact.
   */
  Contact( const std::string name_, const std::string email_ )
    : name(name_),
      email(email_)
  { }

  Contact(const std::u32string email_);

  /*! \brief Get the typical single string form: "name" <email>
   */
  std::string formatted() const
  {
    if( name != "" )
    {
      return "\"" + name + "\" <" + email + ">";
    }
    else
    {
      return email;
    }

  }
};

#endif // CONTACT_H_

