/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * arcus-memcached - Arcus memory cache server
 * Copyright 2019 JaM2in Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CMDLOGMGR_H
#define CMDLOGMGR_H

typedef struct logsn {
    uint32_t filenum;  /* cmdlog file number : 1, 2, ... */
    uint32_t roffset;  /* cmdlog record offset */
} LogSN;

/* command log manager entry structure */
typedef struct _log_waiter {
    struct _log_waiter *wait_next;
    LogSN               lsn;
    int16_t             curr_eid;   /* curr entry id */
    int16_t             next_eid;   /* next entry id */
    int16_t             prev_eid;   /* prev entry id */
    bool                dual_write;
} log_waiter_t;

/* external command log manager functions */
log_waiter_t      *cmdlog_waiter_alloc(void);
void               cmdlog_waiter_free(log_waiter_t *logmgr);
log_waiter_t      *cmdlog_get_cur_waiter(void);
ENGINE_ERROR_CODE  cmdlog_waiter_init(struct default_engine *engine);
void               cmdlog_waiter_final(void);

ENGINE_ERROR_CODE  cmdlog_mgr_init(struct default_engine *engine);
void               cmdlog_mgr_final(void);


/* LogSN : SET_NULL */
#define LOGSN_SET_NULL(lsn) \
        do { (lsn)->filenum = 0; (lsn)->roffset = 0; } while(0)

#endif