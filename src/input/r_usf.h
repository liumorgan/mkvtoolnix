/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   $Id$

   class definition for the USF subtitle reader

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __R_USF_H
#define __R_USF_H

#include "os.h"

#include <expat.h>
#include <setjmp.h>

#include <vector>

#include "mm_io.h"
#include "common.h"
#include "pr_generic.h"

struct usf_entry_t {
  int64_t m_start, m_end;
  string m_text;

  usf_entry_t():
    m_start(-1), m_end(-1) { }

  usf_entry_t(int64_t start, int64_t end, const string &text):
    m_start(start), m_end(end), m_text(text) { }

  bool operator <(const usf_entry_t &cmp) const {
    return m_start < cmp.m_start;
  }
};

struct usf_track_t {
  int m_ptzr;

  string m_language;
  vector<usf_entry_t> m_entries;
  vector<usf_entry_t>::const_iterator m_current_entry;

  usf_track_t():
    m_ptzr(-1) { }
};

class usf_reader_c: public generic_reader_c {
private:
  XML_Parser m_parser;
  int m_copy_depth;

  vector<usf_track_t> m_tracks;
  string m_private_data, m_default_language;
  int m_longest_track;

  vector<string> m_parents;
  string m_data_buffer, m_copy_buffer, m_previous_start;
  bool m_strip;

  jmp_buf m_parse_error_jmp;
  string m_parse_error;

public:
  usf_reader_c(track_info_c &_ti) throw (error_c);
  virtual ~usf_reader_c();

  virtual file_status_e read(generic_packetizer_c *ptzr, bool force = false);
  virtual void identify();
  virtual void create_packetizer(int64_t tid);
  virtual void create_packetizers();
  virtual int get_progress();

  static int probe_file(mm_text_io_c *io, int64_t size);

  virtual void start_cb(const char *name, const char **atts);
  virtual void end_cb(const char *name);
  virtual void add_data_cb(const XML_Char *s, int len);

private:
  virtual int64_t parse_timecode(const char *s);
};

#endif  // __R_USF_H