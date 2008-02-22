/*
 * Automated Testing Framework (atf)
 *
 * Copyright (c) 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(ATF_C_TC_H)
#define ATF_C_TC_H

#include <atf-c/error.h>
#include <atf-c/map.h>
#include <atf-c/object.h>

struct atf_dynstr;
struct atf_tcr;

struct atf_tc;

typedef void (*atf_tc_head_t)(struct atf_tc *);
typedef void (*atf_tc_body_t)(const struct atf_tc *);
typedef void (*atf_tc_cleanup_t)(const struct atf_tc *);

/* ---------------------------------------------------------------------
 * The "atf_tc_pack" type.
 * --------------------------------------------------------------------- */

/* For static initialization only. */
struct atf_tc_pack {
    const char *m_ident;

    atf_tc_head_t m_head;
    atf_tc_body_t m_body;
    atf_tc_cleanup_t m_cleanup;
};
typedef const struct atf_tc_pack atf_tc_pack_t;

/* ---------------------------------------------------------------------
 * The "atf_tc" type.
 * --------------------------------------------------------------------- */

struct atf_tc {
    atf_object_t m_object;

    const char *m_ident;

    atf_map_t m_vars;

    atf_tc_head_t m_head;
    atf_tc_body_t m_body;
    atf_tc_cleanup_t m_cleanup;
};
typedef struct atf_tc atf_tc_t;

/* Constructors/destructors. */
atf_error_t atf_tc_init(atf_tc_t *, const char *, atf_tc_head_t,
                        atf_tc_body_t, atf_tc_cleanup_t);
atf_error_t atf_tc_init_pack(atf_tc_t *, atf_tc_pack_t *);
void atf_tc_fini(atf_tc_t *);

/* Getters. */
const char *atf_tc_get_ident(const atf_tc_t *);
const char *atf_tc_get_var(const atf_tc_t *, const char *);
bool atf_tc_has_var(const atf_tc_t *, const char *);

/* Modifiers. */
atf_error_t atf_tc_set_var(atf_tc_t *, const char *, const char *, ...);

/* ---------------------------------------------------------------------
 * Free functions.
 * --------------------------------------------------------------------- */

atf_error_t atf_tc_run(const atf_tc_t *, struct atf_tcr *);

/* To be run from test case bodies only. */
void atf_tc_fail(const char *, ...) __attribute__((noreturn));
void atf_tc_pass(void) __attribute__((noreturn));
void atf_tc_skip(const char *, ...) __attribute__((noreturn));

#endif /* ATF_C_TC_H */
