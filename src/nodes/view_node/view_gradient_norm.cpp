/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewGradientNorm::ViewGradientNorm(std::string id)
    : ViewNode(), hesiod::cnode::GradientNorm(id)
{
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
  this->set_view3d_elevation_port_id("output");
}

void ViewGradientNorm::serialize_save(cereal::JSONOutputArchive &)
{
}

void ViewGradientNorm::serialize_load(cereal::JSONInputArchive &)
{
}

} // namespace hesiod::vnode
