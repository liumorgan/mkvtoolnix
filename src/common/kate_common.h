/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   $Id: kate_common.h 3134 2005-10-23 18:21:13Z mosu $

   Kate helper functions

   Written by ogg.k.ogg.k <ogg.k.ogg.k@googlemail.com>.
   Adapted from code by Moritz Bunkus <moritz@bunkus.org>.
*/

#ifndef __KATE_COMMON_H
#define __KATE_COMMON_H

#include "os.h"

#include "error.h"

#define KATE_HEADERTYPE_IDENTIFICATION 0x80

struct MTX_DLL_API kate_identification_header_t {
  uint8_t headertype;
  char kate_string[7];

  uint8_t vmaj;
  uint8_t vmin;

  uint8_t nheaders;
  uint8_t tenc;
  uint8_t tdir;

  uint8_t kfgshift;

  int32_t gnum;
  int32_t gden;

  uint8_t language[16];
  uint8_t category[16];

  kate_identification_header_t();
};

void MTX_DLL_API kate_parse_identification_header(const unsigned char *buffer, int size, kate_identification_header_t &header) throw(error_c);

#endif // __KATE_COMMON_H