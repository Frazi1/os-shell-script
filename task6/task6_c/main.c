#include <stdio.h>
#include <tcrdb.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main() {
    TCRDB *rdb;
    int ecode;
    char *value;

    rdb = tcrdbnew();

    if(!tcrdbopen(rdb, "localhost", 1978)) {
        ecode = tcrdbecode(rdb);
        fprintf(stdout, "open error: %s\n", tcrdberrmsg(ecode));
    }

    if(!tcrdbput2(rdb, "test2", "kets2")) {
        ecode = tcrdbecode(rdb);
        fprintf(stdout, "put error: %s'n", tcrdberrmsg(ecode));
    }

    value = tcrdbget2(rdb, "test2");
    if(value) {
        printf("%s\n", value);
    } else {
        ecode = tcrdbecode(rdb);
        fprintf(stdout, "get error: %s\n", tcrdberrmsg(ecode));
    }

    if(!tcrdbclose(rdb)) {
        ecode = tcrdbecode(rdb);
        fprintf(stdout, "close error: %s\n", tcrdberrmsg(ecode));
    }

    tcrdbdel(rdb);

    return 0;
}