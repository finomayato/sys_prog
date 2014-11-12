#include "mymutex.h"

struct MyMutex {
    int isLocked;
};

int lockMyMutex(struct MyMutex* m) {
    if (!m) return -1;
    while (m->isLocked);
    m->isLocked = 1;
    return 0;
}

int unlockMyMutex(struct MyMutex* m) {
    if (!m) return -1;
    m->isLocked = 0;
    return 0;
}
