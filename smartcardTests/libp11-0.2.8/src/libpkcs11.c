/* libp11, a simple layer on to of PKCS#11 API
 * Copyright (C) 2005 Olaf Kirch <okir@lst.de>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

/*
 * Convenience pkcs11 library that can be linked into an application,
 * and will bind to a specific pkcs11 module.
 *
 * Copyright (C) 2002  Olaf Kirch <okir@lst.de>
 */

//#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ltdl.h>
#include "libp11-int.h"

#define MAGIC			0xd00bed00

struct sc_pkcs11_module {
	unsigned int _magic;
	lt_dlhandle handle;
};
typedef struct sc_pkcs11_module sc_pkcs11_module_t;

/*
 * Load a module - this will load the shared object, call
 * C_Initialize, and get the list of function pointers
 */
void *
C_LoadModule(const char *mspec, CK_FUNCTION_LIST_PTR_PTR funcs)
{
	sc_pkcs11_module_t *mod;
	CK_RV (*c_get_function_list)(CK_FUNCTION_LIST_PTR_PTR);
	int rv;

	if (mspec == NULL)
		return NULL;

	if (lt_dlinit() != 0)
		return NULL;

	mod = (sc_pkcs11_module_t *) calloc(1, sizeof(*mod));
	mod->_magic = MAGIC;

	mod->handle = lt_dlopen(mspec);
	if (mod->handle == NULL)
		goto failed;

	/* Get the list of function pointers */
	c_get_function_list = (CK_RV (*)(CK_FUNCTION_LIST_PTR_PTR))
				lt_dlsym(mod->handle, "C_GetFunctionList");
	if (!c_get_function_list)
		goto failed;
	rv = c_get_function_list(funcs);
	if (rv == CKR_OK)
		return (void *) mod;

failed:
	C_UnloadModule((void *) mod);
	return NULL;
}

/*
 * Unload a pkcs11 module.
 * The calling application is responsible for cleaning up
 * and calling C_Finalize
 */
CK_RV
C_UnloadModule(void *module)
{
	sc_pkcs11_module_t *mod = (sc_pkcs11_module_t *) module;

	if (!mod || mod->_magic != MAGIC)
		return CKR_ARGUMENTS_BAD;

	if (lt_dlclose(mod->handle) < 0)
		return CKR_FUNCTION_FAILED;

	memset(mod, 0, sizeof(*mod));
	free(mod);

	lt_dlexit();

	return CKR_OK;
}
