/*
   mkvmerge -- utility for splicing together matroska files
   from component media subtypes

   Distributed under the GPL
   see the file COPYING for details
   or visit http://www.gnu.org/copyleft/gpl.html

   Helper functions for unique random numbers

   Written by Moritz Bunkus <moritz@bunkus.org>.
*/

#include "common/os.h"

#include <cassert>
#include <vector>

#include "common/common.h"
#include "common/hacks.h"
#include "common/random.h"
#include "common/unique_numbers.h"

static std::vector<uint32_t> s_random_unique_numbers[4];

static void
assert_valid_category(unique_id_category_e category) {
  assert((UNIQUE_TRACK_IDS <= category) && (UNIQUE_ATTACHMENT_IDS >= category));
}

void
clear_list_of_unique_uint32(unique_id_category_e category) {
  assert((UNIQUE_ALL_IDS <= category) && (UNIQUE_ATTACHMENT_IDS >= category));

  if (UNIQUE_ALL_IDS == category) {
    int i;
    for (i = 0; 4 > i; ++i)
      clear_list_of_unique_uint32((unique_id_category_e)i);
  } else
    s_random_unique_numbers[category].clear();
}

bool
is_unique_uint32(uint32_t number,
                 unique_id_category_e category) {
  assert_valid_category(category);

  if (hack_engaged(ENGAGE_NO_VARIABLE_DATA))
    return true;

  int i;
  for (i = 0; s_random_unique_numbers[category].size() > i; ++i)
    if (s_random_unique_numbers[category][i] == number)
      return false;

  return true;
}

void
add_unique_uint32(uint32_t number,
                  unique_id_category_e category) {
  assert_valid_category(category);

  if (hack_engaged(ENGAGE_NO_VARIABLE_DATA))
    s_random_unique_numbers[category].push_back(s_random_unique_numbers[category].size() + 1);
  else
    s_random_unique_numbers[category].push_back(number);
}

bool
remove_unique_uint32(uint32_t number,
                     unique_id_category_e category) {
  assert_valid_category(category);

  if (hack_engaged(ENGAGE_NO_VARIABLE_DATA))
    return true;

  std::vector<uint32_t>::iterator dit;
  mxforeach(dit, s_random_unique_numbers[category])
    if (*dit == number) {
      s_random_unique_numbers[category].erase(dit);
      return true;
    }

  return false;
}

uint32_t
create_unique_uint32(unique_id_category_e category) {
  assert_valid_category(category);

  if (hack_engaged(ENGAGE_NO_VARIABLE_DATA)) {
    s_random_unique_numbers[category].push_back(s_random_unique_numbers[category].size() + 1);
    return s_random_unique_numbers[category].size();
  }

  uint32_t random_number;
  do {
    random_number = random_c::generate_32bits();
  } while ((random_number == 0) || !is_unique_uint32(random_number, category));
  add_unique_uint32(random_number, category);

  return random_number;
}
