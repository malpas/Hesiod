/* Copyright (c) 2023 Otto Link. Distributed under the terms of the GNU General
 * Public License. The full license is in the file LICENSE, distributed with
 * this software. */
#include "macrologger.h"

#include "hesiod/control_node.hpp"

namespace hesiod::cnode
{

HydraulicVpipes::HydraulicVpipes(std::string id) : Erosion(id)
{
  this->node_type = "HydraulicVpipes";
  this->category = category_mapping.at(this->node_type);
}

void HydraulicVpipes::compute_erosion(hmap::HeightMap &h,
                                      hmap::HeightMap *p_bedrock,
                                      hmap::HeightMap *p_moisture_map,
                                      hmap::HeightMap *p_mask,
                                      hmap::HeightMap *p_erosion_map,
                                      hmap::HeightMap *p_deposition_map)
{
  LOG_DEBUG("computing erosion node [%s]", this->id.c_str());

  if (p_moisture_map)
    p_moisture_map->remap();
  
  hmap::transform(h,
                  p_bedrock,
                  p_moisture_map,
                  p_mask,
                  p_erosion_map,
                  p_deposition_map,
                  [this](hmap::Array &h_out,
                         hmap::Array *p_bedrock_array,
                         hmap::Array *p_moisture_map_array,
                         hmap::Array *p_mask_array,
                         hmap::Array *p_erosion_map_array,
                         hmap::Array *p_deposition_map_array)
                  {
                    hydraulic_vpipes(h_out,
                                     p_mask_array,
                                     this->iterations,
                                     p_bedrock_array,
                                     p_moisture_map_array,
                                     p_erosion_map_array,
                                     p_deposition_map_array,
                                     this->water_height,
                                     this->c_capacity,
                                     this->c_erosion,
                                     this->c_deposition,
                                     this->rain_rate,
                                     this->evap_rate);
                  });

  h.smooth_overlap_buffers();

  if (p_erosion_map)
    (*p_erosion_map).smooth_overlap_buffers();

  if (p_deposition_map)
    (*p_deposition_map).smooth_overlap_buffers();
}

} // namespace hesiod::cnode
