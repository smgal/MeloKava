
#include "os_dirent.h"
#include "os_utils.h"

#include <string>
#include <vector>
#include <algorithm>

namespace
{
	const unsigned long long MIN_SIZE = 100000000; // Up to 100M

	struct FileInfo
	{
		unsigned long long size;
		std::string full_path;
	};
}

static void _searchAllFiles(std::vector<FileInfo>& out_list, const std::string& root_path, const std::string& local_path, int depth)
{
	os::dir::Context* context = nullptr;
	const os::dir::Info* entry = nullptr;

	if (!(context = os::dir::open((root_path + local_path).c_str())))
		return;

	while ((entry = os::dir::read(context)))
	{
		std::string file_name(entry->name);

		switch (entry->type)
		{
		case os::dir::DT_DIR:
		{
			if (file_name == "." || file_name == "..")
				continue;

			if (depth > 0)
				_searchAllFiles(out_list, root_path, local_path + ((local_path.empty()) ? "" : "/") + file_name, depth - 1);
		}
		break;
		case os::dir::DT_REG:
		{
			if (entry->size >= MIN_SIZE)
				out_list.push_back({ entry->size, local_path + "/" + file_name });
		}
		break;
		default:
			break;
		}
	}

	os::dir::close(context);
}

static void searchAllFiles(std::vector<FileInfo>& out_list, const std::string& root_path)
{
	_searchAllFiles(out_list, root_path, "", 100);
}

int main()
{
	std::vector<FileInfo> result;

	std::vector<std::string> root_paths =
	{
		"y:/",
		"x:/"
	};

	for (const auto& path : root_paths)
		searchAllFiles(result, path);

	std::sort(result.begin(), result.end(), [](const FileInfo& a, const FileInfo& b) -> bool
	{
		return (a.size < b.size);
	});

	if (result.size() > 1)
		for (unsigned int i = 0; i < result.size() - 1; i++)
			if (result[i].size == result[i + 1].size)
				os::log::i("[SAME SIZE]","\n%s\n%s\n", result[i].full_path.c_str(), result[i + 1].full_path.c_str());

    return 0;
}
