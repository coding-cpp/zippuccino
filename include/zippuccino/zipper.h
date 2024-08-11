#pragma once

#include <map>
#include <sstream>

#include <brewtils/os.h>
#include <logger/log.h>

#include <zippuccino/crc.h>
#include <zippuccino/fileinfo.h>

namespace zippuccino {

class Zipper {
private:
  uint32_t offset;
  uint16_t count;

  std::map<std::string, std::string> paths;
  std::map<std::string, std::string>::iterator iterator;
  std::vector<FileInfo> fileInfos;

public:
  Zipper();
  ~Zipper();

  void add(const std::string &path) noexcept(false);
  void zip();

  bool isFinished();

  std::string getHeader();
  std::string getCurrentFile();
  std::string getFooter();
};

} // namespace zippuccino