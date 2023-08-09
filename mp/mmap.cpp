#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
using namespace std;

class MMRecord {
    public:
    int id;
    char name[4];

    MMRecord(): id(0), name("abc") {}
    MMRecord(int id_, char * name_) : id(id_) {
        for (int i = 0; i < 3; i++) {
            name[i] = name_[i];
        }
        name[3] = '\0';
    }
    friend ostream & operator<< (ostream & out, const MMRecord & r) {
        out << "record: " << r.id << " " << r.name << endl;
        return out;
    }
};

int main() {
    int fd;
    struct stat fileInfo;
    const char * filePath = "t_mmap_store.db";
    if ((fd = open(filePath, O_RDWR | O_CREAT, (mode_t)0664)) == -1) {
        cerr << "open failed";
        exit(1);
    }
    if (stat(filePath, &fileInfo) == -1) {
        cerr << "stat failed";
        exit(1);
    }

    if (fileInfo.st_size != 0) {
        cout << "file size " << fileInfo.st_size << endl;
        void * mapped = mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (mapped == MAP_FAILED) {
            cerr << "mmap failed";
            close(fd);
            exit(1);
        }
        MMRecord * records = static_cast<MMRecord *>(mapped);
        for (int i =0; i < 4; i++) {
            cout << records[i];
        }
        if (munmap(mapped, fileInfo.st_size) == -1) {
            close (fd);
            cerr << "error unmapping";
            exit(1);
        }
        close(fd);
        return 0;

    }
    size_t fileSize = sizeof(MMRecord) * 4;
    cout << "calculated file size " <<  fileSize << endl;
    if (ftruncate(fd, fileSize) == -1) {
        close(fd);
        cerr << "error resizing file" ;
        exit(1);
    }
    void * mapped = mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        cerr << "mmap failed";
        close(fd);
        exit(1);
    }
    MMRecord * records = static_cast<MMRecord *> (mapped);
    for (int i = 0; i < 4; i++) {
        records[i].id = i+13;
        records[i].name[0] = 's';
        records[i].name[1] = 'v';
        records[i].name[2] = 'a' + i;
        records[i].name[3] = '\0';
    }
    if (msync(mapped, fileSize, MS_SYNC) == -1)
        cerr << "sync failed";
    if (munmap(mapped, fileSize) == -1) {
        cerr << "unmap failed";
        close(fd);
        exit(1);
    }
    close(fd);
    return 0;
}

