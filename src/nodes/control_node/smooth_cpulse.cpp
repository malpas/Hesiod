/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/control_node.hpp"

namespace hesiod::cnode
{

SmoothCpulse::SmoothCpulse(std::string id) : Filter(id)
{
  this->node_type = "SmoothCpulse";
  this->category = category_mapping.at(this->node_type);
}

int SmoothCpulse::get_ir()
{
  return this->ir;
}

void SmoothCpulse::set_ir(float new_ir)
{
  if (new_ir != this->ir)
  {
    this->ir = new_ir;
    this->force_update();
  }
}

void SmoothCpulse::compute_filter(hmap::HeightMap &h, hmap::HeightMap *p_mask)
{
  LOG_DEBUG("computing filter node [%s]", this->id.c_str());
  hmap::transform(h,
                  p_mask,
                  [this](hmap::Array &x, hmap::Array *p_mask)
                  { hmap::smooth_cpulse(x, this->ir, p_mask); });
  h.smooth_overlap_buffers();
}

} // namespace hesiod::cnode