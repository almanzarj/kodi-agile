/*
 *      Copyright (C) 2005-2017 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <atomic>
#include <deque>
#include <list>
#include <vector>

extern "C" {
#include "libavutil/pixfmt.h"
}

#define MAX_PLANES 3

struct YuvImage
{
  uint8_t* plane[MAX_PLANES];
  int planesize[MAX_PLANES];
  unsigned int stride[MAX_PLANES];
  unsigned int width;
  unsigned int height;
  unsigned int flags;

  unsigned int cshift_x; // this is the chroma shift used
  unsigned int cshift_y;
  unsigned int bpp; // bytes per pixel
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

#define BUFFER_STATE_DECODER 0x01;
#define BUFFER_STATE_RENDER  0x02;

class IVideoBufferCB
{
public:
  virtual void Return(int id) = 0;
  virtual void SetDecoderState(int id, bool state) = 0;
  virtual void SetRenderState(int id, bool state) = 0;
};

class CVideoBuffer
{
friend class CVideoBufferPool;
public:
  void Release();
  void SetDecoderState(bool state);
  void SetRenderState(bool state);

  virtual void Alloc();
  virtual void GetPlanes(uint8_t*(&planes)[MAX_PLANES]);
  virtual void GetStrides(int(&strides)[MAX_PLANES]);

protected:
  CVideoBuffer(IVideoBufferCB &pool, int id, AVPixelFormat format, int width, int height);
  int m_width = 0;
  int m_height = 0;
  AVPixelFormat m_pixFormat = AV_PIX_FMT_NONE;
  YuvImage m_image;
  int m_id;
  std::atomic_int m_state;
  IVideoBufferCB &m_pool;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

class CVideoBufferPool : public IVideoBufferCB
{
public:
  void CreateBuffer(int count);
  CVideoBuffer* Get();
  void Return(int id) override;

protected:
  int m_width = 0;
  int m_height = 0;
  AVPixelFormat m_pixFormat = AV_PIX_FMT_NONE;

  std::vector<CVideoBuffer*> m_all;
  std::deque<int> m_decoder;
  std::deque<int> m_render;
  std::deque<int> m_free;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

class CVideoBufferManager
{
public:

protected:
  std::list<CVideoBufferPool*> m_pools;
};
