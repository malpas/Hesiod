/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/control_node.hpp"

namespace hesiod::cnode
{

Erosion::Erosion(std::string id) : gnode::Node(id)
{
  LOG_DEBUG("Erosion::Erosion()");
  this->add_port(gnode::Port("input", gnode::direction::in, dtype::dHeightMap));
  this->add_port(gnode::Port("bedrock",
                             gnode::direction::in,
                             dtype::dHeightMap,
                             gnode::optional::yes));
  this->add_port(gnode::Port("moisture map",
                             gnode::direction::in,
                             dtype::dHeightMap,
                             gnode::optional::yes));
  this->add_port(gnode::Port("mask",
                             gnode::direction::in,
                             dtype::dHeightMap,
                             gnode::optional::yes));

  this->add_port(
      gnode::Port("output", gnode::direction::out, dtype::dHeightMap));
  this->add_port(
      gnode::Port("erosion map", gnode::direction::out, dtype::dHeightMap));
  this->add_port(
      gnode::Port("deposition map", gnode::direction::out, dtype::dHeightMap));
  this->update_inner_bindings();

  this->erosion_map = hmap::HeightMap();
  this->deposition_map = hmap::HeightMap();
}

void Erosion::update_inner_bindings()
{
  LOG_DEBUG("inner bindings [%s]", this->id.c_str());
  this->set_p_data("output", (void *)&(this->value_out));
  this->set_p_data("deposition map", (void *)&(this->deposition_map));
  this->set_p_data("erosion map", (void *)&(this->erosion_map));
}

void Erosion::compute()
{
  LOG_DEBUG("computing node [%s]", this->id.c_str());
  hmap::HeightMap *p_input_hmap = static_cast<hmap::HeightMap *>(
      (void *)this->get_p_data("input"));
  hmap::HeightMap *p_input_bedrock = static_cast<hmap::HeightMap *>(
      (void *)this->get_p_data("bedrock"));
  hmap::HeightMap *p_input_moisture_map = static_cast<hmap::HeightMap *>(
      (void *)this->get_p_data("moisture map"));
  hmap::HeightMap *p_input_mask = static_cast<hmap::HeightMap *>(
      (void *)this->get_p_data("mask"));

  hmap::HeightMap *p_output_erosion_map = static_cast<hmap::HeightMap *>(
      (void *)this->get_p_data("erosion map"));
  hmap::HeightMap *p_output_deposition_map = static_cast<hmap::HeightMap *>(
      (void *)this->get_p_data("deposition map"));

  // work on a copy of the input
  this->value_out = *p_input_hmap;

  if (p_output_erosion_map)
    this->erosion_map.set_sto(p_input_hmap->shape,
                              p_input_hmap->tiling,
                              p_input_hmap->overlap);

  if (p_output_deposition_map)
    this->deposition_map.set_sto(p_input_hmap->shape,
                                 p_input_hmap->tiling,
                                 p_input_hmap->overlap);

  this->compute_erosion(this->value_out,
                        p_input_bedrock,
                        p_input_moisture_map,
                        p_input_mask,
                        p_output_erosion_map,
                        p_output_deposition_map);
}

} // namespace hesiod::cnode
