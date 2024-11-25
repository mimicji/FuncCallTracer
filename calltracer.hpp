#ifndef __CALLTRACER_HPP__
#define __CALLTRACER_HPP__

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <syscall.h>

#include "dr_api.h"
#include "drmgr.h"
#include "drreg.h"
#include "drutil.h"
#include "drx.h"
#include "dr_defines.h"
#include "drsyms.h"
#include "drwrap.h"
#ifndef WINDOWS 
// Currently DynamoRIO does not support call stack on Winodws
#include "drcallstack.h"
#endif

#define PROJECT_NAME "FuncCallTracer"

// Currently we don't support Windows
#define IF_WINDOWS(x)

#define BUFFER_SIZE_BYTES(buf) sizeof(buf)
#define BUFFER_SIZE_ELEMENTS(buf) (BUFFER_SIZE_BYTES(buf) / sizeof(buf[0]))
#define BUFFER_LAST_ELEMENT(buf) buf[BUFFER_SIZE_ELEMENTS(buf) - 1]
#define NULL_TERMINATE_BUFFER(buf) BUFFER_LAST_ELEMENT(buf) = 0

#ifndef LOG
#define LOG(...) {dr_printf("[%s] ", PROJECT_NAME);dr_printf(__VA_ARGS__); dr_printf("\n");}
#endif
#ifndef DIE
#define DIE() {dr_printf("[%s] ", PROJECT_NAME); dr_printf("Abort at %s:%d\n", __FILE__, __LINE__); exit(1);}
#endif

#define MAX_SYM_RESULT 256
#define MAX_FILE_PATH 256

typedef struct _tls_t
{
    file_t call_trace_file;
    int stack_depth;
} tls_t;


#endif // __CALLTRACER_HPP__