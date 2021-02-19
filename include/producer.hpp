/*
 * Copyright (c) 2017-2020, NVIDIA CORPORATION. All rights reserved.
 * Copyright (C) 2021 Michael de Gans. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef F3BA22E3_6D3F_48E7_81A6_F33CB155167B
#define F3BA22E3_6D3F_48E7_81A6_F33CB155167B

#include "stoppable_thread.hpp"

#include <Argus/Argus.h>

namespace nvcvcam {

class Producer : public thread::StoppableThread {
  uint _csi_id;
  uint _csi_mode;

  Argus::UniqueObj<Argus::CameraProvider> _provider;
  Argus::ICameraProvider* _iprovider;
  Argus::CameraDevice* _device;
  Argus::SensorMode* _mode;
  Argus::ISensorMode* _imode;
  Argus::UniqueObj<Argus::CaptureSession> _session;
  Argus::ICaptureSession* _isession;
  Argus::UniqueObj<Argus::OutputStreamSettings> _settings;
  Argus::IEGLOutputStreamSettings* _isettings;
  Argus::UniqueObj<Argus::OutputStream> _stream;
  Argus::IEGLOutputStream* _istream;
  Argus::UniqueObj<Argus::Request> _request;
  Argus::IRequest* _irequest;
  Argus::ISourceSettings* _isourcesettings;

 protected:
  virtual bool setup();
  virtual bool tick();
  virtual bool cleanup();

  virtual Argus::ICameraProperties* get_properties();

  bool set_mode(Argus::SensorMode* mode);
  bool set_mode(uint32_t csi_mode);

 public:
  Producer(uint csi_id = 0, uint csi_mode = 0)
      : _csi_id(csi_id), _csi_mode(csi_mode){};
  virtual ~Producer();

  // bool enqueue_request(uint64_t timeout_ns = -1);
  Argus::ISensorMode* get_imode();
  std::vector<Argus::SensorMode*> get_modes();
  bool get_resolution(Argus::Size2D<uint32_t>& out);
  Argus::OutputStream* get_output_stream();
};

}  // namespace nvcvcam

#endif /* F3BA22E3_6D3F_48E7_81A6_F33CB155167B */
