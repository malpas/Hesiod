/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewSmoothFillSmearPeaks::ViewSmoothFillSmearPeaks(std::string id)
    : hesiod::cnode::ControlNode(id), ViewNode(id),
      hesiod::cnode::SmoothFillSmearPeaks(id)
{
  this->set_preview_port_id("output");
  this->set_view3d_elevation_port_id("output");
}

bool ViewSmoothFillSmearPeaks::render_settings()
{
  bool has_changed = false;
  has_changed |= this->render_settings_header();

  ImGui::SliderInt("ir", &this->ir, 1, 256);
  has_changed |= this->trigger_update_after_edit();

  has_changed |= this->render_settings_footer();
  return has_changed;
}

} // namespace hesiod::vnode
