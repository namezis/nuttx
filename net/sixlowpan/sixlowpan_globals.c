/****************************************************************************
 * net/sixlowpan/sixlowpan_globals.c
 *
 *   Copyright (C) 2017 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include "sixlowpan/sixlowpan_internal.h"

#ifdef CONFIG_NET_6LOWPAN

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* A pointer to the optional, architecture-specific compressor */

FAR struct sixlowpan_nhcompressor_s *g_sixlowpan_compressor;

#ifdef CONFIG_NET_6LOWPAN_SNIFFER
/* A pointer to the optional, architecture-specific sniffer */

FAR struct sixlowpan_rime_sniffer_s *g_sixlowpan_sniffer;
#endif

/* The following data values are used to hold intermediate settings while
 * processing IEEE802.15.4 frames.  These globals are shared with incoming
 * and outgoing frame processing and possibly with mutliple IEEE802.15.4 MAC
 * devices.  The network lock provides exclusive use of these globals
 * during that processing
 */

/* A pointer to the rime buffer.
 *
 * We initialize it to the beginning of the rime buffer, then access
 * different fields by updating the offset ieee->g_rime_hdrlen.
 */

FAR uint8_t *g_rimeptr;

/* g_uncomp_hdrlen is the length of the headers before compression (if HC2
 * is used this includes the UDP header in addition to the IP header).
 */

uint8_t g_uncomp_hdrlen;

/* g_rime_hdrlen is the total length of (the processed) 6lowpan headers
 * (fragment headers, IPV6 or HC1, HC2, and HC1 and HC2 non compressed
 * fields).
 */

uint8_t g_rime_hdrlen;

/* Offset first available byte for the payload after header region. */

uint8_t g_dataoffset;

/* Packet buffer metadata: Attributes and addresses */

uint16_t g_pktattrs[PACKETBUF_NUM_ATTRS];
struct rimeaddr_s g_pktaddrs[PACKETBUF_NUM_ADDRS];

#endif /* CONFIG_NET_6LOWPAN */