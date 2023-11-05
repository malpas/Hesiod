/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/gui.hpp"
#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewMinimumLocal::ViewMinimumLocal(std::string id)
    : ViewNode(), hesiod::cnode::MinimumLocal(id)
{
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
  this->set_view3d_elevation_port_id("output");
}

bool ViewMinimumLocal::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::SliderInt("ir", &this->ir, 1, 64);
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

void ViewMinimumLocal::serialize_save(cereal::JSONOutputArchive &ar)
{
  ar(cereal::make_nvp("ir", this->ir));
}

void ViewMinimumLocal::serialize_load(cereal::JSONInputArchive &ar)
{
  ar(cereal::make_nvp("ir", this->ir));
}

} // namespace hesiod::vnode
