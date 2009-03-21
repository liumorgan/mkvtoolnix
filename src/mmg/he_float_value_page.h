/*
   mkvmerge GUI -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   header editor: unsigned integer value page class

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __HE_FLOAT_VALUE_PAGE_H
#define __HE_FLOAT_VALUE_PAGE_H

#include "os.h"

#include "he_value_page.h"

class he_float_value_page_c: public he_value_page_c {
public:
  wxTextCtrl *m_tc_text;
  double m_original_value;

public:
  he_float_value_page_c(wxTreebook *parent, he_page_base_c *toplevel_page, EbmlMaster *master, const EbmlCallbacks &callbacks, const wxString &title, const wxString &description);
  virtual ~he_float_value_page_c();

  virtual wxControl *create_input_control();
  virtual wxString get_original_value_as_string();
  virtual wxString get_current_value_as_string();
  virtual bool validate_value();
  virtual void reset_value();
  virtual void copy_value_to_element();
};

#endif // __HE_FLOAT_VALUE_PAGE_H