#ifndef __OS_DIRENT_H__
#define __OS_DIRENT_H__

////////////////////////////////////////////////////////////////////////////////
// constant

namespace os
{
	namespace dir
	{
		const char DT_BLK     = 'B'; // block device.
		const char DT_CHR     = 'C'; // character device.
		const char DT_DIR     = 'D'; // directory.
		const char DT_FIFO    = 'F'; // named pipe(FIFO).
		const char DT_LNK     = 'L'; // symbolic link.
		const char DT_REG     = 'R'; // regular file.
		const char DT_SOCK    = 'S'; // UNIX domain socket.
		const char DT_UNKNOWN = '?'; // not be determined.
	}
}

////////////////////////////////////////////////////////////////////////////////
// interface

namespace os
{
	namespace dir
	{
		struct Info
		{
			const char* name;
			char  type;
			unsigned long long size;
		};

		struct Context;

		Context* open(const char*);
		int close(Context*);
		const Info* read(Context*);
		void rewind(Context*);
	}
}

#endif
