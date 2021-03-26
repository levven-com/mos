/* This file is auto-generated by mos build, do not edit! */

#include <stdbool.h>
#include <stdio.h>

#include "common/cs_dbg.h"

#include "mgos_app.h"

extern bool mgos_core_init(void);
extern bool mgos_lib1_init(void);


#ifndef MGOS_LIB_INFO_VERSION
struct mgos_lib_info {
  const char *name;
  const char *version;
  const char *repo_version;
  const char *binary_libs;
  bool (*init)(void);
};
#define MGOS_LIB_INFO_VERSION 2
#endif

#ifndef MGOS_MODULE_INFO_VERSION
struct mgos_module_info {
  const char *name;
  const char *version;
};
#define MGOS_MODULE_INFO_VERSION 1
#endif

const struct mgos_lib_info mgos_libs_info[] = {

    // "core". deps: [ ]
#if MGOS_LIB_INFO_VERSION == 1
    {.name = "core", .version = NULL, .init = mgos_core_init},
#else
    {.name = "core", .version = NULL, .repo_version = NULL, .binary_libs = NULL, .init = mgos_core_init},
#endif

    // "lib1". deps: [ "core" ]
#if MGOS_LIB_INFO_VERSION == 1
    {.name = "lib1", .version = NULL, .init = mgos_lib1_init},
#else
    {.name = "lib1", .version = NULL, .repo_version = NULL, .binary_libs = NULL, .init = mgos_lib1_init},
#endif

    // Last entry.
    {.name = NULL},
};

const struct mgos_module_info mgos_modules_info[] = {

    {.name = "mongoose-os", .repo_version = NULL},

    // Last entry.
    {.name = NULL},
};

bool mgos_deps_init(void) {
  for (const struct mgos_lib_info *l = mgos_libs_info; l->name != NULL; l++) {
#if MGOS_LIB_INFO_VERSION == 1
    LOG(LL_DEBUG, ("Init %s %s...", l->name, (l->version ? l->version : "")));
#else
    LOG(LL_DEBUG, ("Init %s %s (%s)...",
          l->name,
          (l->version ? l->version : ""),
          (l->repo_version ? l->repo_version : "")));
#endif
    if (l->init != NULL && !l->init()) {
      LOG(LL_ERROR, ("%s init failed", l->name));
      return false;
    }
  }
  for (const struct mgos_module_info *m = mgos_modules_info; m->name != NULL; m++) {
    LOG(LL_DEBUG, ("Module %s %s", m->name, (m->repo_version ? m->repo_version : "")));
  }
  return true;
}
