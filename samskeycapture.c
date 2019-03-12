//
//  samskeycapture.c
//  PySamKeyCapture
//
//  Created by Sam Eriksson on 2018-12-19.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Python.h"
#include "controller.h"

static PyObject *SkcError;

static PyObject * skc_getset(PyObject *self, PyObject *args) {
    int sts;
    //if (!PyArg_ParseTuple(args, "s", &path))
        //return NULL;
    getSet();
    getSetSize();
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * skc_replay(PyObject *self, PyObject *args) {
    char *target;
    int sts;
    if (!PyArg_ParseTuple(args, "s", &target))
        return NULL;
    replay(target);
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * skc_record(PyObject *self, PyObject *args) {
    int sts;
    //if (!PyArg_ParseTuple(args, "sis", &path, &display, &filename))
        //return NULL;
    record();
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * skc_setpath(PyObject *self, PyObject *args) {
    int sts;
    char * path;
    if (!PyArg_ParseTuple(args, "s", &path))
        return NULL;
    setpath(path);
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * skc_save(PyObject *self, PyObject *args) {
    int sts;
    //if (!PyArg_ParseTuple(args, "s", &path))
        //return NULL;
    save();
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * skc_stop(PyObject *self, PyObject *args) {
    int sts;
    //if (!PyArg_ParseTuple(args, "s", &path))
    //return NULL;
    stop();
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * skc_deleteAndCreateFileIfNeeded(PyObject *self, PyObject *args) {
    int sts;
    char * path;
    if (!PyArg_ParseTuple(args, "s", &path))
        return NULL;
    deleteAndCreateFileIfNeeded(path);
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SkcError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyMethodDef SkcMethods[] = {
    {"getset",  skc_getset, METH_VARARGS,
        "Get captured keystroke data array: key (int),start time (float),end time (float)."},
    {"replay",  skc_replay, METH_VARARGS,
        "Replay keystroke data from file specified in path to specified target."},
    {"record",  skc_record, METH_VARARGS,
        "Record keystroke information to specied path."},
    {"setpath",  skc_setpath, METH_VARARGS,
        "Set path to file to save keystroke information."},
    {"save",  skc_save, METH_VARARGS,
        "Save keystroke information to path that is specified."},
    {"stop",  skc_stop, METH_VARARGS,
        "Stop recording keystrokes."},
    {"deletecreatefile",  skc_deleteAndCreateFileIfNeeded, METH_VARARGS,
        "Delete and create file."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef skcmodule = {
    PyModuleDef_HEAD_INIT,
    "skcmodule",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
               or -1 if the module keeps state in global variables. */
    SkcMethods
};

PyMODINIT_FUNC PyInit_skc(void) {
    PyObject *m;
    
    m = PyModule_Create(&skcmodule);
    if (m == NULL)
        return NULL;
    
    SkcError = PyErr_NewException("ssc.error", NULL, NULL);
    Py_INCREF(SkcError);
    PyModule_AddObject(m, "error", SkcError);
    return m;
}

int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    
    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("skc", PyInit_skc);
    
    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);
    
    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();
    
    /* Optionally import the module; alternatively,
     import can be deferred until the embedded script
     imports it. */
    PyImport_ImportModule("skc");
    
    
    PyMem_RawFree(program);
    return 0;
}
