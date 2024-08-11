#include <zippuccino/zipper.h>

int main(int argc, char **argv) {
  zippuccino::Zipper zipper;
  zipper.add("../example");
  zipper.add("../include");
  zipper.add("../lib");
  zipper.add("../src");
  zipper.add("../CMakeLists.txt");
  zipper.zip();

  std::ofstream zipFile("../zippuccino.zip", std::ios::binary);
  if (!zipFile.is_open()) {
    std::cerr << "Unable to open output file" << std::endl;
    return EXIT_FAILURE;
  }

  while (!zipper.isFinished()) {
    const std::string header = zipper.getHeader();
    zipFile.write(header.c_str(), header.size());

    std::string path = zipper.getCurrentFile();
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Unable to open file: " << path << std::endl;
      return EXIT_FAILURE;
    }

    std::copy(std::istreambuf_iterator<char>(file),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(zipFile));
    file.close();
  }

  const std::string footer = zipper.getFooter();
  zipFile.write(footer.c_str(), footer.size());
  zipFile.close();

  return EXIT_SUCCESS;
}