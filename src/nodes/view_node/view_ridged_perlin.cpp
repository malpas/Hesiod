/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "imgui.h"
#include "macrologger.h"

#include "hesiod/control_node.hpp"
#include "hesiod/gui.hpp"
#include "hesiod/view_node.hpp"

namespace hesiod::vnode
{

ViewRidgedPerlin::ViewRidgedPerlin(std::string     id,
                                   hmap::Vec2<int> shape,
                                   hmap::Vec2<int> tiling,
                                   float           overlap)
    : ViewNode(), hesiod::cnode::RidgedPerlin(id, shape, tiling, overlap)
{
  LOG_DEBUG("ViewRidgedPerlin::ViewRidgedPerlin()");
  this->set_p_control_node((gnode::Node *)this);
  this->set_preview_port_id("output");
}

bool ViewRidgedPerlin::render_settings()
{
  bool has_changed = false;

  has_changed |= this->render_settings_header();

  ImGui::AlignTextToFramePadding();
  if (ImGui::Button("Re-seed"))
  {
    this->seed = (int)time(NULL);
    this->force_update();
    has_changed = true;
  }

  ImGui::DragInt("seed", &this->seed);
  has_changed |= this->trigger_update_after_edit();

  if (hesiod::gui::drag_float_vec2(this->kw, this->link_kxy))
  {
    has_changed = true;
    this->force_update();
  }

  ImGui::InputInt("octaves", &this->octaves);
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("weight", &this->weight, 0.f, 1.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("persistence", &this->persistence, 0.01f, 1.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::SliderFloat("lacunarity", &this->lacunarity, 0.01f, 4.f, "%.2f");
  has_changed |= this->trigger_update_after_edit();

  ImGui::Separator();

  if (hesiod::gui::slider_vmin_vmax(vmin, vmax))
  {
    this->force_update();
    has_changed = true;
  }

  has_changed |= this->render_settings_footer();

  return has_changed;
}

} // namespace hesiod::vnode