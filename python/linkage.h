/* XXXXXXXXXXXXXXXXX
 * ugly ugly ugly...
 */
#ifndef LINKAGE_H_ONCE
/* First inclusion (before Python.h) */
#ifdef EMBEDDED
#define Py_NO_ENABLE_SHARED 1
#ifdef PYDEGA_C
/* change this list if the symbols used by pydega changes */
#define PyArg_Parse (*pPyArg_Parse)
#define PyArg_ParseTuple (*pPyArg_ParseTuple)
#define PyArg_ParseTupleAndKeywords (*pPyArg_ParseTupleAndKeywords)
#define PyCallable_Check (*pPyCallable_Check)
#define PyErr_Print (*pPyErr_Print)
#define PyErr_SetFromErrno (*pPyErr_SetFromErrno)
#define PyErr_SetString (*pPyErr_SetString)
#define PyExc_IOError (*pPyExc_IOError)
#define PyExc_IndexError (*pPyExc_IndexError)
#define PyExc_TypeError (*pPyExc_TypeError)
#define PyModule_AddIntConstant (*pPyModule_AddIntConstant)
#define PyModule_AddObject (*pPyModule_AddObject)
#define PyObject_CallObject (*pPyObject_CallObject)
#define PySequence_Check (*pPySequence_Check)
#define PySequence_GetItem (*pPySequence_GetItem)
#define PySequence_Size (*pPySequence_Size)
#define PyString_FromString (*pPyString_FromString)
#define PyType_IsSubtype (*pPyType_IsSubtype)
#define PyType_Ready (*pPyType_Ready)
#define Py_BuildValue (*pPy_BuildValue)
#define Py_InitModule4 (*pPy_InitModule4)
#define _Py_NoneStruct (*p_Py_NoneStruct)
#define PyAPI_DATA(RTYPE) static RTYPE
#endif

#define Py_Initialize (*pPy_Initialize)
#define Py_Finalize (*pPy_Finalize)
#define PyEval_AcquireThread (*pPyEval_AcquireThread)
#define PyEval_InitThreads (*pPyEval_InitThreads)
#define PyEval_ReleaseThread (*pPyEval_ReleaseThread)
#define PyEval_RestoreThread (*pPyEval_RestoreThread)
#define PyEval_SaveThread (*pPyEval_SaveThread)
#define PyRun_SimpleFile (*pPyRun_SimpleFile)
#define PyRun_AnyFile (*pPyRun_AnyFile)
#define PySys_SetArgv (*pPySys_SetArgv)
#define PyThreadState_New (*pPyThreadState_New)
#define PyThreadState_Delete (*pPyThreadState_Delete)
#define PyCallable_Check (*pPyCallable_Check)
#define PyErr_Print (*pPyErr_Print)
#define PyEval_AcquireLock (*pPyEval_AcquireLock)
#define PyEval_ReleaseLock (*pPyEval_ReleaseLock)
#define PyObject_CallObject (*pPyObject_CallObject)
#define PyThreadState_Clear (*pPyThreadState_Clear)
#define PyThreadState_Get (*pPyThreadState_Get)
#define PyThread_acquire_lock (*pPyThread_acquire_lock)
#define PyThread_allocate_lock (*pPyThread_allocate_lock)
#define PyThread_free_lock (*pPyThread_free_lock)
#define PyThread_get_thread_ident (*pPyThread_get_thread_ident)
#define PyThread_release_lock (*pPyThread_release_lock)
#define Py_EndInterpreter (*pPy_EndInterpreter)
#define Py_NewInterpreter (*pPy_NewInterpreter)
#define _PyImport_FixupExtension (*p_PyImport_FixupExtension)
#ifndef PYDEGA_C
#define PyAPI_FUNC(RTYPE) extern RTYPE
#endif

#endif /* EMBEDDED */

#define LINKAGE_H_ONCE

#else /* LINKAGE_H_ONCE */
/* Second inclusion (after python.h) */

