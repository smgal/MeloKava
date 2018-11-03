
#if defined(_MSC_VER)
#pragma warning(disable: 4996)
#endif

////////////////////////////////////////////////////////////////////////////////
// uses

#include "os_dirent.h"

#if defined(_MSC_VER)

#include <io.h>
#include <cstring>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
// macro

#define CHECK_COND(cond) if (!(cond)) return NULL
#define SM_INVALID (-1)

////////////////////////////////////////////////////////////////////////////////
// internal type

struct os::dir::Context
{
	ptrdiff_t   h_find;
	char        path_name[256];
	_finddata_t find_data;
    Info        user_data;
};

////////////////////////////////////////////////////////////////////////////////
// implementation

os::dir::Context* os::dir::open(const char* file_name)
{
	std::unique_ptr<Context> dir(new Context);

	CHECK_COND(file_name != NULL && file_name[0] != '\0');

	const char* name_last = file_name + strlen(file_name) - 1;

	strcpy(dir->path_name, file_name);

	if (*name_last == '/' || *name_last == '\\')
		strcat(dir->path_name, "*");
	else
		strcat(dir->path_name, "/*");

	dir->h_find = _findfirst(dir->path_name, &dir->find_data);
	dir->h_find = (dir->h_find != -1) ? dir->h_find : SM_INVALID;

	CHECK_COND(dir->h_find != SM_INVALID);

	dir->user_data.name = NULL;

    return dir.release();
}

int os::dir::close(Context* dir_native)
{
	if (dir_native == NULL)
		return SM_INVALID;

	std::unique_ptr<Context> dir(dir_native);

	return (dir->h_find != SM_INVALID) ? _findclose(dir->h_find) : SM_INVALID;
}

const os::dir::Info* os::dir::read(Context* dir_native)
{
	CHECK_COND(dir_native && dir_native->h_find != SM_INVALID);

	CHECK_COND(!dir_native->user_data.name || _findnext(dir_native->h_find, &dir_native->find_data) != SM_INVALID);

	dir_native->user_data.name = dir_native->find_data.name;
	dir_native->user_data.size = dir_native->find_data.size;

	if (dir_native->find_data.attrib & _A_SYSTEM)
		dir_native->user_data.type = DT_BLK;
	else if (dir_native->find_data.attrib & _A_SUBDIR)
		dir_native->user_data.type = DT_DIR;
	else if (dir_native->find_data.attrib & _A_ARCH)
		dir_native->user_data.type = DT_REG;
	else
		dir_native->user_data.type = DT_UNKNOWN;

    return &dir_native->user_data;
}

void os::dir::rewind(Context* dir_native)
{
    if (dir_native && dir_native->h_find != SM_INVALID)
    {
        _findclose(dir_native->h_find);

		dir_native->h_find = _findfirst(dir_native->path_name, &dir_native->find_data);
		dir_native->user_data.name = NULL;

		dir_native->h_find = (dir_native->h_find != -1) ? dir_native->h_find : SM_INVALID;
	}
}

#else

struct os::dir::Context
{
	int dummy;
};

#define SM_INVALID (-1)

os::dir::Context* os::dir::open(const char* file_name)
{
	return nullptr;
}

int os::dir::close(Context* dir_native)
{
	return SM_INVALID;
}

const os::dir::Info* os::dir::read(Context* dir_native)
{
	return nullptr;
}

void os::dir::rewind(Context* dir_native)
{
}

#endif
