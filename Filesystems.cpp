#include <iostream>

#include "PathPlayground.h"

#include "FileMarker.h"
#include "DirectoryDumper.h"

int main()
{
	//PathPlayground playground;
	//std::filesystem::path doc_path = playground.pathGeneration();

	//playground.introspectPath(doc_path);

	//playground.fileSystemManagement();

	//playground.introspectFileContent();

	//playground.iterateDirContent();

	/*
		FileMarker fileMarker("test\\test1.accdb");
		fileMarker.load_content();
	*/

	DirectoryDumper dumper("test", "test1\\dump.bin");
	dumper.dumpDirectory();
}