#ifdef EMBEDDED
#ifdef PYDEGA_C
#ifdef unix
#include <dlfcn.h>
#define LNK_INIT \
	void *handle = dlopen("libpython2.4.so", RTLD_LAZY|RTLD_GLOBAL); \
	if (!handle) return 0;

#define LNK_SYM(sym) \
	p##sym = dlsym(handle, #sym); \
	if (!p##sym) return 0;

#define LNK_FINI \
	return 1;
#endif /* unix */

#ifdef WIN32
#include <windows.h>
#define LNK_INIT \
	HMODULE handle = LoadLibrary("python24.dll"); \
	if (!handle) return 0;

#define LNK_SYM(sym) \
	p##sym = GetProcAddress(handle, #sym); \
	if (!p##sym) return 0;

#define LNK_FINI \
	return 1;
#endif /* WIN32 */

int initlinkage(void) {
	LNK_INIT
/* change this list if the symbols used by pydega changes */
	LNK_SYM(PyArg_Parse)
	LNK_SYM(PyArg_ParseTuple)
	LNK_SYM(PyArg_ParseTupleAndKeywords)
	LNK_SYM(PyCallable_Check)
	LNK_SYM(PyErr_Print)
	LNK_SYM(PyErr_SetFromErrno)
	LNK_SYM(PyErr_SetString)
	LNK_SYM(PyExc_IOError)
	LNK_SYM(PyExc_IndexError)
	LNK_SYM(PyExc_TypeError)
	LNK_SYM(PyModule_AddIntConstant)
	LNK_SYM(PyModule_AddObject)
	LNK_SYM(PyObject_CallObject)
	LNK_SYM(PySequence_Check)
	LNK_SYM(PySequence_GetItem)
	LNK_SYM(PySequence_Size)
	LNK_SYM(PyString_FromString)
	LNK_SYM(PyType_IsSubtype)
	LNK_SYM(PyType_Ready)
	LNK_SYM(Py_BuildValue)
	LNK_SYM(Py_InitModule4)
	LNK_SYM(_Py_NoneStruct)
	LNK_SYM(Py_Initialize)
	LNK_SYM(Py_Finalize)
	LNK_SYM(PyEval_AcquireThread)
	LNK_SYM(PyEval_InitThreads)
	LNK_SYM(PyEval_ReleaseThread)
	LNK_SYM(PyEval_RestoreThread)
	LNK_SYM(PyEval_SaveThread)
	LNK_SYM(PyRun_SimpleFile)
	LNK_SYM(PyRun_AnyFile)
	LNK_SYM(PySys_SetArgv)
	LNK_SYM(PyThreadState_New)
	LNK_SYM(PyThreadState_Delete)
	LNK_SYM(PyCallable_Check)
	LNK_SYM(PyErr_Print)
	LNK_SYM(PyEval_AcquireLock)
	LNK_SYM(PyEval_ReleaseLock)
	LNK_SYM(PyObject_CallObject)
	LNK_SYM(PyThreadState_Clear)
	LNK_SYM(PyThreadState_Get)
	LNK_SYM(PyThread_acquire_lock)
	LNK_SYM(PyThread_allocate_lock)
	LNK_SYM(PyThread_free_lock)
	LNK_SYM(PyThread_get_thread_ident)
	LNK_SYM(PyThread_release_lock)
	LNK_SYM(Py_EndInterpreter)
	LNK_SYM(Py_NewInterpreter)
	LNK_SYM(_PyImport_FixupExtension)
	LNK_FINI
}

#undef LNK_INIT
#undef LNK_SYM
#undef LNK_FINI

#else /* !PYDEGA_C */
#ifdef __cplusplus
extern "C" {
#endif
int initlinkage(void);
PyMODINIT_FUNC initpydega(void);
/*
void pydega_cbpostframe(PyThreadState *threadstate);
*/
extern int pydega_exiting;
#ifdef __cplusplus
}
#endif
#endif /* PYDEGA_C */

#else /* !EMBEDDED */
static int initlinkage(void) {
	return 1;
}
#endif /* EMBEDDED */

#endif /* LINKAGE_H_ONCE */
