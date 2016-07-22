#include <stdio.h>
#include <stdlib.h>
#include <netcdf.h>

#define FILE_NAME "test.nc"
#define NX 21
#define NY 21
#define NL 1
#define NT 24

#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}

int main()
{
    int ncid, varid;
    int data[NT][NL][NY][NX];

    int t, x, y, retval;

    if ((retval = nc_open(FILE_NAME, NC_NOWRITE, &ncid))) {
        ERR(retval);
    }

    if ((retval = nc_inq_varid(ncid, "data", &varid))) {
        ERR(retval);
    }

    if ((retval = nc_get_var_int(ncid, varid, &data[0][0][0][0]))) {
        ERR(retval);
    }

    for (t = 0; t < NT; t++) {
        for (x = 0; x < NX; x++) {
            for (y = 0; y < NY; y++) {
                if (!data[t][0][x][y] == t + x + y) {
                    return ERRCODE;
                }
            }
        }
    }

    if ((retval = nc_close(ncid))) {
        ERR(retval);
    }

    printf("*** [info] SUCCESS reading example file %s!\n", FILE_NAME);
    return 0;
}