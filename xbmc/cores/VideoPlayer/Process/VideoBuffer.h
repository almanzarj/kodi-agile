/*
 *      Copyright (C) 2005-2016 Team XBMC
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

class CVideoBuffer
{
public:
  uint8_t (*GetPlanePointers())[MAX_PLANES];

protected:
  YuvImage m_image;
};
