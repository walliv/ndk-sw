/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * libnfb public header file - extension module
 *
 * Copyright (C) 2018-2022 CESNET
 * Author(s):
 *   Martin Spinler <spinler@cesnet.cz>
 */

#ifndef LIBNFB_EXTENSION_H
#define LIBNFB_EXTENSION_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct nfb_device;
struct nfb_bus;
struct nfb_comp;

struct libnfb_ext_abi_version {
	uint32_t major;
	uint32_t minor;
};

#define libnfb_ext_abi_version_current { \
	.major = 1,\
	.minor = 0,\
}

typedef ssize_t nfb_bus_read_func(void *p, void *buf, size_t nbyte, off_t offset);
typedef ssize_t nfb_bus_write_func(void *p, const void *buf, size_t nbyte, off_t offset);

struct libnfb_bus_ext_ops {
	nfb_bus_read_func *read;
	nfb_bus_write_func *write;
};

struct libnfb_ext_ops {
	int (*open)(const char *devname, int oflag, void **priv, void **fdt);
	void (*close)(void *priv);
	int (*bus_open_mi)(void *dev_priv, int bus_node, int comp_node, void ** bus_priv, struct libnfb_bus_ext_ops* ops);
	void (*bus_close_mi)(void *bus_priv);
	int (*comp_lock)(const struct nfb_comp *comp, uint32_t features);
	void (*comp_unlock)(const struct nfb_comp *comp, uint32_t features);
};

typedef int libnfb_ext_get_ops_t(const char *devname, struct libnfb_ext_ops *ops);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* LIBNFB_EXTENSION_H */ 
