/****************************************************************************
 * include/locale.h
 *
 *   Copyright (C) 2016 Gregory Nutt. All rights reserved.
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

#ifndef __INCLUDE_LOCALE_H
#define __INCLUDE_LOCALE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5
#define LC_MESSAGES 6

#define LC_COLLATE_MASK			(1 << 0)
#define LC_CTYPE_MASK			(1 << 1)
#define LC_MESSAGES_MASK		(1 << 2)
#define LC_MONETARY_MASK		(1 << 3)
#define LC_NUMERIC_MASK			(1 << 4)
#define LC_TIME_MASK			(1 << 5)
#define LC_ALL_MASK			(  LC_COLLATE_MASK \
					 | LC_CTYPE_MASK \
					 | LC_MESSAGES_MASK \
					 | LC_MONETARY_MASK \
					 | LC_NUMERIC_MASK \
					 | LC_TIME_MASK )

#define _LC_LAST_MASK			(1 << (6 - 1))

#define LC_GLOBAL_LOCALE		((locale_t)-1)

#ifdef MB_CUR_MAX
#undef MB_CUR_MAX
#define MB_CUR_MAX			(___mb_cur_max())
#ifndef MB_CUR_MAX_L
#define MB_CUR_MAX_L(x)			(___mb_cur_max_l(x))
#endif /* !MB_CUR_MAX_L */
#endif /* MB_CUR_MAX */

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/

struct lconv
{
  FAR char *decimal_point;
  FAR char *thousands_sep;
  FAR char *grouping;
  FAR char *int_curr_symbol;
  FAR char *currency_symbol;
  FAR char *mon_decimal_point;
  FAR char *mon_thousands_sep;
  FAR char *mon_grouping;
  FAR char *positive_sign;
  FAR char *negative_sign;
  FAR char int_frac_digits;
  FAR char frac_digits;
  FAR char p_cs_precedes;
  FAR char p_sep_by_space;
  FAR char n_cs_precedes;
  FAR char n_sep_by_space;
  FAR char p_sign_posn;
  FAR char n_sign_posn;
  FAR char int_n_cs_precedes;
  FAR char int_n_sep_by_space;
  FAR char int_n_sign_posn;
  FAR char int_p_cs_precedes;
  FAR char int_p_sep_by_space;
  FAR char int_p_sign_posn;
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

FAR char *setlocale(int category, FAR const char *locale);
FAR struct lconv *localeconv(void);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_LOCALE_H */
