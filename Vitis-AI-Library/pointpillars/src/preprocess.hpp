/*
 * Copyright 2019 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "./types.hpp"

namespace vitis { namespace ai {

class PointPillarsPre
{
  public:
    PointPillarsPre( PFN_T* in_addr1, int in_scale1, int in_width1, int in_height1, int in_channel1,
                    PFN_QUANTIZED_T* out_addr1, float out_scale1, int out_width1, int out_height1, int out_channel1,
                    BACKBONE_T* in_addr2, int in_scale2, int in_width2, int in_height2, int in_channel2
    );
    ~PointPillarsPre();

    void process_net0(const V1F& points);
    void process_net1();
    void process_net1_cleanmem();
    void process_net1_thread( int start, int len);

   void extend_feature_vector();
   void extend_feature_vector_thread(int idx, int start, int len);

   inline bool judge_op_same(int canvas_index, int idx);
   void process_net0_thread(const V1F& points , int idx, int start, int len, int&);

    std::shared_ptr<preout_dict>   pre_dict_;

  private:

    std::array<int, 3> voxelmap_shape_;
    V1I coor_to_voxelidx;
    PFN_T *in_addr1_;
    int in_scale1_;
    int in_height1_;
    PFN_QUANTIZED_T *out_addr1_;
    float out_scale1_;
    BACKBONE_T *in_addr2_;
    int in_scale2_, in_width2_, in_height2_, in_channel2_;
    int cfg_max_number_of_points_per_voxel;
    V1F cfg_voxel_size;
    int cfg_max_number_of_voxels;
    bool bDirect;

    std::vector<std::thread> vth0;
    std::mutex mtx;
    int PRE_MT_NUM = 4;
    int canvas_index_arr[8];


    std::array<float, 3> scale_pclen;
    std::array<float, 3> scale_pcstartlen;
    std::array<float, 3> point_range;
};


}}


