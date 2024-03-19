// #include "zlib.h"
#include "minizip/unzip.h"
#include "minizip/zip.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define WRITEBUFFERSIZE (16384)

/**
 * @brief 压缩输入的文件列表，并可以选择在压缩包中去除路径前缀
 * 
 * @param outname 输出的压缩包文件名
 * @param filelist 要压缩的文件列表
 * @param prefix 压缩包中文件名去除前缀
 * @return int 
 */
int zipPath(std::string outname, std::vector<std::string> filelist, std::string prefix) {

    zipFile zf = zipOpen64(outname.c_str(), APPEND_STATUS_CREATE);
    if (zf == nullptr) {
        std::cout << "zip open error, " << outname << std::endl;
        return -1;
    }

    std::shared_ptr<char> readbuf = std::shared_ptr<char>(new char[WRITEBUFFERSIZE], [](void *ptr) {
        if (ptr) {
            delete[] (char *)ptr;
        }
    });
    if (readbuf == nullptr) {
        std::cout << "malloc readbuf error";
        zipClose(zf, nullptr);
        return -1;
    }

    int ret = 0;
    for (auto &filename : filelist) {
        auto nameInZip = filename;
        auto pos       = filename.find(prefix);
        if (pos == 0 && prefix.size() < filename.size()) {
            nameInZip.assign(filename.begin() + pos + prefix.size(), filename.end());
        }
        std::cout << "nameInZip: " << nameInZip << std::endl;
        ret = zipOpenNewFileInZip64(zf, nameInZip.c_str(), NULL, NULL, 0, NULL, 0, NULL, Z_DEFLATED,
                                    Z_BEST_SPEED, 1);
        if (ret != ZIP_OK) {
            std::cout << "Error adding " << filename << " to " << outname << std::endl;
            break;
        }

        FILE *f = fopen(filename.c_str(), "rb");
        if (f) {
            int len;
            while ((len = fread(readbuf.get(), 1, WRITEBUFFERSIZE, f)) > 0) {
                zipWriteInFileInZip(zf, readbuf.get(), len);
            }
            fclose(f);
        } else {
            std::cout << "fopen error, " << filename;
        }

        ret = zipCloseFileInZip(zf);
        if (ret != ZIP_OK) {
            break;
        }
    }

    zipClose(zf, NULL);
    return ret;
}

/**
 * @brief 解压zip压缩包，并输出文件名称列表
 * 
 * @param zipfile 压缩包名
 * @param outfile 解压出的文件名
 * @return int 
 */
int unzip_test(std::string zipfile, std::vector<std::string> &outfile) {
    unzFile uf = unzOpen2_64(zipfile.c_str(), NULL);
    if (uf == nullptr) {
        std::cerr << "Error opening " << zipfile << std::endl;
        return -1;
    }

    // 打开zip中的文件
    int ret = unzLocateFile(uf, "hello.txt", 0);
    if (ret != UNZ_OK) {
        std::cerr << "Error locating hello.txt in " << zipfile << std::endl;
        unzClose(uf);
        return -1;
    }

    // 打开文件
    ret = unzOpenCurrentFile(uf);
    if (ret != UNZ_OK) {
        std::cerr << "Error opening file" << std::endl;
        unzClose(uf);
        return -1;
    }

    std::shared_ptr<char> readbuf = std::shared_ptr<char>(new char[WRITEBUFFERSIZE], [](void *ptr) {
        if (ptr) {
            delete[] (char *)ptr;
        }
    });
    if (readbuf == nullptr) {
        std::cout << "malloc readbuf error";
        unzClose(uf);
        return -1;
    }

    // 读取文件
    int   len = 0;
    FILE *f   = fopen("hello_out.txt", "wb");
    while ((len = unzReadCurrentFile(uf, readbuf.get(), WRITEBUFFERSIZE)) > 0) {
        fwrite(readbuf.get(), len, 1, f);
    }
    fclose(f);

    // 关闭文件
    unzCloseCurrentFile(uf);
    unzClose(uf);

    return 0;

    // 获取zip中文件的信息
    // unz_file_info file_info;
    // char filename[512];
    // err = unzGetCurrentFileInfo(uf, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);
    // if(err != UNZ_OK)
    // {
    //     std::cerr << "Error getting file info for " << file << std::endl;
    //     unzClose(uf);
    //     return 1;
    // }
}

int main() {

    std::vector<std::string> filevec;
    unzip_test("test.zip", filevec);
    return 0;
}