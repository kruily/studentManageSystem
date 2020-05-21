#include "function.h"
#include "global.h"
int main() {
    H = createClass();
    db = openDatabase(db);
    mainPage(db,H);
    free(H);
    sqlite3_close(db);
    return 0;
}
