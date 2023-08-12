/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/control_node.hpp"

namespace hesiod::cnode
{

GradientTalus::GradientTalus(std::string id) : Unary(id)
{
  this->category += "/Operator/Gradient";
  this->node_type = "GradientTalus";
  this->update_inner_bindings();
}

void GradientTalus::compute_in_out(hmap::HeightMap &talus,
                                   hmap::HeightMap *p_input)
{
  LOG_DEBUG("computing node [%s]", this->id.c_str());

  hmap::transform(talus,    // output
                  *p_input, // input
                  [](hmap::Array &z) { return hmap::gradient_talus(z); });
}

} // namespace hesiod::cnode
