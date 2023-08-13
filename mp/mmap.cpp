#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHARED_OBJ_NAME "test_comm.obj"

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

int memmap_store() {
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

/**
 * Sample code for sharing memory between processes
 * Two processes will iteratively increase a counter which values stored in a shared memory
 * 
 */




// shared data struct
struct message
{
    int pid;
    int counter;
};

bool write_message(int pid, int value)
{
    int shmFd = shm_open(SHARED_OBJ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(shmFd, sizeof(message));
    message *msg_ptr = (message*)mmap(NULL, sizeof(message), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    
    printf("Process %d: Increase the counter.\n", pid);
    msg_ptr->pid = pid;
    msg_ptr->counter = value;

    munmap(msg_ptr, sizeof(message));

    // remember to close to not hit an error of
    // opening too many files
    close(shmFd);

    return true;
}

bool read_message(int curr_pid, int &curr_value)
{
    int shmFd = shm_open(SHARED_OBJ_NAME, O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(shmFd, sizeof(message));
    message *msg_ptr = (message*)mmap(NULL, sizeof(message), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);

    if (msg_ptr->pid == curr_pid)
    {
        printf("Process %d: No new msg available.\n", curr_pid);
        return false;
    }
    else
    {
        printf("Process %d: Receive %d from PID %d.\n", curr_pid, msg_ptr->counter, msg_ptr->pid);
        curr_value = msg_ptr->counter;
        munmap(msg_ptr, sizeof(message));
    }

    close(shmFd);

    return true;
}

int memmap_comm()
{
    printf("Init the initial value.\n");
    write_message(-1, 0);

    // create a child process by calling folk, 
    // it returns a non-zero pid for parent process and 0 for child process created
    pid_t pid = fork();

    //--- PARENT PROCESS
    if (pid != 0)
    {
        for (int i = 0; i < 5; i++)
        {
            int value;
            // only write message if reading sucessfully
            if (read_message(pid, value))
                write_message(pid, ++value);
            sleep(1);
        }
    }
    //--- CHILD PROCESS
    else
    {
        for (int j = 0; j < 5; j++)
        {
            int value;
            if (read_message(pid, value))
                write_message(pid, ++value);
            sleep(1);
        }
    }

    printf("=========== End of process %d\n", pid);
    return 0;
}

int main() {
    return memmap_comm();
}
